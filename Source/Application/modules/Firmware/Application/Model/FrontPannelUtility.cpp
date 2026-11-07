#include "Firmware/Application/Model/FrontPannelUtility.h"


using namespace Ignite;
FrontPannelUtility::FrontPannelUtility (FrontPannelManager* FrontPanneMgr) : FrontPanneMgr (FrontPanneMgr)
{
	SetMcuLedMapping ();
}

bool FrontPannelUtility::SysMessageHandlerFromMCU (SysMessage Message)
{
	switch (Message.Header)
	{
		case SYS_SYTM_MSG:
			SystemMessageHandlerFromMCU (Message);
			break;
		case SYS_MIDI_MSG:
			MidiMessageHandlerFromMCU (Message);
			break;
		case SYS_KEY_MSG:
			KeyMessageHandlerFromMCU (Message);
			break;
		case SYS_LED_MSG:
			LedMessageHandlerFromMCU (Message);
			break;
		case SYS_KNOB_MSG:
			KeyMessageHandlerFromMCU(Message);//this handled as SYS_KEY_MSG
			//EncoderMessageHandlerFromMCU (Message);
			break;
		case SYS_SYNC_MSG:
			GateCvMessageHandlerFromMCU (Message);
			break;
		default:
			break;
	}
	return true;
}

bool FrontPannelUtility::SystemMessageHandlerFromMCU (SysMessage Message)
{
	switch (Message.Id)
	{
		case POWER_ON_COMPLETED:
		case POWER_OFF_REQ:
		case SYSTEM_RESET:
		case SW_UPGRADE_REQ:
			break;//Fall through 

		case HW_REMOVED:
			break;
		case HW_DETECTED:
			break;
	}
	return true;
}


bool FrontPannelUtility::MidiMessageHandlerFromMCU(SysMessage& Message)
{
	std::vector<uint8_t>* Tmp = nullptr;
	uint8_t* TmpMCUPortRxWaitNum = nullptr;
	uint8_t* TmpMidiMCUPortStatus = nullptr;
	uint8_t PortID = Message.Id;
	uint8_t IgniteMapPortID = 0;
	String portname;
	bool Proceed = true;

	auto initializePort = [&](std::vector<uint8_t>& data, uint8_t& rxWaitNum, uint8_t& status, const String& name, uint8_t mapPortID) {
		Tmp = &data;
		TmpMCUPortRxWaitNum = &rxWaitNum;
		TmpMidiMCUPortStatus = &status;
		portname = name;
		IgniteMapPortID = mapPortID;
		};

	switch (PortID) {
	case MIDI_MCU_PORT_1:
		initializePort(MidiMCUPortData1, MCUPortRxWaitNum1, MidiMCUPortStatus1, IGNITE_DIN_MIDI_PORT_1_NAME, midiDataIOPorts::dinMidi1);
		break;
	case MIDI_MCU_PORT_2:
		initializePort(MidiMCUPortData2, MCUPortRxWaitNum2, MidiMCUPortStatus2, IGNITE_DIN_MIDI_PORT_2_NAME, midiDataIOPorts::dinMidi2);
		break;
	case MIDI_MCU_PORT_3:
		initializePort(MidiMCUPortData3, MCUPortRxWaitNum3, MidiMCUPortStatus3, IGNITE_DIN_MIDI_PORT_3_NAME, midiDataIOPorts::dinMidi3);
		break;
	case MIDI_MCU_PORT_4:
		initializePort(MidiMCUPortData4, MCUPortRxWaitNum4, MidiMCUPortStatus4, IGNITE_DIN_MIDI_PORT_4_NAME, midiDataIOPorts::dinMidi4);
		break;
	case MIDI_MCU_PORT_5:
		initializePort(MidiMCUPortData5, MCUPortRxWaitNum5, MidiMCUPortStatus5, IGNITE_DIN_MIDI_PORT_5_NAME, midiDataIOPorts::dinMidi5);
		break;
	default:
		DBG(String(__FUNCTION__) + "::" + String(__LINE__) + "::" + "ERROR: invalidPortId");
		return false;
	}

	Tmp->insert(Tmp->end(), Message.Data, Message.Data + Message.size);

	for (int i = 0; (i < Message.size) && (Tmp->size() >= Message.size); i++) {
		switch (*TmpMidiMCUPortStatus) {
		case MIDI_HANDLE_STATE_SYSEX_IGNORE:
			handleSysExIgnore(*Tmp, *TmpMidiMCUPortStatus, IgniteMapPortID);
			break;
		case MIDI_HANDLE_STATE_IDLE:
			handleIdleState(*Tmp, *TmpMCUPortRxWaitNum, *TmpMidiMCUPortStatus, IgniteMapPortID, portname);
			break;
		case MIDI_HANDLE_STATE_RECIVE:
			handleReceiveState(*Tmp, *TmpMCUPortRxWaitNum, *TmpMidiMCUPortStatus, portname, Proceed);
			break;
		}
	}
	return Proceed;
}

void FrontPannelUtility::handleSysExIgnore(std::vector<uint8_t>& Tmp, uint8_t& TmpMidiMCUPortStatus, uint8_t IgniteMapPortID)
{
	switch (Tmp.front()) {
	case MIDI_SYSEX_MSG_ID_END:
		TmpMidiMCUPortStatus = MIDI_HANDLE_STATE_IDLE;//wait till end of sysex to change state
	default://Fall through
		Tmp.erase(Tmp.begin());
		break;
	}
}

void FrontPannelUtility::handleIdleState(std::vector<uint8_t>& Tmp, uint8_t& TmpMCUPortRxWaitNum, uint8_t& TmpMidiMCUPortStatus, uint8_t IgniteMapPortID, const String& portname)
{
	switch (Tmp.front() & 0xF0)
	{
	case MIDI_NOTE_OFF_MSG_ID:
	case MIDI_NOTE_ON_MSG_ID:
	case MIDI_AFTERTOUCH_MSG_ID:
	case MIDI_PITCH_BEND_MSG_ID:
	case MIDI_CC_MSG_ID:
		TmpMCUPortRxWaitNum = MIDI_PACKET_MSG_SIZE_TYPE_3;
		TmpMidiMCUPortStatus = MIDI_HANDLE_STATE_RECIVE;
		break;
	case MIDI_CONTROLL_MSG_ID:
	case MIDI_CHANNEL_PRESSURE_MSG_ID:
		TmpMCUPortRxWaitNum = MIDI_PACKET_MSG_SIZE_TYPE_2;
		TmpMidiMCUPortStatus = MIDI_HANDLE_STATE_RECIVE;
		break;

	case MIDI_SYM_COMMON_MSG://msg start with 0xF
	{
		switch (Tmp.front())
		{
		case MIDI_SYM_COMMON_MSG_TIMING_CLOCK:// Single byte msg :: MIDI_PACKET_MSG_SIZE_TYPE_1
		{
			Tmp.erase(Tmp.begin());
			auto clockPort = FrontPanneMgr->engine.settingsMidiClkCnfg->getParamSingle(SettingsMidiClkCnfgParam::clkInPort);
			auto configPort = clockPort.get<int8_t>();
			if (configPort == IgniteMapPortID)
				MidiClockDetect(IgniteMapPortID);
			TmpMidiMCUPortStatus = MIDI_HANDLE_STATE_IDLE;
		}
		break;
		case MIDI_SYM_COMMON_MSG_START_SEQUENCE:// Single byte msg :: MIDI_PACKET_MSG_SIZE_TYPE_1
		case MIDI_SYM_COMMON_MSG_CONTINUE_SEQUENCE:
		case MIDI_SYM_COMMON_MSG_STOP_SEQUENCE:
		case MIDI_SYM_COMMON_MSG_ACTIVE_SENSING:
		case MIDI_SYM_COMMON_MSG_SYSTEM_RESET:
			FrontPanneMgr->engine.songManager->handleIncomingMcuMidiMessage(portname, MidiMessage(Tmp[0]));
			Tmp.erase(Tmp.begin());
			break;
		case MIDI_SYSEX_MSG_ID_START:
			TmpMidiMCUPortStatus = MIDI_HANDLE_STATE_SYSEX_IGNORE;//SYSEX:: set and wait till end of sysex,remove all data
			break;
		}
	}
	default:
		if (Tmp.front() & 0xF0) {
			Tmp.erase(Tmp.begin());
		}
		else {
			DBG(String(__FUNCTION__) + "::" + String(__LINE__) + "::" + "ERROR: invalid midi msg");
			Tmp.clear();
		}
		return;
	}
}

void FrontPannelUtility::handleReceiveState(std::vector<uint8_t>& Tmp, uint8_t& TmpMCUPortRxWaitNum, uint8_t& TmpMidiMCUPortStatus, const String& portname, bool& Proceed)
{
	if (TmpMCUPortRxWaitNum == 0 || TmpMidiMCUPortStatus == 0 || Tmp.empty()) {
		DBG(String(__FUNCTION__) + "::" + String(__LINE__) + "::" + "invalid Data");
		Proceed = false;
		return;
	}

	if (Tmp.size() > 1) {
		uint8_t data = Tmp[1];
		uint8_t error = isValidMidiMsgToRecive(data);
		if (error == MIDI_MSG_SYSTEM) {
			Tmp.erase(Tmp.begin(), Tmp.begin() + 1);
			Proceed = false;
		}
		else if (error == MIDI_MSG_IGNORE) {
			Tmp.erase(Tmp.begin(), Tmp.begin() + 1);
			Proceed = false;
		}
		else if (error == MIDI_MSG_ERROR) {
			Tmp.clear();
			Tmp.push_back(data);
			TmpMidiMCUPortStatus = MIDI_HANDLE_STATE_IDLE;
			Proceed = false;
		}
	}

	if (Tmp.size() > 2 && TmpMCUPortRxWaitNum == MIDI_PACKET_MSG_SIZE_TYPE_3) {
		uint8_t data = Tmp[2];
		uint8_t error = isValidMidiMsgToRecive(data);
		if (error == MIDI_MSG_SYSTEM) {
			Tmp.erase(Tmp.begin(), Tmp.begin() + 2);
			Proceed = false;
		}
		else if (error == MIDI_MSG_IGNORE) {
			Tmp.erase(Tmp.begin(), Tmp.begin() + 2);
			Proceed = false;
		}
		else if (error == MIDI_MSG_ERROR) {
			if ((Tmp[0] & 0xF0) == MIDI_CC_MSG_ID && Tmp[1] == 0x7b) { // CC msg for all note off
				Tmp.erase(Tmp.begin(), Tmp.begin() + 2);
				Proceed = false;
			}
			else {
				Tmp.clear();
				TmpMidiMCUPortStatus = MIDI_HANDLE_STATE_IDLE;
				Proceed = false;
			}
		}
	}

	if (Proceed && Tmp.size() >= TmpMCUPortRxWaitNum) {
		if (TmpMCUPortRxWaitNum == MIDI_PACKET_MSG_SIZE_TYPE_3) {
			FrontPanneMgr->engine.songManager->handleIncomingMcuMidiMessage(portname, MidiMessage(Tmp[0], Tmp[1], Tmp[2]));
		}
		else if (TmpMCUPortRxWaitNum == MIDI_PACKET_MSG_SIZE_TYPE_2) {
			FrontPanneMgr->engine.songManager->handleIncomingMcuMidiMessage(portname, MidiMessage(Tmp[0], Tmp[1]));
		}
		Tmp.erase(Tmp.begin(), Tmp.begin() + TmpMCUPortRxWaitNum);
		TmpMidiMCUPortStatus = MIDI_HANDLE_STATE_IDLE;
	}
	//if ((*TmpMCUPortRxWaitNum) == MIDI_PACKET_MSG_SIZE_TYPE_1) should be handled earlier
}
uint8 FrontPannelUtility::isValidMidiMsgToRecive(uint8 data)
{
	if (data >= 0xF8)
	{
		return MIDI_MSG_SYSTEM;
	}
	else if (data >= 0xF1 && data <= 0xF7)
	{
		return MIDI_MSG_IGNORE;
	}
	else if ((data & 0x80) || data == 0xF0)
	{
		return MIDI_MSG_ERROR;
	}
	return MIDI_MSG_OK;
}

bool FrontPannelUtility::KeyMessageHandlerFromMCU (SysMessage Message)
{
	if ((paramId_t)Message.Id == ((paramId_t)FrontPannelParam::paramKey_ROTARY_NAV) && (Message.Data[0] == 1 || Message.Data[0] == 0) )
	{
		if(Message.Data[0] == 1) //TODO : need to change in MCU
			Message.Id = (paramId_t)FrontPannelParam::paramKey_RMOVELEFT;
		else if (Message.Data[0] == 0)
			Message.Id = (paramId_t)FrontPannelParam::paramKey_RMOVERIGHT;
		Message.Data[0] = 1;
	}

	if ((FrontPannelParam)Message.Id < FrontPannelParam::paramFrontPannelMax)
		FrontPanneMgr->engine.SendResponse ((moduleId_t)ModuleName::moduleFrontPannel, (moduleId_t)ModuleName::moduleUI, (paramId_t)Message.Id, Message.Data[0]);
	return true;
}
bool FrontPannelUtility::LedMessageHandlerFromMCU (SysMessage Message)
{
	return true;
}
bool FrontPannelUtility::EncoderMessageHandlerFromMCU (SysMessage Message)
{
	return true;
}
bool FrontPannelUtility::GateCvMessageHandlerFromMCU (SysMessage Message)
{
	return true;
}

void FrontPannelUtility::MidiClockDetect (uint8_t PortId)
{
	if (_MidiClockDetectLock)
		return;
	_MidiClockDetectLock = true;
	bool clearData = (MidiRxClkPortId != PortId); // We should recive from same port ID

	if (FrontPannelUtility::numberOfTaps > 1)
	{
		if ((int)std::chrono::duration_cast<std::chrono::milliseconds>
			((std::chrono::system_clock::now ()) - (MidiClkRecivedTime.back ())).count () > 5000)
		{
			clearData = true; //Took  Long time in between signal
		}
	}
	if (clearData)
	{
		numberOfTaps = 0;
		totalElapsedTime = 0;
		MidiRxClkPortId = PortId;
		MidiClkRecivedTime.clear ();
	}

	MidiClkRecivedTime.push_back (std::chrono::system_clock::now ());
	numberOfTaps++;

	if (numberOfTaps >= FrontPanneMgr->engine.get_settingsSongCnfg()->getSongTapTempo ())
	{
		totalElapsedTime = 0;
		for (auto ct = MidiClkRecivedTime.begin (); ct != MidiClkRecivedTime.end (); ++ct)
		{
			auto ctnext = ct + 1;
			if (ctnext != MidiClkRecivedTime.end ())
			{
				totalElapsedTime = totalElapsedTime + (int)std::chrono::duration_cast<std::chrono::milliseconds>(*ctnext - *ct).count ();
			}
		}

		if (totalElapsedTime > 0.0f)
		{
			float averageElapsedTime = totalElapsedTime / (MidiClkRecivedTime.size () - 1);
			if (averageElapsedTime > 0.0f)
			{
				float tempo = ((1000.0f / averageElapsedTime) * 60.0f);
				tempo = tempo < minTempo ? minTempo : tempo;
				tempo = tempo > maxTempo ? maxTempo : tempo;
				if (MCU_KEY_TEMP_KEY_ID == MidiRxClkPortId)
				{
					FrontPanneMgr->engine.SendResponse((moduleId_t)ModuleName::moduleFrontPannel, (moduleId_t)ModuleName::moduleUI, (paramId_t)FrontPannelParam::paramKey_TempoValue, (float)tempo);
					//FrontPanneMgr->engine.setParam((moduleId_t)ModuleName::moduleFrontPannel, (moduleId_t)ModuleName::moduleSong, (paramId_t)SongParam::paramSongTempo, (float)tempo, true);
				}
				else
					FrontPanneMgr->engine.setParam ((moduleId_t)ModuleName::moduleFrontPannel, (moduleId_t)ModuleName::moduleSong, (paramId_t)SongParam::paramSongTempo, (float)tempo, true);
			}
		}
#if 1 //defined TEMPO_CALCULATION_LAST_N_STEPS
		MidiClkRecivedTime.erase(MidiClkRecivedTime.begin());
		numberOfTaps--;
#else
		numberOfTaps = 0;
		totalElapsedTime = 0;
		MidiClkRecivedTime.clear ();
#endif
	}
	_MidiClockDetectLock = false;
}
void FrontPannelUtility::SetMcuLedMapping ()
{
	FrontPanneMgr->McuLedMapping[(uint8_t)FrontPannelParam::paramKey_MENU] = fpLED::EN_LED_MENU;
	FrontPanneMgr->McuLedMapping[(uint8_t)FrontPannelParam::paramKey_BRAY] = fpLED::EN_LED_BRAY;
	FrontPanneMgr->McuLedMapping[(uint8_t)FrontPannelParam::paramKey_ENTER_NAV] = fpLED::EN_LED_ENTER_NAV;
	FrontPanneMgr->McuLedMapping[(uint8_t)FrontPannelParam::paramKey_MINUS_NAV] = fpLED::EN_LED_MINUS_NAV;
	FrontPanneMgr->McuLedMapping[(uint8_t)FrontPannelParam::paramKey_PLUS_NAV] = fpLED::EN_LED_PLUS_NAV;
	FrontPanneMgr->McuLedMapping[(uint8_t)FrontPannelParam::paramKey_RETURN_NAV] = fpLED::EN_LED_RETURN_NAV;
	FrontPanneMgr->McuLedMapping[(uint8_t)FrontPannelParam::paramKey_COPY_NAV] = fpLED::EN_LED_COPY_NAV;
	FrontPanneMgr->McuLedMapping[(uint8_t)FrontPannelParam::paramKey_ROTARYROW] = fpLED::EN_LED_ROTARYROW;
	FrontPanneMgr->McuLedMapping[(uint8_t)FrontPannelParam::paramKey_TRACK] = fpLED::EN_LED_TRACK;
	FrontPanneMgr->McuLedMapping[(uint8_t)FrontPannelParam::paramKey_SCENE] = fpLED::EN_LED_SCENE;
	FrontPanneMgr->McuLedMapping[(uint8_t)FrontPannelParam::paramKey_USB_STOP] = fpLED::EN_LED_USB_STOP;
	FrontPanneMgr->McuLedMapping[(uint8_t)FrontPannelParam::paramKey_SAVE] = fpLED::EN_LED_SAVE;
	FrontPanneMgr->McuLedMapping[(uint8_t)FrontPannelParam::paramKey_SONG] = fpLED::EN_LED_SONG;
	FrontPanneMgr->McuLedMapping[(uint8_t)FrontPannelParam::paramKey_PATTERN] = fpLED::EN_LED_PATTERN;
	FrontPanneMgr->McuLedMapping[(uint8_t)FrontPannelParam::paramKey_TEMPO] = fpLED::EN_LED_TEMPO;
	FrontPanneMgr->McuLedMapping[(uint8_t)FrontPannelParam::paramKey_INTERNALSOUNDS] = fpLED::EN_LED_INTERNALSOUNDS;
	FrontPanneMgr->McuLedMapping[(uint8_t)FrontPannelParam::paramKey_LAST] = fpLED::EN_LED_LAST;
	FrontPanneMgr->McuLedMapping[(uint8_t)FrontPannelParam::paramKey_REC] = fpLED::EN_LED_REC;
	FrontPanneMgr->McuLedMapping[(uint8_t)FrontPannelParam::paramKey_STOP] = fpLED::EN_LED_STOP;
	FrontPanneMgr->McuLedMapping[(uint8_t)FrontPannelParam::paramKey_SCULPT] = fpLED::EN_LED_SCULPT;
	FrontPanneMgr->McuLedMapping[(uint8_t)FrontPannelParam::paramKey_INSERT] = fpLED::EN_LED_INSERT;
	FrontPanneMgr->McuLedMapping[(uint8_t)FrontPannelParam::paramKey_SHIFT] = fpLED::EN_LED_SHIFT;
	FrontPanneMgr->McuLedMapping[(uint8_t)FrontPannelParam::paramKey_BACKFORWARD] = fpLED::EN_LED_BACKFORWARD;
	FrontPanneMgr->McuLedMapping[(uint8_t)FrontPannelParam::paramKey_PLAY] = fpLED::EN_LED_PLAY;
	FrontPanneMgr->McuLedMapping[(uint8_t)FrontPannelParam::paramKey_DELETE] = fpLED::EN_LED_DELETE;
	FrontPanneMgr->McuLedMapping[(uint8_t)FrontPannelParam::paramKey_FILL_X] = fpLED::EN_LED_FILL_X;
	FrontPanneMgr->McuLedMapping[(uint8_t)FrontPannelParam::paramKey_NEXT_TIE] = fpLED::EN_LED_NEXT_TIE;
	FrontPanneMgr->McuLedMapping[(uint8_t)FrontPannelParam::paramKey_SOLO_SKIP] = fpLED::EN_LED_SOLO_SKIP;
	FrontPanneMgr->McuLedMapping[(uint8_t)FrontPannelParam::paramKey_GANG] = fpLED::EN_LED_GANG;
	FrontPanneMgr->McuLedMapping[(uint8_t)FrontPannelParam::paramKey_ROTARYBAR] = fpLED::EN_LED_ROTARYBAR;
	FrontPanneMgr->McuLedMapping[(uint8_t)FrontPannelParam::paramKey_TRACKSEL1] = fpLED::EN_LED_TRACKSEL1;
	FrontPanneMgr->McuLedMapping[(uint8_t)FrontPannelParam::paramKey_TRACKSEL2] = fpLED::EN_LED_TRACKSEL2;
	FrontPanneMgr->McuLedMapping[(uint8_t)FrontPannelParam::paramKey_TRACKSEL3] = fpLED::EN_LED_TRACKSEL3;
	FrontPanneMgr->McuLedMapping[(uint8_t)FrontPannelParam::paramKey_TRACKSEL4] = fpLED::EN_LED_TRACKSEL4;
	FrontPanneMgr->McuLedMapping[(uint8_t)FrontPannelParam::paramKey_TRACKSEL5] = fpLED::EN_LED_TRACKSEL5;
	FrontPanneMgr->McuLedMapping[(uint8_t)FrontPannelParam::paramKey_TRACKSEL6] = fpLED::EN_LED_TRACKSEL6;
	FrontPanneMgr->McuLedMapping[(uint8_t)FrontPannelParam::paramKey_TRACKSEL7] = fpLED::EN_LED_TRACKSEL7;
	FrontPanneMgr->McuLedMapping[(uint8_t)FrontPannelParam::paramKey_TRACKSEL8] = fpLED::EN_LED_TRACKSEL8;
	FrontPanneMgr->McuLedMapping[(uint8_t)FrontPannelParam::paramKey_TRACKSEL9] = fpLED::EN_LED_TRACKSEL9;
	FrontPanneMgr->McuLedMapping[(uint8_t)FrontPannelParam::paramKey_TRACKSEL10] = fpLED::EN_LED_TRACKSEL10;
	FrontPanneMgr->McuLedMapping[(uint8_t)FrontPannelParam::paramKey_TRACKSEL11] = fpLED::EN_LED_TRACKSEL11;
	FrontPanneMgr->McuLedMapping[(uint8_t)FrontPannelParam::paramKey_TRACKSEL12] = fpLED::EN_LED_TRACKSEL12;
	FrontPanneMgr->McuLedMapping[(uint8_t)FrontPannelParam::paramKey_TRACKSEL13] = fpLED::EN_LED_TRACKSEL13;
	FrontPanneMgr->McuLedMapping[(uint8_t)FrontPannelParam::paramKey_TRACKSEL14] = fpLED::EN_LED_TRACKSEL14;
	FrontPanneMgr->McuLedMapping[(uint8_t)FrontPannelParam::paramKey_TRACKSEL15] = fpLED::EN_LED_TRACKSEL15;
	FrontPanneMgr->McuLedMapping[(uint8_t)FrontPannelParam::paramKey_TRACKSEL16] = fpLED::EN_LED_TRACKSEL16;
	FrontPanneMgr->McuLedMapping[(uint8_t)FrontPannelParam::paramKey_TRACKROTARY1] = fpLED::EN_LED_TRACKROTARY1;
	FrontPanneMgr->McuLedMapping[(uint8_t)FrontPannelParam::paramKey_TRACKROTARY2] = fpLED::EN_LED_TRACKROTARY2;
	FrontPanneMgr->McuLedMapping[(uint8_t)FrontPannelParam::paramKey_TRACKROTARY3] = fpLED::EN_LED_TRACKROTARY3;
	FrontPanneMgr->McuLedMapping[(uint8_t)FrontPannelParam::paramKey_TRACKROTARY4] = fpLED::EN_LED_TRACKROTARY4;
	FrontPanneMgr->McuLedMapping[(uint8_t)FrontPannelParam::paramKey_TRACKROTARY5] = fpLED::EN_LED_TRACKROTARY5;
	FrontPanneMgr->McuLedMapping[(uint8_t)FrontPannelParam::paramKey_TRACKROTARY6] = fpLED::EN_LED_TRACKROTARY6;
	FrontPanneMgr->McuLedMapping[(uint8_t)FrontPannelParam::paramKey_TRACKROTARY7] = fpLED::EN_LED_TRACKROTARY7;
	FrontPanneMgr->McuLedMapping[(uint8_t)FrontPannelParam::paramKey_TRACKROTARY8] = fpLED::EN_LED_TRACKROTARY8;
	FrontPanneMgr->McuLedMapping[(uint8_t)FrontPannelParam::paramKey_TRACKROTARY9] = fpLED::EN_LED_TRACKROTARY9;
	FrontPanneMgr->McuLedMapping[(uint8_t)FrontPannelParam::paramKey_TRACKROTARY10] = fpLED::EN_LED_TRACKROTARY10;
	FrontPanneMgr->McuLedMapping[(uint8_t)FrontPannelParam::paramKey_TRACKROTARY11] = fpLED::EN_LED_TRACKROTARY11;
	FrontPanneMgr->McuLedMapping[(uint8_t)FrontPannelParam::paramKey_TRACKROTARY12] = fpLED::EN_LED_TRACKROTARY12;
	FrontPanneMgr->McuLedMapping[(uint8_t)FrontPannelParam::paramKey_TRACKROTARY13] = fpLED::EN_LED_TRACKROTARY13;
	FrontPanneMgr->McuLedMapping[(uint8_t)FrontPannelParam::paramKey_TRACKROTARY14] = fpLED::EN_LED_TRACKROTARY14;
	FrontPanneMgr->McuLedMapping[(uint8_t)FrontPannelParam::paramKey_TRACKROTARY15] = fpLED::EN_LED_TRACKROTARY15;
	FrontPanneMgr->McuLedMapping[(uint8_t)FrontPannelParam::paramKey_TRACKROTARY16] = fpLED::EN_LED_TRACKROTARY16;
	FrontPanneMgr->McuLedMapping[(uint8_t)FrontPannelParam::paramKey_RMOVELEFT] = fpLED::EN_LED_RMOVELEFT;
	FrontPanneMgr->McuLedMapping[(uint8_t)FrontPannelParam::paramKey_RMOVERIGHT] = fpLED::EN_LED_RMOVERIGHT;
	FrontPanneMgr->McuLedMapping[(uint8_t)FrontPannelParam::paramKey_RSELECT] = fpLED::EN_LED_RSELECT;
}

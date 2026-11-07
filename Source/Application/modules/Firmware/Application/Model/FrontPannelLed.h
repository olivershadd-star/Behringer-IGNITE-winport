#pragma once
#include <stdint.h>
#include "Firmware/Application/Model/ModelParams.h"
#include "Firmware/Application/Model/MCUInterfaceParams.h"

namespace Ignite
{
	class FrontPannelLed
	{
//#define DEBUG_PRINT_PARAM_NAME

#define LED_MAX_NUM 75

#define LED_SINGLE_COLOR_DSP_1_MAX 61
#define LED_SINGLE_COLOR_DSP_2_MAX 61

#define DISP_CHIP_ID_1 1 // i2c_2 Slave Address 1
#define DISP_CHIP_ID_2 2 // i2c_2 Slave Address 2
#define DISP_CHIP_ID_3 3 // SPI
#define LED_REG_BANKS_DISP_1 16
#define LED_REG_BANKS_DISP_2 16

		// Count is, Count of execute() call that required before changing value in Led Data; execute() will be called by pre difined TIMER
		// This means Value will be changed after (Count * TIMER)

#define LED_BLINK_COUNT_1  4
#define LED_BLINK_COUNT_2  8
#define LED_BLINK_COUNT_3  12
#define LED_BLINK_COUNT_4  16
#define LED_BLINK_COUNT_5  20
#define LED_BLINK_COUNT_6  24
#define LED_BLINK_COUNT_7  28
#define LED_BLINK_COUNT_8  32
#define LED_BLINK_COUNT_9  36
#define LED_BLINK_SLOW_COUNT 8
#define LED_BLINK_FAST_COUNT 2

#define LED_POWER_ON			0x0F
#define LED_POWER_OFF			0x00	

		struct fpledData // check init function before add any Variable, add at end if required
		{
			uint8_t Com;
			uint8_t Row;
			bool  	incCom;     // if count more than 0; increment Col or Row
			uint8_t	dspId;      // Display chip connected with
			uint8_t value; 		// current state used bit wise to controll group LEDs
			uint8_t count; 		// Number of LEDs associated with
			uint8_t pattern;	// Current pattern
			uint8_t tCount;     // Time count = time depends on execute() delay set, (i.e time to stay on the current state)
			uint8_t ledParamKeyId = 0;
		}_fpled;

		struct ledsRgb
		{
			uint8_t color[16];
			uint8_t pattern[16];
			uint32_t tCount[16];
		}fpledsRgb;

	public:
		explicit FrontPannelLed(FrontPannelManager* FrontPanneMgr);
		FrontPannelLed(const FrontPannelLed&);
		FrontPannelLed& operator= (const FrontPannelLed&) = default;
		~FrontPannelLed() = default;

		bool Init();
		bool HandleLedMessageFromUI(uint8_t ledParamId, uint8_t LedPattern, uint8_t LedColor);

		CThread FrontPannelLedExecuteThread;
		ThreadFunction FrontPannelLedExecuteThreadFunctionCB;
		void FrontPannelLedExecuteThreadFunction(void);

		bool execute();
		bool startLedExecuteThread();
		bool isLedThreadStarted = false;
		FrontPannelManager* FrontPanneMgr;

		//--> Shared Mapping data
		const uint8_t KetToLedPositionMapping[61] = {
			(paramId_t)FrontPannelParam::paramKey_USB_STOP, (paramId_t)FrontPannelParam::paramKey_MENU, (paramId_t)FrontPannelParam::paramKey_BRAY, (paramId_t)FrontPannelParam::paramKey_RETURN_NAV, (paramId_t)FrontPannelParam::paramKey_COPY_NAV, (paramId_t)FrontPannelParam::paramKey_MINUS_NAV, (paramId_t)FrontPannelParam::paramKey_PLUS_NAV, 	/* End of Line */
			(paramId_t)FrontPannelParam::paramKey_ROTARYROW, (paramId_t)FrontPannelParam::paramKey_SAVE, (paramId_t)FrontPannelParam::paramKey_LAST, (paramId_t)FrontPannelParam::paramKey_SHIFT, (paramId_t)FrontPannelParam::paramKey_REC, (paramId_t)FrontPannelParam::paramKey_BACKFORWARD, (paramId_t)FrontPannelParam::paramKey_STOP, (paramId_t)FrontPannelParam::paramKey_PLAY, (paramId_t)FrontPannelParam::paramKey_SCULPT, (paramId_t)FrontPannelParam::paramKey_DELETE, (paramId_t)FrontPannelParam::paramKey_INSERT, (paramId_t)FrontPannelParam::paramKey_ROTARYBAR,/* End of Line */
			(paramId_t)FrontPannelParam::paramKey_SONG, (paramId_t)FrontPannelParam::paramKey_SCENE, (paramId_t)FrontPannelParam::paramKey_TRACK, (paramId_t)FrontPannelParam::paramKey_NEXT_TIE, (paramId_t)FrontPannelParam::paramKey_FILL_X, (paramId_t)FrontPannelParam::paramKey_SOLO_SKIP, (paramId_t)FrontPannelParam::paramKey_GANG, (paramId_t)FrontPannelParam::paramKey_PATTERN, (paramId_t)FrontPannelParam::paramKey_TEMPO, (paramId_t)FrontPannelParam::paramKey_INTERNALSOUNDS,/* End of Line */
			(paramId_t)FrontPannelParam::paramKey_TRACKROTARY1, (paramId_t)FrontPannelParam::paramKey_TRACKROTARY2, (paramId_t)FrontPannelParam::paramKey_TRACKROTARY3, (paramId_t)FrontPannelParam::paramKey_TRACKROTARY4, (paramId_t)FrontPannelParam::paramKey_TRACKROTARY5, (paramId_t)FrontPannelParam::paramKey_TRACKROTARY6, (paramId_t)FrontPannelParam::paramKey_TRACKROTARY7, (paramId_t)FrontPannelParam::paramKey_TRACKROTARY8, (paramId_t)FrontPannelParam::paramKey_TRACKROTARY9, (paramId_t)FrontPannelParam::paramKey_TRACKROTARY10, (paramId_t)FrontPannelParam::paramKey_TRACKROTARY11, (paramId_t)FrontPannelParam::paramKey_TRACKROTARY12, (paramId_t)FrontPannelParam::paramKey_TRACKROTARY13, (paramId_t)FrontPannelParam::paramKey_TRACKROTARY14, (paramId_t)FrontPannelParam::paramKey_TRACKROTARY15, (paramId_t)FrontPannelParam::paramKey_TRACKROTARY16,/* End of Line */
			(paramId_t)FrontPannelParam::paramKey_TRACKSEL1, (paramId_t)FrontPannelParam::paramKey_TRACKSEL2, (paramId_t)FrontPannelParam::paramKey_TRACKSEL3, (paramId_t)FrontPannelParam::paramKey_TRACKSEL4, (paramId_t)FrontPannelParam::paramKey_TRACKSEL5, (paramId_t)FrontPannelParam::paramKey_TRACKSEL6, (paramId_t)FrontPannelParam::paramKey_TRACKSEL7, (paramId_t)FrontPannelParam::paramKey_TRACKSEL8, (paramId_t)FrontPannelParam::paramKey_TRACKSEL9, (paramId_t)FrontPannelParam::paramKey_TRACKSEL10, (paramId_t)FrontPannelParam::paramKey_TRACKSEL11, (paramId_t)FrontPannelParam::paramKey_TRACKSEL12, (paramId_t)FrontPannelParam::paramKey_TRACKSEL13, (paramId_t)FrontPannelParam::paramKey_TRACKSEL14, (paramId_t)FrontPannelParam::paramKey_TRACKSEL15, (paramId_t)FrontPannelParam::paramKey_TRACKSEL16,/* End of Line */
		};
	private:

		fpledData LedData[LED_MAX_NUM];    // Info as the way the Led connected to the chip (Row and Colum)
		bool  executeDone = false; // Lock to avoid Led Pattern update before execute
		uint8_t DataToDsp1[LED_REG_BANKS_DISP_1] = { 0, };   // save last sent data
		uint8_t DataToDsp2[LED_REG_BANKS_DISP_2] = { 0, };
		bool PatternValueUpdate();
		bool PatternMapping(uint8_t* InPatternArray, uint8_t size);
		bool PatternGenericHandler(uint8_t PatternVal);

#if defined DEBUG_PRINT_PARAM_NAME
		String  tmpParam[200]; //Todo - remove only for testing
#endif

		//  *** LedPosition has data as the way it shown in Front pannel
		uint8_t LedPosition_Dsp1[LED_SINGLE_COLOR_DSP_1_MAX] = {
				EN_LED_USB_STOP, EN_LED_MENU, EN_LED_BRAY, EN_LED_RETURN_NAV, EN_LED_COPY_NAV, EN_LED_MINUS_NAV, EN_LED_PLUS_NAV, 	/* End of Line */
				EN_LED_ROTARYROW, EN_LED_SAVE, EN_LED_LAST, EN_LED_SHIFT, EN_LED_REC, EN_LED_BACKFORWARD, EN_LED_STOP, EN_LED_PLAY, EN_LED_SCULPT, EN_LED_DELETE, EN_LED_INSERT, EN_LED_ROTARYBAR,/* End of Line */
				EN_LED_SONG, EN_LED_SCENE, EN_LED_TRACK, EN_LED_NEXT_TIE, EN_LED_FILL_X, EN_LED_SOLO_SKIP, EN_LED_GANG, EN_LED_PATTERN, EN_LED_TEMPO, EN_LED_INTERNALSOUNDS,/* End of Line */
				EN_LED_TRACKROTARY1, EN_LED_TRACKROTARY2, EN_LED_TRACKROTARY3, EN_LED_TRACKROTARY4, EN_LED_TRACKROTARY5, EN_LED_TRACKROTARY6, EN_LED_TRACKROTARY7, EN_LED_TRACKROTARY8, EN_LED_TRACKROTARY9, EN_LED_TRACKROTARY10, EN_LED_TRACKROTARY11, EN_LED_TRACKROTARY12, EN_LED_TRACKROTARY13, EN_LED_TRACKROTARY14, EN_LED_TRACKROTARY15, EN_LED_TRACKROTARY16,/* End of Line */
				EN_LED_TRACKSEL1, EN_LED_TRACKSEL2, EN_LED_TRACKSEL3, EN_LED_TRACKSEL4, EN_LED_TRACKSEL5, EN_LED_TRACKSEL6, EN_LED_TRACKSEL7, EN_LED_TRACKSEL8, EN_LED_TRACKSEL9, EN_LED_TRACKSEL10, EN_LED_TRACKSEL11, EN_LED_TRACKSEL12, EN_LED_TRACKSEL13, EN_LED_TRACKSEL14, EN_LED_TRACKSEL15, EN_LED_TRACKSEL16,/* End of Line */
		};
		uint8_t LedPosition_Dsp2[LED_SINGLE_COLOR_DSP_1_MAX] = {
				EN_LED_ROTARY_RELEASE, EN_LED_ROTARY_FILTER, EN_LED_ROTARY_RESONANCE, EN_LED_ROTARY_VOLUME,
				EN_LED_ROTARY_REVERB_AMT, EN_LED_ROTARY_CHORUS_AMT, EN_LED_ROTARY_EQ_HIGH, EN_LED_ROTARY_EQ_LOW
		};

		// Pre define pattern
		uint8_t	LedTestAllPowerOn[LED_SINGLE_COLOR_DSP_1_MAX] = {
				EN_LED_PATT_ON, EN_LED_PATT_ON, EN_LED_PATT_ON, EN_LED_PATT_ON, EN_LED_PATT_ON, EN_LED_PATT_ON, EN_LED_PATT_ON,
				EN_LED_PATT_ON, EN_LED_PATT_ON, EN_LED_PATT_ON, EN_LED_PATT_ON, EN_LED_PATT_ON, EN_LED_PATT_ON, EN_LED_PATT_ON, EN_LED_PATT_ON, EN_LED_PATT_ON, EN_LED_PATT_ON, EN_LED_PATT_ON, EN_LED_PATT_ON,
				EN_LED_PATT_ON, EN_LED_PATT_ON, EN_LED_PATT_ON, EN_LED_PATT_ON, EN_LED_PATT_ON, EN_LED_PATT_ON, EN_LED_PATT_ON, EN_LED_PATT_ON, EN_LED_PATT_ON, EN_LED_PATT_ON,
				EN_LED_PATT_ON, EN_LED_PATT_ON, EN_LED_PATT_ON, EN_LED_PATT_ON, EN_LED_PATT_ON, EN_LED_PATT_ON, EN_LED_PATT_ON, EN_LED_PATT_ON, EN_LED_PATT_ON, EN_LED_PATT_ON, EN_LED_PATT_ON, EN_LED_PATT_ON, EN_LED_PATT_ON, EN_LED_PATT_ON, EN_LED_PATT_ON, EN_LED_PATT_ON,
				EN_LED_PATT_ON, EN_LED_PATT_ON, EN_LED_PATT_ON, EN_LED_PATT_ON, EN_LED_PATT_ON, EN_LED_PATT_ON, EN_LED_PATT_ON, EN_LED_PATT_ON, EN_LED_PATT_ON, EN_LED_PATT_ON, EN_LED_PATT_ON, EN_LED_PATT_ON, EN_LED_PATT_ON, EN_LED_PATT_ON, EN_LED_PATT_ON, EN_LED_PATT_ON,
		};
		uint8_t LedAllPowerOFF[LED_SINGLE_COLOR_DSP_1_MAX] = {
				EN_LED_PATT_OFF, EN_LED_PATT_OFF, EN_LED_PATT_OFF, EN_LED_PATT_OFF, EN_LED_PATT_OFF, EN_LED_PATT_OFF, EN_LED_PATT_OFF,
				EN_LED_PATT_OFF, EN_LED_PATT_OFF, EN_LED_PATT_OFF, EN_LED_PATT_OFF, EN_LED_PATT_OFF, EN_LED_PATT_OFF, EN_LED_PATT_OFF, EN_LED_PATT_OFF, EN_LED_PATT_OFF, EN_LED_PATT_OFF, EN_LED_PATT_OFF, EN_LED_PATT_OFF,
				EN_LED_PATT_OFF, EN_LED_PATT_OFF, EN_LED_PATT_OFF, EN_LED_PATT_OFF, EN_LED_PATT_OFF, EN_LED_PATT_OFF, EN_LED_PATT_OFF, EN_LED_PATT_OFF, EN_LED_PATT_OFF, EN_LED_PATT_OFF,
				EN_LED_PATT_OFF, EN_LED_PATT_OFF, EN_LED_PATT_OFF, EN_LED_PATT_OFF, EN_LED_PATT_OFF, EN_LED_PATT_OFF, EN_LED_PATT_OFF, EN_LED_PATT_OFF, EN_LED_PATT_OFF, EN_LED_PATT_OFF, EN_LED_PATT_OFF, EN_LED_PATT_OFF, EN_LED_PATT_OFF, EN_LED_PATT_OFF, EN_LED_PATT_OFF, EN_LED_PATT_OFF,
				EN_LED_PATT_OFF, EN_LED_PATT_OFF, EN_LED_PATT_OFF, EN_LED_PATT_OFF, EN_LED_PATT_OFF, EN_LED_PATT_OFF, EN_LED_PATT_OFF, EN_LED_PATT_OFF, EN_LED_PATT_OFF, EN_LED_PATT_OFF, EN_LED_PATT_OFF, EN_LED_PATT_OFF, EN_LED_PATT_OFF, EN_LED_PATT_OFF, EN_LED_PATT_OFF, EN_LED_PATT_OFF,
		};

	};
};

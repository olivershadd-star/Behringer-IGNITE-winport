#pragma once
#include <stdint.h>

namespace Ignite
{
#define DIRECTION_IN   0x01 // MSG from MCU
#define DIRECTION_OUT  0x02 // MSG Out to MCU

#define MCU_DATA_SIZE_POS	0x3 //position of the total packet size
#define MCU_HEADRD_SIZE		0x4

#define SYS_SYTM_MSG	0xE0  // System
#define SYS_KEY_MSG	0xE1  // Keys Press/Release/Hold
#define SYS_LED_MSG	0xE2  // LEDs On/Off/Pattern
#define SYS_PAD_MSG	0xE3  // LEDs RGB Pattern
#define SYS_KNOB_MSG	0xE4  // Knob messages
#define SYS_MIDI_MSG	0xE5  // Midi messages
#define SYS_SYNC_MSG	0xE7  // Sync in/out messages
#define SYS_BRAY_MSG	0xE8  // Sync in/out messages

#define RGB_LED_COUNT	0x10  // MSG Out to MCU
#define CV_KNOB_COUNT	0x08  // Nuber of CV Knob - each has 16 leds

#define POWER_ON_COMPLETED 0x01 // Out to MCU
#define POWER_OFF_REQ      0x02 // Out to MCU 
#define SYSTEM_RESET       0x03 // Out to MCU
#define SW_UPGRADE_REQ     0x04 // Out to MCU
#define HW_REMOVED         0x05 // In from MCU
#define HW_DETECTED        0x06 // In from MCU

#define SYS_SYTM_SW_UPGRADE		0xEE
#define SYS_SYTM_ALIVE_STATE	0xEC

#define SYS_SW_UPGRADE_READY   0XAA
#define SYS_SW_UPGRADE_REQ	   0xAB
#define SYS_SW_UPGRADE_ACK	   0xAC
#define SYS_SW_UPGARDE_DONE	   0xAD
#define SYS_SW_UPGRADE_DATA	   0xAE
#define SYS_SW_UPDATE_SOM	   0xA6

#define ROTARY_DIRECTION_LEFT    0x00
#define ROTARY_DIRECTION_RIGHT   0x01
#define ROTARY_DIRECTION_FAST_LEFT    0x02
#define ROTARY_DIRECTION_FAST_RIGHT   0x03

#define SYS_SYTM_HW_TEST				0xA1
#define SYS_MCU_SLEEP					0xA4
#define SYS_MCU_HB_STATE				0xA2
#define SYS_MCU_SYNC_STATE				0xA3
#define SYS_MCU_LED_BRIGHTNESS			0xA5
#define SYS_MCU_FW_VERSION				0xA8
#define SYS_MCU_READY					0xA9

#define LED_BRIGHTNESS_25				0x10
#define LED_BRIGHTNESS_50				0x11
#define LED_BRIGHTNESS_75				0x12
#define LED_BRIGHTNESS_100				0x13
#define LED_BRIGHTNESS_0				0x14

#define SYNC_IN   0x01 
#define SYNC_OUT  0x02 

	typedef enum fpLED : uint8_t
	{
		EN_LED_ALL, // set Pattern ex. power On , SW Upgrade
		EN_LED_MENU,
		EN_LED_BRAY,
		EN_LED_ENTER_NAV,
		EN_LED_MINUS_NAV,
		EN_LED_PLUS_NAV,
		EN_LED_RETURN_NAV,
		EN_LED_COPY_NAV,
		EN_LED_ROTARYROW,
		EN_LED_TRACK,
		EN_LED_SCENE,
		EN_LED_USB_STOP,
		EN_LED_SAVE,
		EN_LED_SONG,
		EN_LED_PATTERN,
		EN_LED_TEMPO,
		EN_LED_INTERNALSOUNDS,
		EN_LED_LAST,
		EN_LED_REC,
		EN_LED_STOP,
		EN_LED_SCULPT,
		EN_LED_INSERT,
		EN_LED_SHIFT,
		EN_LED_BACKFORWARD,
		EN_LED_PLAY,
		EN_LED_DELETE,
		EN_LED_FILL_X,
		EN_LED_NEXT_TIE,
		EN_LED_SOLO_SKIP,
		EN_LED_GANG,
		EN_LED_ROTARYBAR,
		EN_LED_TRACKSEL1,
		EN_LED_TRACKSEL2,
		EN_LED_TRACKSEL3,
		EN_LED_TRACKSEL4,
		EN_LED_TRACKSEL5,
		EN_LED_TRACKSEL6,
		EN_LED_TRACKSEL7,
		EN_LED_TRACKSEL8,
		EN_LED_TRACKSEL9,
		EN_LED_TRACKSEL10,
		EN_LED_TRACKSEL11,
		EN_LED_TRACKSEL12,
		EN_LED_TRACKSEL13,
		EN_LED_TRACKSEL14,
		EN_LED_TRACKSEL15,
		EN_LED_TRACKSEL16,
		EN_LED_TRACKROTARY1,
		EN_LED_TRACKROTARY2,
		EN_LED_TRACKROTARY3,
		EN_LED_TRACKROTARY4,
		EN_LED_TRACKROTARY5,
		EN_LED_TRACKROTARY6,
		EN_LED_TRACKROTARY7,
		EN_LED_TRACKROTARY8,
		EN_LED_TRACKROTARY9,
		EN_LED_TRACKROTARY10,
		EN_LED_TRACKROTARY11,
		EN_LED_TRACKROTARY12,
		EN_LED_TRACKROTARY13,
		EN_LED_TRACKROTARY14,
		EN_LED_TRACKROTARY15,
		EN_LED_TRACKROTARY16,
		EN_LED_RMOVELEFT,
		EN_LED_RMOVERIGHT,
		EN_LED_RSELECT,
		EN_LED_ROTARY_RELEASE,
		EN_LED_ROTARY_FILTER,
		EN_LED_ROTARY_RESONANCE,
		EN_LED_ROTARY_VOLUME,
		EN_LED_ROTARY_CHORUS_AMT,
		EN_LED_ROTARY_REVERB_AMT,
		EN_LED_ROTARY_EQ_HIGH,
		EN_LED_ROTARY_EQ_LOW,
		EN_MX_LED
	}FPLED;
	
	typedef enum fpLEDPattern : uint8_t //Control group of Leds(pre defined) or individual
	{
		EN_LED_PATT_None = 0,
		EN_LED_PATT_NoChange,
		EN_LED_PATT_ON,
		EN_LED_PATT_OFF,
		EN_LED_PATT_FadeON,
		EN_LED_PATT_FadeOFF,
		EN_LED_PATT_Blink3_On,  // Blink and Keep the LED On - 3 times
		EN_LED_PATT_Blink3_Off, // Blink and Keep the LED Off - 3 times
		EN_LED_PATT_Blink5_On,  // Blink and Keep the LED On - 5 times
		EN_LED_PATT_Blink5_Off, // Blink and Keep the LED Off - 5 times
		EN_LED_PATT_Blink_Slow,
		EN_LED_PATT_Blink_Fast,

		EN_LED_PATT_GENERIC_START, // Pattern setting forr all led or Pre Defined Group; LED ID should be EN_LED_ALL
		EN_LED_PATT_PowerON = EN_LED_PATT_GENERIC_START,
		EN_LED_PATT_ON_ALL,
		EN_LED_PATT_OFF_ALL,
		EN_LED_PATT_SW_UPGRADE,
		EN_LED_PATT_SongPage,
		EN_LED_PATT_ScenePage,
		EN_LED_PATT_TrackPage,
		EN_LED_PATT_PatternPage,
		/*EN_LED_PATT_GENERIC_START end*/

		EN_RGB_LED_OFF = 0xA0,
		EN_RGB_LED_RED,
		EN_RGB_LED_GREEN,
		EN_RGB_LED_BLUE,
		EN_RGB_LED_PURPLE,
		EN_RGB_LED_WHITE,
		EN_RGB_LED_LBLUE,
		EN_RGB_LED_SOLIDGRAY,
		EN_RGB_LED_LPURPLE,

		EN_RGB_LED_DARKGREEN,
		EN_RGB_LED_DARKYELLOW,
		EN_RGB_LED_DARKORAGE,
		EN_RGB_LED_DARKRED,
		EN_RGB_LED_DARKPURPLE,
		EN_RGB_LED_DARKBLUE,
		EN_RGB_LED_DARKPURPLE1,
		EN_RGB_LED_DARKBLUE1,
		EN_RGB_LED_PALEGREEN,
		EN_RGB_LED_DARKORANGE1,

		/*EN_LED_PATT_GENERIC_START end*/
		EN_LED_PATT_Max
	}FPLedPattern;

	enum class FrontPannelMcuMap : uint8_t
	{
		McuMapKey_ROTARYROW = 0,
		McuMapKey_SAVE,
		McuMapKey_LAST,
		McuMapKey_SHIFT,
		McuMapKey_REC,
		McuMapKey_BACKFORWARD,
		McuMapKey_STOP,
		McuMapKey_PLAY,
		McuMapKey_SCULPT,
		McuMapKey_DELETE,
		McuMapKey_INSERT,
		McuMapKey_ROTARYBAR,
		McuMapKey_SONG = 17,
		McuMapKey_SCENE,
		McuMapKey_TRACK,
		McuMapKey_NEXT_TIE,
		McuMapKey_FILL_X,
		McuMapKey_SOLO_SKIP,
		McuMapKey_GANG,
		McuMapKey_PATTERN,
		McuMapKey_TEMPO,
		McuMapKey_INTERNALSOUNDS,
		McuMapKey_USB_STOP = 32,
		McuMapKey_MENU,
		McuMapKey_BRAY,
		McuMapKey_RETURN_NAV,
		McuMapKey_COPY_NAV,
		McuMapKey_RSELECT,
		McuMapKey_MINUS_NAV,
		McuMapKey_PLUS_NAV,
		McuMapKey_TRACKSEL1 = 48, //RGB Key --> button + led + below * BLUE LED *
		McuMapKey_TRACKSEL2,
		McuMapKey_TRACKSEL3,
		McuMapKey_TRACKSEL4,
		McuMapKey_TRACKSEL5,
		McuMapKey_TRACKSEL6,
		McuMapKey_TRACKSEL7,
		McuMapKey_TRACKSEL8,
		McuMapKey_TRACKSEL9,
		McuMapKey_TRACKSEL10,
		McuMapKey_TRACKSEL11,
		McuMapKey_TRACKSEL12,
		McuMapKey_TRACKSEL13 = 64,
		McuMapKey_TRACKSEL14,
		McuMapKey_TRACKSEL15,
		McuMapKey_TRACKSEL16,   // RGB Key <<-- End + below * BLUE LED * ; RGB define below McuMap_RGB_DISP1

		McuMapKey_TRACKROTARY1, // Rotary push Key --> button + led
		McuMapKey_TRACKROTARY2,
		McuMapKey_TRACKROTARY3,
		McuMapKey_TRACKROTARY4,
		McuMapKey_TRACKROTARY5,
		McuMapKey_TRACKROTARY6,
		McuMapKey_TRACKROTARY7,
		McuMapKey_TRACKROTARY8,
		McuMapKey_TRACKROTARY9 = 80,
		McuMapKey_TRACKROTARY10,
		McuMapKey_TRACKROTARY11,
		McuMapKey_TRACKROTARY12,
		McuMapKey_TRACKROTARY13,
		McuMapKey_TRACKROTARY14,
		McuMapKey_TRACKROTARY15,
		McuMapKey_TRACKROTARY16, //Rotary push Key <-- button + led

		McuMapKey_ROTARY_NAV,
		McuMapKey_RELEASE,
		McuMapKey_FILTER,
		McuMapKey_RESONANCE,
		McuMapKey_VOLUME,
		McuMapKey_REVERBE,
		McuMapKey_CHORUS,
		McuMapKey_EQHI,
		McuMapKey_EQLO,

		McuMapRot_ROW,	  //Rotary rotate --> Right/Left + led

		McuMapRot_PADROT1, // Rotary rotate --> Right/Left + led
		McuMapRot_PADROT2,
		McuMapRot_PADROT3,
		McuMapRot_PADROT4,
		McuMapRot_PADROT5,
		McuMapRot_PADROT6,
		McuMapRot_PADROT7,
		McuMapRot_PADROT8,
		McuMapRot_PADROT9,
		McuMapRot_PADROT10,
		McuMapRot_PADROT11,
		McuMapRot_PADROT12,
		McuMapRot_PADROT13,
		McuMapRot_PADROT14,
		McuMapRot_PADROT15,
		McuMapRot_PADROT16,  // Rotary rotate --> Right/Left + led
		McuMapRot_BAR,		// Rotary rotate-- > Right / Left + led

		// --> Below has no mapping on MCU/Front pannel internel Key mapping
		McuMapKey_Internals,
		McuMapKey_PAGESHIFT,
		McuMapKey_MouseClick,
		McuMapKey_ENTER_NAV,
		McuMapKey_RDBLSELECT,
		McuMapKey_RMOVELEFT,
		McuMapKey_RMOVERIGHT,
		McuMapKey_SHIFT_NEXT_TIE,
		McuMapKey_SHIFT_FILL_X,
		McuMapKey_SHIFT_SOLO_SKIP,
		McuMapKey_TempoValue,
		// <---------- internel Key mapping
		McuMap_RGB_DISP1, // Only to set color -- for key event use McuMapKey_TRACKSEL
		McuMap_RGB_DISP2,
		McuMap_RGB_DISP3,
		McuMap_RGB_DISP4,
		McuMap_RGB_DISP5,
		McuMap_RGB_DISP6,
		McuMap_RGB_DISP7,
		McuMap_RGB_DISP8,
		McuMap_RGB_DISP9,
		McuMap_RGB_DISP10,
		McuMap_RGB_DISP11,
		McuMap_RGB_DISP12,
		McuMap_RGB_DISP13,
		McuMap_RGB_DISP14,
		McuMap_RGB_DISP15,
		McuMap_RGB_DISP16,
		// --- > System Events
		McuMapKey_LCD_Brightness,
		McuMapKey_FPLED_Brightness,
		McuMapKey_PowerKey_Event,
		McuMapKey_USBStop,

		McuMapKey_getSerialNumber,
		McuMapKey_getFirmwareVersion,
		McuMapKey_getFirmwareBuildInfo,
		McuMapKey_Firmware_Update,
		McuMapKey_Valid_Firmware_check,
		McuMapKey_EmmcGetTotalSize,
		McuMapKey_EmmcGetFreeSize,
		McuMapKey_UsbGetConnectionStatus,
		McuMapKey_UsbGetTotalSize,
		McuMapKey_UsbGetFreeSize,
		McuMapKey_RamGetTotalSize,
		McuMapKey_RamGetFreeSize,
		McuMapKey_FactoryReset,
		//<--- System Events

		McuMapFrontPannelMax
	};
};

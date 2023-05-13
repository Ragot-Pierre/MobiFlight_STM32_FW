//
// MFBoards.h (Arduino Mega)
//
// (C) MobiFlight Project 2022
//

#ifndef MFBoardSTM32F103_h
#define MFBoardSTM32F103_h

#ifndef MF_SEGMENT_SUPPORT
#define MF_SEGMENT_SUPPORT 0
#endif
#ifndef MF_LCD_SUPPORT
#define MF_LCD_SUPPORT 0
#endif
#ifndef MF_STEPPER_SUPPORT
#define MF_STEPPER_SUPPORT 0
#endif
#ifndef MF_SERVO_SUPPORT
#define MF_SERVO_SUPPORT 0
#endif
#ifndef MF_ANALOG_SUPPORT
#define MF_ANALOG_SUPPORT 0
#endif
#ifndef MF_OUTPUT_SHIFTER_SUPPORT
#define MF_OUTPUT_SHIFTER_SUPPORT 0
#endif
#ifndef MF_INPUT_SHIFTER_SUPPORT
#define MF_INPUT_SHIFTER_SUPPORT 0
#endif
#ifndef MF_MUX_SUPPORT
#define MF_MUX_SUPPORT 0
#endif
#ifndef MF_DIGIN_MUX_SUPPORT
#define MF_MUX_SUPPORT       0
#define MF_DIGIN_MUX_SUPPORT 0
#endif

#define MAX_OUTPUTS         35
#define MAX_BUTTONS         35
#define MAX_LEDSEGMENTS     0
#define MAX_ENCODERS        0
#define MAX_STEPPERS        0
#define MAX_MFSERVOS        0
#define MAX_MFLCD_I2C       0
#define MAX_ANALOG_INPUTS   10
#define MAX_OUTPUT_SHIFTERS 0
#define MAX_INPUT_SHIFTERS  0
#define MAX_DIGIN_MUX       0



#define MOBIFLIGHT_TYPE     "MobiFlight STM32F103C8"
#define MOBIFLIGHT_SERIAL   "7159371593"
#define MOBIFLIGHT_NAME     "STM32F103C8"
#define BUILD_VERSION       2.4.1
#define EEPROM_SIZE         4096 // EEPROMSizeMega
#define MEMLEN_CONFIG       2048 // max. size for config which wil be stored in EEPROM
#define MEMLEN_NAMES_BUFFER 1000 // max. size for configBuffer, contains only names from inputs
#define MF_MAX_DEVICEMEM    2048 // max. memory size for devices


#endif

// MFBoards.h
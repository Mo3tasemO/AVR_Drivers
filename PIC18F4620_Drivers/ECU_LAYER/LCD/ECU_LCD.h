/* 
 * File:   ECU_LCD.h
 * Author: Moata
 *
 * Created on January 1, 2026, 2:07 PM
 */

#ifndef ECU_LCD_H
#define	ECU_LCD_H

// Section: Includes

#include "ECU_LCD_CFG.h"
#include "../../MCAL_LAYER/GPIO/HAL_GPIO.h"

// Section: Data Type Declarations
typedef struct{
    pin_config_t lcd_rs;
    pin_config_t lcd_e;
    pin_config_t lcd_data[4];
}LCD_4_BIT_T;

typedef struct{
    pin_config_t lcd_rs;
    pin_config_t lcd_e;
    pin_config_t lcd_data[8];
}LCD_8_BIT_T;

// Section: Macro Declarations


// DISPLAY_CONTROL
#define CLEAR_DISPLAY 0x01
#define RETURN_HOME   0x02
#define DISPLAY_OFF   0x08
#define DISPLAY_ON_CURSOR_OFF_BLINK_OFF     0x0C
#define DISPLAY_ON_CURSOR_ON_BLINK_OFF     0x0E
#define DISPLAY_ON_CURSOR_ON_BLINK_ON     0x0F
#define DISPLAY_ON_CURSOR_OFF_BLINK_ON     0x0D

// FUNCTION_SET
#define DISPLAY_ON_4_BIT_1_LINE_5X8_FONT     0x20
#define DISPLAY_ON_4_BIT_2_LINE_5X8_FONT     0x28
#define DISPLAY_ON_8_BIT_1_LINE_5X8_FONT     0x30
#define DISPLAY_ON_8_BIT_2_LINE_5X8_FONT    0x38

// ENTRY_MODE
#define DISPLAY_ON_NO_INCREAMENT_NO_SHIFT_DISPLAY    0x04
#define DISPLAY_ON_NO_INCREAMENT_SHIFT_DISPLAY    0x05
#define DISPLAY_ON_INCREAMENT_NO_SHIFT_DISPLAY    0x06
#define DISPLAY_ON_INCREAMENT_SHIFT_DISPLAY    0x07

// CURSOR_OR_DISPLAY_SHIFT
#define DISPLAY_ON_SHIFT_CUR_LEFT    0x10
#define DISPLAY_ON_SHIFT_CUR_RIGHT    0x14
#define DISPLAY_ON_SHIFT_ALL_DISPLAY_LEFT    0x18
#define DISPLAY_ON_SHIFT_ALL_DISPLAY_RIGHT    0x1C

// CGRAM, DDRAM START_ADDRESS
#define CGRAM_START 0x40
#define DDRAM_START 0x80

#define ROW_1 1
#define ROW_2 2
#define ROW_3 3
#define ROW_4 4


// Section: Macro Functions Declarations
// Section: Function Declarations

Std_ReturnType LCD_4_BIT_INIT(const LCD_4_BIT_T *lcd);
Std_ReturnType LCD_4_BIT_SEND_COMMAND(const LCD_4_BIT_T *lcd, uint8 command);
Std_ReturnType LCD_4_BIT_SEND_CHR_DATA(const LCD_4_BIT_T *lcd, uint8 data);
Std_ReturnType LCD_4_BIT_SEND_CHR_DATA_POS(const LCD_4_BIT_T *lcd, uint8 row, uint8 column, uint8 data);
Std_ReturnType LCD_4_BIT_SEND_STRING(const LCD_4_BIT_T *lcd, uint8 *str);
Std_ReturnType LCD_4_BIT_SEND_STRING_POS(const LCD_4_BIT_T *lcd, uint8 row, uint8 column, uint8 *str);
Std_ReturnType LCD_4_BIT_SEND_CUSTOM_CHR(const LCD_4_BIT_T *lcd, uint8 row, uint8 column, uint8 chr[], uint8 mem_pos);

Std_ReturnType LCD_8_BIT_INIT(const LCD_8_BIT_T *lcd);
Std_ReturnType LCD_8_BIT_SEND_COMMAND(const LCD_8_BIT_T *lcd, uint8 command);
Std_ReturnType LCD_8_BIT_SEND_CHR_DATA(const LCD_8_BIT_T *lcd, uint8 data);
Std_ReturnType LCD_8_BIT_SEND_CHR_DATA_POS(const LCD_8_BIT_T *lcd, uint8 row, uint8 column, uint8 data);
Std_ReturnType LCD_8_BIT_SEND_STRING(const LCD_8_BIT_T *lcd, uint8 *str);
Std_ReturnType LCD_8_BIT_SEND_STRING_POS(const LCD_8_BIT_T *lcd, uint8 row, uint8 column, uint8 *str);
Std_ReturnType LCD_8_BIT_SEND_CUSTOM_CHR(const LCD_8_BIT_T *lcd, uint8 row, uint8 column, uint8 chr[], uint8 mem_pos);

/*
 * Conversion Interfaces
 */

Std_ReturnType CONVERT_BYTE_TO_STRING(uint8 value, uint8 *str);
Std_ReturnType CONVERT_SHORT_TO_STRING(uint16 value, uint8 *str);
Std_ReturnType CONVERT_INT_TO_STRING(uint32 value, uint8 *str);

#endif	/* ECU_LCD_H */


/* 
 * File:   ECU_KEYPAD.h
 * Author: Moata
 *
 * Created on November 26, 2025, 12:55 PM
 */

#ifndef ECU_KEYPAD_H
#define	ECU_KEYPAD_H



// Section: Includes

#include "ECU_KEYPAD_CFG.h"
#include "../../MCAL_LAYER/GPIO/HAL_GPIO.h"

// Section: Data Type Declarations

typedef enum{
    KEYPAD_ROWS_PINS = 4,
    KEYPAD_COLUMNS_PINS = 4
}KEYPAD_PIN_CONFIGURATION;
// Section: Macro Declarations

typedef struct{
    pin_config_t KEYPAD_ROWS[KEYPAD_ROWS_PINS];
    pin_config_t KEYPAD_COLUMNS[KEYPAD_COLUMNS_PINS];
}KEYPAD_T;

// Section: Macro Functions Declarations
// Section: Function Declarations

Std_ReturnType KEYPAD_INIT(const KEYPAD_T *KEYPAD);
Std_ReturnType KEYPAD_GET_VALUE(const KEYPAD_T *KEYPAD, uint8 *value);




#endif	/* ECU_KEYPAD_H */


/* 
 * File:   ECU_INITIALIZE.c
 * Author: Moata
 *
 * Created on November 26, 2025, 9:34 PM
 */


#include "ECU_INITIALIZE.h"

LCD_4_BIT_T lcd_1 = {
    .lcd_rs.port = PORTC_INDEX,
    .lcd_rs.pin = GPIO_PIN0,
    .lcd_rs.logic = GPIO_LOW,
    .lcd_rs.direction = GPIO_OUTPUT,
    .lcd_e.port = PORTC_INDEX,
    .lcd_e.pin = GPIO_PIN1,
    .lcd_e.logic = GPIO_LOW,
    .lcd_e.direction = GPIO_OUTPUT,
    .lcd_data[0].port = PORTC_INDEX,
    .lcd_data[0].pin = GPIO_PIN2,
    .lcd_data[0].logic = GPIO_LOW,
    .lcd_data[0].direction = GPIO_OUTPUT,
    .lcd_data[1].port = PORTC_INDEX,
    .lcd_data[1].pin = GPIO_PIN3,
    .lcd_data[1].logic = GPIO_LOW,
    .lcd_data[1].direction = GPIO_OUTPUT,
    .lcd_data[2].port = PORTC_INDEX,
    .lcd_data[2].pin = GPIO_PIN4,
    .lcd_data[2].logic = GPIO_LOW,
    .lcd_data[2].direction = GPIO_OUTPUT,
    .lcd_data[3].port = PORTC_INDEX,
    .lcd_data[3].pin = GPIO_PIN5,
    .lcd_data[3].logic = GPIO_LOW,
    .lcd_data[3].direction = GPIO_OUTPUT
};
LCD_8_BIT_T lcd_2 = {
    .lcd_rs.port = PORTC_INDEX,
    .lcd_rs.pin = GPIO_PIN6,
    .lcd_rs.logic = GPIO_LOW,
    .lcd_rs.direction = GPIO_OUTPUT,
    .lcd_e.port = PORTC_INDEX,
    .lcd_e.pin = GPIO_PIN7,
    .lcd_e.logic = GPIO_LOW,
    .lcd_e.direction = GPIO_OUTPUT,
    .lcd_data[0].port = PORTD_INDEX,
    .lcd_data[0].pin = GPIO_PIN0,
    .lcd_data[0].logic = GPIO_LOW,
    .lcd_data[0].direction = GPIO_OUTPUT,
    .lcd_data[1].port = PORTD_INDEX,
    .lcd_data[1].pin = GPIO_PIN1,
    .lcd_data[1].logic = GPIO_LOW,
    .lcd_data[1].direction = GPIO_OUTPUT,
    .lcd_data[2].port = PORTD_INDEX,
    .lcd_data[2].pin = GPIO_PIN2,
    .lcd_data[2].logic = GPIO_LOW,
    .lcd_data[2].direction = GPIO_OUTPUT,
    .lcd_data[3].port = PORTD_INDEX,
    .lcd_data[3].pin = GPIO_PIN3,
    .lcd_data[3].logic = GPIO_LOW,
    .lcd_data[3].direction = GPIO_OUTPUT,
    .lcd_data[4].port = PORTD_INDEX,
    .lcd_data[4].pin = GPIO_PIN4,
    .lcd_data[4].logic = GPIO_LOW,
    .lcd_data[4].direction = GPIO_OUTPUT,
    .lcd_data[5].port = PORTD_INDEX,
    .lcd_data[5].pin = GPIO_PIN5,
    .lcd_data[5].logic = GPIO_LOW,
    .lcd_data[5].direction = GPIO_OUTPUT,
    .lcd_data[6].port = PORTD_INDEX,
    .lcd_data[6].pin = GPIO_PIN6,
    .lcd_data[6].logic = GPIO_LOW,
    .lcd_data[6].direction = GPIO_OUTPUT,
    .lcd_data[7].port = PORTD_INDEX,
    .lcd_data[7].pin = GPIO_PIN7,
    .lcd_data[7].logic = GPIO_LOW,
    .lcd_data[7].direction = GPIO_OUTPUT
};

//KEYPAD_T KEYPAD_1 = {
//    .KEYPAD_ROWS[0].port = PORTC_INDEX,
//    .KEYPAD_ROWS[0].pin = GPIO_PIN0,
//    .KEYPAD_ROWS[0].direction = GPIO_OUTPUT,
//    .KEYPAD_ROWS[0].logic = GPIO_LOW,
//    .KEYPAD_ROWS[1].port = PORTC_INDEX,
//    .KEYPAD_ROWS[1].pin = GPIO_PIN1,
//    .KEYPAD_ROWS[1].direction = GPIO_OUTPUT,
//    .KEYPAD_ROWS[1].logic = GPIO_LOW,
//    .KEYPAD_ROWS[2].port = PORTC_INDEX,
//    .KEYPAD_ROWS[2].pin = GPIO_PIN2,
//    .KEYPAD_ROWS[2].direction = GPIO_OUTPUT,
//    .KEYPAD_ROWS[2].logic = GPIO_LOW,
//    .KEYPAD_ROWS[3].port = PORTC_INDEX,
//    .KEYPAD_ROWS[3].pin = GPIO_PIN3,
//    .KEYPAD_ROWS[3].direction = GPIO_OUTPUT,
//    .KEYPAD_ROWS[3].logic = GPIO_LOW,
//    .KEYPAD_COLUMNS[0].port = PORTC_INDEX,
//    .KEYPAD_COLUMNS[0].pin = GPIO_PIN4,
//    .KEYPAD_COLUMNS[0].direction = GPIO_INPUT,
//    .KEYPAD_COLUMNS[0].logic = GPIO_LOW,
//    .KEYPAD_COLUMNS[1].port = PORTC_INDEX,
//    .KEYPAD_COLUMNS[1].pin = GPIO_PIN5,
//    .KEYPAD_COLUMNS[1].direction = GPIO_INPUT,
//    .KEYPAD_COLUMNS[1].logic = GPIO_LOW,
//    .KEYPAD_COLUMNS[2].port = PORTC_INDEX,
//    .KEYPAD_COLUMNS[2].pin = GPIO_PIN6,
//    .KEYPAD_COLUMNS[2].direction = GPIO_INPUT,
//    .KEYPAD_COLUMNS[2].logic = GPIO_LOW,
//    .KEYPAD_COLUMNS[3].port = PORTC_INDEX,
//    .KEYPAD_COLUMNS[3].pin = GPIO_PIN7,
//    .KEYPAD_COLUMNS[3].direction = GPIO_INPUT,
//    .KEYPAD_COLUMNS[3].logic = GPIO_LOW,
//};



void ECU_INIT(void){
    Std_ReturnType ret = E_NOT_OK;
//    ret = LCD_4_BIT_INIT(&lcd_1);
//    ret = LCD_8_BIT_INIT(&lcd_2);

    
}

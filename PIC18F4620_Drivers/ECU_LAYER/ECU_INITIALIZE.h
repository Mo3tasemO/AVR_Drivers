/* 
 * File:   ECU_INITIALIZE.h
 * Author: Moata
 *
 * Created on November 26, 2025, 9:34 PM
 */

#ifndef ECU_INITIALIZE_H
#define	ECU_INITIALIZE_H

// HAL Header Files

#include "LED/ECU_LED.h"
#include "BUTTON/ECU_BTN.h"
#include "RELAY/ECU_RELAY.h"
#include "DC_Motor/ECU_DC_MOTOR.h"
#include "7_SEGMENT/ECU_7_SEGMENT.h"
#include "KEYPAD/ECU_KEYPAD.h"
#include "LCD/ECU_LCD.h"

// MCAL Header Files

#include "../MCAL_LAYER/Interrupt/MCAL_INTERRUPT_MANAGER.h"
#include "../MCAL_LAYER/EEPROM/HAL_EEPROM.h"
#include "../MCAL_LAYER/HAL_ADC.h"
#include "../MCAL_LAYER/Timers/HAL_TIMER0.h"
#include "../MCAL_LAYER/Timer1/HAL_TIMER1.h"


void ECU_INIT(void);

extern KEYPAD_T KEYPAD_1;
extern LCD_8_BIT_T lcd_2;


#endif	/* ECU_INITIALIZE_H */


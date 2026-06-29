/*
 * ECU_LED.c
 *
 *  Created on: Feb 19, 2026
 *      Author: Moata
 */
#include "ECU_LED.h"

led_config led1 = {
		.led_pin_t.port = PORTD_INDEX,
		.led_pin_t.pin = GPIO_PIN5,
		.led_pin_t.direction = GPIO_DIRECTION_OUTPUT,
		.led_pin_t.logic = GPIO_LOW,
};


Std_ReturnType LED_INIT(const led_config *led_t){
	Std_ReturnType ret = E_OK;
	if(NULL == led_t){
		ret = E_NOT_OK;
	}
	else{
		ret = GPIO_PIN_INIT(&(led_t->led_pin_t));
	}
	return ret;
}
Std_ReturnType LED_ON(const led_config *led_t){
	Std_ReturnType ret = E_OK;
	if(NULL == led_t){
		ret = E_NOT_OK;
	}
	else{
		ret = GPIO_PIN_WRITE_LOGIC(&(led_t->led_pin_t), GPIO_HIGH);

	}
	return ret;
}
Std_ReturnType LED_OFF(const led_config *led_t){
	Std_ReturnType ret = E_OK;
	if(NULL == led_t){
		ret = E_NOT_OK;
	}
	else{
		ret = GPIO_PIN_WRITE_LOGIC(&(led_t->led_pin_t), GPIO_LOW);
	}
	return ret;
}

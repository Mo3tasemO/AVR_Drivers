/*
 * ECU_LED.h
 *
 *  Created on: Feb 19, 2026
 *      Author: Moata
 */

#ifndef ECU_LAYER_LED_ECU_LED_H_
#define ECU_LAYER_LED_ECU_LED_H_

/* Section : Includes */
#include "ECU_LED_CFG.h"
#include "../../MCAL_LAYER/GPIO/HAL_GPIO.h"

/* Section: Macro Declarations */
/* Section: Macro Functions Declarations */

/* Section: Data Type Declarations */


typedef struct {
	pin_config_t led_pin_t;
}led_config;
extern led_config led1;

/* Section: Function Declarations */

Std_ReturnType LED_INIT(const led_config *led_t);
Std_ReturnType LED_ON(const led_config *led_t);
Std_ReturnType LED_OFF(const led_config *led_t);


#endif /* ECU_LAYER_LED_ECU_LED_H_ */

/* 
 * File:   ECU_LED.h
 * Author: Moata
 *
 * Created on September 30, 2025, 6:46 PM
 */

#ifndef ECU_LED_H
#define	ECU_LED_H

// Section: Includes

#include "../../MCAL_LAYER/GPIO/HAL_GPIO.h"
#include "../LED/ECU_LED_CONFIG.h"

// Section: Data Type Definition
typedef enum{
    LED_OFF,
    LED_ON
}led_status;

typedef struct{
    uint8 port_name : 3;
    uint8 pin : 3;
    uint8 led_status : 1;
}led_t;


// Section: Macro Declarations


// Section: Macro Functions Declarations


// Section: Function Declarations
Std_ReturnType led_init(const led_t *led);
Std_ReturnType led_turn_on(const led_t *led);
Std_ReturnType led_turn_off(const led_t *led);
Std_ReturnType led_toggle(const led_t *led);


#endif	/* ECU_LED_H */


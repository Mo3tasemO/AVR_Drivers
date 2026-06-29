/* 
 * File:   ECU_RELAY.h
 * Author: Moata
 *
 * Created on November 2, 2025, 8:05 PM
 */

#ifndef ECU_RELAY_H
#define	ECU_RELAY_H


// Section: Includes
#include "ECU_RELAY_CONFIG.h"
#include "../../MCAL_LAYER/GPIO/HAL_GPIO.h"
// Section: Data Type Declarations

typedef enum{
    RELAY_ON = 0x01U,
    RELAY_OFF = 0x00U
}relay_st;

typedef struct{
    uint8 relay_port : 4;
    uint8 relay_pin : 3;
    uint8 relay_status : 1;
}relay_t;

// Section: Macro Declarations


// Section: Macro Functions Declarations


// Section: Function Declarations
Std_ReturnType RELAY_INIT(const relay_t *relay);
Std_ReturnType RELAY_TURN_ON(const relay_t *relay);
Std_ReturnType RELAY_TURN_OFF(const relay_t *relay);
Std_ReturnType RELAY_TOGGLE(const relay_t *relay);



#endif	/* ECU_RELAY_H */


/* 
 * File:   ECU_DC_MOTOR.h
 * Author: Moata
 *
 * Created on November 13, 2025, 10:21 PM
 */

#ifndef ECU_DC_MOTOR_H
#define	ECU_DC_MOTOR_H


// Section: Includes
#include "ECU_DC_MOTOR_CFG.h"
#include "../../MCAL_LAYER/GPIO/HAL_GPIO.h"

// Section: Data Type Declarations
typedef enum{
    DC_MOTOR_ON = 0x01U,
    DC_MOTOR_OFF = 0x00U,
}dc_motor_status;

#define DC_MOTOR_PIN1 0x00U
#define DC_MOTOR_PIN2 0x01U
#define DC_MOTOR_PIN3 0x02U
#define DC_MOTOR_PIN4 0x03U


// Section: Macro Declarations


typedef struct{
    pin_config_t dc_motor_pin[4];
}dc_motor_t;

// Section: Macro Functions Declarations
Std_ReturnType DC_MOTOR_INIT(const dc_motor_t *dc_motor);
Std_ReturnType DC_MOTOR_FORWARD(const dc_motor_t *dc_motor);
Std_ReturnType DC_MOTOR_BACKWARD(const dc_motor_t *dc_motor);
Std_ReturnType DC_MOTOR_RIGHT(const dc_motor_t *dc_motor);
Std_ReturnType DC_MOTOR_LEFT(const dc_motor_t *dc_motor);
Std_ReturnType DC_MOTOR_STOP(const dc_motor_t *dc_motor);

// Section: Function Declarations


#endif	/* ECU_DC_MOTOR_H */


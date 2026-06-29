/* 
 * File:   ECU_BTN.h
 * Author: Moata
 *
 * Created on October 28, 2025, 12:35 PM
 */

#ifndef ECU_BTN_H
#define	ECU_BTN_H

// Section: Includes

#include "ECU_BTN_CONFIG.h"
#include "../../MCAL_LAYER/GPIO/HAL_GPIO.h"

// Section: Data Type Declarations
typedef enum{
    BUTTON_PRESSED,
    BUTTON_RELEASED
}btn_status_t;

typedef enum{
    BUTTON_ACTIVE_HIGH,
    BUTTON_ACTIVE_LOW
}btn_active_t;

typedef struct{
    pin_config_t btn_pin;
    btn_status_t btn_st;
    btn_active_t btn_active_st;
}btn_t;


// Section: Macro Declarations
// Section: Macro Functions Declarations
// Section: Function Declarations


/**
 * @brief : Initialize The Assigned Pin To Input
 * @param btn : Pointer to the button configurations
 * @return Status of the function 
 *          (E_OK) : Funtion Done Successfully
 *          (E_NOT_OK) : Funtion Has An Issue While Performing Its Action
 */
Std_ReturnType BUTTON_INIT(const btn_t * btn);


/**
 * @brief : Read The Button Status
 * @param btn : Pointer to the button configurations
 * @param status : Pointer to the button status
 * @return Status of the function 
 *          (E_OK) : Funtion Done Successfully
 *          (E_NOT_OK) : Funtion Has An Issue While Performing Its Action
 */
Std_ReturnType BUTTON_READ_STATUS(const btn_t * btn, btn_status_t *status);




#endif	/* ECU_BTN_H */


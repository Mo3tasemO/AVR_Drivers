/* 
 * File:   ECU_BTN
 * Author: Moata
 *
 * Created on October 28, 2025, 12:42 PM
 */

#include "ECU_BTN.h"




/**
 * @brief : Initialize The Assigned Pin To Input
 * @param btn : Pointer to the button configurations
 * @return Status of the function 
 *          (E_OK) : Funtion Done Successfully
 *          (E_NOT_OK) : Funtion Has An Issue While Performing Its Action
 */
Std_ReturnType BUTTON_INIT(const btn_t * btn){
    Std_ReturnType ret = E_OK;
    if((NULL == btn) || (btn->btn_pin.port > GPIO_MAX_PORT_NUMBER - 1))
    {
        ret = E_NOT_OK;
    }
    else        
    {
        ret = gpio_pin_set_direction(&(btn->btn_pin));
    }
    return ret;
}


/**
 * @brief : Read The Button Status
 * @param btn : Pointer to the button configurations
 * @param status : Pointer to the button status
 * @return Status of the function 
 *          (E_OK) : Funtion Done Successfully
 *          (E_NOT_OK) : Funtion Has An Issue While Performing Its Action
 */
Std_ReturnType BUTTON_READ_STATUS(const btn_t * btn, btn_status_t *status){
    Std_ReturnType ret = E_NOT_OK;
    logic_t Pin_Logic_status = GPIO_LOW;
    if((NULL == btn) || (NULL == status) || (btn->btn_pin.port > GPIO_MAX_PORT_NUMBER - 1))
    {
        ret = E_NOT_OK;
    }
    else        
    {
        gpio_pin_read_logic(&(btn->btn_pin), &Pin_Logic_status);
        if(BUTTON_ACTIVE_HIGH == btn->btn_active_st)
        {
            if(GPIO_HIGH == Pin_Logic_status)
            {
                *status = BUTTON_PRESSED;
            }
            else{
                *status = BUTTON_RELEASED;
            }
        }
        else if(BUTTON_ACTIVE_LOW == btn->btn_active_st){
            if(GPIO_HIGH == Pin_Logic_status){
                *status = BUTTON_RELEASED;
            }
            else{
                *status = BUTTON_PRESSED;
            }
        }
        else{
            /*Nothing*/
        }
        ret = E_OK;
    }
    return ret;
}


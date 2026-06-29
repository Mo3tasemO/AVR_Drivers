/* 
 * File:   ECU_LED.c
 * Author: Moata
 *
 * Created on September 30, 2025, 6:46 PM
 */
#include "ECU_LED.h"


/**
 * @brief Initialize the assigned pin and make it output and turn the led off 
 * @param led pointer to the led from the led configuration
 * @return the function returns the status of the function
 */
Std_ReturnType led_init(const led_t *led){
    Std_ReturnType ret = E_OK;
    if((NULL == led) || (led->port_name > GPIO_MAX_PORT_NUMBER - 1))
    {
        ret = E_NOT_OK;
    }
    else        
    {
        pin_config_t pin_o = {
        .port = led->port_name,
        .pin = led->pin,
        .direction = GPIO_OUTPUT,
        .logic = led -> led_status
        };
        gpio_pin_initialize(&pin_o);
    }
    return ret;
}
/**
 * @brief Turn the led that assigned from the led configuration to be ON
 * @param led pointer to the led from the led configuration
 * @return the function returns the status of the function
 */
Std_ReturnType led_turn_on(const led_t *led){
    Std_ReturnType ret = E_OK;
    if((NULL == led) || (led->port_name > GPIO_MAX_PORT_NUMBER - 1))
    {
        ret = E_NOT_OK;
    }
    else        
    {
        pin_config_t pin_o = {
        .port = led->port_name,
        .pin = led->pin,
        .direction = GPIO_OUTPUT,
        .logic = led -> led_status
        };
        gpio_pin_write_logic(&pin_o, GPIO_HIGH);
    }
    return ret;
}
/**
 * @brief Turn the led that assigned from the led configuration to be OFF
 * @param led pointer to the led from the led configuration
 * @return the function returns the status of the function
 */
Std_ReturnType led_turn_off(const led_t *led){
    Std_ReturnType ret = E_OK;
    if((NULL == led) || (led->port_name > GPIO_MAX_PORT_NUMBER - 1))
    {
        ret = E_NOT_OK;
    }
    else        
    {
        pin_config_t pin_o = {
        .port = led->port_name,
        .pin = led->pin,
        .direction = GPIO_OUTPUT,
        .logic = led -> led_status
        };
        gpio_pin_write_logic(&pin_o, GPIO_LOW);
    }
    return ret;
}
/**
 * @brief Toggle the Led that assigned from led configuration
 * @param led pointer to the led from the led configuration
 * @return the function returns the status of the function
 */
Std_ReturnType led_toggle(const led_t *led){
    Std_ReturnType ret = E_OK;
    if((NULL == led) || (led->port_name > GPIO_MAX_PORT_NUMBER - 1))
    {
        ret = E_NOT_OK;
    }
    else        
    {
        pin_config_t pin_o = {
        .port = led->port_name,
        .pin = led->pin,
        .direction = GPIO_OUTPUT,
        .logic = led -> led_status
        };
        gpio_pin_toggle(&pin_o);
    }
    return ret;
}



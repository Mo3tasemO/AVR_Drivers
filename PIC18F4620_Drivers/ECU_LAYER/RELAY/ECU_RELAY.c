/* 
 * File:   ECU_RELAY.c
 * Author: Moata
 *
 * Created on November 2, 2025, 8:05 PM
 */

// Section: Includes
#include "ECU_RELAY.h"


/**
 * 
 * @param relay
 * @return 
 */
Std_ReturnType RELAY_INIT(const relay_t *relay)
{
    Std_ReturnType ret = E_OK;
    if(NULL == relay)
    {
        ret = E_NOT_OK;
    }
    else
    {
        pin_config_t relay_config = {
            .port = relay->relay_port,
            .pin = relay->relay_pin,
            .direction = GPIO_OUTPUT,
            .logic = relay->relay_status
        };
        gpio_pin_initialize(&relay_config);
    }
    return ret;
}

/**
 * 
 * @param relay
 * @return 
 */
Std_ReturnType RELAY_TURN_ON(const relay_t *relay)
{
    Std_ReturnType ret = E_OK;
    if(NULL == relay)
    {
        ret = E_NOT_OK;
    }
    else
    {
        pin_config_t relay_config = {
            .port = relay->relay_port,
            .pin = relay->relay_pin,
            .direction = GPIO_OUTPUT,
            .logic = relay->relay_status
        };
        gpio_pin_write_logic(&relay_config, GPIO_HIGH);
    }
    return ret;
}

/**
 * 
 * @param relay
 * @return 
 */
Std_ReturnType RELAY_TURN_OFF(const relay_t *relay)
{
    Std_ReturnType ret = E_OK;
    if(NULL == relay)
    {
        ret = E_NOT_OK;
    }
    else
    {
        pin_config_t relay_config = {
            .port = relay->relay_port,
            .pin = relay->relay_pin,
            .direction = GPIO_OUTPUT,
            .logic = relay->relay_status
        };
        gpio_pin_write_logic(&relay_config, GPIO_LOW);
    }
    return ret;
}

/**
 * 
 * @param relay
 * @return 
 */
Std_ReturnType RELAY_TOGGLE(const relay_t *relay)
{
    Std_ReturnType ret = E_OK;
    if(NULL == relay)
    {
        ret = E_NOT_OK;
    }
    else
    {
        pin_config_t relay_config = {
            .port = relay->relay_port,
            .pin = relay->relay_pin,
            .direction = GPIO_OUTPUT,
            .logic = relay->relay_status
        };
        gpio_pin_toggle(&relay_config);
    }
    return ret;
}



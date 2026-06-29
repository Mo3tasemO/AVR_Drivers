/* 
 * File:   HAL_GPIO.c
 * Author: Moata
 *
 * Created on September 30, 2025, 6:28 PM
 */

#include "HAL_GPIO.h"

// PIC18f4620 GPIO Registers
volatile uint8 *TRIS_REG[] = {&TRISA, &TRISB, &TRISC, &TRISD, &TRISE};
volatile uint8 *PORT_REG[] = {&PORTA, &PORTB, &PORTC, &PORTD, &PORTE};
volatile uint8 *LAT_REG[] = {&LATA, &LATB, &LATC, &LATD, &LATE};

/**
 * 
 * @param _pin_config
 * @return 
 */
#if GPIO_PORT_PIN_CONFIGURATION==CONFIG_ENABLE
Std_ReturnType gpio_pin_set_direction(const pin_config_t *_pin_config){
    Std_ReturnType ret = E_OK;
    if((NULL == _pin_config) || (_pin_config->pin > GPIO_MAX_PIN_NUMBER - 1))
    {
        ret = E_NOT_OK;
    }
    else{
        switch(_pin_config->direction)
        {
            case GPIO_OUTPUT:
                CLEAR_BIT(*TRIS_REG[_pin_config->port],_pin_config->pin);
                break;
            case GPIO_INPUT:
                SET_BIT(*TRIS_REG[_pin_config->port],_pin_config->pin);
                break;
            default : ret = E_NOT_OK;
        }
    }
    return ret;
}
#endif
/**
 * 
 * @param _pin_config
 * @param dir_status
 * @return 
 */
#if GPIO_PORT_PIN_CONFIGURATION==CONFIG_ENABLE
Std_ReturnType gpio_pin_read_direction(const pin_config_t *_pin_config, direction_t *dir_status){
    uint8 ret = E_OK;
    if((NULL == _pin_config) || (NULL == dir_status) || (_pin_config->pin > GPIO_MAX_PIN_NUMBER - 1))
    {
        ret = E_NOT_OK;
    }
    else{
        *dir_status = READ_BIT(*TRIS_REG[_pin_config->port],_pin_config->pin);
    }
    return ret;
}
#endif
/**
 * 
 * @param _pin_config
 * @param logic
 * @return 
 */
#if GPIO_PORT_PIN_CONFIGURATION==CONFIG_ENABLE
Std_ReturnType gpio_pin_write_logic(const pin_config_t *_pin_config, logic_t logic){
    uint8 ret = E_OK;
    if((NULL == _pin_config) || (_pin_config->pin > GPIO_MAX_PIN_NUMBER - 1))
    {
        ret = E_NOT_OK;
    }
    else{
        switch(logic)
        {
            case GPIO_LOW:
                CLEAR_BIT(*LAT_REG[_pin_config->port], _pin_config->pin);
                break;
            case GPIO_HIGH:
                SET_BIT(*LAT_REG[_pin_config->port], _pin_config->pin);
                break;
            default : ret = E_NOT_OK;
        }
    }
    return ret;
}
#endif
/**
 * 
 * @param _pin_config
 * @param logic
 * @return 
 */
#if GPIO_PORT_PIN_CONFIGURATION==CONFIG_ENABLE
Std_ReturnType gpio_pin_read_logic(const pin_config_t *_pin_config, logic_t *logic){
    uint8 ret = E_OK;
    if((NULL == _pin_config) || (NULL == logic) || (_pin_config->pin > GPIO_MAX_PIN_NUMBER - 1))
    {
        ret = E_NOT_OK;
    }
    else{
        *logic = READ_BIT(*PORT_REG[_pin_config->port],_pin_config->pin);
    }
    return ret;
}
#endif
/**
 * 
 * @param _pin_config
 * @return 
 */
#if GPIO_PORT_PIN_CONFIGURATION==CONFIG_ENABLE
Std_ReturnType gpio_pin_toggle(const pin_config_t *_pin_config){
    uint8 ret = E_OK;
    if((NULL == _pin_config) || (_pin_config->pin > GPIO_MAX_PIN_NUMBER - 1))
    {
        ret = E_NOT_OK;
    }
    else{
        TOGGLE_BIT(*LAT_REG[_pin_config->port], _pin_config->pin);
    }
    return ret;
}
#endif
/**
 * 
 * @param _pin_config
 * @return 
 */
#if GPIO_PORT_PIN_CONFIGURATION==CONFIG_ENABLE
Std_ReturnType gpio_pin_initialize(const pin_config_t *_pin_config)
{
    uint8 ret = E_OK;
    if((NULL == _pin_config) || (_pin_config->pin > GPIO_MAX_PIN_NUMBER - 1))
    {
        ret = E_NOT_OK;
    }
    else{
        gpio_pin_set_direction(_pin_config);
        gpio_pin_write_logic(_pin_config, _pin_config->logic);
    }
    return ret;
}
#endif
/**
 * 
 * @param port
 * @param direction
 * @return 
 */
#if GPIO_PORT_CONFIGURATION==CONFIG_ENABLE
Std_ReturnType gpio_port_set_direction(port_index_t port, uint8 direction){
    uint8 ret = E_OK;
    if(port > GPIO_MAX_PORT_NUMBER - 1)
    {
        ret = E_NOT_OK;
    }
    else{
        *TRIS_REG[port] = direction;
    }
    return ret;
}
#endif
/**
 * 
 * @param port
 * @param dir_status
 * @return 
 */
#if GPIO_PORT_CONFIGURATION==CONFIG_ENABLE
Std_ReturnType gpio_port_read_direction(port_index_t port, uint8 *dir_status){
    uint8 ret = E_OK;
    if((NULL == dir_status) || (port > GPIO_MAX_PORT_NUMBER - 1))
    {
        ret = E_NOT_OK;
    }
    else{
        *dir_status = *TRIS_REG[port];
    }
    return ret;
}
#endif
/**
 * 
 * @param port
 * @param logic
 * @return 
 */
#if GPIO_PORT_CONFIGURATION==CONFIG_ENABLE
Std_ReturnType gpio_port_write_logic(port_index_t port, uint8 logic){
    uint8 ret = E_OK;
    if(port > GPIO_MAX_PORT_NUMBER - 1)
    {
        ret = E_NOT_OK;
    }
    else{
        *LAT_REG[port] = logic;
    }
    return ret;
}
#endif
/**
 * 
 * @param port
 * @param logic
 * @return 
 */
#if GPIO_PORT_CONFIGURATION==CONFIG_ENABLE
Std_ReturnType gpio_port_read_logic(port_index_t port, uint8 *logic){
    uint8 ret = E_OK;
    if((NULL == logic) || (port > GPIO_MAX_PORT_NUMBER - 1))
    {
        ret = E_NOT_OK;
    }
    else{
        *logic = *LAT_REG[port];
    }
    return ret;
}
#endif
/**
 * 
 * @param port
 * @return 
 */
#if GPIO_PORT_CONFIGURATION==CONFIG_ENABLE
Std_ReturnType gpio_port_toggle(port_index_t port){
    uint8 ret = E_OK;
    if(port > GPIO_MAX_PORT_NUMBER - 1)
    {
        ret = E_NOT_OK;
    }
    else{
        *LAT_REG[port] ^= TOGGLE_MASK;
    }
    return ret;
}
#endif

/* 
 * File:   ECU_DC_MOTOR.c
 * Author: Moata
 *
 * Created on November 13, 2025, 10:21 PM
 */

#include "ECU_DC_MOTOR.h"




Std_ReturnType DC_MOTOR_INIT(const dc_motor_t *dc_motor)
{
    Std_ReturnType ret = E_OK;
    if(NULL == dc_motor){
        ret = E_NOT_OK;
    }
    else
    {
        gpio_pin_initialize(&(dc_motor->dc_motor_pin[DC_MOTOR_PIN1]));
        gpio_pin_initialize(&(dc_motor->dc_motor_pin[DC_MOTOR_PIN2]));
        gpio_pin_initialize(&(dc_motor->dc_motor_pin[DC_MOTOR_PIN3]));
        gpio_pin_initialize(&(dc_motor->dc_motor_pin[DC_MOTOR_PIN4]));
    }
    return ret;
}
Std_ReturnType DC_MOTOR_FORWARD(const dc_motor_t *dc_motor)
{
    Std_ReturnType ret = E_OK;
    if(NULL == dc_motor){
        ret = E_NOT_OK;
    }
    else
    {
        gpio_pin_write_logic(&(dc_motor->dc_motor_pin[DC_MOTOR_PIN1]), GPIO_HIGH);
        gpio_pin_write_logic(&(dc_motor->dc_motor_pin[DC_MOTOR_PIN2]), GPIO_LOW);
        gpio_pin_write_logic(&(dc_motor->dc_motor_pin[DC_MOTOR_PIN3]), GPIO_HIGH);
        gpio_pin_write_logic(&(dc_motor->dc_motor_pin[DC_MOTOR_PIN4]), GPIO_LOW);

    }
    return ret;
}
Std_ReturnType DC_MOTOR_BACKWARD(const dc_motor_t *dc_motor)
{
    Std_ReturnType ret = E_OK;
    if(NULL == dc_motor){
        ret = E_NOT_OK;
    }
    else
    {
        gpio_pin_write_logic(&(dc_motor->dc_motor_pin[DC_MOTOR_PIN1]), GPIO_LOW);
        gpio_pin_write_logic(&(dc_motor->dc_motor_pin[DC_MOTOR_PIN2]), GPIO_HIGH);
        gpio_pin_write_logic(&(dc_motor->dc_motor_pin[DC_MOTOR_PIN3]), GPIO_LOW);
        gpio_pin_write_logic(&(dc_motor->dc_motor_pin[DC_MOTOR_PIN4]), GPIO_HIGH);   
    }
    return ret;
}
Std_ReturnType DC_MOTOR_RIGHT(const dc_motor_t *dc_motor){
    Std_ReturnType ret = E_OK;
    if(NULL == dc_motor){
        ret = E_NOT_OK;
    }
    else
    {
        gpio_pin_write_logic(&(dc_motor->dc_motor_pin[DC_MOTOR_PIN1]), GPIO_HIGH);
        gpio_pin_write_logic(&(dc_motor->dc_motor_pin[DC_MOTOR_PIN2]), GPIO_LOW);
        gpio_pin_write_logic(&(dc_motor->dc_motor_pin[DC_MOTOR_PIN3]), GPIO_LOW);
        gpio_pin_write_logic(&(dc_motor->dc_motor_pin[DC_MOTOR_PIN4]), GPIO_LOW);
    }
    return ret;
}
Std_ReturnType DC_MOTOR_LEFT(const dc_motor_t *dc_motor){
    Std_ReturnType ret = E_OK;
    if(NULL == dc_motor){
        ret = E_NOT_OK;
    }
    else
    {
        gpio_pin_write_logic(&(dc_motor->dc_motor_pin[DC_MOTOR_PIN1]), GPIO_LOW);
        gpio_pin_write_logic(&(dc_motor->dc_motor_pin[DC_MOTOR_PIN2]), GPIO_LOW);
        gpio_pin_write_logic(&(dc_motor->dc_motor_pin[DC_MOTOR_PIN3]), GPIO_HIGH);
        gpio_pin_write_logic(&(dc_motor->dc_motor_pin[DC_MOTOR_PIN4]), GPIO_LOW);
    }
    return ret;
}
Std_ReturnType DC_MOTOR_STOP(const dc_motor_t *dc_motor)
{
    Std_ReturnType ret = E_OK;
    if(NULL == dc_motor){
        ret = E_NOT_OK;
    }
    else
    {
        gpio_pin_write_logic(&(dc_motor->dc_motor_pin[DC_MOTOR_PIN1]), GPIO_LOW);
        gpio_pin_write_logic(&(dc_motor->dc_motor_pin[DC_MOTOR_PIN2]), GPIO_LOW);
        gpio_pin_write_logic(&(dc_motor->dc_motor_pin[DC_MOTOR_PIN3]), GPIO_LOW);
        gpio_pin_write_logic(&(dc_motor->dc_motor_pin[DC_MOTOR_PIN4]), GPIO_LOW);
    }
    return ret;
}
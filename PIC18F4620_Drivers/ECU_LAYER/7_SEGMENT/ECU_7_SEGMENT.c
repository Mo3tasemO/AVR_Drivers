/* 
 * File:   ECU_7_SEGMENT.c
 * Author: Moata
 *
 * Created on November 24, 2025, 11:10 PM
 */

#include "ECU_7_SEGMENT.h"






Std_ReturnType SEVEN_SEGMENT_INIT(const SEGMENT_T * SEGMENT)
{
    Std_ReturnType ret = E_OK;
    if(NULL == SEGMENT)
    {
        ret = E_NOT_OK;
    }
    else
    {
        ret = gpio_pin_initialize(&(SEGMENT->SEGMENT_PINS[SEVEN_SEGMENT_PIN1]));
        ret = gpio_pin_initialize(&(SEGMENT->SEGMENT_PINS[SEVEN_SEGMENT_PIN2]));
        ret = gpio_pin_initialize(&(SEGMENT->SEGMENT_PINS[SEVEN_SEGMENT_PIN3]));
        ret = gpio_pin_initialize(&(SEGMENT->SEGMENT_PINS[SEVEN_SEGMENT_PIN4]));
    }
    return ret;
}
Std_ReturnType SEVEN_SEGMENT_WRITE_NUMBER(const SEGMENT_T * SEGMENT, uint8 number)
{
    Std_ReturnType ret = E_OK;
    if((NULL == SEGMENT) || (number > 9))
    {
        ret = E_NOT_OK;
    }
    else
    {
        ret = gpio_pin_write_logic(&(SEGMENT->SEGMENT_PINS[SEVEN_SEGMENT_PIN1]), (number & 0x01));
        ret = gpio_pin_write_logic(&(SEGMENT->SEGMENT_PINS[SEVEN_SEGMENT_PIN2]), ((number >> 1) & 0x01));
        ret = gpio_pin_write_logic(&(SEGMENT->SEGMENT_PINS[SEVEN_SEGMENT_PIN3]), ((number >> 2) & 0x01));
        ret = gpio_pin_write_logic(&(SEGMENT->SEGMENT_PINS[SEVEN_SEGMENT_PIN4]), ((number >> 3) & 0x01));
    }
    return ret;
}






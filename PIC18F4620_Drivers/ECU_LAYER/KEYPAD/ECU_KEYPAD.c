/* 
 * File:   ECU_KEYPAD.c
 * Author: Moata
 *
 * Created on November 26, 2025, 12:55 PM
 */

#include "ECU_KEYPAD.h"


static uint8 KEYPAD_VALUES[KEYPAD_ROWS_PINS][KEYPAD_COLUMNS_PINS] = {
                                                                    {'7', '8', '9', '/'},
                                                                    {'4', '5', '6', '*'},
                                                                    {'1', '2', '3', '-'},
                                                                    {'#', '0', '=', '+'}
                        
};




/**
 * @brief : Initialize the keypad pins (rows, columns)
 * @param KEYPAD : Pointer to the keypad configurations
 * @return Status of the function 
 *          (E_OK) : Funtion Done Successfully
 *          (E_NOT_OK) : Funtion Has An Issue While Performing Its Action
 */
Std_ReturnType KEYPAD_INIT(const KEYPAD_T *KEYPAD)
{
    Std_ReturnType ret = E_OK;
    uint8 ROWS_COUNTER = 0, COLUMNS_COUNTER = 0;
    if(NULL == KEYPAD)
    {
        ret = E_NOT_OK;
    }
    else{
        for(ROWS_COUNTER = 0; ROWS_COUNTER < KEYPAD_ROWS_PINS; ROWS_COUNTER++)
        {
            ret = gpio_pin_initialize(&KEYPAD->KEYPAD_ROWS[ROWS_COUNTER]);
        }
        for(COLUMNS_COUNTER = 0; COLUMNS_COUNTER < KEYPAD_COLUMNS_PINS; COLUMNS_COUNTER++)
        {
            ret = gpio_pin_initialize(&KEYPAD->KEYPAD_COLUMNS[COLUMNS_COUNTER]);
        }
        
    }
    return ret;
}
/**
 * @brief : Initialize the keypad pins (rows, columns)
 * @param KEYPAD : Pointer to the keypad configurations
 * @param value : Pointer to value that will be return
 * @return Status of the function 
 *          (E_OK) : Funtion Done Successfully
 *          (E_NOT_OK) : Funtion Has An Issue While Performing Its Action
 */
Std_ReturnType KEYPAD_GET_VALUE(const KEYPAD_T *KEYPAD, uint8 *value)
{
    Std_ReturnType ret = E_OK;
    uint8 rows = 0, columns = 0;
    uint8 l_rows = 0, column_logic = 0;
    if((NULL == KEYPAD) || (NULL == value))
    {
        ret = E_NOT_OK;
    }
    else{
        for(rows = 0; rows < KEYPAD_ROWS_PINS; rows++){
            for(l_rows = 0; l_rows < KEYPAD_ROWS_PINS; l_rows++)
            {
                ret = gpio_pin_write_logic(&(KEYPAD->KEYPAD_ROWS[l_rows]), GPIO_LOW);
            }
            ret = gpio_pin_write_logic(&(KEYPAD->KEYPAD_ROWS[rows]), GPIO_HIGH);
            for(columns = 0; columns < KEYPAD_COLUMNS_PINS; columns++){
                ret = gpio_pin_read_logic(&(KEYPAD->KEYPAD_COLUMNS[columns]), &column_logic);
                if(GPIO_HIGH == column_logic)
                {
                    *value = KEYPAD_VALUES[rows][columns];
                }
            }
        }
    }
    return ret;
}



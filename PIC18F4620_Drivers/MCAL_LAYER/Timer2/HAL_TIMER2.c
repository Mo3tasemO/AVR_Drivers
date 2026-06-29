/* 
 * File:   HAL_TIMER2.c
 * Author: Moata
 *
 * Created on June 29, 2026, 9:14 PM
 */

#include "HAL_TIMER2.h"


Std_ReturnType TIMER2_INIT(const TIMER2_T *_Timer){
    Std_ReturnType ret = E_OK;
    if(NULL == _Timer){
        ret = E_NOT_OK;
    }
    else{
    
    }
    return ret;
}
Std_ReturnType TIMER2_DENIT(const TIMER2_T *_Timer){
    Std_ReturnType ret = E_OK;
    if(NULL == _Timer){
        ret = E_NOT_OK;
    }
    else{
    
    }
    return ret;    
}
Std_ReturnType TIMER2_WRITE_VALUE(const TIMER2_T *_Timer, uint8 value){
    Std_ReturnType ret = E_OK;
    if(NULL == _Timer){
        ret = E_NOT_OK;
    }
    else{
    
    }
    return ret;    
}
Std_ReturnType TIMER2_READ_VALUE(const TIMER2_T *_Timer, uint8 *value){
    Std_ReturnType ret = E_OK;
    if((NULL == _Timer) || (NULL == value)){
        ret = E_NOT_OK;
    }
    else{
    
    }
    return ret;    
}



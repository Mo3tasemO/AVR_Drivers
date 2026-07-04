/* 
 * File:   HAL_TIMER3.c
 * Author: Moata
 *
 * Created on June 29, 2026, 9:14 PM
 */

#include "HAL_TIMER3.h"


static inline void TMR3_MODE_SELECT(const TIMER3_T *_Timer);
static inline void TMR3_RW_CFG_SELECT(const TIMER3_T *_Timer);
#ifdef TIMER3_INTERRUPT_FEATURE_ENABLE
    static void (*TIMER3_INTERRUPT_HANDLER)(void) = NULL;
#endif
static uint16 timer3_preload = 0;




Std_ReturnType TIMER3_INIT(const TIMER3_T *_Timer){
    Std_ReturnType ret = E_OK;
    if(NULL == _Timer){
        ret = E_NOT_OK;
    }
    else{
        TIMER3_DISABLE();
        TIMER3_PRESCALLER_SELECT(_Timer->PRESCALER_VAL);
        TMR3_MODE_SELECT(_Timer);
        TMR3_RW_CFG_SELECT(_Timer);
        TMR3H = (_Timer->TIMER3_PRELOAD_VALUE) >> 8;
        TMR3L = (uint8)(_Timer->TIMER3_PRELOAD_VALUE);
        timer3_preload = _Timer->TIMER3_PRELOAD_VALUE;
#ifdef TIMER3_INTERRUPT_FEATURE_ENABLE
        TIMER3_INTERRUPT_ENABLE();
        TIMER3_INTERRUPT_FLAG_CLEAR();
        TIMER3_INTERRUPT_HANDLER = _Timer->TMR3_INTERRUPT_HANDLER;
#if  INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE
        INTERRUPT_Priority_Level_Enable();
        if(INTERRUPT_LOW_PRIORITY == _Timer->TMR3_priority){
            INTERRUPT_GlobalInterruptLowEnable();
            TIMER3_INTERRUPT_PRIORITY_LOW();
        }
        else if(INTERRUPT_HIGH_PRIORITY == _Timer->TMR3_priority){
            INTERRUPT_GlobalInterruptHighEnable();
            TIMER3_INTERRUPT_PRIORITY_HIGH();
        }
        else {/*Nothing*/}
#else
        INTERRUPT_GlobalInterruptEnable();
        INTERRUPT_Peripheral_Interrupt_Enable(); 
#endif
#endif
        TIMER3_ENABLE();
    }
    return ret;    
}
Std_ReturnType TIMER3_DENIT(const TIMER3_T *_Timer){
    Std_ReturnType ret = E_OK;
    if(NULL == _Timer){
        ret = E_NOT_OK;
    }
    else{
        TIMER3_DISABLE();
#ifdef TIMER3_INTERRUPT_FEATURE_ENABLE
        TIMER3_INTERRUPT_DISABLE();
#endif        
    }
    return ret;       
}
Std_ReturnType TIMER3_WRITE_VALUE(const TIMER3_T *_Timer, uint16 value){
    Std_ReturnType ret = E_OK;
    if(NULL == _Timer){
        ret = E_NOT_OK;
    }
    else{
        TMR3H = (value) >> 8;
        TMR3L = (uint8)(value);
    }
    return ret;      
}
Std_ReturnType TIMER3_READ_VALUE(const TIMER3_T *_Timer, uint16 *value){
    Std_ReturnType ret = E_OK;
    uint8 L_tmr3 = 0, H_tmr3 = 0;
    if((NULL == _Timer) || (NULL == value)){
        ret = E_NOT_OK;
    }
    else{
        L_tmr3 = TMR3L;
        H_tmr3 = TMR3H;
        *value = (uint16)((H_tmr3 << 8) + L_tmr3);    
    }
    return ret;        
}



static inline void TMR3_MODE_SELECT(const TIMER3_T *_Timer){
    if(TIMER3_TIMER_MODE == _Timer->TIMER3_MODE){
        TIMER3_TIMER_MODE_ENABLE();
    }
    else if(TIMER3_COUNTER_MODE == _Timer->TIMER3_MODE){
        TIMER3_COUNTER_MODE_ENABLE();
        if(TIMER3_ASYNC_COUNTER == _Timer->TIMER3_SYNC_SELECT){
            TIMER3_ASYNCHRONIZE_COUNTER_MODE_ENABLE();
        }
        else if(TIMER3_SYNC_COUNTER == _Timer->TIMER3_SYNC_SELECT){
            TIMER3_SYNCHRONIZE_COUNTER_MODE_ENABLE();
        }
        else{
            /*Nothing*/
        }
    }
    else{
        /*Nothing*/
    }        
}
static inline void TMR3_RW_CFG_SELECT(const TIMER3_T *_Timer){
    if(TIMER3_RW_16_BIT_CFG == _Timer->TIMER3_RW_MODE_CFG){
        TIMER3_16_BIT_CONFIGURATION();
    }
    else if(TIMER3_RW_8_BIT_CFG == _Timer->TIMER3_RW_MODE_CFG){
        TIMER3_8_BIT_CONFIGURATION();
    }
    else{
        /*Nothing*/
    }        
}

void TMR3_ISR(void){
    /* The Flag of TMR0 Interrupt Must be Cleared*/
    TIMER3_INTERRUPT_FLAG_CLEAR();
    TMR3H = (timer3_preload) >> 8;
    TMR3L = (uint8)(timer3_preload);
    /*Check The Interrupt Handler Pointer To Function if it is equal to address of the Application Interrupt handler
     And It callback the function gets called every time this ISR executes*/
    if(TIMER3_INTERRUPT_HANDLER){
        TIMER3_INTERRUPT_HANDLER();
    }
}
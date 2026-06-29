/* 
 * File:   HAL_TIMER1.c
 * Author: Moata
 *
 * Created on June 28, 2026, 6:59 PM
 */


#include "HAL_TIMER1.h"

static inline void TMR1_MODE_SELECT(const TIMER1_T *_Timer);
static inline void TMR1_RW_CFG_SELECT(const TIMER1_T *_Timer);
#ifdef TIMER1_INTERRUPT_FEATURE_ENABLE
    static void (*TIMER1_INTERRUPT_HANDLER)(void) = NULL;
#endif
static uint16 timer1_preload = 0;



Std_ReturnType TIMER1_INIT(const TIMER1_T *_Timer){
    Std_ReturnType ret = E_OK;
    if(NULL == _Timer){
        ret = E_NOT_OK;
    }
    else{
        TIMER1_DISABLE();
        TIMER1_PRESCALLER_SELECT(_Timer->PRESCALER_VAL);
        TMR1_MODE_SELECT(_Timer);
        TMR1_RW_CFG_SELECT(_Timer);
        TMR1H = (_Timer->TIMER1_PRELOAD_VALUE) >> 8;
        TMR1L = (uint8)(_Timer->TIMER1_PRELOAD_VALUE);
        timer1_preload = _Timer->TIMER1_PRELOAD_VALUE;
#ifdef TIMER1_INTERRUPT_FEATURE_ENABLE
        TIMER1_INTERRUPT_ENABLE();
        TIMER1_INTERRUPT_FLAG_CLEAR();
        TIMER1_INTERRUPT_HANDLER = _Timer->TMR1_INTERRUPT_HANDLER;
#if  INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE
        INTERRUPT_Priority_Level_Enable();
        if(INTERRUPT_LOW_PRIORITY == _Timer->TMR1_priority){
            INTERRUPT_GlobalInterruptLowEnable();
            TIMER1_INTERRUPT_PRIORITY_LOW();
        }
        else if(INTERRUPT_HIGH_PRIORITY == _Timer->TMR1_priority){
            INTERRUPT_GlobalInterruptHighEnable();
            TIMER1_INTERRUPT_PRIORITY_HIGH();
        }
        else {/*Nothing*/}
#else
        INTERRUPT_GlobalInterruptEnable();
        INTERRUPT_Peripheral_Interrupt_Enable(); 
#endif
#endif        
        
        
        TIMER1_ENABLE();
    }
    return ret;
}
Std_ReturnType TIMER1_DENIT(const TIMER1_T *_Timer){
    Std_ReturnType ret = E_OK;
    if(NULL == _Timer){
        ret = E_NOT_OK;
    }
    else{
        TIMER1_DISABLE();
#ifdef TIMER1_INTERRUPT_FEATURE_ENABLE
        TIMER1_INTERRUPT_FLAG_CLEAR();
#endif        
    }
    return ret;    
}
Std_ReturnType TIMER1_WRITE_VALUE(const TIMER1_T *_Timer, uint16 value){
    Std_ReturnType ret = E_OK;
    if(NULL == _Timer){
        ret = E_NOT_OK;
    }
    else{
        TMR1H = (value) >> 8;
        TMR1L = (uint8)(value);
    }
    return ret;    
}
Std_ReturnType TIMER1_READ_VALUE(const TIMER1_T *_Timer, uint16 *value){
    Std_ReturnType ret = E_OK;
    uint8 L_tmr1 = 0, H_tmr1 = 0;
    if((NULL == _Timer) || (NULL == value)){
        ret = E_NOT_OK;
    }
    else{
        L_tmr1 = TMR1L;
        H_tmr1 = TMR1H;
        *value = (uint16)((H_tmr1 << 8) + L_tmr1);    
    }
    return ret;    
}

static inline void TMR1_RW_CFG_SELECT(const TIMER1_T *_Timer){
    if(TIMER1_RW_16_BIT_CFG == _Timer->TIMER1_RW_MODE_CFG){
        TIMER1_16_BIT_CONFIGURATION();
    }
    else if(TIMER1_RW_8_BIT_CFG == _Timer->TIMER1_RW_MODE_CFG){
        TIMER1_8_BIT_CONFIGURATION();
    }
    else{
        /*Nothing*/
    }    
}

static inline void TMR1_MODE_SELECT(const TIMER1_T *_Timer){
    if(TIMER1_TIMER_MODE == _Timer->TIMER1_MODE){
        TIMER1_TIMER_MODE_ENABLE();
    }
    else if(TIMER1_COUNTER_MODE == _Timer->TIMER1_MODE){
        TIMER1_COUNTER_MODE_ENABLE();
        if(TIMER1_ASYNC_COUNTER == _Timer->TIMER1_SYNC_SELECT){
            TIMER1_ASYNCHRONIZE_COUNTER_MODE_ENABLE();
        }
        else if(TIMER1_SYNC_COUNTER == _Timer->TIMER1_SYNC_SELECT){
            TIMER1_SYNCHRONIZE_COUNTER_MODE_ENABLE();
        }
        else{
            /*Nothing*/
        }
    }
    else{
        /*Nothing*/
    }    
}
void TMR1_ISR(void){
    /* The Flag of TMR0 Interrupt Must be Cleared*/
    TIMER1_INTERRUPT_FLAG_CLEAR();
    TMR1H = (timer1_preload) >> 8;
    TMR1L = (uint8)(timer1_preload);
    /*Check The Interrupt Handler Pointer To Function if it is equal to address of the Application Interrupt handler
     And It callback the function gets called every time this ISR executes*/
    if(TIMER1_INTERRUPT_HANDLER){
        TIMER1_INTERRUPT_HANDLER();
    }
}




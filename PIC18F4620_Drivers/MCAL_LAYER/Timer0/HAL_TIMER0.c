/* 
 * File:   HAL_TIMER0.c
 * Author: Moata
 *
 * Created on June 14, 2026, 6:34 PM
 */

#include "HAL_TIMER0.h"


static inline void TMR0_Prescaler_CFG(const TIMER0_T *_Timer);
static inline void TMR0_MODE_SELECT(const TIMER0_T *_Timer);
static inline void TMR0_REGISTER_SIZE_SELECT(const TIMER0_T *_Timer);
#ifdef TIMER0_INTERRUPT_FEATURE_ENABLE
    static void (*TIMER0_INTERRUPT_HANDLER)(void) = NULL;
#endif
static uint16 timer0_preload = 0;
    
    
Std_ReturnType TIMER0_INIT(const TIMER0_T *_Timer){
    Std_ReturnType ret = E_OK;
    if(NULL == _Timer){
        ret = E_NOT_OK;
    }
    else{
        TIMER0_DISABLE();
        TMR0_Prescaler_CFG(_Timer);
        TMR0_MODE_SELECT(_Timer);
        TMR0_REGISTER_SIZE_SELECT(_Timer);
        TMR0H = (_Timer->TIMER0_PRELOAD_VALUE) >> 8;
        TMR0L = (uint8)(_Timer->TIMER0_PRELOAD_VALUE);
        timer0_preload = _Timer->TIMER0_PRELOAD_VALUE;
#ifdef TIMER0_INTERRUPT_FEATURE_ENABLE
        TIMER0_INTERRUPT_ENABLE();
        TIMER0_INTERRUPT_FLAG_CLEAR();
        TIMER0_INTERRUPT_HANDLER = _Timer->TMR0_INTERRUPT_HANDLER;
#if  INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE
        INTERRUPT_Priority_Level_Enable();
        if(INTERRUPT_LOW_PRIORITY == _Timer->TMR0_priority){
            INTERRUPT_GlobalInterruptLowEnable();
            TIMER0_INTERRUPT_PRIORITY_LOW();
        }
        else if(INTERRUPT_HIGH_PRIORITY == _Timer->TMR0_priority){
            INTERRUPT_GlobalInterruptHighEnable();
            TIMER0_INTERRUPT_PRIORITY_HIGH();
        }
        else {/*Nothing*/}
#else
        INTERRUPT_GlobalInterruptEnable();
        INTERRUPT_Peripheral_Interrupt_Enable(); 
#endif
#endif
        TIMER0_ENABLE();
    }
    return ret;
}
Std_ReturnType TIMER0_DENIT(const TIMER0_T *_Timer){
    Std_ReturnType ret = E_OK;
    if(NULL == _Timer){
        ret = E_NOT_OK;
    }
    else{
        TIMER0_DISABLE();
    #ifdef TIMER0_INTERRUPT_FEATURE_ENABLE
        TIMER0_INTERRUPT_FLAG_CLEAR();
    #endif
    }
    return ret;
}
Std_ReturnType TIMER0_8BIT_WRITE_VALUE(const TIMER0_T *_Timer, uint8 value){
    Std_ReturnType ret = E_OK;
    if(NULL == _Timer){
        ret = E_NOT_OK;
    }
    else{
        TMR0L = (uint8)(value);
    }
    return ret;
}
Std_ReturnType TIMER0_8BIT_READ_VALUE(const TIMER0_T *_Timer, uint8 *value){
    Std_ReturnType ret = E_OK;
    if(NULL == _Timer){
        ret = E_NOT_OK;
    }
    else{
        *value = TMR0L;
    }
    return ret;    
}
Std_ReturnType TIMER0_16BIT_WRITE_VALUE(const TIMER0_T *_Timer, uint16 value){
    Std_ReturnType ret = E_OK;
    if(NULL == _Timer){
        ret = E_NOT_OK;
    }
    else{
        TMR0H = (value) >> 8;
        TMR0L = (uint8)(value);
    }
    return ret;    
}
Std_ReturnType TIMER0_16BIT_READ_VALUE(const TIMER0_T *_Timer, uint16 *value){
    Std_ReturnType ret = E_OK;
    uint8 L_tmr0 = 0, H_tmr0 = 0;
    if(NULL == _Timer){
        ret = E_NOT_OK;
    }
    else{
        L_tmr0 = TMR0L;
        H_tmr0 = TMR0H;
        *value = (uint16)((H_tmr0 << 8) + L_tmr0);
    }
    return ret;    
}


static inline void TMR0_MODE_SELECT(const TIMER0_T *_Timer){
    if(TIMER0_TIMER_MODE == _Timer->TIMER0_MODE){
        TIMER0_TIMER_MODE_ENABLE();
    }
    else if(TIMER0_COUNTER_MODE == _Timer->TIMER0_MODE){
        TIMER0_COUNTER_MODE_ENABLE();
        if(TIMER0_RISING_EDGE == _Timer->TIMER0_COUNTER_EDGE){
            TIMER0_COUNTER_MODE_RISING_EDGE();
        }
        else if(TIMER0_FALLING_EDGE == _Timer->TIMER0_COUNTER_EDGE){
            TIMER0_COUNTER_MODE_FALLING_EDGE();
        }
        else{
            /*Nothing*/
        }
    }
    else{
        /*Nothing*/
    }
}
static inline void TMR0_REGISTER_SIZE_SELECT(const TIMER0_T *_Timer){
    if(TIMER0_8BIT_CFG == _Timer->TIMER0_REGISTER_SIZE){
        TIMER0_8_BIT_CONFIGURATION();
    }
    else if(TIMER0_16BIT_CFG == _Timer->TIMER0_REGISTER_SIZE){
        TIMER0_16_BIT_CONFIGURATION();
    }
    else{
        /*Nothing*/
    }
}
static inline void TMR0_Prescaler_CFG(const TIMER0_T *_Timer){
    if(TIMER0_PRESCALER_ON == _Timer->PRESCALER_ENABLE){
        TIMER0_PRESCALER_ENABLE();
        T0CONbits.T0PS = _Timer->PRESCALER_VAL;
    }
    else if(TIMER0_PRESCALER_OFF == _Timer->PRESCALER_ENABLE){
        TIMER0_PRESCALER_DISABLE();
    }
    else{
        /*Nothing*/
    }
}


void TMR0_ISR(void){
    /* The Flag of TMR0 Interrupt Must be Cleared*/
    TIMER0_INTERRUPT_FLAG_CLEAR();
    TMR0H = (timer0_preload) >> 8;
    TMR0L = (uint8)(timer0_preload);
    /*Check The Interrupt Handler Pointer To Function if it is equal to address of the Application Interrupt handler
     And It callback the function gets called every time this ISR executes*/
    if(TIMER0_INTERRUPT_HANDLER){
        TIMER0_INTERRUPT_HANDLER();
    }
}
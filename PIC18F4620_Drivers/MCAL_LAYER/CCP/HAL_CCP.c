/* 
 * File:   HAL_CCP1.c
 * Author: Moata
 *
 * Created on July 5, 2026, 7:01 PM
 */

// Section: Includes
#include "HAL_CCP.h"

static inline void CCP_CFG_SELECT(const CCP_T *_CCP);
static inline void CCP_TIMER_SELECT_CFG(const CCP_T *_CCP);
#ifdef CCP1_INTERRUPT_FEATURE_ENABLE
    static void (*CCP1_INTERRUPT_HANDLER)(void) = NULL;
#endif
    
#ifdef CCP2_INTERRUPT_FEATURE_ENABLE
    static void (*CCP2_INTERRUPT_HANDLER)(void) = NULL;
#endif
    
Std_ReturnType CCP_INIT(const CCP_T *_CCP){
    Std_ReturnType ret = E_OK;
    if(NULL == _CCP){
        
    }
    else{
        CCP1_CONFIGURATION_SELECT(CCP_MODULE_DISABLE);
        CCP2_CONFIGURATION_SELECT(CCP_MODULE_DISABLE);
        CCP_CFG_SELECT(_CCP);
        CCP_TIMER_SELECT_CFG(_CCP);
        if(CCP1_SELECT == _CCP->CCP_SELECT){
#if CCP1_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
            CCP1_INTERRUPT_ENABLE();
            CCP1_INTERRUPT_FLAG_CLEAR();
            CCP1_INTERRUPT_HANDLER = _CCP->CCP1_INTERRUPT_HANDLER;
#if INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE
            INTERRUPT_Priority_Level_Enable();
            if(INTERRUPT_LOW_PRIORITY == _Timer->CCP1_priority){
                INTERRUPT_GlobalInterruptLowEnable();
                CCP1_INTERRUPT_PRIORITY_LOW();
            }
            else if(INTERRUPT_HIGH_PRIORITY == _Timer->CCP1_priority){
                INTERRUPT_GlobalInterruptHighEnable();
                CCP1_INTERRUPT_PRIORITY_HIGH();
            }
            else {/*Nothing*/}
#else
            INTERRUPT_GlobalInterruptEnable();
            INTERRUPT_Peripheral_Interrupt_Enable(); 
#endif
#endif
        }
        else if(CCP2_SELECT == _CCP->CCP_SELECT){
#if CCP2_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
            CCP2_INTERRUPT_ENABLE();
            CCP2_INTERRUPT_FLAG_CLEAR();
            CCP2_INTERRUPT_HANDLER = _CCP->CCP2_INTERRUPT_HANDLER;
#if INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE
            INTERRUPT_Priority_Level_Enable();
            if(INTERRUPT_LOW_PRIORITY == _Timer->CCP2_priority){
                INTERRUPT_GlobalInterruptLowEnable();
                CCP2_INTERRUPT_PRIORITY_LOW();
            }
            else if(INTERRUPT_HIGH_PRIORITY == _Timer->CCP2_priority){
                INTERRUPT_GlobalInterruptHighEnable();
                CCP2_INTERRUPT_PRIORITY_HIGH();
            }
            else {/*Nothing*/}
#else
            INTERRUPT_GlobalInterruptEnable();
            INTERRUPT_Peripheral_Interrupt_Enable(); 
#endif
#endif            
        }
        else{/*Nothing*/}
        ret = gpio_pin_initialize(&(_CCP->ccp_pin_cfg));
    }
    return ret;
}
Std_ReturnType CCP_DEINIT(const CCP_T *_CCP){
    Std_ReturnType ret = E_OK;
    if(NULL == _CCP){
        
    }
    else{
        if(CCP1_SELECT == _CCP->CCP_SELECT){
        CCP1_CONFIGURATION_SELECT(CCP_MODULE_DISABLE);
#ifdef CCP1_INTERRUPT_FEATURE_ENABLE
        CCP1_INTERRUPT_DISABLE();
#endif    
        }
        else if(CCP2_SELECT == _CCP->CCP_SELECT){
        CCP2_CONFIGURATION_SELECT(CCP_MODULE_DISABLE);
#ifdef CCP2_INTERRUPT_FEATURE_ENABLE
        CCP2_INTERRUPT_DISABLE();
#endif                
        }
        else{/*Nothing*/}          
    }
    return ret;
}

#if (CCP_MODE_CONFIGURATION_SELECT==CCP_CFG_CAPTURE_MODE_SELECT)
Std_ReturnType CCP_IS_CAPTURE_DATA_READY(const CCP_T *_CCP, uint8 *Capture_Status){
    Std_ReturnType ret = E_OK;
    if((NULL == _CCP) || (NULL == Capture_Status)){
        
    }
    else{
        if(CCP1_SELECT == _CCP->CCP_SELECT){
            if(CCP_CAPTURE_READY == PIR1bits.CCP1IF){
                *Capture_Status = CCP_CAPTURE_READY;
            }
            else{
                *Capture_Status = CCP_CAPTURE_NOT_READY;
            }
        }
        else if(CCP2_SELECT == _CCP->CCP_SELECT){
            if(CCP_CAPTURE_READY == PIR2bits.CCP2IF){
                *Capture_Status = CCP_CAPTURE_READY;
            }
            else{
                *Capture_Status = CCP_CAPTURE_NOT_READY;
            }
        }
        else{/*Nothing*/}           
    }
    return ret;
}
Std_ReturnType CCP_CAPTURE_MODE_READ_VALUE(const CCP_T *_CCP, uint16 *Capture_Value){
    Std_ReturnType ret = E_OK;
    CCP_REG_T Capture_temp1_value = {.CCP_LOW = 0, .CCP_HIGH = 0};
    CCP_REG_T Capture_temp2_value = {.CCP_LOW = 0, .CCP_HIGH = 0};
    if((NULL == _CCP) || (NULL == Capture_Value)){
        
    }
    else{
        if(CCP1_SELECT == _CCP->CCP_SELECT){
            Capture_temp1_value.CCP_LOW = CCPR1L;
            Capture_temp1_value.CCP_HIGH = CCPR1H;
            *Capture_Value = Capture_temp1_value.CCP_UINT16;
        }
        else if(CCP2_SELECT == _CCP->CCP_SELECT){
            Capture_temp2_value.CCP_LOW = CCPR2L;
            Capture_temp2_value.CCP_HIGH = CCPR2H;
            *Capture_Value = Capture_temp2_value.CCP_UINT16;
        }
        else{/*Nothing*/}             
    }
    return ret;
}
#endif
    
#if (CCP_MODE_CONFIGURATION_SELECT==CCP_CFG_COMPARE_MODE_SELECT)
Std_ReturnType CCP_IS_COMPARE_COMPLETE(const CCP_T *_CCP, uint8 *Compare_Status){
    Std_ReturnType ret = E_OK;
    if((NULL == _CCP) || (NULL == Compare_Status)){
        
    }
    else{
        if(CCP1_SELECT == _CCP->CCP_SELECT){
            if(CCP_CAPTURE_READY == PIR1bits.CCP1IF){
                *Compare_Status = CCP_COMPARE_READY;
            }
            else{
                *Compare_Status = CCP_COMPARE_NOT_READY;
            }
        }
        else if(CCP2_SELECT == _CCP->CCP_SELECT){
            if(CCP_CAPTURE_READY == PIR2bits.CCP2IF){
                *Compare_Status = CCP_COMPARE_READY;
            }
            else{
                *Compare_Status = CCP_COMPARE_NOT_READY;
            }
        }
        else{/*Nothing*/}  
    }
    return ret;
}
Std_ReturnType CCP_COMPARE_MODE_SET_VALUE(const CCP_T *_CCP, uint16 Compare_Value){
    Std_ReturnType ret = E_OK;
    CCP_REG_T Compare_temp1_value = {.CCP_LOW = 0, .CCP_HIGH = 0};
    Compare_temp1_value.CCP_UINT16 = Compare_Value;
    if(NULL == _CCP){
        
    }
    else{
        if(CCP1_SELECT == _CCP->CCP_SELECT){
            CCPR1L = Compare_temp1_value.CCP_LOW;
            CCPR1H = Compare_temp1_value.CCP_HIGH;
        }
        else if(CCP2_SELECT == _CCP->CCP_SELECT){
            CCPR2L = Compare_temp1_value.CCP_LOW;
            CCPR2H = Compare_temp1_value.CCP_HIGH;
        }
        else{/*Nothing*/}             
    }
    return ret;
}
#endif

#if (CCP_MODE_CONFIGURATION_SELECT==CCP_CFG_PWM_MODE_SELECT)
Std_ReturnType CCP_PWM_SET_DUTY_CYCLE(const CCP_T *_CCP, const uint8 _duty){
    Std_ReturnType ret = E_OK;
    uint16 duty_temp_value = 0;
    duty_temp_value = (uint16)((PR2 + 1)*4*(_duty/100.0));
    if(NULL == _CCP){
        
    }
    else{
        if(CCP1_SELECT == _CCP->CCP_SELECT){
            CCP1CONbits.DC1B = (uint8)(duty_temp_value & 0x03);
            CCPR1L = (uint8)(duty_temp_value >> 2);
        }
        else if(CCP2_SELECT == _CCP->CCP_SELECT){
            CCP2CONbits.DC2B = (uint8)(duty_temp_value & 0x03);
            CCPR2L = (uint8)(duty_temp_value >> 2);
        }
        else{/*Nothing*/}    
    return ret;
    }
}
Std_ReturnType CCP_PWM_GENERATE(const CCP_T *_CCP){
    Std_ReturnType ret = E_OK;
    if(NULL == _CCP){
        
    }
    else{
        if(CCP1_SELECT == _CCP->CCP_SELECT){
            CCP1CONbits.CCP1M = CCP_PWM_MODE;
        }
        else if(CCP2_SELECT == _CCP->CCP_SELECT){
            CCP2CONbits.CCP2M = CCP_PWM_MODE;
        }
    }
    return ret;
}
Std_ReturnType CCP_PWM_STOP(const CCP_T *_CCP){
    Std_ReturnType ret = E_OK;
    if(NULL == _CCP){
        
    }
    else{
        if(CCP1_SELECT == _CCP->CCP_SELECT){
            CCP1CONbits.CCP1M = CCP_MODULE_DISABLE;        
        }
        else if(CCP2_SELECT == _CCP->CCP_SELECT){
            CCP2CONbits.CCP2M = CCP_MODULE_DISABLE;        
        }
    }    
    return ret;
}
#endif

static inline void CCP_CFG_SELECT(const CCP_T *_CCP){
    if(CCP1_SELECT == _CCP->CCP_SELECT){
        switch(_CCP->mode_select){
            case CCP_CAPTURE_MODE_SELECT:
                switch(_CCP->CCP_mode_variant){
                    case CCP_CAPTURE_MODE_FALLING_EDGE:
                        CCP1_CONFIGURATION_SELECT(CCP_CAPTURE_MODE_FALLING_EDGE);
                        break;
                    case CCP_CAPTURE_MODE_RISING_EDGE:
                        CCP1_CONFIGURATION_SELECT(CCP_CAPTURE_MODE_RISING_EDGE);
                        break;
                    case CCP_CAPTURE_MODE_4TH_RISING_EDGE:
                        CCP1_CONFIGURATION_SELECT(CCP_CAPTURE_MODE_4TH_RISING_EDGE);
                        break;
                    case CCP_CAPTURE_MODE_16TH_RISING_EDGE:
                        CCP1_CONFIGURATION_SELECT(CCP_CAPTURE_MODE_16TH_RISING_EDGE);
                        break;
                }
                break;
            case CCP_COMPARE_MODE_SELECT:
                switch(_CCP->CCP_mode_variant){
                    case CCP_COMPARE_MODE_INIT_PIN_LOW_FORCE_HIGH:
                        CCP1_CONFIGURATION_SELECT(CCP_COMPARE_MODE_INIT_PIN_LOW_FORCE_HIGH);
                        break;
                    case CCP_COMPARE_MODE_INIT_PIN_HIGH_FORCE_LOW:
                        CCP1_CONFIGURATION_SELECT(CCP_COMPARE_MODE_INIT_PIN_HIGH_FORCE_LOW);
                        break;
                    case CCP_COMPARE_MODE_GENERATE_SW_INTERRUPT:
                        CCP1_CONFIGURATION_SELECT(CCP_COMPARE_MODE_GENERATE_SW_INTERRUPT);
                        break;
                    case CCP_COMPARE_MODE_TRIGGER_SPECIAL_EVENT:
                        CCP1_CONFIGURATION_SELECT(CCP_COMPARE_MODE_TRIGGER_SPECIAL_EVENT);
                        break;
                    case CCP_COMPARE_MODE_TOGGLE_OUTPUT:
                        CCP1_CONFIGURATION_SELECT(CCP_COMPARE_MODE_TOGGLE_OUTPUT);
                        break;
                }
                break;
            case CCP_PWM_MODE_SELECT:  
#if (CCP_MODE_CONFIGURATION_SELECT==CCP_CFG_PWM_MODE_SELECT)                
                PR2 = (uint8)((_XTAL_FREQ/(_CCP->PWM_Frequency * 4.0 * _CCP->CCP_POSTSCALE_VAL * _CCP->CCP_PRESCALER_VAL)) - 1);
#endif                
                break;
        }
    }
    else if(CCP2_SELECT == _CCP->CCP_SELECT){
        switch(_CCP->mode_select){
            case CCP_CAPTURE_MODE_SELECT:
                switch(_CCP->CCP_mode_variant){
                    case CCP_CAPTURE_MODE_FALLING_EDGE:
                        CCP2_CONFIGURATION_SELECT(CCP_CAPTURE_MODE_FALLING_EDGE);
                        break;
                    case CCP_CAPTURE_MODE_RISING_EDGE:
                        CCP2_CONFIGURATION_SELECT(CCP_CAPTURE_MODE_RISING_EDGE);
                        break;
                    case CCP_CAPTURE_MODE_4TH_RISING_EDGE:
                        CCP2_CONFIGURATION_SELECT(CCP_CAPTURE_MODE_4TH_RISING_EDGE);
                        break;
                    case CCP_CAPTURE_MODE_16TH_RISING_EDGE:
                        CCP2_CONFIGURATION_SELECT(CCP_CAPTURE_MODE_16TH_RISING_EDGE);
                        break;
                }
                break;
            case CCP_COMPARE_MODE_SELECT:
                switch(_CCP->CCP_mode_variant){
                    case CCP_COMPARE_MODE_INIT_PIN_LOW_FORCE_HIGH:
                        CCP2_CONFIGURATION_SELECT(CCP_COMPARE_MODE_INIT_PIN_LOW_FORCE_HIGH);
                        break;
                    case CCP_COMPARE_MODE_INIT_PIN_HIGH_FORCE_LOW:
                        CCP2_CONFIGURATION_SELECT(CCP_COMPARE_MODE_INIT_PIN_HIGH_FORCE_LOW);
                        break;
                    case CCP_COMPARE_MODE_GENERATE_SW_INTERRUPT:
                        CCP2_CONFIGURATION_SELECT(CCP_COMPARE_MODE_GENERATE_SW_INTERRUPT);
                        break;
                    case CCP_COMPARE_MODE_TRIGGER_SPECIAL_EVENT:
                        CCP2_CONFIGURATION_SELECT(CCP_COMPARE_MODE_TRIGGER_SPECIAL_EVENT);
                        break;
                    case CCP_COMPARE_MODE_TOGGLE_OUTPUT:
                        CCP2_CONFIGURATION_SELECT(CCP_COMPARE_MODE_TOGGLE_OUTPUT);
                        break;
                }
                break;
            case CCP_PWM_MODE_SELECT:    
#if (CCP_MODE_CONFIGURATION_SELECT==CCP_CFG_PWM_MODE_SELECT)                
                PR2 = (uint8)((_XTAL_FREQ/(_CCP->PWM_Frequency * 4.0 * _CCP->CCP_POSTSCALE_VAL * _CCP->CCP_PRESCALER_VAL)) - 1);
#endif                
                break;
        }        
    }
    else{/*Nothing*/}   
}
static inline void CCP_TIMER_SELECT_CFG(const CCP_T *_CCP){
    if(CCP1_AND_CCP2_TIMER3 == _CCP->ccp_timer_select){
        T3CONbits.T3CCP1 = 0;
        T3CONbits.T3CCP2 = 1;
    }
    else if(CCP2_TIMER3_CCP1_TIMER_1 == _CCP->ccp_timer_select){
        T3CONbits.T3CCP1 = 1;
        T3CONbits.T3CCP2 = 0;
    }
    else if(CCP1_AND_CCP2_TIMER1 == _CCP->ccp_timer_select){
        T3CONbits.T3CCP1 = 0;
        T3CONbits.T3CCP2 = 0;
    }
    else{/*Nothing*/}
}

Std_ReturnType CCP_CAPTURE_MODE_SET(const CCP_T *_CCP)
{
    if(_CCP == NULL)
        return E_NOT_OK;

    if(_CCP->CCP_SELECT == CCP1_SELECT)
    {
        CCP1_CONFIGURATION_SELECT(_CCP->CCP_mode_variant);
    }
    else
    {
        CCP2_CONFIGURATION_SELECT(_CCP->CCP_mode_variant);
    }

    return E_OK;
}

void CCP1_ISR(void){
    /* The Flag of CCP1 Interrupt Must be Cleared*/
    CCP1_INTERRUPT_FLAG_CLEAR();
    /*Check The Interrupt Handler Pointer To Function if it is equal to address of the Application Interrupt handler
     And It callback the function gets called every time this ISR executes*/
    if(CCP1_INTERRUPT_HANDLER){
        CCP1_INTERRUPT_HANDLER();
    }
}
void CCP2_ISR(void){
    /* The Flag of CCP1 Interrupt Must be Cleared*/
    CCP2_INTERRUPT_FLAG_CLEAR();
    /*Check The Interrupt Handler Pointer To Function if it is equal to address of the Application Interrupt handler
     And It callback the function gets called every time this ISR executes*/
    if(CCP2_INTERRUPT_HANDLER){
        CCP2_INTERRUPT_HANDLER();
    }
}



/* 
 * File:   HAL_ADC.h
 * Author: Moata
 *
 * Created on May 3, 2026, 2:59 PM
 */
#include "HAL_ADC.h"

static inline void ADC_INPUT_CHANNEL_CONFIG(ADC_CHANNEL_SELECT_T channel);
static inline void RESULT_SELECT_FORMAT(const ADC_CONFIG_T *ADC_CFG);
static inline void VOLTAGE_REF_SELECT(const ADC_CONFIG_T *ADC_CFG);

static void (*ADC_INTERRUPT_HANDLER)(void) = NULL;

/**
 * 
 * @param ADC_CFG
 * @return 
 */
Std_ReturnType ADC_INIT(const ADC_CONFIG_T *ADC_CFG){
    Std_ReturnType ret = E_OK;
    if(NULL == ADC_CFG){
        ret = E_NOT_OK;
    }
    else{
        /* Disable ADC*/
        ADC_CONVERTER_DISABLE();
        /* Configure ACQUISITION_TIME*/
        ADCON2bits.ACQT = ADC_CFG->ADC_ACQUISITION_TIME;
        /* Configure Conversion Clock*/
        ADCON2bits.ADCS = ADC_CFG->ADC_CONVERSION_CLOCK;
        /* Configure Channel*/
        ADCON0bits.CHS = ADC_CFG->ADC_CHANNEL_SELECT;
        ADC_INPUT_CHANNEL_CONFIG(ADC_CFG->ADC_CHANNEL_SELECT);
        /* Configure Interrupt*/
        #ifdef ADC_INTERRUPT_FEATURE_ENABLE
        INTERRUPT_GlobalInterruptEnable();
        INTERRUPT_Peripheral_Interrupt_Enable();
        ADC_INTERRUPT_ENABLE();
        #ifdef  INTERRUPT_PRIORITY_LEVELS_ENABLE
        if(INTERRUPT_LOW_PRIORITY == ADC_CFG->adc_priority){
            ADC_INTERRUPT_PRIORITY_LOW();
        }
        else if(INTERRUPT_HIGH_PRIORITY == ADC_CFG->adc_priority){
            ADC_INTERRUPT_PRIORITY_HIGH();
        }
        else {/*Nothing*/}
        #endif
        ADC_INTERRUPT_HANDLER = ADC_CFG->ADC_INTERRUPT_HANDLER;
        #endif
        /* Configure Result Format*/
        RESULT_SELECT_FORMAT(ADC_CFG);
        /* Configure Voltage Reference*/
        VOLTAGE_REF_SELECT(ADC_CFG);
        /* A/D Port Configuration Control Bits*/
        /* While We Turned OFF The PBADEN then PORTB from pin 0-4 is digital pins other pins will be in analog
         *  it depends on the application */
        
        /* Enable ADC*/
        ADC_CONVERTER_ENABLE();
    }
    return ret;
}
/**
 * 
 * @param ADC_CFG
 * @return 
 */
Std_ReturnType ADC_DEINIT(const ADC_CONFIG_T *ADC_CFG){
    Std_ReturnType ret = E_OK;
    if(NULL == ADC_CFG){
        ret = E_NOT_OK;
    }
    else{
        /* Disable The ADC*/
        ADC_CONVERTER_DISABLE();
        /* Configure Interrupt*/
        #ifdef ADC_INTERRUPT_FEATURE_ENABLE
        
        #endif
    }
    return ret;
}
/**
 * 
 * @param ADC_CFG
 * @param Channel
 * @return 
 */
Std_ReturnType ADC_CHANNEL_SELECT(const ADC_CONFIG_T *ADC_CFG, ADC_CHANNEL_SELECT_T channel){
    Std_ReturnType ret = E_OK;
    if(NULL == ADC_CFG){
        ret = E_NOT_OK;
    }
    else{
        ADCON0bits.CHS = channel;
        ADC_INPUT_CHANNEL_CONFIG(channel);
    }
    return ret;
}
/**
 * 
 * @param ADC_CFG
 * @return 
 */
Std_ReturnType ADC_START_CONV(const ADC_CONFIG_T *ADC_CFG){
    Std_ReturnType ret = E_OK;
    if(NULL == ADC_CFG){
        ret = E_NOT_OK;
    }
    else{
        ADC_START_CONVERSION();
    }
    return ret;
}
/**
 * @discription if the Status is True -> A/D conversion completed/not in progress GODONE = (0)
 *                               False ->  A/D conversion cycle in progress/ In Idle state GODONE = (1)
 * @param ADC_CFG
 * @param Conversion_Status
 * @return 
 */
Std_ReturnType ADC_CONV_STATUS(const ADC_CONFIG_T *ADC_CFG, uint8 *Conversion_Status){
    Std_ReturnType ret = E_OK;
    if((NULL == ADC_CFG) || (NULL == Conversion_Status)){
        ret = E_NOT_OK;
    }
    else{
       *Conversion_Status = (uint8)(!(ADCON0bits.GO_nDONE));
    }
    return ret;
}
/**
 * 
 * @param ADC_CFG
 * @param Conversion_Result
 * @return 
 */
Std_ReturnType ADC_CONV_RESULT(const ADC_CONFIG_T *ADC_CFG, uint16 *Conversion_Result){
    Std_ReturnType ret = E_OK;
    if((NULL == ADC_CFG) || (NULL == Conversion_Result)){
        ret = E_NOT_OK;
    }
    else{
        if(ADC_RESULT_RIGHT == ADC_CFG->RESULT_FORMAT){
            *Conversion_Result = (uint16)((ADRESH << 8) + ADRESL);
        }
        else if(ADC_RESULT_LEFT == ADC_CFG->RESULT_FORMAT){
            *Conversion_Result = (uint16)(((ADRESH << 8) + ADRESL) >> 6);
        }
        else{
            *Conversion_Result = (uint16)((ADRESH << 8) + ADRESL);
        }
    }
    return ret;
}
/**
 * 
 * @param ADC_CFG
 * @param Channel
 * @param Conversion_Status
 * @return 
 */
Std_ReturnType ADC_GET_CONV_BLOCKING(const ADC_CONFIG_T *ADC_CFG, ADC_CHANNEL_SELECT_T Channel, uint16 *Conversion_Result){
    Std_ReturnType ret = E_OK;
    if((NULL == ADC_CFG) || (NULL == Conversion_Result)){
        ret = E_NOT_OK;
    }
    else{
        /* Channel Select*/
        ret = ADC_CHANNEL_SELECT(ADC_CFG, Channel);
        /* Start Conversion*/
        ret = ADC_START_CONV(ADC_CFG);
        /* Wait till the Conversion is completed*/
        while(ADCON0bits.GO_nDONE);
        ret = ADC_CONV_RESULT(ADC_CFG, Conversion_Result);
    }
    return ret;
}
Std_ReturnType ADC_GET_CONV_INTERRUPT(const ADC_CONFIG_T *ADC_CFG, ADC_CHANNEL_SELECT_T Channel){
    Std_ReturnType ret = E_OK;
    if(NULL == ADC_CFG){
        ret = E_NOT_OK;
    }
    else{
        /* Channel Select*/
        ret = ADC_CHANNEL_SELECT(ADC_CFG, Channel);
        /* Start Conversion*/
        ret = ADC_START_CONV(ADC_CFG);
    }
    return ret;
}

/**
 * @discription Make The Pin Of the analog (INPUT)
 * @param ADC_CFG
 */
static inline void ADC_INPUT_CHANNEL_CONFIG(ADC_CHANNEL_SELECT_T channel){
    switch(channel){
        case ADC_CHANNEL_AN0:   SET_BIT(TRISA, _TRISA_RA0_POSITION); break; // Disable Digital Output Driver
        case ADC_CHANNEL_AN1:   SET_BIT(TRISA, _TRISA_RA1_POSITION); break; // Disable Digital Output Driver
        case ADC_CHANNEL_AN2:   SET_BIT(TRISA, _TRISA_RA2_POSITION); break; // Disable Digital Output Driver
        case ADC_CHANNEL_AN3:   SET_BIT(TRISA, _TRISA_RA3_POSITION); break; // Disable Digital Output Driver
        case ADC_CHANNEL_AN4:   SET_BIT(TRISA, _TRISA_RA5_POSITION); break; // Disable Digital Output Driver
        case ADC_CHANNEL_AN5:   SET_BIT(TRISE, _TRISE_RE0_POSITION); break; // Disable Digital Output Driver
        case ADC_CHANNEL_AN6:   SET_BIT(TRISE, _TRISE_RE1_POSITION); break; // Disable Digital Output Driver
        case ADC_CHANNEL_AN7:   SET_BIT(TRISE, _TRISE_RE2_POSITION); break; // Disable Digital Output Driver
        case ADC_CHANNEL_AN8:   SET_BIT(TRISB, _TRISB_RB2_POSITION); break; // Disable Digital Output Driver
        case ADC_CHANNEL_AN9:   SET_BIT(TRISB, _TRISB_RB3_POSITION); break; // Disable Digital Output Driver
        case ADC_CHANNEL_AN10:  SET_BIT(TRISB, _TRISB_RB1_POSITION); break; // Disable Digital Output Driver
        case ADC_CHANNEL_AN11:  SET_BIT(TRISB, _TRISB_RB4_POSITION); break; // Disable Digital Output Driver
        case ADC_CHANNEL_AN12:  SET_BIT(TRISB, _TRISB_RB0_POSITION); break; // Disable Digital Output Driver
    }
}

static inline void RESULT_SELECT_FORMAT(const ADC_CONFIG_T *ADC_CFG){
    switch(ADC_CFG->RESULT_FORMAT){
        case ADC_RESULT_RIGHT: ADC_RIGHT_JUSTIFIED(); break;
        case ADC_RESULT_LEFT: ADC_LEFT_JUSTIFIED(); break;
        default:    ADC_RIGHT_JUSTIFIED();
    }
}
static inline void VOLTAGE_REF_SELECT(const ADC_CONFIG_T *ADC_CFG){
    switch(ADC_CFG->VOLTAGE_REF){
        case ADC_VOLTAGE_REF_ENABLE: ADC_VOLTAGE_REFERENCE_ENABLE(); break;
        case ADC_VOLTAGE_REF_DISABLE: ADC_VOLTAGE_REFERENCE_DISABLE(); break;
        default:    ADC_VOLTAGE_REFERENCE_DISABLE();
    }
}


void ADC_ISR(void){
    /* The Flag of INT2 Must be Cleared*/
    ADC_INTERRUPT_FLAG_CLEAR();
    /*Check The Interrupt Handler Pointer To Function if it is equal to address of the Application Interrupt handler
     And It callback the function gets called every time this ISR executes*/
    if(ADC_INTERRUPT_HANDLER){
        ADC_INTERRUPT_HANDLER();
    }
}
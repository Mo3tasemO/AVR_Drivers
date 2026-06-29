/* 
 * File:   HAL_ADC.h
 * Author: Moata
 *
 * Created on May 3, 2026, 2:59 PM
 */

#ifndef HAL_ADC_H
#define	HAL_ADC_H

// Section: Includes
#include "../MCAL_LAYER/MCAL_STD_TYPES.h"
#include "pic18f4620.h"
#include "../MCAL_LAYER/GPIO/HAL_GPIO.h"
#include "HAL_ADC_CFG.h"
#include "../MCAL_LAYER/Interrupt/MCAL_INTERNAL_INTERRUPT.h"
// Section: Data Type Declarations

/**
 ADC Channel Select From (AN0-AN12) For PIC18F4620
 */
typedef enum {
    ADC_CHANNEL_AN0 = 0,
    ADC_CHANNEL_AN1,
    ADC_CHANNEL_AN2,
    ADC_CHANNEL_AN3,
    ADC_CHANNEL_AN4,
    ADC_CHANNEL_AN5,
    ADC_CHANNEL_AN6,
    ADC_CHANNEL_AN7,
    ADC_CHANNEL_AN8,
    ADC_CHANNEL_AN9,
    ADC_CHANNEL_AN10,
    ADC_CHANNEL_AN11,
    ADC_CHANNEL_AN12,
}ADC_CHANNEL_SELECT_T;
 
typedef enum {
    ADC_0_TAD = 0,
    ADC_2_TAD,
    ADC_4_TAD,
    ADC_6_TAD,
    ADC_8_TAD,
    ADC_12_TAD,
    ADC_16_TAD,
    ADC_20_TAD      
}ADC_ACQUISITION_TIME_T;

typedef enum {
    ADC_CONVERSION_CLOCK_DIV_2 = 0,
    ADC_CONVERSION_CLOCK_DIV_8,
    ADC_CONVERSION_CLOCK_DIV_32,
    ADC_CONVERSION_CLOCK_FRC,   // Derived From Internal Oscillator
    ADC_CONVERSION_CLOCK_DIV_4,
    ADC_CONVERSION_CLOCK_DIV_16,
    ADC_CONVERSION_CLOCK_DIV_64        
}ADC_CONVERSION_CLOCK_T;

typedef struct {
    #ifdef ADC_INTERRUPT_FEATURE_ENABLE
    void (* ADC_INTERRUPT_HANDLER)(void);
    interrupt_priority_t adc_priority;
    #endif
    ADC_ACQUISITION_TIME_T  ADC_ACQUISITION_TIME; /* @ref ADC_ACQUISITION_TIME_T */
    ADC_CONVERSION_CLOCK_T   ADC_CONVERSION_CLOCK; /* @ref ADC_CONVERSION_TIME_T */
    ADC_CHANNEL_SELECT_T    ADC_CHANNEL_SELECT; /* @ref ADC_CHANNEL_SELECT_T */
    uint8 VOLTAGE_REF :1;                       /* Voltage Reference Configuration*/
    uint8 RESULT_FORMAT : 1;                    /* Result Format Selection*/
    uint8 ADC_RESERVED : 6;
}ADC_CONFIG_T;

// Section: Macro Declarations

#define ADC_AN0_ANALOG_FUNCTIONALITY    0x0E
#define ADC_AN1_ANALOG_FUNCTIONALITY    0x0D
#define ADC_AN2_ANALOG_FUNCTIONALITY    0x0C
#define ADC_AN3_ANALOG_FUNCTIONALITY    0x0B
#define ADC_AN4_ANALOG_FUNCTIONALITY    0x0A
#define ADC_AN5_ANALOG_FUNCTIONALITY    0x09
#define ADC_AN6_ANALOG_FUNCTIONALITY    0x08
#define ADC_AN7_ANALOG_FUNCTIONALITY    0x07
#define ADC_AN8_ANALOG_FUNCTIONALITY    0x06
#define ADC_AN9_ANALOG_FUNCTIONALITY    0x05
#define ADC_AN10_ANALOG_FUNCTIONALITY   0x04
#define ADC_AN11_ANALOG_FUNCTIONALITY   0x03
#define ADC_AN12_ANALOG_FUNCTIONALITY   0x02
#define ADC_ALL_ANALOG_FUNCTIONALITY    0x01
#define ADC_ALL_DIGITAL_FUNCTIONALITY   0x0F

#define ADC_RESULT_RIGHT    0x01U
#define ADC_RESULT_LEFT    0x00U

#define ADC_VOLTAGE_REF_ENABLE  0x01U
#define ADC_VOLTAGE_REF_DISABLE  0x00U
// Section: Macro Functions Declarations


/**
 * ADON = 1 -> ADC Peripheral is enable, ADON = 0 -> -> ADC Peripheral is disable
 */
#define ADC_CONVERTER_ENABLE() (ADCON0bits.ADON = 1)
#define ADC_CONVERTER_DISABLE() (ADCON0bits.ADON = 0)



/**
 * A/D conversion cycle in progress if it's = 1, A/D conversion completed/not in progress/idle if it's = 0
 */
#define ADC_CONVERSION_STATUS() (ADCON0bits.GO_nDONE)
#define ADC_START_CONVERSION() (ADCON0bits.GODONE = 1)  /*Set GODONE Bit To Start Conversion*/

#define ADC_STOP_CONVERSION() (ADCON0bits.GODONE = 0)   /*Clear GODONE Bit Means The Conversion is completed/Idle*/


/**
 * @brief   ADC_VOLTAGE_REFERENCE_Configuration
 * @note    ADC_VOLTAGE_REFERENCE_ENABLE -> Then You Should Connect External Supply in AN2 & AN3
 *          ADC_VOLTAGE_REFERENCE_DISABLE -> Then You Will Use Your AVDD, AVSS Of the PIC
 */
#define ADC_VOLTAGE_REFERENCE_ENABLE()  do{ ADCON1bits.VCFG0 = 1;   \
                                            ADCON1bits.VCFG1 = 1;   \
                                           }while(0);

#define ADC_VOLTAGE_REFERENCE_DISABLE()  do{ ADCON1bits.VCFG0 = 0;   \
                                            ADCON1bits.VCFG1 = 0;   \
                                           }while(0);

/* The ADC is 10bit ADC Have Resolution 10 bit then the result is 10bit stored in 2 registers (ADRESH, ADRESL)*/
#define ADC_RIGHT_JUSTIFIED() (ADCON2bits.ADFM = 1) // Take All ADRESL and First 2 bits from ADRESH
#define ADC_LEFT_JUSTIFIED() (ADCON2bits.ADFM = 0)  // Take All ADRESH and First 2 bits from ADRESL from left

#define ADC_ANALOG_DIGITAL_CONFIG(_CONFIG)  (ADCON1bits.PCFG = _CONFIG)

// Section: Function Declarations

Std_ReturnType ADC_INIT(const ADC_CONFIG_T *ADC_CFG);
Std_ReturnType ADC_DEINIT(const ADC_CONFIG_T *ADC_CFG);
Std_ReturnType ADC_CHANNEL_SELECT(const ADC_CONFIG_T *ADC_CFG, ADC_CHANNEL_SELECT_T channel);
Std_ReturnType ADC_START_CONV(const ADC_CONFIG_T *ADC_CFG);
Std_ReturnType ADC_CONV_STATUS(const ADC_CONFIG_T *ADC_CFG, uint8 *Conversion_Status);
Std_ReturnType ADC_CONV_RESULT(const ADC_CONFIG_T *ADC_CFG, uint16 *Conversion_Result);
Std_ReturnType ADC_GET_CONV_BLOCKING(const ADC_CONFIG_T *ADC_CFG, ADC_CHANNEL_SELECT_T Channel, uint16 *Conversion_Result);
Std_ReturnType ADC_GET_CONV_INTERRUPT(const ADC_CONFIG_T *ADC_CFG, ADC_CHANNEL_SELECT_T Channel);



#endif	/* HAL_ADC_H */


/*
 * HAL_ADC.h
 *
 *  Created on: Feb 7, 2026
 *      Author: Moata
 */

#ifndef MCAL_LAYER_ADC_HAL_ADC_H_
#define MCAL_LAYER_ADC_HAL_ADC_H_


/* Section : Includes */

#include "HAL_ADC_CFG.h"
#include "../GPIO/HAL_GPIO.h"
#include "../INTERRUPT/HAL_INTERRUPT.h"

/* Section: Macro Declarations */



#define	ACSR	(*(volatile uint8*)(0x28))
#define	ADMUX	(*(volatile uint8*)(0x27))
#define	ADCSRA	(*(volatile uint8*)(0x26))
#define	ADCH	(*(volatile uint8*)(0x25))
#define	ADCL	(*(volatile uint8*)(0x24))
#define	SFIOR	(*(volatile uint8*)(0x50))


/*ADC Multiplexer Selection Register*/
#define MUX0	0
#define MUX1	1
#define MUX2	2
#define MUX3	3
#define MUX4	4
#define	ADLAR	5
#define REFS0	6
#define REFS1	7
/*ADC Control and Status Register A*/
#define ADPS0	0
#define ADPS1	1
#define ADPS2	2
#define ADIE	3
#define ADIF	4
#define ADATE	5
#define ADSC	6
#define ADEN	7


/* Section: Macro Functions Declarations */


#define		ADC_INTERNAL_VOLTAGE_REFERENCE_OFF()	do{CLEAR_BIT(ADMUX, REFS0);\
													   CLEAR_BIT(ADMUX, REFS1);\
													}while(0)

#define		ADC_AVCC_VOLTAGE_REFERENCE()			do{SET_BIT(ADMUX, REFS0);\
													   CLEAR_BIT(ADMUX, REFS1);\
													}while(0)

#define		ADC_INTERNAL_VOLTAGE_REFERENCE_ON()		do{SET_BIT(ADMUX, REFS0);\
													SET_BIT(ADMUX, REFS1);\
													}while(0)

#define		ADC_LEFT_ADJUST_RESULT()				SET_BIT(ADMUX, ADLAR)
#define		ADC_RIGHT_ADJUST_RESULT()				CLEAR_BIT(ADMUX, ADLAR)
#define		ADC_ENABLE()							SET_BIT(ADCSRA, ADEN)
#define		ADC_DISABLE()							CLEAR_BIT(ADCSRA, ADEN)
#define		ADC_START_CONVERSION()					SET_BIT(ADCSRA, ADSC)
#define		ADC_AUTO_TRIGGER_ENABLE()				SET_BIT(ADCSRA, ADATE)
#define		ADC_AUTO_TRIGGER_FREE_RUNNING_MODE()	do{CLEAR_BIT(SFIOR, 5);\
													   CLEAR_BIT(SFIOR, 6);\
													   CLEAR_BIT(SFIOR, 7);\
													}while(0)
#define		ADC_CLEAR_INTERRUPT_FLAG()				SET_BIT(ADCSRA, ADIF)


#if ADC_INTERRUPT_FEATURE_ENABLE
	#define		ADC_INTERRUPT_ENABLE()				SET_BIT(ADCSRA, ADIE)	// Global Interrupt Must Be Enable ->SREG,I-bit
	#define		ADC_INTERRUPT_DISABLE()				CLEAR_BIT(ADCSRA, ADIE)
#endif


/* Section: Data Type Declarations */
typedef enum {
		ADC_CHANNEL_0 = 0,
		ADC_CHANNEL_1,
		ADC_CHANNEL_2,
		ADC_CHANNEL_3,
		ADC_CHANNEL_4,
		ADC_CHANNEL_5,
		ADC_CHANNEL_6,
		ADC_CHANNEL_7,
}ADC_CHANNEL_SELECT_T;

typedef enum {
	ADC_PRESCALER_DIV_2 = 1,
	ADC_PRESCALER_DIV_4,
	ADC_PRESCALER_DIV_8,
	ADC_PRESCALER_DIV_16,
	ADC_PRESCALER_DIV_32,
	ADC_PRESCALER_DIV_64,
	ADC_PRESCALER_DIV_128
}ADC_PRESCALER_SELECT_T;

typedef enum {
	INTERNAL_VOLTAGE_REFERENCE_ON = 0,
	INTERNAL_VOLTAGE_REFERENCE_OFF,
	AVCC_VOLTAGE_REFERENCE
}ADC_VOLTAGE_REFERENCE_CONFIG_T;
typedef enum {
	ADC_RESULT_RIGHT_ADJUST = 0,
	ADC_RESULT_LEFT_ADJUST
}ADC_RESULT_ADJUST_T;
typedef enum {
	SINGLE_CONVERSION = 0,
	AUTO_TRIGGER_ENABLE,
	AUTO_TRIGGER_FREE_RUNNING_MODE
}ADC_SOURCE_ADJUST_T;

typedef struct {
#if ADC_INTERRUPT_FEATURE_ENABLE
	void (* ADC_InterruptHandler)(void);
#endif
	ADC_CHANNEL_SELECT_T Channel_Select;
	ADC_PRESCALER_SELECT_T Prescaler_Select;
	ADC_RESULT_ADJUST_T	Result_Format;
	ADC_VOLTAGE_REFERENCE_CONFIG_T Voltage_Config;
	ADC_SOURCE_ADJUST_T ADC_Source_Config;
}ADC_CONFIG_T;

/* Section: Function Declarations */

/**
 * @author Mo3
 * @brief This Function Initialize the ADC Peripheral And Adjust
 * The Configuration of the ADC Depending On the User Selection
 * @param ADC_T-> Struct Has The Configuration of ADC
 * @return	ret-> if it E_OK (means function succeeded), E_NOT_OK (means function doesnt succeeded)
 * */
Std_ReturnType ADC_INIT(const ADC_CONFIG_T *ADC_T);
/**
 * @author Mo3
 * @brief This Function Deinitialize the ADC Peripheral
 * @param ADC_T-> Struct Has The Configuration of ADC
 * @return	ret-> if it E_OK (means function succeeded), E_NOT_OK (means function doesnt succeeded)
 * */
Std_ReturnType ADC_DEINIT(const ADC_CONFIG_T *ADC_T);
/**
 * @author Mo3
 * @brief This Function Start The Conversion Of ADC
 * @param ADC_T-> Struct Has The Configuration of ADC
 * @return	ret-> if it E_OK (means function succeeded), E_NOT_OK (means function doesnt succeeded)
 * */
Std_ReturnType ADC_StartConversion(const ADC_CONFIG_T *ADC_T);
/**
 * @author Mo3
 * @brief This Function Tells You If The Conversion Completed Or Not
 * @param ADC_T-> Struct Has The Configuration of ADC
 * @param Conversion_Status-> Pointer, Points to the Return Value From the ADC_Start_Converion_BIT
 * @return	ret-> if it E_OK (means function succeeded), E_NOT_OK (means function doesnt succeeded)
 * */
Std_ReturnType ADC_IS_CONVERSION_DONE(const ADC_CONFIG_T *ADC_T, uint8 *Conversion_Status);
/**
 * @author Mo3
 * @brief This Function gets the result of conversion from ADCH/ADCL
 * @param ADC_T-> Struct Has The Configuration of ADC
 * @return	ret-> if it E_OK (means function succeeded), E_NOT_OK (means function doesnt succeeded)
 * */
Std_ReturnType ADC_GET_CONVERSION_RESULT(const ADC_CONFIG_T *ADC_T, uint16 *Conversion_Result);












#endif /* MCAL_LAYER_ADC_HAL_ADC_H_ */

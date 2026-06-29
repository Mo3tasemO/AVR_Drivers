/*
 * HAL_ADC.c
 *
 *  Created on: Feb 7, 2026
 *      Author: Moata
 */
#include "HAL_ADC.h"


static void ADC_CHANNEL_SELECT(ADC_CHANNEL_SELECT_T Channel);
static void ADC_PRESCALER_SELECT(ADC_PRESCALER_SELECT_T Prescaler);
static void ADC_VOLTAGE_REFERENCE_CONFIG(ADC_VOLTAGE_REFERENCE_CONFIG_T Voltage_config);
static void ADC_RESULT_FORMAT(ADC_RESULT_ADJUST_T result_f);
static void ADC_SOURCE_ADJUST(ADC_SOURCE_ADJUST_T adc_Source);
#if ADC_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
	static void (*ADC_InterruptHandler)(void) = NULL;
#endif



/**
 * @author Mo3
 * @brief This Function Initialize the ADC Peripheral And Adjust
 * The Configuration of the ADC Depending On the User Selection
 * @param ADC_T-> Struct Has The Configuration of ADC
 * @return	ret-> if it E_OK (means function succeeded), E_NOT_OK (means function doesnt succeeded)
 * */
Std_ReturnType ADC_INIT(const ADC_CONFIG_T *ADC_T){
	Std_ReturnType ret = E_OK;
	if(NULL == ADC_T){
		ret = E_NOT_OK;
	}
	else{
		ADC_DISABLE();
		ADC_PRESCALER_SELECT(ADC_T->Prescaler_Select);
		ADC_CHANNEL_SELECT(ADC_T->Channel_Select);
	#if ADC_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
		INTERRUPT_GLOBAL_ENABLE();
		ADC_INTERRUPT_ENABLE();
		ADC_CLEAR_INTERRUPT_FLAG();
		ADC_InterruptHandler = ADC_T->ADC_InterruptHandler;
	#endif
		ADC_VOLTAGE_REFERENCE_CONFIG(ADC_T->Voltage_Config);
		ADC_RESULT_FORMAT(ADC_T->Result_Format);
		ADC_ENABLE();
	}
	return ret;
}
/**
 * @author Mo3
 * @brief This Function Deinitialize the ADC Peripheral
 * @param ADC_T-> Struct Has The Configuration of ADC
 * @return	ret-> if it E_OK (means function succeeded), E_NOT_OK (means function doesnt succeeded)
 * */
Std_ReturnType ADC_DEINIT(const ADC_CONFIG_T *ADC_T){
	Std_ReturnType ret = E_OK;
	if(NULL == ADC_T){
		ret = E_NOT_OK;
	}
	else{
		ADC_DISABLE();
	#if ADC_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
		ADC_INTERRUPT_DISABLE();
	#endif
	}
	return ret;
}
/**
 * @author Mo3
 * @brief This Function Start The Conversion Of ADC
 * @param ADC_T-> Struct Has The Configuration of ADC
 * @return	ret-> if it E_OK (means function succeeded), E_NOT_OK (means function doesnt succeeded)
 * */
Std_ReturnType ADC_StartConversion(const ADC_CONFIG_T *ADC_T){
	Std_ReturnType ret = E_OK;
	if(NULL == ADC_T){
		ret = E_NOT_OK;
	}
	else{
		ADC_CLEAR_INTERRUPT_FLAG();
		ADC_SOURCE_ADJUST(ADC_T->ADC_Source_Config);
	}
	return ret;
}
/**
 * @author Mo3
 * @brief This Function Tells You If The Conversion Completed Or Not
 * @param ADC_T-> Struct Has The Configuration of ADC
 * @param Conversion_Status-> Pointer, Points to the Return Value From the ADC_Start_Converion_BIT
 * @return	ret-> if it E_OK (means function succeeded), E_NOT_OK (means function doesnt succeeded)
 * */
Std_ReturnType ADC_IS_CONVERSION_DONE(const ADC_CONFIG_T *ADC_T, uint8 *Conversion_Status){
	Std_ReturnType ret = E_OK;
	if((NULL == ADC_T) || (NULL == Conversion_Status)){
		ret = E_NOT_OK;
	}
	else{
		*Conversion_Status = READ_BIT(ADCSRA, ADSC);	// If this bit is 1 then conversion still in progress
	}
	return ret;
}

/**
 * @author Mo3
 * @brief This Function gets the result of conversion from ADCH/ADCL
 * @param ADC_T-> Struct Has The Configuration of ADC
 * @return	ret-> if it E_OK (means function succeeded), E_NOT_OK (means function doesnt succeeded)
 * */
Std_ReturnType ADC_GET_CONVERSION_RESULT(const ADC_CONFIG_T *ADC_T, uint16 *Conversion_Result){
	Std_ReturnType ret = E_OK;
	if((NULL == ADC_T) || (NULL == Conversion_Result)){
		ret = E_NOT_OK;
	}
	else{
		while(READ_BIT(ADCSRA, ADSC) != 0);
		if(ADC_RESULT_RIGHT_ADJUST == ADC_T->Result_Format){
			*Conversion_Result = (uint16)(ADCL + (ADCH << 8));
		}
		else if(ADC_RESULT_LEFT_ADJUST == ADC_T->Result_Format){
			*Conversion_Result = (uint16)((ADCL + (ADCH << 8)) >> 6);
		}
		else{
			*Conversion_Result = (uint16)(ADCL + (ADCH << 8));
		}
	}
	return ret;
}






static void ADC_RESULT_FORMAT(ADC_RESULT_ADJUST_T result_f){
	switch(result_f){
		case ADC_RESULT_RIGHT_ADJUST:
			ADC_RIGHT_ADJUST_RESULT();
			break;
		case ADC_RESULT_LEFT_ADJUST:
			ADC_LEFT_ADJUST_RESULT();
			break;
	}
}
static void ADC_CHANNEL_SELECT(ADC_CHANNEL_SELECT_T Channel){
	switch(Channel){
		case ADC_CHANNEL_0:
			CLEAR_BIT(ADMUX, MUX0);
			CLEAR_BIT(ADMUX, MUX1);
			CLEAR_BIT(ADMUX, MUX2);
			CLEAR_BIT(ADMUX, MUX3);
			CLEAR_BIT(ADMUX, MUX4);
			break;
		case ADC_CHANNEL_1:
			SET_BIT(ADMUX, MUX0);
			CLEAR_BIT(ADMUX, MUX1);
			CLEAR_BIT(ADMUX, MUX2);
			CLEAR_BIT(ADMUX, MUX3);
			CLEAR_BIT(ADMUX, MUX4);
			break;
		case ADC_CHANNEL_2:
			CLEAR_BIT(ADMUX, MUX0);
			SET_BIT(ADMUX, MUX1);
			CLEAR_BIT(ADMUX, MUX2);
			CLEAR_BIT(ADMUX, MUX3);
			CLEAR_BIT(ADMUX, MUX4);
			break;
		case ADC_CHANNEL_3:
			SET_BIT(ADMUX, MUX0);
			SET_BIT(ADMUX, MUX1);
			CLEAR_BIT(ADMUX, MUX2);
			CLEAR_BIT(ADMUX, MUX3);
			CLEAR_BIT(ADMUX, MUX4);
			break;
		case ADC_CHANNEL_4:
			CLEAR_BIT(ADMUX, MUX0);
			CLEAR_BIT(ADMUX, MUX1);
			SET_BIT(ADMUX, MUX2);
			CLEAR_BIT(ADMUX, MUX3);
			CLEAR_BIT(ADMUX, MUX4);
			break;
		case ADC_CHANNEL_5:
			SET_BIT(ADMUX, MUX0);
			CLEAR_BIT(ADMUX, MUX1);
			SET_BIT(ADMUX, MUX2);
			CLEAR_BIT(ADMUX, MUX3);
			CLEAR_BIT(ADMUX, MUX4);
			break;
		case ADC_CHANNEL_6:
			CLEAR_BIT(ADMUX, MUX0);
			SET_BIT(ADMUX, MUX1);
			SET_BIT(ADMUX, MUX2);
			CLEAR_BIT(ADMUX, MUX3);
			CLEAR_BIT(ADMUX, MUX4);
			break;
		case ADC_CHANNEL_7:
			SET_BIT(ADMUX, MUX0);
			SET_BIT(ADMUX, MUX1);
			SET_BIT(ADMUX, MUX2);
			CLEAR_BIT(ADMUX, MUX3);
			CLEAR_BIT(ADMUX, MUX4);
			break;
		}
}
static void ADC_PRESCALER_SELECT(ADC_PRESCALER_SELECT_T Prescaler){
	switch(Prescaler){
		case ADC_PRESCALER_DIV_2:
			SET_BIT(ADCSRA, ADPS0);
			CLEAR_BIT(ADCSRA, ADPS1);
			CLEAR_BIT(ADCSRA, ADPS2);
			break;
		case ADC_PRESCALER_DIV_4:
			CLEAR_BIT(ADCSRA, ADPS0);
			SET_BIT(ADCSRA, ADPS1);
			CLEAR_BIT(ADCSRA, ADPS2);
			break;
		case ADC_PRESCALER_DIV_8:
			SET_BIT(ADCSRA, ADPS0);
			SET_BIT(ADCSRA, ADPS1);
			CLEAR_BIT(ADCSRA, ADPS2);
			break;
		case ADC_PRESCALER_DIV_16:
			CLEAR_BIT(ADCSRA, ADPS0);
			CLEAR_BIT(ADCSRA, ADPS1);
			SET_BIT(ADCSRA, ADPS2);
			break;
		case ADC_PRESCALER_DIV_32:
			SET_BIT(ADCSRA, ADPS0);
			CLEAR_BIT(ADCSRA, ADPS1);
			SET_BIT(ADCSRA, ADPS2);
			break;
		case ADC_PRESCALER_DIV_64:
			CLEAR_BIT(ADCSRA, ADPS0);
			SET_BIT(ADCSRA, ADPS1);
			SET_BIT(ADCSRA, ADPS2);
			break;
		case ADC_PRESCALER_DIV_128:
			SET_BIT(ADCSRA, ADPS0);
			SET_BIT(ADCSRA, ADPS1);
			SET_BIT(ADCSRA, ADPS2);
			break;
		}
}
static void ADC_VOLTAGE_REFERENCE_CONFIG(ADC_VOLTAGE_REFERENCE_CONFIG_T Voltage_config){
	switch(Voltage_config){
		case INTERNAL_VOLTAGE_REFERENCE_ON:
			ADC_INTERNAL_VOLTAGE_REFERENCE_ON();
			break;
		case INTERNAL_VOLTAGE_REFERENCE_OFF:
			ADC_INTERNAL_VOLTAGE_REFERENCE_OFF();
			break;
		case AVCC_VOLTAGE_REFERENCE:
			ADC_AVCC_VOLTAGE_REFERENCE();
			break;
	}
}
static void ADC_SOURCE_ADJUST(ADC_SOURCE_ADJUST_T adc_Source){
	switch(adc_Source){
		case SINGLE_CONVERSION:
			ADC_START_CONVERSION();
			break;
		case AUTO_TRIGGER_ENABLE:

			break;
		case AUTO_TRIGGER_FREE_RUNNING_MODE:

			break;
	}
}
#if ADC_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
	void __vector_16 (void)__attribute__((signal)) ;
	void __vector_16 (void)
	{
		if(NULL != ADC_InterruptHandler){
			ADC_InterruptHandler();
		}
	}
#endif

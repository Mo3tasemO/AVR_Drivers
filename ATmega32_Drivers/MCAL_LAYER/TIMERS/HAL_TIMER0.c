/*
 * HAL_TIMER.c
 *
 *  Created on: Feb 7, 2026
 *      Author: Moata
 */

#include "HAL_TIMER0.h"

#if TIMER0_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
void (*TIMER0_INTERRUPT_OVF)(void) = NULL;
void (*TIMER0_INTERRUPT_COMP)(void) = NULL;
#endif
static void TIMER0_MODE_SELECT(TIMER0_MODE_SELECT_T Mode);
static void TIMER0_COMPARE_OUTPUT_MODE_SELECT(TIMER0_COMPARE_OUTPUT_MODE_SELECT_T Com_mode,
		TIMER0_COMPARE_OUTPUT_OPERATION_SELECT_T Com_operation);
static void TIMER0_CLOCK_SELECT(TIMER0_CLOCK_SELECT_T Clock_S, TIMER0_PRESCALER_SELECT_T Prescaler_S);



Std_ReturnType TIMER0_INIT(const TIMER0_t *_Timer){
	Std_ReturnType ret = E_OK;
	if(NULL == _Timer){
		ret = E_NOT_OK;
	}
	else{
		pin_config_t oc0_pin = {
				.pin = GPIO_PIN3,
				.port = PORTB_INDEX,
				.direction = GPIO_DIRECTION_OUTPUT,
				.logic = GPIO_LOW,
		};
		ret = GPIO_PIN_INIT(&oc0_pin);
		TIMER0_MODE_SELECT(_Timer->Mode_Select);
		TIMER0_COMPARE_OUTPUT_MODE_SELECT(_Timer->COM_Mode, _Timer->COM_Operaion);
		TIMER0_CLOCK_SELECT(_Timer->Clock_Select, _Timer->Prescaler);
		TCNT0 = _Timer->Preload;
#if TIMER0_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
		SET_BIT(SREG, I_BIT);
		TIMER0_OVERFLOW_INTERRUPT_ENABLE();
		TIMER0_INTERRUPT_OVF = _Timer->TIMER0_INTERRUPT_HANDLER_OVF;
#endif
	}
	return ret;
}

Std_ReturnType TIMER0_WRITE_VALUE(const TIMER0_t *_Timer, uint8 Preload_Val){
	Std_ReturnType ret = E_OK;
	if(NULL == _Timer){
		ret = E_NOT_OK;
	}
	else{
		TCNT0 = Preload_Val;
	}
	return ret;
}
Std_ReturnType TIMER0_READ_VALUE(const TIMER0_t *_Timer, uint8 *ret_value){
	Std_ReturnType ret = E_OK;
	if((NULL == _Timer) || (NULL == ret_value)){
		ret = E_NOT_OK;
	}
	else{
		*ret_value = TCNT0;
	}
	return ret;
}
void TIMER0_GENERATE_PWM(uint8 OC0_Val){
		OCR0 = OC0_Val;
}


static void TIMER0_MODE_SELECT(TIMER0_MODE_SELECT_T Mode){
	switch(Mode){
	case TIMER0_NORMAL_MODE:
		TIMER0_NORMAL_MODE_ENABLE();
		break;
	case TIMER0_PWM_PHASE_CORRECT:
		TIMER0_PWM_PHASE_CORRECT_ENABLE();
		break;
	case TIMER0_CLEAR_TIMER_ON_COMPARE_MATCH:
		TIMER0_CLEAR_TIMER_ON_COMPARE_MATCH_ENABLE();
		break;
	case TIMER0_FAST_PWM:
		TIMER0_FAST_PWM_ENABLE();
		break;
	}
}

static void TIMER0_COMPARE_OUTPUT_MODE_SELECT(TIMER0_COMPARE_OUTPUT_MODE_SELECT_T Com_mode,
		TIMER0_COMPARE_OUTPUT_OPERATION_SELECT_T Com_operation){
	switch(Com_mode){
	case TIMER0_NON_PWM_MODE:
		if(NORMAL_OPERATION == Com_operation){
			TIMER0_NORMAL_OPERATION();
		}
		else if(TOGGLE_OC0 == Com_operation){
			TIMER0_NON_PWM_MODE_TOGGLE_OC0_COMPARE_MATCH();
		}
		else if(CLEAR_OC0 == Com_operation){
			TIMER0_CLEAR_OC0_COMPARE_MATCH();
		}
		else if(SET_OC0 == Com_operation){
			TIMER0_SET_OC0_COMPARE_MATCH();
		}
		else{
			TIMER0_NORMAL_OPERATION();
		}
		break;
	case TIMER0_FAST_PWM_MODE:
		if(NORMAL_OPERATION == Com_operation){
			TIMER0_NORMAL_OPERATION();
		}
		else if(CLEAR_OC0 == Com_operation){
			TIMER0_CLEAR_OC0_COMPARE_MATCH();
		}
		else if(SET_OC0 == Com_operation){
			TIMER0_SET_OC0_COMPARE_MATCH();
		}
		else{
			TIMER0_NORMAL_OPERATION();
		}
		break;
	case TIMER0_PWM_PHASE_CORRECT_MODE:
		if(NORMAL_OPERATION == Com_operation){
			TIMER0_NORMAL_OPERATION();
		}
		else if(CLEAR_OC0 == Com_operation){
			TIMER0_CLEAR_OC0_COMPARE_MATCH();
		}
		else if(SET_OC0 == Com_operation){
			TIMER0_SET_OC0_COMPARE_MATCH();
		}
		else{
			TIMER0_NORMAL_OPERATION();
		}
		break;
	}
}

static void TIMER0_CLOCK_SELECT(TIMER0_CLOCK_SELECT_T Clock_S, TIMER0_PRESCALER_SELECT_T Prescaler_S){
	switch(Clock_S){
	case TIMER0_NO_CLOCK_SOURCE:
		TIMER0_CLOCK_SELECT_DISABLE();
		break;
	case TIMER0_PRESCALLER_CLOCK_SOURCE:
		if(TIMER0_PRESCALER_DIV_1 == Prescaler_S){
			TIMER0_NO_PRESCALER_CLOCK_SELECT();
		}
		else if(TIMER0_PRESCALER_DIV_8 == Prescaler_S){
			TIMER0_PRESCALER_DIV_8_CLOCK_SELECT();
		}
		else if(TIMER0_PRESCALER_DIV_64 == Prescaler_S){
			TIMER0_PRESCALER_DIV_64_CLOCK_SELECT();
		}
		else if(TIMER0_PRESCALER_DIV_256 == Prescaler_S){
			TIMER0_PRESCALER_DIV_256_CLOCK_SELECT();
		}
		else if(TIMER0_PRESCALER_DIV_1024 == Prescaler_S){
			TIMER0_PRESCALER_DIV_1024_CLOCK_SELECT();
		}
		else{
			TIMER0_NO_PRESCALER_CLOCK_SELECT();
		}
		break;
	case TIMER0_EXTERNAL_CLOCK_SOURCE_FALLING_EDGE:
		TIMER0_EXTERNAL_FALLING_EDGE_CLOCK_SELECT();
		break;
	case TIMER0_EXTERNAL_CLOCK_SOURCE_RISING_EDGE:
		TIMER0_EXTERNAL_RISING_EDGE_CLOCK_SELECT();
		break;
	}
}





#if TIMER0_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
void __vector_11 (void)__attribute__((signal)) ;
void __vector_11 (void)
{
	if(NULL != TIMER0_INTERRUPT_OVF){
		TIMER0_INTERRUPT_OVF();
	}
}
void __vector_10 (void)__attribute__((signal)) ;
void __vector_10 (void)
{
	if(NULL != TIMER0_INTERRUPT_COMP){
		TIMER0_INTERRUPT_COMP();
	}
}

#endif








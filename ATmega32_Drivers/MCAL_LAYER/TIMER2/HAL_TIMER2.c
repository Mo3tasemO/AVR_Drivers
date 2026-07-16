/*
 * HAL_TIMER2.c
 *
 *  Created on: Jul 16, 2026
 *      Author: Moata
 */

#include "HAL_TIMER2.h"

#if TIMER2_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
void (*TIMER2_INTERRUPT_OVF)(void) = NULL;
void (*TIMER2_INTERRUPT_COMP)(void) = NULL;
#endif
static void TIMER2_MODE_SELECT(TIMER2_MODE_SELECT_T Mode);
static void TIMER2_COMPARE_OUTPUT_MODE_SELECT(TIMER2_COMPARE_OUTPUT_MODE_SELECT_T Com_mode,
		TIMER2_COMPARE_OUTPUT_OPERATION_SELECT_T Com_operation);
static void TIMER2_CLOCK_SELECT(TIMER2_CLOCK_SELECT_T Clock_S, TIMER2_PRESCALER_SELECT_T Prescaler_S);
static Std_ReturnType TIMER2_AS2_CONFIG(const TIMER2_t *_Timer);


Std_ReturnType TIMER2_INIT(const TIMER2_t *_Timer){
	Std_ReturnType ret = E_OK;
	if(NULL == _Timer){
		ret = E_NOT_OK;
	}
	else{
		ret = GPIO_PIN_INIT(&(_Timer->oc2_pin));
		TIMER2_MODE_SELECT(_Timer->Mode_Select);
		TIMER2_COMPARE_OUTPUT_MODE_SELECT(_Timer->COM_Mode, _Timer->COM_Operaion);
		ret = TIMER2_AS2_CONFIG(_Timer);
		TIMER2_CLOCK_SELECT(_Timer->Clock_Select, _Timer->Prescaler);
		TCNT2 = _Timer->Preload;
#if TIMER2_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
		SET_BIT(SREG, I_BIT);
		TIMER2_OVERFLOW_INTERRUPT_ENABLE();
		TIMER2_OUTPUT_COMPARE_MATCH_INTERRUPT_ENABLE();
		TIMER2_INTERRUPT_OVF = _Timer->TIMER2_INTERRUPT_HANDLER_OVF;
#endif
	}
	return ret;
}

Std_ReturnType TIMER2_WRITE_VALUE(const TIMER2_t *_Timer, uint8 Preload_Val){
	Std_ReturnType ret = E_OK;
	if(NULL == _Timer){
		ret = E_NOT_OK;
	}
	else{
		TCNT2 = Preload_Val;
	}
	return ret;
}
Std_ReturnType TIMER2_READ_VALUE(const TIMER2_t *_Timer, uint8 *ret_value){
	Std_ReturnType ret = E_OK;
	if((NULL == _Timer) || (NULL == ret_value)){
		ret = E_NOT_OK;
	}
	else{
		*ret_value = TCNT2;
	}
	return ret;
}
void TIMER2_GENERATE_PWM(uint8 OC2_Val){
		OCR2 = OC2_Val;
}


static void TIMER2_MODE_SELECT(TIMER2_MODE_SELECT_T Mode){
	switch(Mode){
	case TIMER2_NORMAL_MODE:
		TIMER2_NORMAL_MODE_ENABLE();
		break;
	case TIMER2_PWM_PHASE_CORRECT:
		TIMER2_PWM_PHASE_CORRECT_ENABLE();
		break;
	case TIMER2_CLEAR_TIMER_ON_COMPARE_MATCH:
		TIMER2_CLEAR_TIMER_ON_COMPARE_MATCH_ENABLE();
		break;
	case TIMER2_FAST_PWM:
		TIMER2_FAST_PWM_ENABLE();
		break;
	}
}

static void TIMER2_COMPARE_OUTPUT_MODE_SELECT(TIMER2_COMPARE_OUTPUT_MODE_SELECT_T Com_mode,
		TIMER2_COMPARE_OUTPUT_OPERATION_SELECT_T Com_operation){
	switch(Com_mode){
	case TIMER2_NON_PWM_MODE:
		if(TIMER2_NORMAL_OPERATION_SELECTED == Com_operation){
			TIMER2_NORMAL_OPERATION();
		}
		else if(TIMER2_TOGGLE_OC2_SELECTED == Com_operation){
			TIMER2_NON_PWM_MODE_TOGGLE_OC2_COMPARE_MATCH();
		}
		else if(TIMER2_CLEAR_OC2_SELECTED == Com_operation){
			TIMER2_CLEAR_OC2_COMPARE_MATCH();
		}
		else if(TIMER2_SET_OC2_SELECTED == Com_operation){
			TIMER2_SET_OC2_COMPARE_MATCH();
		}
		else{
			TIMER2_NORMAL_OPERATION();
		}
		break;
	case TIMER2_FAST_PWM_MODE:
		if(TIMER2_NORMAL_OPERATION_SELECTED == Com_operation){
			TIMER2_NORMAL_OPERATION();
		}
		else if(TIMER2_CLEAR_OC2_SELECTED == Com_operation){
			TIMER2_CLEAR_OC2_COMPARE_MATCH();
		}
		else if(TIMER2_SET_OC2_SELECTED == Com_operation){
			TIMER2_SET_OC2_COMPARE_MATCH();
		}
		else{
			TIMER2_NORMAL_OPERATION();
		}
		break;
	case TIMER2_PWM_PHASE_CORRECT_MODE:
		if(TIMER2_NORMAL_OPERATION_SELECTED == Com_operation){
			TIMER2_NORMAL_OPERATION();
		}
		else if(TIMER2_CLEAR_OC2_SELECTED == Com_operation){
			TIMER2_CLEAR_OC2_COMPARE_MATCH();
		}
		else if(TIMER2_SET_OC2_SELECTED == Com_operation){
			TIMER2_SET_OC2_COMPARE_MATCH();
		}
		else{
			TIMER2_NORMAL_OPERATION();
		}
		break;
	}
}

static void TIMER2_CLOCK_SELECT(TIMER2_CLOCK_SELECT_T Clock_S, TIMER2_PRESCALER_SELECT_T Prescaler_S){
	switch(Clock_S){
	case TIMER2_NO_CLOCK_SOURCE:
		TIMER2_CLOCK_SELECT_DISABLE();
		break;
	case TIMER2_PRESCALLER_CLOCK_SOURCE:
		if(TIMER2_PRESCALER_DIV_1 == Prescaler_S){
			TIMER2_NO_PRESCALER_CLOCK_SELECT();
		}
		else if(TIMER2_PRESCALER_DIV_8 == Prescaler_S){
			TIMER2_PRESCALER_DIV_8_CLOCK_SELECT();
		}
		else if(TIMER2_PRESCALER_DIV_64 == Prescaler_S){
			TIMER2_PRESCALER_DIV_64_CLOCK_SELECT();
		}
		else if(TIMER2_PRESCALER_DIV_256 == Prescaler_S){
			TIMER2_PRESCALER_DIV_256_CLOCK_SELECT();
		}
		else if(TIMER2_PRESCALER_DIV_1024 == Prescaler_S){
			TIMER2_PRESCALER_DIV_1024_CLOCK_SELECT();
		}
		else{
			TIMER2_NO_PRESCALER_CLOCK_SELECT();
		}
		break;
	case TIMER2_EXTERNAL_CLOCK_SOURCE_FALLING_EDGE:
		TIMER2_EXTERNAL_FALLING_EDGE_CLOCK_SELECT();
		break;
	case TIMER2_EXTERNAL_CLOCK_SOURCE_RISING_EDGE:
		TIMER2_EXTERNAL_RISING_EDGE_CLOCK_SELECT();
		break;
	}
}

static Std_ReturnType TIMER2_AS2_CONFIG(const TIMER2_t *_Timer){
	Std_ReturnType ret = E_OK;
	if(NULL == _Timer){
		ret = E_NOT_OK;
	}
	else{
		if(TIMER2_ASYNCHRONOUS_CLOCKED_FROM_INTERNAL_CLOCK == _Timer->Asynchronous_cfg){
			TIMER2_AS2_CLOCKED_FROM_INTERNAL_CLOCK();
		}
		else if(TIMER2_ASYNCHRONOUS_CLOCKED_FROM_CRYSTAL_OSCILLATOR == _Timer->Asynchronous_cfg){
			TIMER2_AS2_CLOCKED_FROM_CRYSTAL_OSCILLATOR();
		}
		else{/* Nothing*/}
	}
	return ret;
}



#if TIMER2_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
void __vector_5 (void)__attribute__((signal)) ;
void __vector_5 (void)
{
	if(NULL != TIMER2_INTERRUPT_OVF){
		TIMER2_INTERRUPT_OVF();
	}
}
void __vector_4 (void)__attribute__((signal)) ;
void __vector_4 (void)
{
	if(NULL != TIMER2_INTERRUPT_COMP){
		TIMER2_INTERRUPT_COMP();
	}
}

#endif



/*
 * HAL_TIMER2.h
 *
 *  Created on: Jul 16, 2026
 *      Author: Moata
 */

#ifndef MCAL_LAYER_TIMER2_HAL_TIMER2_H_
#define MCAL_LAYER_TIMER2_HAL_TIMER2_H_

/* Section : Includes */
#include "../GPIO/HAL_GPIO.h"
#include "../INTERRUPT/HAL_INTERRUPT.h"
#include "HAL_TIMER2_CFG.h"

/* Section: Macro Declarations */

#define TCCR2		(*(volatile uint8*)(0x45))
#define TCNT2		(*(volatile uint8*)(0x44))
#define OCR2		(*(volatile uint8*)(0x43))
#define ASSR		(*(volatile uint8*)(0x42))
#define TIMSK		(*(volatile uint8*)(0x59))
#define TIFR		(*(volatile uint8*)(0x58))

// Timer/Counter Control Register_BITS


#define	CS20		0
#define	CS21		1
#define	CS22		2
#define	WGM21		3
#define	COM20		4
#define	COM21		5
#define	WGM20		6
#define	FOC2		7

//Asynchronous Status Register_BITS

#define TCR2UB		0
#define OCR2UB		1
#define TCN2UB		2
#define AS2			3

// Timer/Counter Interrupt Mask Register_BITS

#define	TOIE2		6
#define OCIE2		7

// Timer/Counter Interrupt Flag Register_BITS

#define TOV2		6
#define OCF2		7

#define TIMER2_ASYNCHRONOUS_CLOCKED_FROM_INTERNAL_CLOCK			0
#define TIMER2_ASYNCHRONOUS_CLOCKED_FROM_CRYSTAL_OSCILLATOR		1


/* Section: Macro Functions Declarations */
#define TIMER2_FORCE_OUTPUT_COMPARE()		(SET_BIT(TCCR2, FOC2))

#define	TIMER2_NORMAL_MODE_ENABLE()			do{						   \
											   CLEAR_BIT(TCCR2, WGM20);\
									   	   	   CLEAR_BIT(TCCR2, WGM21);\
											}while(0)

#define	TIMER2_PWM_PHASE_CORRECT_ENABLE()	do{						    \
												SET_BIT(TCCR2, WGM20);  \
												CLEAR_BIT(TCCR2, WGM21);\
											}while(0)

#define	TIMER2_CLEAR_TIMER_ON_COMPARE_MATCH_ENABLE()	do{						    \
															CLEAR_BIT(TCCR2, WGM20);\
															SET_BIT(TCCR2, WGM21);  \
														}while(0)

#define	TIMER2_FAST_PWM_ENABLE()	do{						  \
										SET_BIT(TCCR2, WGM20);\
										SET_BIT(TCCR2, WGM21);\
									}while(0)

//	Compare Output Mode (OC0 Must Configured as Output)

#define	TIMER2_NORMAL_OPERATION()	do{						    \
										CLEAR_BIT(TCCR2, COM20);\
										CLEAR_BIT(TCCR2, COM21);\
									}while(0)

#define	TIMER2_NON_PWM_MODE_TOGGLE_OC2_COMPARE_MATCH()	do{						    \
															SET_BIT(TCCR2, COM20);  \
															CLEAR_BIT(TCCR2, COM21);\
														}while(0)
// non-inverting mode
#define	TIMER2_CLEAR_OC2_COMPARE_MATCH()				do{						    \
															CLEAR_BIT(TCCR2, COM20);\
															SET_BIT(TCCR2, COM21);  \
														}while(0)
// inverting mode
#define	TIMER2_SET_OC2_COMPARE_MATCH()					do{						  \
															SET_BIT(TCCR2, COM20);\
															SET_BIT(TCCR2, COM21);\
														}while(0)


// Clock_Select
#define TIMER2_CLOCK_SELECT_DISABLE()	do{						   \
											CLEAR_BIT(TCCR2, CS20);\
											CLEAR_BIT(TCCR2, CS21);\
											CLEAR_BIT(TCCR2, CS22);\
										}while(0)

#define TIMER2_NO_PRESCALER_CLOCK_SELECT()	do{						   \
													SET_BIT(TCCR2, CS20);  \
													CLEAR_BIT(TCCR2, CS21);\
													CLEAR_BIT(TCCR2, CS22);\
												}while(0)

#define TIMER2_PRESCALER_DIV_8_CLOCK_SELECT()	do{						   \
													CLEAR_BIT(TCCR2, CS20);\
													SET_BIT(TCCR2, CS21);  \
													CLEAR_BIT(TCCR2, CS22);\
												}while(0)

#define TIMER2_PRESCALER_DIV_64_CLOCK_SELECT()	do{						   \
													SET_BIT(TCCR2, CS20);  \
													SET_BIT(TCCR2, CS21);  \
													CLEAR_BIT(TCCR2, CS22);\
												}while(0)

#define TIMER2_PRESCALER_DIV_256_CLOCK_SELECT()	do{						   \
													CLEAR_BIT(TCCR2, CS20);\
													CLEAR_BIT(TCCR2, CS21);\
													SET_BIT(TCCR2, CS22);  \
												}while(0)

#define TIMER2_PRESCALER_DIV_1024_CLOCK_SELECT()	do{					   \
													SET_BIT(TCCR2, CS20);  \
													CLEAR_BIT(TCCR2, CS21);\
													SET_BIT(TCCR2, CS22);  \
												    }while(0)

#define TIMER2_EXTERNAL_FALLING_EDGE_CLOCK_SELECT()	do{					   \
													CLEAR_BIT(TCCR2, CS20);\
													SET_BIT(TCCR2, CS21);  \
													SET_BIT(TCCR2, CS22);  \
												    }while(0)

#define TIMER2_EXTERNAL_RISING_EDGE_CLOCK_SELECT()	do{					 \
													SET_BIT(TCCR2, CS20);\
													SET_BIT(TCCR2, CS21);\
													SET_BIT(TCCR2, CS22);\
												    }while(0)
// Asynchronous Timer/Counter2

#define TIMER2_AS2_CLOCKED_FROM_INTERNAL_CLOCK()			(CLEAR_BIT(ASSR, AS2))
#define TIMER2_AS2_CLOCKED_FROM_CRYSTAL_OSCILLATOR()		(SET_BIT(ASSR, AS2)) /* NOTE!! -> The MCU Clocked through TOSC1 pin That make MCU runs at 32.768KHz..
and go to (Low Power Mode)*/



#if TIMER2_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE

#define TIMER2_OUTPUT_COMPARE_MATCH_INTERRUPT_ENABLE()		(SET_BIT(TIMSK, OCIE2))
#define TIMER2_OUTPUT_COMPARE_MATCH_INTERRUPT_CLEAR_FLAG()	(SET_BIT(TIFR, OCF2))

#define TIMER2_OVERFLOW_INTERRUPT_ENABLE()					(SET_BIT(TIMSK, TOIE2))
#define TIMER2_OVERFLOW_INTERRUPT_CLEAR_FLAG()				(SET_BIT(TIFR, TOV2))


#endif


/* Section: Data Type Declarations */

typedef enum {
	TIMER2_NORMAL_MODE = 0,
	TIMER2_PWM_PHASE_CORRECT,
	TIMER2_CLEAR_TIMER_ON_COMPARE_MATCH,
	TIMER2_FAST_PWM
}TIMER2_MODE_SELECT_T;
typedef enum {
	TIMER2_NON_PWM_MODE = 0,
	TIMER2_FAST_PWM_MODE,
	TIMER2_PWM_PHASE_CORRECT_MODE
}TIMER2_COMPARE_OUTPUT_MODE_SELECT_T;

typedef enum {
	TIMER2_NORMAL_OPERATION_SELECTED = 0,
	TIMER2_TOGGLE_OC2_SELECTED,
	TIMER2_CLEAR_OC2_SELECTED,
	TIMER2_SET_OC2_SELECTED
}TIMER2_COMPARE_OUTPUT_OPERATION_SELECT_T;

typedef enum {
	TIMER2_NO_CLOCK_SOURCE = 0,
	TIMER2_PRESCALLER_CLOCK_SOURCE,
	TIMER2_EXTERNAL_CLOCK_SOURCE_FALLING_EDGE = 6,
	TIMER2_EXTERNAL_CLOCK_SOURCE_RISING_EDGE
}TIMER2_CLOCK_SELECT_T;

typedef enum {
	TIMER2_PRESCALER_DIV_1 = 1,
	TIMER2_PRESCALER_DIV_8,
	TIMER2_PRESCALER_DIV_64,
	TIMER2_PRESCALER_DIV_256,
	TIMER2_PRESCALER_DIV_1024
}TIMER2_PRESCALER_SELECT_T;

typedef struct {
#if TIMER2_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
	void (*TIMER2_INTERRUPT_HANDLER_OVF)(void);
	void (*TIMER2_INTERRUPT_HANDLER_COMP)(void);
#endif
	pin_config_t oc2_pin;
	uint16 Preload;
	TIMER2_MODE_SELECT_T Mode_Select;
	TIMER2_PRESCALER_SELECT_T Prescaler;
	TIMER2_COMPARE_OUTPUT_MODE_SELECT_T COM_Mode;
	TIMER2_COMPARE_OUTPUT_OPERATION_SELECT_T COM_Operaion;
	uint8 Clock_Select : 4;
	uint8 Asynchronous_cfg : 1;
	uint8 Timer2_Reserved : 3;
}TIMER2_t;



/* Section: Function Declarations */


Std_ReturnType TIMER2_INIT(const TIMER2_t *_Timer);
Std_ReturnType TIMER2_WRITE_VALUE(const TIMER2_t *_Timer, uint8 Preload_Val);
Std_ReturnType TIMER2_READ_VALUE(const TIMER2_t *_Timer, uint8 *ret_value);
void TIMER2_GENERATE_PWM(uint8 OC0_Val);







#endif /* MCAL_LAYER_TIMER2_HAL_TIMER2_H_ */

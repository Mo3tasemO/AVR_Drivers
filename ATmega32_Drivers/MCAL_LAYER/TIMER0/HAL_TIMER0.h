/*
 * HAL_TIMER.h
 *
 *  Created on: Feb 7, 2026
 *      Author: Moata
 */

#ifndef MCAL_LAYER_TIMERS_HAL_TIMER0_H_
#define MCAL_LAYER_TIMERS_HAL_TIMER0_H_


/* Section : Includes */
#include "HAL_TIMER0_CFG.h"
#include "../GPIO/HAL_GPIO.h"
#include "../INTERRUPT/HAL_INTERRUPT.h"


/* Section: Macro Declarations */

#define TCCR0		(*(volatile uint8*)(0x53))
#define TCNT0		(*(volatile uint8*)(0x52))
#define OCR0		(*(volatile uint8*)(0x5C))
#define TIMSK		(*(volatile uint8*)(0x59))
#define TIFR		(*(volatile uint8*)(0x58))

// Timer/Counter Control Register_BITS


#define	CS00		0
#define	CS01		1
#define	CS02		2
#define	WGM01		3
#define	COM00		4
#define	COM01		5
#define	WGM00		6
#define	FOC0		7

// Timer/Counter Interrupt Mask Register_BITS

#define	TOIE0		0
#define OCIE0		1

// Timer/Counter Interrupt Flag Register_BITS

#define TOV0		0
#define OCF0		1


/* Section: Macro Functions Declarations */
#define TIMER0_FORCE_OUTPUT_COMPARE()		(SET_BIT(TCCR0, FOC0))

#define	TIMER0_NORMAL_MODE_ENABLE()			do{						   \
											   CLEAR_BIT(TCCR0, WGM00);\
									   	   	   CLEAR_BIT(TCCR0, WGM01);\
											}while(0)

#define	TIMER0_PWM_PHASE_CORRECT_ENABLE()	do{						    \
												SET_BIT(TCCR0, WGM00);  \
												CLEAR_BIT(TCCR0, WGM01);\
											}while(0)

#define	TIMER0_CLEAR_TIMER_ON_COMPARE_MATCH_ENABLE()	do{						    \
															CLEAR_BIT(TCCR0, WGM00);\
															SET_BIT(TCCR0, WGM01);  \
														}while(0)

#define	TIMER0_FAST_PWM_ENABLE()	do{						  \
										SET_BIT(TCCR0, WGM00);\
										SET_BIT(TCCR0, WGM01);\
									}while(0)

//	Compare Output Mode (OC0 Must Configured as Output)

#define	TIMER0_NORMAL_OPERATION()	do{						    \
										CLEAR_BIT(TCCR0, COM00);\
										CLEAR_BIT(TCCR0, COM01);\
									}while(0)

#define	TIMER0_NON_PWM_MODE_TOGGLE_OC0_COMPARE_MATCH()	do{						    \
															SET_BIT(TCCR0, COM00);  \
															CLEAR_BIT(TCCR0, COM01);\
														}while(0)
// non-inverting mode
#define	TIMER0_CLEAR_OC0_COMPARE_MATCH()				do{						    \
															CLEAR_BIT(TCCR0, COM00);\
															SET_BIT(TCCR0, COM01);  \
														}while(0)
// inverting mode
#define	TIMER0_SET_OC0_COMPARE_MATCH()					do{						  \
															SET_BIT(TCCR0, COM00);\
															SET_BIT(TCCR0, COM01);\
														}while(0)


// Clock_Select
#define TIMER0_CLOCK_SELECT_DISABLE()	do{						   \
											CLEAR_BIT(TCCR0, CS00);\
											CLEAR_BIT(TCCR0, CS01);\
											CLEAR_BIT(TCCR0, CS02);\
										}while(0)

#define TIMER0_NO_PRESCALER_CLOCK_SELECT()	do{						   \
													SET_BIT(TCCR0, CS00);  \
													CLEAR_BIT(TCCR0, CS01);\
													CLEAR_BIT(TCCR0, CS02);\
												}while(0)

#define TIMER0_PRESCALER_DIV_8_CLOCK_SELECT()	do{						   \
													CLEAR_BIT(TCCR0, CS00);\
													SET_BIT(TCCR0, CS01);  \
													CLEAR_BIT(TCCR0, CS02);\
												}while(0)

#define TIMER0_PRESCALER_DIV_64_CLOCK_SELECT()	do{						   \
													SET_BIT(TCCR0, CS00);  \
													SET_BIT(TCCR0, CS01);  \
													CLEAR_BIT(TCCR0, CS02);\
												}while(0)

#define TIMER0_PRESCALER_DIV_256_CLOCK_SELECT()	do{						   \
													CLEAR_BIT(TCCR0, CS00);\
													CLEAR_BIT(TCCR0, CS01);\
													SET_BIT(TCCR0, CS02);  \
												}while(0)

#define TIMER0_PRESCALER_DIV_1024_CLOCK_SELECT()	do{					   \
													SET_BIT(TCCR0, CS00);  \
													CLEAR_BIT(TCCR0, CS01);\
													SET_BIT(TCCR0, CS02);  \
												    }while(0)

#define TIMER0_EXTERNAL_FALLING_EDGE_CLOCK_SELECT()	do{					   \
													CLEAR_BIT(TCCR0, CS00);\
													SET_BIT(TCCR0, CS01);  \
													SET_BIT(TCCR0, CS02);  \
												    }while(0)

#define TIMER0_EXTERNAL_RISING_EDGE_CLOCK_SELECT()	do{					 \
													SET_BIT(TCCR0, CS00);\
													SET_BIT(TCCR0, CS01);\
													SET_BIT(TCCR0, CS02);\
												    }while(0)


#if TIMER0_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE

#define TIMER0_OUTPUT_COMPARE_MATCH_INTERRUPT_ENABLE()		(SET_BIT(TIMSK, OCIE0))
#define TIMER0_OUTPUT_COMPARE_MATCH_INTERRUPT_CLEAR_FLAG()	(SET_BIT(TIFR, OCF0))

#define TIMER0_OVERFLOW_INTERRUPT_ENABLE()					(SET_BIT(TIMSK, TOIE0))
#define TIMER0_OVERFLOW_INTERRUPT_CLEAR_FLAG()				(SET_BIT(TIFR, TOV0))


#endif


/* Section: Data Type Declarations */

typedef enum {
	TIMER0_NORMAL_MODE = 0,
	TIMER0_PWM_PHASE_CORRECT,
	TIMER0_CLEAR_TIMER_ON_COMPARE_MATCH,
	TIMER0_FAST_PWM
}TIMER0_MODE_SELECT_T;
typedef enum {
	TIMER0_NON_PWM_MODE = 0,
	TIMER0_FAST_PWM_MODE,
	TIMER0_PWM_PHASE_CORRECT_MODE
}TIMER0_COMPARE_OUTPUT_MODE_SELECT_T;

typedef enum {
	NORMAL_OPERATION = 0,
	TOGGLE_OC0,
	CLEAR_OC0,
	SET_OC0
}TIMER0_COMPARE_OUTPUT_OPERATION_SELECT_T;

typedef enum {
	TIMER0_NO_CLOCK_SOURCE = 0,
	TIMER0_PRESCALLER_CLOCK_SOURCE,
	TIMER0_EXTERNAL_CLOCK_SOURCE_FALLING_EDGE = 6,
	TIMER0_EXTERNAL_CLOCK_SOURCE_RISING_EDGE
}TIMER0_CLOCK_SELECT_T;

typedef enum {
	TIMER0_PRESCALER_DIV_1 = 1,
	TIMER0_PRESCALER_DIV_8,
	TIMER0_PRESCALER_DIV_64,
	TIMER0_PRESCALER_DIV_256,
	TIMER0_PRESCALER_DIV_1024
}TIMER0_PRESCALER_SELECT_T;

typedef struct {
#if TIMER0_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
	void (*TIMER0_INTERRUPT_HANDLER_OVF)(void);
	void (*TIMER0_INTERRUPT_HANDLER_COMP)(void);
#endif
	uint16 Preload;
	TIMER0_MODE_SELECT_T Mode_Select;
	TIMER0_PRESCALER_SELECT_T Prescaler;
	TIMER0_COMPARE_OUTPUT_MODE_SELECT_T COM_Mode;
	TIMER0_COMPARE_OUTPUT_OPERATION_SELECT_T COM_Operaion;
	uint8 Clock_Select : 4;
	uint8 Timer0_Reserved : 4;
}TIMER0_t;



/* Section: Function Declarations */


Std_ReturnType TIMER0_INIT(const TIMER0_t *_Timer);
Std_ReturnType TIMER0_WRITE_VALUE(const TIMER0_t *_Timer, uint8 Preload_Val);
Std_ReturnType TIMER0_READ_VALUE(const TIMER0_t *_Timer, uint8 *ret_value);
void TIMER0_GENERATE_PWM(uint8 OC0_Val);










#endif /* MCAL_LAYER_TIMERS_HAL_TIMER0_H_ */

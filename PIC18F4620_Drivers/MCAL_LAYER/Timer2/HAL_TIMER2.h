/* 
 * File:   HAL_TIMER2.h
 * Author: Moata
 *
 * Created on June 29, 2026, 9:14 PM
 */

#ifndef HAL_TIMER2_H
#define	HAL_TIMER2_H

// Section: Includes
#include "HAL_TIMER2_CFG.h"
#include "../GPIO/HAL_GPIO.h"
#include "pic18f4620.h"
#include "../../MCAL_LAYER/Interrupt/MCAL_INTERNAL_INTERRUPT.h"

// Section: Macro Declarations
/* Timer2 Output Postscale Select bits */
#define TIMER2_POSTSCALE_DIV_1      0
#define TIMER2_POSTSCALE_DIV_2      1
#define TIMER2_POSTSCALE_DIV_3      2
#define TIMER2_POSTSCALE_DIV_4      3
#define TIMER2_POSTSCALE_DIV_5      4
#define TIMER2_POSTSCALE_DIV_6      5
#define TIMER2_POSTSCALE_DIV_7      6
#define TIMER2_POSTSCALE_DIV_8      7
#define TIMER2_POSTSCALE_DIV_9      8
#define TIMER2_POSTSCALE_DIV_10     9
#define TIMER2_POSTSCALE_DIV_11     10
#define TIMER2_POSTSCALE_DIV_12     11
#define TIMER2_POSTSCALE_DIV_13     12
#define TIMER2_POSTSCALE_DIV_14     13
#define TIMER2_POSTSCALE_DIV_15     14
#define TIMER2_POSTSCALE_DIV_16     15

/* Timer2 Input Clock Prescale Select bits */
#define TIMER2_PRESCALLER_DIV_1     0
#define TIMER2_PRESCALLER_DIV_4     1
#define TIMER2_PRESCALLER_DIV_16     2



// Section: Macro Functions Declarations
#define TIMER2_ENABLE()                                 (T2CONbits.TMR2ON = 1)
#define TIMER2_DISABLE()                                (T2CONbits.TMR2ON = 0)
// Section: Data Type Declarations
typedef struct {
#ifdef TIMER1_INTERRUPT_FEATURE_ENABLE
    void (* TMR2_INTERRUPT_HANDLER)(void);
    interrupt_priority_t TMR2_priority;
#endif
    uint16 TIMER1_PRELOAD_VALUE;
    uint8 POSTSCALE_VAL : 4;
    uint8 PRESCALER_VAL : 2;
    uint8 TIMER1_RESERVED : 2;
}TIMER2_T;
// Section: Function Declarations

Std_ReturnType TIMER2_INIT(const TIMER2_T *_Timer);
Std_ReturnType TIMER2_DENIT(const TIMER2_T *_Timer);
Std_ReturnType TIMER2_WRITE_VALUE(const TIMER2_T *_Timer, uint8 value);
Std_ReturnType TIMER2_READ_VALUE(const TIMER2_T *_Timer, uint8 *value);



#endif	/* HAL_TIMER2_H */


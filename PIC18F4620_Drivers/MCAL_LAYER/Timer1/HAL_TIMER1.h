/* 
 * File:   HAL_TIMER1.h
 * Author: Moata
 *
 * Created on June 28, 2026, 6:59 PM
 */

#ifndef HAL_TIMER1_H
#define	HAL_TIMER1_H





// Section: Includes
#include "HAL_TIMER1_CFG.h"
#include "../GPIO/HAL_GPIO.h"
#include "pic18f4620.h"
#include "../../MCAL_LAYER/Interrupt/MCAL_INTERNAL_INTERRUPT.h"

// Section: Data Type Declarations

typedef struct {
#ifdef TIMER1_INTERRUPT_FEATURE_ENABLE
    void (* TMR1_INTERRUPT_HANDLER)(void);
    interrupt_priority_t TMR1_priority;
#endif
    uint16 TIMER1_PRELOAD_VALUE;
    uint8 TIMER1_MODE : 1;
    uint8 PRESCALER_VAL : 2;
    uint8 TIMER1_SYNC_SELECT : 1;
    uint8 TIMER1_OSC_CFG : 1;
    uint8 TIMER1_RW_MODE_CFG : 1;
    uint8 TIMER1_RESERVED : 2;
}TIMER1_T;

// Section: Macro Declarations
/* Timer1 On bit */
#define TIMER1_TIMER_MODE     0
#define TIMER1_COUNTER_MODE   1
/* Timer1 External Clock Input Synchronization Select bit */
#define TIMER1_ASYNC_COUNTER  1
#define TIMER1_SYNC_COUNTER   0
/* Timer1 Oscillator Enable bit */
#define TIMER1_OSCILLATOR_ENABLE    1
#define TIMER1_OSCILLATOR_DISABLE   0
/* Timer1 Input Clock Prescale Select bits */
#define TIMER1_PRESCALLER_DIV_1     0
#define TIMER1_PRESCALLER_DIV_2     1
#define TIMER1_PRESCALLER_DIV_4     2
#define TIMER1_PRESCALLER_DIV_8     3
/* 16-bit Read/Write Mode Enable bit */
#define TIMER1_RW_16_BIT_CFG        1
#define TIMER1_RW_8_BIT_CFG         0

// Section: Macro Functions Declarations

/* Timer1 On bit */
#define TIMER1_ENABLE()                                 (T1CONbits.TMR1ON = 1)
#define TIMER1_DISABLE()                                (T1CONbits.TMR1ON = 0)
/* Timer1 Clock Source Select bit */
#define TIMER1_TIMER_MODE_ENABLE()                      (T1CONbits.TMR1CS = 0)
#define TIMER1_COUNTER_MODE_ENABLE()                    (T1CONbits.TMR1CS = 1)
/* Timer1 External Clock Input Synchronization Select bit */
#define TIMER1_SYNCHRONIZE_COUNTER_MODE_ENABLE()        (T1CONbits.T1SYNC = 0)
#define TIMER1_ASYNCHRONIZE_COUNTER_MODE_ENABLE()       (T1CONbits.T1SYNC = 1)
/* 16-bit Read/Write Mode Enable bit */
#define TIMER1_8_BIT_CONFIGURATION()                    (T1CONbits.RD16 = 0)
#define TIMER1_16_BIT_CONFIGURATION()                   (T1CONbits.RD16 = 1)
/* Timer1 Oscillator Enable bit */
#define TIMER1_HW_OSCILLATOR_ENABLE()                   (T1CONbits.T1OSCEN = 1)
#define TIMER1_HW_OSCILLATOR_DISABLE()                  (T1CONbits.T1OSCEN = 0)
/* Timer1 Input Clock Prescale Select bits */
#define TIMER1_PRESCALLER_SELECT(_PRESCALLER_)          (T1CONbits.T1CKPS = _PRESCALLER_)
/* Timer1 System Clock Status bit */
#define TIMER1_SYSTEM_CLK_STATUS()                      (T1CONbits.T1RUN)

// Section: Function Declarations


Std_ReturnType TIMER1_INIT(const TIMER1_T *_Timer);
Std_ReturnType TIMER1_DENIT(const TIMER1_T *_Timer);
Std_ReturnType TIMER1_WRITE_VALUE(const TIMER1_T *_Timer, uint16 value);
Std_ReturnType TIMER1_READ_VALUE(const TIMER1_T *_Timer, uint16 *value);



#endif	/* HAL_TIMER1_H */


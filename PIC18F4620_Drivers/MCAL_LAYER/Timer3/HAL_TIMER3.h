/* 
 * File:   HAL_TIMER3.h
 * Author: Moata
 *
 * Created on June 29, 2026, 9:14 PM
 */

#ifndef HAL_TIMER3_H
#define	HAL_TIMER3_H


// Section: Includes
#include "HAL_TIMER3_CFG.h"
#include "../GPIO/HAL_GPIO.h"
#include "pic18f4620.h"
#include "../../MCAL_LAYER/Interrupt/MCAL_INTERNAL_INTERRUPT.h"
// Section: Macro Declarations
/* Timer3 On bit */
#define TIMER3_TIMER_MODE     0
#define TIMER3_COUNTER_MODE   1
/* Timer3 External Clock Input Synchronization Select bit */
#define TIMER3_ASYNC_COUNTER  1
#define TIMER3_SYNC_COUNTER   0
/* Timer3 Input Clock Prescale Select bits */
#define TIMER3_PRESCALLER_DIV_1     0
#define TIMER3_PRESCALLER_DIV_2     1
#define TIMER3_PRESCALLER_DIV_4     2
#define TIMER3_PRESCALLER_DIV_8     3
/* 16-bit Read/Write Mode Enable bit */
#define TIMER3_RW_16_BIT_CFG        1
#define TIMER3_RW_8_BIT_CFG         0

// Section: Macro Functions Declarations
/* Timer3 On bit */
#define TIMER3_ENABLE()                                 (T3CONbits.TMR3ON = 1)
#define TIMER3_DISABLE()                                (T3CONbits.TMR3ON = 0)
/* Timer3 Clock Source Select bit */
#define TIMER3_TIMER_MODE_ENABLE()                      (T3CONbits.TMR3CS = 0)
#define TIMER3_COUNTER_MODE_ENABLE()                    (T3CONbits.TMR3CS = 1)
/* Timer3 External Clock Input Synchronization Select bit */
#define TIMER3_SYNCHRONIZE_COUNTER_MODE_ENABLE()        (T3CONbits.T3SYNC = 0)
#define TIMER3_ASYNCHRONIZE_COUNTER_MODE_ENABLE()       (T3CONbits.T3SYNC = 1)
/* 16-bit Read/Write Mode Enable bit */
#define TIMER3_8_BIT_CONFIGURATION()                    (T3CONbits.RD16 = 0)
#define TIMER3_16_BIT_CONFIGURATION()                   (T3CONbits.RD16 = 1)
/* Timer3 Input Clock Prescale Select bits */
#define TIMER3_PRESCALLER_SELECT(_PRESCALLER_)          (T3CONbits.T3CKPS = _PRESCALLER_)
// Section: Data Type Declarations
typedef struct {
#ifdef TIMER3_INTERRUPT_FEATURE_ENABLE
    void (* TMR3_INTERRUPT_HANDLER)(void);
    interrupt_priority_t TMR3_priority;
#endif
    uint16 TIMER3_PRELOAD_VALUE;
    uint8 TIMER3_MODE : 1;
    uint8 PRESCALER_VAL : 2;
    uint8 TIMER3_SYNC_SELECT : 1;
    uint8 TIMER3_RW_MODE_CFG : 1;
    uint8 TIMER3_RESERVED : 3;
}TIMER3_T;

// Section: Function Declarations

Std_ReturnType TIMER3_INIT(const TIMER3_T *_Timer);
Std_ReturnType TIMER3_DENIT(const TIMER3_T *_Timer);
Std_ReturnType TIMER3_WRITE_VALUE(const TIMER3_T *_Timer, uint16 value);
Std_ReturnType TIMER3_READ_VALUE(const TIMER3_T *_Timer, uint16 *value);



#endif	/* HAL_TIMER3_H */


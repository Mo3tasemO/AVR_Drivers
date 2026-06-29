/* 
 * File:   HAL_TIMER0.h
 * Author: Moata
 *
 * Created on June 14, 2026, 6:34 PM
 */

#ifndef HAL_TIMER0_H
#define	HAL_TIMER0_H




// Section: Includes
#include "HAL_TIMER0_CFG.h"
#include "../GPIO/HAL_GPIO.h"
#include "pic18f4620.h"
#include "../../MCAL_LAYER/Interrupt/MCAL_INTERNAL_INTERRUPT.h"

// Section: Data Type Declarations

typedef enum {
    TIMER0_PRESCALER_DIV_2 = 0,
    TIMER0_PRESCALER_DIV_4,
    TIMER0_PRESCALER_DIV_8,
    TIMER0_PRESCALER_DIV_16,
    TIMER0_PRESCALER_DIV_32,
    TIMER0_PRESCALER_DIV_64,
    TIMER0_PRESCALER_DIV_128,
    TIMER0_PRESCALER_DIV_256            
}TIMER0_PRESCALER_SELECT_T;

typedef struct {
#ifdef TIMER0_INTERRUPT_FEATURE_ENABLE
    void (* TMR0_INTERRUPT_HANDLER)(void);
    interrupt_priority_t TMR0_priority;
#endif
    TIMER0_PRESCALER_SELECT_T PRESCALER_VAL;
    uint16 TIMER0_PRELOAD_VALUE;
    uint8 PRESCALER_ENABLE : 1;
    uint8 TIMER0_COUNTER_EDGE : 1;
    uint8 TIMER0_MODE : 1;
    uint8 TIMER0_REGISTER_SIZE : 1;
    uint8 TIMER0_RESERVED : 4;
}TIMER0_T;



// Section: Macro Declarations
#define TIMER0_ON             1
#define TIMER0_OFF            0

#define TIMER0_8BIT_CFG       1
#define TIMER0_16BIT_CFG      0

#define TIMER0_TIMER_MODE     0
#define TIMER0_COUNTER_MODE   1

#define TIMER0_FALLING_EDGE   1
#define TIMER0_RISING_EDGE    0

#define TIMER0_PRESCALER_ON   0
#define TIMER0_PRESCALER_OFF  1
// Section: Macro Functions Declarations
#define TIMER0_ENABLE()                     (T0CONbits.TMR0ON = 1)
#define TIMER0_DISABLE()                    (T0CONbits.TMR0ON = 0)

#define TIMER0_8_BIT_CONFIGURATION()        (T0CONbits.T08BIT = 1)
#define TIMER0_16_BIT_CONFIGURATION()       (T0CONbits.T08BIT = 0)

#define TIMER0_TIMER_MODE_ENABLE()          (T0CONbits.T0CS = 0)
#define TIMER0_COUNTER_MODE_ENABLE()        (T0CONbits.T0CS = 1)

#define TIMER0_COUNTER_MODE_FALLING_EDGE()  (T0CONbits.T0SE = 1)
#define TIMER0_COUNTER_MODE_RISING_EDGE()   (T0CONbits.T0SE = 0)

#define TIMER0_PRESCALER_ENABLE()           (T0CONbits.PSA = 0)
#define TIMER0_PRESCALER_DISABLE()          (T0CONbits.PSA = 1)
// Section: Function Declarations

Std_ReturnType TIMER0_INIT(const TIMER0_T *_Timer);
Std_ReturnType TIMER0_DENIT(const TIMER0_T *_Timer);
Std_ReturnType TIMER0_8BIT_WRITE_VALUE(const TIMER0_T *_Timer, uint8 value);
Std_ReturnType TIMER0_8BIT_READ_VALUE(const TIMER0_T *_Timer, uint8 *value);
Std_ReturnType TIMER0_16BIT_WRITE_VALUE(const TIMER0_T *_Timer, uint16 value);
Std_ReturnType TIMER0_16BIT_READ_VALUE(const TIMER0_T *_Timer, uint16 *value);













#endif	/* HAL_TIMER0_H */


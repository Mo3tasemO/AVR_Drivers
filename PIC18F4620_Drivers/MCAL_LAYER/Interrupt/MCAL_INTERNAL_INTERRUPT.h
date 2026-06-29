/* 
 * File:   MCAL_INTERNAL_INTERRUPT.h
 * Author: Moata
 *
 * Created on February 21, 2026, 10:37 PM
 */

#ifndef MCAL_INTERNAL_INTERRUPT_H
#define	MCAL_INTERNAL_INTERRUPT_H





// Section: Includes
#include "MCAL_INTERRUPT_CONFIG.h"


// Section: Data Type Declarations
// Section: Macro Declarations
#ifdef ADC_INTERRUPT_FEATURE_ENABLE
    #define ADC_INTERRUPT_ENABLE()          (PIE1bits.ADIE = 1)
    #define ADC_INTERRUPT_DISABLE()          (PIE1bits.ADIE = 0)
    #define ADC_INTERRUPT_FLAG_CLEAR()      (PIR1bits.ADIF = 0)
#ifdef INTERRUPT_PRIORITY_LEVELS_ENABLE
    /*Enable External Interrupt High Priority*/
    #define ADC_INTERRUPT_PRIORITY_HIGH()         (IPR1bits.ADIP = 1)
    /*Disable External Interrupt Low Priority*/
    #define ADC_INTERRUPT_PRIORITY_LOW()          (IPR1bits.ADIP = 0)
#endif
#endif

#ifdef TIMER0_INTERRUPT_FEATURE_ENABLE
    #define TIMER0_INTERRUPT_ENABLE()              (INTCONbits.TMR0IE = 1)
    #define TIMER0_INTERRUPT_DISABLE()             (INTCONbits.TMR0IE = 0)
    #define TIMER0_INTERRUPT_FLAG_CLEAR()          (INTCONbits.TMR0IF = 0)
#ifdef INTERRUPT_PRIORITY_LEVELS_ENABLE
    /*Enable External Interrupt High Priority*/
    #define TIMER0_INTERRUPT_PRIORITY_HIGH()       (INTCON2bits.TMR0IP = 1)
    /*Disable External Interrupt Low Priority*/
    #define TIMER0_INTERRUPT_PRIORITY_LOW()        (INTCON2bits.TMR0IP = 0)
#endif
#endif

#ifdef TIMER1_INTERRUPT_FEATURE_ENABLE
    #define TIMER1_INTERRUPT_ENABLE()              (PIE1bits.TMR1IE = 1)
    #define TIMER1_INTERRUPT_DISABLE()             (PIE1bits.TMR1IE = 0)
    #define TIMER1_INTERRUPT_FLAG_CLEAR()          (PIR1bits.TMR1IF = 0)
#ifdef INTERRUPT_PRIORITY_LEVELS_ENABLE
    /*Enable External Interrupt High Priority*/
    #define TIMER1_INTERRUPT_PRIORITY_HIGH()       (IPR1bits.TMR1IP = 1)
    /*Disable External Interrupt Low Priority*/
    #define TIMER1_INTERRUPT_PRIORITY_LOW()        (IPR1bits.TMR1IP = 0)
#endif
#endif

#ifdef TIMER2_INTERRUPT_FEATURE_ENABLE
    #define TIMER2_INTERRUPT_ENABLE()              (PIE1bits.TMR2IE = 1)
    #define TIMER2_INTERRUPT_DISABLE()             (PIE1bits.TMR2IE = 0)
    #define TIMER2_INTERRUPT_FLAG_CLEAR()          (PIR1bits.TMR2IF = 0)
#ifdef INTERRUPT_PRIORITY_LEVELS_ENABLE
    /*Enable External Interrupt High Priority*/
    #define TIMER2_INTERRUPT_PRIORITY_HIGH()       (IPR1bits.TMR2IP = 1)
    /*Disable External Interrupt Low Priority*/
    #define TIMER2_INTERRUPT_PRIORITY_LOW()        (IPR1bits.TMR2IP = 0)
#endif
#endif

#ifdef TIMER3_INTERRUPT_FEATURE_ENABLE
    #define TIMER3_INTERRUPT_ENABLE()              (PIE2its.TMR3IE = 1)
    #define TIMER3_INTERRUPT_DISABLE()             (PIE2bits.TMR3IE = 0)
    #define TIMER3_INTERRUPT_FLAG_CLEAR()          (PIR2bits.TMR3IF = 0)
#ifdef INTERRUPT_PRIORITY_LEVELS_ENABLE
    /*Enable External Interrupt High Priority*/
    #define TIMER3_INTERRUPT_PRIORITY_HIGH()       (IPR2bits.TMR3IP = 1)
    /*Disable External Interrupt Low Priority*/
    #define TIMER3_INTERRUPT_PRIORITY_LOW()        (IPR2bits.TMR3IP = 0)
#endif
#endif

// Section: Macro Functions Declarations
// Section: Function Declarations




#endif	/* MCAL_INTERNAL_INTERRUPT_H */


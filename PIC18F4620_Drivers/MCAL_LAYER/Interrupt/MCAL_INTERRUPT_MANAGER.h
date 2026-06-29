/* 
 * File:   MCAL_INTERRUPT_MANAGER.h
 * Author: Moata
 *
 * Created on February 21, 2026, 10:38 PM
 */

#ifndef MCAL_INTERRUPT_MANAGER_H
#define	MCAL_INTERRUPT_MANAGER_H

// Section: Includes
#include "MCAL_INTERRUPT_CONFIG.h"




// Section: Data Type Declarations
// Section: Macro Declarations
// Section: Macro Functions Declarations
// Section: Function Declarations
void INT0_ISR(void);
void INT1_ISR(void);
void INT2_ISR(void);
void RB4_ISR(uint8 RBx_Source);
void RB5_ISR(uint8 RBx_Source);
void RB6_ISR(uint8 RBx_Source);
void RB7_ISR(uint8 RBx_Source);
void ADC_ISR(void);
void TMR0_ISR(void);
void TMR1_ISR(void);
#endif	/* MCAL_INTERRUPT_MANAGER_H */


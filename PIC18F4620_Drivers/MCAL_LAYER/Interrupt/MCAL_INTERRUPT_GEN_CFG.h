/* 
 * File:   MCAL_INTERRUPT_GEN_CFG.h
 * Author: Moata
 *
 * Created on February 23, 2026, 3:11 PM
 */

#ifndef MCAL_INTERRUPT_GEN_CFG_H
#define	MCAL_INTERRUPT_GEN_CFG_H

// Section: Includes

// Section: Data Type Declarations
// Section: Macro Declarations

#define INTERRUPT_FEATURE_ENABLE                       1
//#define INTERRUPT_PRIORITY_LEVELS_ENABLE             INTERRUPT_FEATURE_ENABLE
#define EXTERNAL_INTERRUPT_INTx_FEATURE_ENABLE         INTERRUPT_FEATURE_ENABLE
#define EXTERNAL_INTERRUPT_ON_CHANGE_FEATURE_ENABLE    INTERRUPT_FEATURE_ENABLE

#define ADC_INTERRUPT_FEATURE_ENABLE                   INTERRUPT_FEATURE_ENABLE

#define TIMER0_INTERRUPT_FEATURE_ENABLE                INTERRUPT_FEATURE_ENABLE
#define TIMER1_INTERRUPT_FEATURE_ENABLE                INTERRUPT_FEATURE_ENABLE
#define TIMER2_INTERRUPT_FEATURE_ENABLE                INTERRUPT_FEATURE_ENABLE
#define TIMER3_INTERRUPT_FEATURE_ENABLE                INTERRUPT_FEATURE_ENABLE
// Section: Macro Functions 
// Section: Function Declarations





#endif	/* MCAL_INTERRUPT_GEN_CFG_H */


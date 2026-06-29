/* 
 * File:   MCAL_INTERRUPT_CONFIG.h
 * Author: Moata
 *
 * Created on February 21, 2026, 10:37 PM
 */

#ifndef MCAL_INTERRUPT_CONFIG_H
#define	MCAL_INTERRUPT_CONFIG_H

// Section: Includes
#include <xc.h>
#include "../MCAL_STD_TYPES.h"
#include "MCAL_INTERRUPT_GEN_CFG.h"
#include "../GPIO/HAL_GPIO.h"
// Section: Data Type Declarations
typedef enum{
    INTERRUPT_LOW_PRIORITY = 0,
    INTERRUPT_HIGH_PRIORITY = 1      
}interrupt_priority_t;


// Section: Macro Declarations

#define INTERRUPT_ENABLE             1
#define INTERRUPT_DISABLE            0
#define INTERRUPT_OCCUR              1
#define INTERRUPT_NOT_OCCUR          0
#define INTERRUPT_PRIORITY_ENABLE    1
#define INTERRUPT_PRIORITY_DISABLE    0

// Section: Macro Functions 


#ifdef INTERRUPT_PRIORITY_LEVELS_ENABLE
/*Enable Priority Level*/
#define INTERRUPT_Priority_Level_Enable()        (RCONbits.IPEN = 1)
/*Disable Priority Level*/
#define INTERRUPT_Priority_Level_Disable()       (RCONbits.IPEN = 0)
/*Enable High Interrupt Priority*/
#define INTERRUPT_GlobalInterruptHighEnable()    (INTCONbits.GIEH = 1)
/*Disable High Interrupt Priority*/
#define INTERRUPT_GlobalInterruptHighDisable()   (INTCONbits.GIEH = 0)
/*Enable Low Interrupt Priority*/
#define INTERRUPT_GlobalInterruptLowEnable()     (INTCONbits.GIEL = 1)
/*Disable Low Interrupt Priority*/
#define INTERRUPT_GlobalInterruptLowDisable()    (INTCONbits.GIEL = 0)
#else
/*Enable Global Interrupt*/
#define INTERRUPT_GlobalInterruptEnable()        (INTCONbits.GIE = 1)
/*Disable Global Interrupt*/
#define INTERRUPT_GlobalInterruptDisable()       (INTCONbits.GIE = 0)
/*Enable Peripheral Interrupt*/
#define INTERRUPT_Peripheral_Interrupt_Enable()  (INTCONbits.PEIE = 1)
/*Disable Peripheral Interrupt*/
#define INTERRUPT_Peripheral_Interrupt_Disable() (INTCONbits.PEIE = 0)
#endif




// Section: Function Declarations




#endif	/* MCAL_INTERRUPT_CONFIG_H */


/* 
 * File:   MCAL_STD_TYPES.h
 * Author: Moata
 *
 * Created on September 30, 2025, 6:39 PM
 */

#ifndef MCAL_STD_TYPES_H
#define	MCAL_STD_TYPES_H



// Section: Includes
#include "STD_LIB.h"
#include "COMPLILER.h"
#include "GPIO/HAL_GPIO_CFG.h"

// Section: Data Type Declarations
typedef unsigned char uint8;
typedef unsigned short uint16;
typedef unsigned int uint32;
typedef signed char sint8;
typedef signed short sint16;
typedef signed int sint32;

typedef uint8 Std_ReturnType;

// Section: Macro Declarations
#define STD_HIGH    0x01
#define STD_LOW    0x00

#define STD_ON    0x01
#define STD_OFF    0x00

#define STD_Alive   0x01
#define STD_Idle    0x00

#define E_OK    (Std_ReturnType)0x01
#define E_NOT_OK    (Std_ReturnType)0x00

#define GPIO_PORT_PIN_CONFIGURATION CONFIG_ENABLE
#define GPIO_PORT_CONFIGURATION CONFIG_ENABLE
// Section: Macro Functions Declarations


// Section: Function Declarations



#endif	/* MCAL_STD_TYPES_H */


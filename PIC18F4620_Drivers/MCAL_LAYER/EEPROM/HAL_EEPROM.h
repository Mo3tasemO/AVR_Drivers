/* 
 * File:   HAL_EEPROM.h
 * Author: Moata
 *
 * Created on March 23, 2026, 12:58 AM
 */

#ifndef HAL_EEPROM_H
#define	HAL_EEPROM_H

// Section: Includes
#include "../MCAL_STD_TYPES.h"
#include "pic18f4620.h"
#include "../Interrupt/MCAL_INTERNAL_INTERRUPT.h"
// Section: Data Type Declarations



typedef enum{
    ACCESS_MEMORY,
    ACCESS_CONFIGURATION_REGISTER
}ACCESS_CONTROL_T;
typedef enum{
    ACCESS_EEPROM_MEMORY,
    ACCESS_PROGRAM_MEMORY
}MEMORY_TYPE_ACCESS_T;
typedef struct{
    ACCESS_CONTROL_T ACCESS_CONTROL;
    MEMORY_TYPE_ACCESS_T MEMORY_TYPE_ACCESS;
}EEPROM_CONFIG_T;


// Section: Macro Declarations
// Section: Macro Functions Declarations

#define EEPROM_CONTROL_ACCESS_CONFIG_REG()  (EECON1bits.CFGS = 1)
#define EEPROM_CONTROL_ACCESS_EEPROM_DATA_AND_PROGRAM_MEMORY()  (EECON1bits.CFGS = 0)
#define EEPROM_ACCESS_EEPROM_MEMORY()  (EECON1bits.EEPGD = 0)
#define EEPROM_ACCESS_PROGRAM_MEMORY()  (EECON1bits.EEPGD = 1)
#define EEPROM_ALLOW_WRITE_OPERATION()  (EECON1bits.WREN = 1)
#define EEPROM_INHIBIT_WRITE_OPERATION()  (EECON1bits.WREN = 0)
#define EEPROM_WRITE_INIT_CONTROL()  (EECON1bits.WR = 1)
#define EEPROM_READ_INIT_CONTROL()  (EECON1bits.RD = 1) // Cant be Set When using program memory
#define EEPROM_INTERRUPT_FLAG_ENABLE()  (PIR2bits.EEIF = 1)
#define EEPROM_INTERRUPT_FLAG_DISABLE()  (PIR2bits.EEIF = 0)



// Section: Function Declarations
/**
 * 
 * @param EEPROM_CONFIG
 * @return 
 */
Std_ReturnType EEPROM_INIT(const EEPROM_CONFIG_T *EEPROM_CONFIG);
/**
 * 
 * @param EEPROM_CONFIG
 * @return 
 */
Std_ReturnType EEPROM_WRITE_BYTE(uint16 Address, uint8 Data);
/**
 * 
 * @param EEPROM_CONFIG
 * @return 
 */
Std_ReturnType EEPROM_READ_BYTE(uint16 Address, uint8 *Data);

#endif	/* HAL_EEPROM_H */


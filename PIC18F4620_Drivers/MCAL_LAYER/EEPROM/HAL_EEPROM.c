/* 
 * File:   HAL_EEPROM.c
 * Author: Moata
 *
 * Created on March 23, 2026, 12:58 AM
 */

#include "HAL_EEPROM.h"



Std_ReturnType EEPROM_INIT(const EEPROM_CONFIG_T *EEPROM_CONFIG){
    Std_ReturnType ret = E_OK;
    if(NULL == EEPROM_CONFIG){
        ret = E_NOT_OK;
    }
    else{
        if(ACCESS_MEMORY == EEPROM_CONFIG->ACCESS_CONTROL){
            EEPROM_CONTROL_ACCESS_EEPROM_DATA_AND_PROGRAM_MEMORY();
            switch(EEPROM_CONFIG->MEMORY_TYPE_ACCESS){
                case ACCESS_EEPROM_MEMORY:
                    EEPROM_ACCESS_EEPROM_MEMORY();
                    break;
                case ACCESS_PROGRAM_MEMORY:
                    EEPROM_ACCESS_PROGRAM_MEMORY();
                    break;
                default:
                    ret = E_NOT_OK;
            }
        }
        else if(ACCESS_CONFIGURATION_REGISTER == EEPROM_CONFIG->ACCESS_CONTROL){
            EEPROM_CONTROL_ACCESS_CONFIG_REG();
        }
        else{/*Nothing*/}
        ret = E_OK;
    }
    return ret;
}
Std_ReturnType EEPROM_WRITE_BYTE(uint16 Address, uint8 Data){
    Std_ReturnType ret = E_OK;
    /* Read Global Interrupt Enable Status*/
    uint8 Global_Interrupt_Status = INTCONbits.GIE;
    /*Update Address Register*/
    EEADRH = (uint8)((Address >> 8) & 0x03);
    EEADR = (uint8)(Address & 0xFF);
    /*Initialize the data register*/
    EEDATA = Data;
    /*Allow Write Operation WREN*/
    EEPROM_ALLOW_WRITE_OPERATION();
    /*Disable Global Interrupt*/
    INTERRUPT_GlobalInterruptDisable();
    /*Write the Recommended sequence*/
    EECON2 = 0x55;
    EECON2 = 0xAA;
    /*INITIATE Write Control*/
    EEPROM_WRITE_INIT_CONTROL();
    /*Wait For Write Operation Complete*/
    while(EECON1bits.WR);
    /*Inhibit write operation*/
    EEPROM_INHIBIT_WRITE_OPERATION();
    /*Restore the Interrupt status*/
    INTCONbits.GIE = Global_Interrupt_Status;
    ret= E_OK;
    return ret;
}
Std_ReturnType EEPROM_READ_BYTE(uint16 Address, uint8 *Data){
    Std_ReturnType ret = E_OK;
    if(NULL == Data){
        ret = E_NOT_OK;        
    }
    else{
        /*Update Address Register*/
        EEADRH = (uint8)((Address >> 8) & 0x03);
        EEADR = (uint8)(Address & 0xFF);
        /* clear the EEPGD control bit of the EECON1 register*/
        EEPROM_ACCESS_EEPROM_MEMORY();
        EEPROM_CONTROL_ACCESS_EEPROM_DATA_AND_PROGRAM_MEMORY();
        /* set control bit RD*/
        EEPROM_READ_INIT_CONTROL();
        NOP();
        NOP();
        /*Read The Data at the given address*/
        *Data = EEDATA;
        ret= E_OK;
    }
    return ret;    
}

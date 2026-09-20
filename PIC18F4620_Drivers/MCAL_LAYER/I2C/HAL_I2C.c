/* 
 * File:   HAL_I2C.c
 * Author: Moata
 *
 * Created on September 3, 2026, 1:55 PM
 */

#include "HAL_I2C.h"

static inline void MSSP_I2C_GPIO_CONFIG();
static inline void MSSP_I2C_MASTER_CLOCK_CONFIG(const MSSP_I2C_T *MSSP_I2C);
static inline void MSSP_I2C_SLAVE_CONFIG(const MSSP_I2C_T *MSSP_I2C);
static inline void MSSP_I2C_INTERRUPT_CONFIGURATIONS(const MSSP_I2C_T *MSSP_I2C);
#ifdef MSSP_I2C_INTERRUPT_FEATURE_ENABLE
    static void (*MSSP_I2C_INTERRUPT_HANDLER)(void) = NULL;
    static void (*MSSP_I2C_RECIEVE_OVERFLOW_INTERRUPT_HANDLER)(void) = NULL;
#endif
#ifdef MSSP_I2C_BUS_COL_INTERRUPT_FEATURE_ENABLE
    static void (*MSSP_I2C_BUS_COL_INTERRUPT_HANDLER)(void) = NULL;
#endif
Std_ReturnType MSSP_I2C_INIT(const MSSP_I2C_T *MSSP_I2C){
    Std_ReturnType ret = E_NOT_OK;
    if(NULL == MSSP_I2C){
        ret = E_NOT_OK;
    }
    else{
        /* Disable MSSP Module */
        MSSP_I2C_MODULE_DISABLE_CFG();
        /* I2C Mode Select (Master/Slave) */
        if(MSSP_I2C_MASTER_MODE == MSSP_I2C->I2C_CONFIG.I2C_mode){
            /* I2C Master Mode Clock Configuration */
            MSSP_I2C_MASTER_CLOCK_CONFIG(MSSP_I2C);
        }
        else if(MSSP_I2C_SLAVE_MODE == MSSP_I2C->I2C_CONFIG.I2C_mode){
            if(I2C_GENERAL_CALL_ENABLE == MSSP_I2C->I2C_CONFIG.I2C_General_Call){
                I2C_GENERAL_CALL_ENABLE_CFG();
            }
            else if(I2C_GENERAL_CALL_DISABLE == MSSP_I2C->I2C_CONFIG.I2C_General_Call){
                I2C_GENERAL_CALL_DISABLE_CFG();
            }
            else{/* Nothing */}
            /* Clear Write Collision Detect */
            I2C_WRITE_COLLISION_DETECT_NO_COLLISION();
            /* Clear Receive Overflow Indicator */
            I2C_RECIEVE_OVERFLOW_INDICATOR_NO_OVERFLOW();
            /* Release Clock */
            I2C_SLAVE_SCK_RELEASE_CONTROL_RELEASE();
            /* Assign Slave Address*/
            SSPADD = MSSP_I2C->I2C_CONFIG.I2C_Salve_Add;
            /* I2C Slave Mode Configuration */
            MSSP_I2C_SLAVE_CONFIG(MSSP_I2C);
        }
        else{/* Nothing */}
        /* I2C GPIO Configuration */
        MSSP_I2C_GPIO_CONFIG();
        if(I2C_SLEW_RATE_ENABLE == MSSP_I2C->I2C_CONFIG.I2C_slew_rate){
            I2C_SLEW_RATE_ENABLE_CFG();
        }
        else if(I2C_SLEW_RATE_DISABLE == MSSP_I2C->I2C_CONFIG.I2C_slew_rate){
            I2C_SLEW_RATE_DISABLE_CFG();
        }
        else{/* Nothing */}
        if(I2C_SMBus_ENABLE == MSSP_I2C->I2C_CONFIG.I2C_SMBus_Control){
            I2C_SMBus_ENABLE_CFG();
        }
        else if(I2C_SMBus_DISABLE == MSSP_I2C->I2C_CONFIG.I2C_SMBus_Control){
            I2C_SMBus_DISABLE_CFG();
        }
        else{/* Nothing */}
#ifdef MSSP_I2C_INTERRUPT_FEATURE_ENABLE        
        /* Interrupt Configuration */
        MSSP_I2C_INTERRUPT_CONFIGURATIONS(MSSP_I2C);
#endif        
        /* Enable MSSP Module */
        MSSP_I2C_MODULE_ENABLE_CFG();
    }
    return ret;
}
Std_ReturnType MSSP_I2C_DEINIT(const MSSP_I2C_T *MSSP_I2C){
    Std_ReturnType ret = E_NOT_OK;
    if(NULL == MSSP_I2C){
        ret = E_NOT_OK;
    }
    else{
        MSSP_I2C_MODULE_DISABLE_CFG();
#ifdef MSSP_I2C_INTERRUPT_FEATURE_ENABLE
        MSSP_I2C_INTERRUPT_DISABLE();
#ifdef MSSP_I2C_BUS_COL_INTERRUPT_FEATURE_ENABLE
        MSSP_I2C_BUS_COL_INTERRUPT_DISABLE();        
#endif        
#endif        
    }
    return ret; 
}
Std_ReturnType MSSP_I2C_SEND_START_CONDITION(const MSSP_I2C_T *MSSP_I2C){
    Std_ReturnType ret = E_NOT_OK;
    if(NULL == MSSP_I2C){
        ret = E_NOT_OK;
    }
    else{
        I2C_MASTER_START_CONDITION_INIT();
        while(SSPCON2bits.SEN);
        PIR1bits.SSPIF = 0;
        if(I2C_START_BIT_DETECTED == SSPSTATbits.S){
            ret = E_OK;
        }
        else{
            ret = E_NOT_OK;
        }
    }
    return ret;
}
Std_ReturnType MSSP_I2C_SEND_REPEATED_START_CONDITION(const MSSP_I2C_T *MSSP_I2C){
    Std_ReturnType ret = E_NOT_OK;
    if(NULL == MSSP_I2C){
        ret = E_NOT_OK;
    }
    else{
        I2C_REPEATED_START_CONDITION_INIT();
        while(SSPCON2bits.RSEN);
        PIR1bits.SSPIF = 0;
    }
    return ret;
}
Std_ReturnType MSSP_I2C_SEND_STOP_CONDITION(const MSSP_I2C_T *MSSP_I2C){
    Std_ReturnType ret = E_NOT_OK;
    if(NULL == MSSP_I2C){
        ret = E_NOT_OK;
    }
    else{
        I2C_STOP_CONDITION_INIT();
        while(SSPCON2bits.PEN);
        PIR1bits.SSPIF = 0;
        if(I2C_STOP_BIT_DETECTED == SSPSTATbits.P){
            ret = E_OK;
        }
        else{
            ret = E_NOT_OK;
        }
    }
    return ret;
}
Std_ReturnType MSSP_I2C_MASTER_WRITE_BLOCKING(const MSSP_I2C_T *MSSP_I2C, uint8 data, uint8 *_ack){
    Std_ReturnType ret = E_NOT_OK;
    if((NULL == MSSP_I2C) || (NULL == _ack)){
        ret = E_NOT_OK;
    }
    else{
        SSPBUF = data;
        while(!PIR1bits.SSPIF);
        PIR1bits.SSPIF = 0;
        if(I2C_MASTER_RECIEVED_ACK_FROM_SLAVE == SSPCON2bits.ACKSTAT){
            *_ack = I2C_MASTER_RECIEVED_ACK_FROM_SLAVE;
        }
        else{
            *_ack = I2C_MASTER_NOT_RECIEVED_ACK_FROM_SLAVE;
        }
    }
    return ret;
}
Std_ReturnType MSSP_I2C_MASTER_READ_BLOCKING(const MSSP_I2C_T *MSSP_I2C, uint8 ack, uint8 *data){
    Std_ReturnType ret = E_NOT_OK;
    if((NULL == MSSP_I2C) || (NULL == data)){
        ret = E_NOT_OK;
    }
    else{
        I2C_MASTER_RECIEVE_ENABLE_CFG();
        while(!SSPSTATbits.BF);        
        *data = SSPBUF;
        if(I2C_MASTER_SEND_ACK == ack){
            SSPCON2bits.ACKDT = I2C_MASTER_SEND_ACK;
            SSPCON2bits.ACKEN = 1;
            while(SSPCON2bits.ACKEN);
        }
        else if(I2C_MASTER_SEND_NACK == ack){
            SSPCON2bits.ACKDT = I2C_MASTER_SEND_NACK;
            SSPCON2bits.ACKEN = 1;
            while(SSPCON2bits.ACKEN);
        }
        else{/* Nothing */}
    }
    return ret;
}
Std_ReturnType MSSP_I2C_MASTER_WRITE_NBLOCKING(const MSSP_I2C_T *MSSP_I2C, uint8 data, uint8 *_ack){
    Std_ReturnType ret = E_NOT_OK;
    if((NULL == MSSP_I2C) || (NULL == _ack)){
        ret = E_NOT_OK;
    }
    else{
    
        
        ret = E_OK;
    }
    return ret;
}
Std_ReturnType MSSP_I2C_MASTER_READ_NBLOCKING(const MSSP_I2C_T *MSSP_I2C, uint8 ack, uint8 *data){
    Std_ReturnType ret = E_NOT_OK;
    if((NULL == MSSP_I2C) || (NULL == data)){
        ret = E_NOT_OK;
    }
    else{
    
        
        ret = E_OK;
    }
    return ret;    
}
Std_ReturnType MSSP_I2C_SLAVE_WRITE_BLOCKING(const MSSP_I2C_T *MSSP_I2C, uint8 data, uint8 *_ack){
    Std_ReturnType ret = E_NOT_OK;
    if((NULL == MSSP_I2C) || (NULL == _ack)){
        ret = E_NOT_OK;
    }
    else{
        uint8 dummy_buffer = SSPBUF; /* Dummy Buffer used to clear the data in the SSPBUF by reading it*/
        SSPBUF = data;  /*Sent the data you want*/
        if(I2C_MASTER_SEND_NACK == SSPCON2bits.ACKDT){
            *_ack = I2C_MASTER_SEND_NACK;
        }
        else{
            *_ack = I2C_MASTER_SEND_ACK;
        }        
        ret = E_OK;
    }
    return ret;    
}
void MSSP_I2C_SLAVE_READ_BLOCKING(uint8 *data){
        uint8 dummy_buffer = SSPBUF;
        while(!SSPSTATbits.BF); // wait until the BF bit set that means the SSPBUF is now FULL then you can read it
        *data = SSPBUF;
}



static inline void MSSP_I2C_GPIO_CONFIG(){
    TRISCbits.TRISC3 = 1;      
    TRISCbits.TRISC4 = 1;   
}
static inline void MSSP_I2C_MASTER_CLOCK_CONFIG(const MSSP_I2C_T *MSSP_I2C){
    SSPCON1bits.SSPM = MSSP_I2C->I2C_CONFIG.I2C_mode_cfg;
    SSPADD = (uint8)(((_XTAL_FREQ / 4.0) / MSSP_I2C->I2C_Clock) - 1);
}
static inline void MSSP_I2C_SLAVE_CONFIG(const MSSP_I2C_T *MSSP_I2C){
    SSPCON1bits.SSPM = MSSP_I2C->I2C_CONFIG.I2C_mode_cfg;
}
static inline void MSSP_I2C_INTERRUPT_CONFIGURATIONS(const MSSP_I2C_T *MSSP_I2C){
#ifdef MSSP_I2C_INTERRUPT_FEATURE_ENABLE
        MSSP_I2C_INTERRUPT_ENABLE();
        MSSP_I2C_INTERRUPT_FLAG_CLEAR();
        MSSP_I2C_INTERRUPT_HANDLER = MSSP_I2C->I2C_DEFAULT_INTERRUPT_HANDLER;
        MSSP_I2C_RECIEVE_OVERFLOW_INTERRUPT_HANDLER = MSSP_I2C->I2C_REPORT_RECIEVE_OVERFLOW_INDICATOR;
#ifdef MSSP_I2C_BUS_COL_INTERRUPT_FEATURE_ENABLE
        MSSP_I2C_BUS_COL_INTERRUPT_ENABLE();
        MSSP_I2C_BUS_COL_INTERRUPT_FLAG_CLEAR();
        MSSP_I2C_BUS_COL_INTERRUPT_HANDLER = MSSP_I2C->I2C_REPORT_WRITE_COLLISION;
#if  INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE
        INTERRUPT_Priority_Level_Enable();
        if(INTERRUPT_LOW_PRIORITY == MSSP_I2C->MSSP_I2C_BUS_COL_PRIORITY){
            INTERRUPT_GlobalInterruptLowEnable();
            MSSP_I2C_BUS_COL_INTERRUPT_PRIORITY_LOW();
        }
        else if(INTERRUPT_HIGH_PRIORITY == MSSP_I2C->MSSP_I2C_BUS_COL_PRIORITY){
            INTERRUPT_GlobalInterruptHighEnable();
            MSSP_I2C_BUS_COL_INTERRUPT_PRIORITY_HIGH();
        }
        else {/*Nothing*/}        
#endif        
#endif
#if  INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE
        INTERRUPT_Priority_Level_Enable();
        if(INTERRUPT_LOW_PRIORITY == MSSP_I2C->MSSP_I2C_PRIORITY){
            INTERRUPT_GlobalInterruptLowEnable();
            MSSP_I2C_INTERRUPT_PRIORITY_LOW();
        }
        else if(INTERRUPT_HIGH_PRIORITY == MSSP_I2C->MSSP_I2C_PRIORITY){
            INTERRUPT_GlobalInterruptHighEnable();
            MSSP_I2C_INTERRUPT_PRIORITY_HIGH();
        }
        else {/*Nothing*/}
#else
        INTERRUPT_GlobalInterruptEnable();
        INTERRUPT_Peripheral_Interrupt_Enable(); 
#endif
#endif    
}

void MSSP_I2C_ISR(){
#ifdef MSSP_I2C_INTERRUPT_FEATURE_ENABLE    
    MSSP_I2C_INTERRUPT_FLAG_CLEAR();
    if(MSSP_I2C_INTERRUPT_HANDLER){
        MSSP_I2C_INTERRUPT_HANDLER();
    }
#endif    
}

void MSSP_I2C_BUS_COL_ISR(){
#ifdef MSSP_I2C_BUS_COL_INTERRUPT_FEATURE_ENABLE    
    MSSP_I2C_BUS_COL_INTERRUPT_FLAG_CLEAR();
    if(MSSP_I2C_BUS_COL_INTERRUPT_HANDLER){
        MSSP_I2C_BUS_COL_INTERRUPT_HANDLER();
    }
#endif    
}
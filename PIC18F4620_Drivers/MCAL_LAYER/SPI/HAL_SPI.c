/* 
 * File:   HAL_SPI.c
 * Author: Moata
 *
 * Created on September 17, 2026, 1:06 AM
 */

#include "HAL_SPI.h"

static inline void MSSP_SPI_MASTER_CLOCK_CONFIG(const MSSP_SPI_T *MSSP_SPI);
static inline void MSSP_SPI_SLAVE_CONFIG(const MSSP_SPI_T *MSSP_SPI);
static inline void MSSP_SPI_IO_PINS_CONFIG(const MSSP_SPI_T *MSSP_SPI);
static inline void MSSP_SPI_INTERRUPT_CONFIGURATIONS(const MSSP_SPI_T *MSSP_SPI);
#ifdef MSSP_SPI_INTERRUPT_FEATURE_ENABLE
    static void (*MSSP_SPI_INTERRUPT_HANDLER)(void) = NULL;
    static void (*MSSP_SPI_RECIEVE_OVERFLOW_INTERRUPT_HANDLER)(void) = NULL;
#endif
#ifdef MSSP_SPI_BUS_COL_INTERRUPT_FEATURE_ENABLE
    static void (*MSSP_SPI_BUS_COL_INTERRUPT_HANDLER)(void) = NULL;
#endif
    
pin_config_t Slave_select_pin_cfg = {
    .port = PORTA_INDEX,
    .pin = GPIO_PIN5,
    .direction = GPIO_OUTPUT,
    .logic = GPIO_HIGH
};


Std_ReturnType MSSP_SPI_INIT(const MSSP_SPI_T * MSSP_SPI){
    Std_ReturnType ret = E_NOT_OK;
    if(NULL == MSSP_SPI){
        ret = E_NOT_OK;
    }
    else{
        /* Disable SPI Module */
        MSSP_SPI_MODULE_DISABLE_CFG();
        if(MSSP_SPI_MASTER_MODE == MSSP_SPI->SPI_CONFIG.SPI_mode){
            MSSP_SPI_MASTER_CLOCK_CONFIG(MSSP_SPI);
        }
        else if(MSSP_SPI_SLAVE_MODE == MSSP_SPI->SPI_CONFIG.SPI_mode){
            /* Clear Write Collision Detect */
            SPI_WRITE_COLLISION_DETECT_NO_COLLISION();
            /* Clear Receive Overflow Indicator */
            SPI_RECIEVE_OVERFLOW_INDICATOR_NO_OVERFLOW();
            SSPSTATbits.SMP = 0;
            MSSP_SPI_SLAVE_CONFIG(MSSP_SPI);
        }
        else{/* Nothing */}
        if(MSSP_SPI_OUTPUT_DATA_FROM_ACTIVE_TO_IDLE == MSSP_SPI->SPI_CONFIG.SPI_clock_select){
            SPI_OUT_DATA_ACTIVE_TO_IDLE();
        }
        else if(MSSP_SPI_OUTPUT_DATA_FROM_IDLE_TO_ACTIVE == MSSP_SPI->SPI_CONFIG.SPI_clock_select){
            SPI_OUT_DATA_IDLE_TO_ACTIVE();
        }
        else{/* Nothing */}
        MSSP_SPI_IO_PINS_CONFIG(MSSP_SPI);
        /* Interrupt Configuration */
        MSSP_SPI_INTERRUPT_CONFIGURATIONS(MSSP_SPI);
        /* Enable SPI Module */
        MSSP_SPI_MODULE_ENABLE_CFG();
        ret = E_OK;
    }
    return ret;
}
Std_ReturnType MSSP_SPI_DEINIT(const MSSP_SPI_T * MSSP_SPI){
    Std_ReturnType ret = E_NOT_OK;
    if(NULL == MSSP_SPI){
        ret = E_NOT_OK;
    }
    else{
        MSSP_SPI_MODULE_DISABLE_CFG();
#ifdef MSSP_SPI_INTERRUPT_FEATURE_ENABLE
        MSSP_SPI_INTERRUPT_DISABLE();
#ifdef MSSP_SPI_BUS_COL_INTERRUPT_FEATURE_ENABLE
        MSSP_SPI_BUS_COL_INTERRUPT_DISABLE();        
#endif        
#endif        
        ret = E_OK;
    }
    return ret;
}
Std_ReturnType MSSP_SPI_MASTER_SEND_DATA_BLOCKING(const MSSP_SPI_T * MSSP_SPI, uint8 data){
    Std_ReturnType ret = E_NOT_OK;
    uint8 dummy_read = 0;
    if(NULL == MSSP_SPI){
        ret = E_NOT_OK;
    }
    else{
        ret = gpio_pin_write_logic(&Slave_select_pin_cfg, GPIO_LOW); // Hold Slave select 
        PIR1bits.SSPIF = 0; // Clear Flag
        SSPBUF = data;  // Send the data
        while(!PIR1bits.SSPIF); // Wait until the data have been transmitted the flag will set
        dummy_read = SSPBUF;    // Read the SSPBUF To remove the data from it
        ret = gpio_pin_write_logic(&Slave_select_pin_cfg, GPIO_HIGH);   // Release the Slave Select
        ret = E_OK;
    }
    return ret;
}
Std_ReturnType MSSP_SPI_MASTER_READ_DATA_BLOCKING(const MSSP_SPI_T * MSSP_SPI, uint8 *data){
    Std_ReturnType ret = E_NOT_OK;
    if((NULL == MSSP_SPI) || (NULL == data)){
        ret = E_NOT_OK;
    }
    else{
        
        
        ret = E_OK;
    }
    return ret;
}
Std_ReturnType MSSP_SPI_MASTER_SEND_DATA_NBLOCKING(const MSSP_SPI_T * MSSP_SPI, uint8 data){
    Std_ReturnType ret = E_NOT_OK;
    if(NULL == MSSP_SPI){
        ret = E_NOT_OK;
    }
    else{
        
        
        ret = E_OK;
    }
    return ret;
}
Std_ReturnType MSSP_SPI_MASTER_READ_DATA_NBLOCKING(const MSSP_SPI_T * MSSP_SPI, uint8 *data){
    Std_ReturnType ret = E_NOT_OK;
    if((NULL == MSSP_SPI) || (NULL == data)){
        ret = E_NOT_OK;
    }
    else{
        
        
        ret = E_OK;
    }
    return ret;
}
Std_ReturnType MSSP_SPI_SLAVE_SEND_DATA_BLOCKING(const MSSP_SPI_T * MSSP_SPI, uint8 data){
    Std_ReturnType ret = E_NOT_OK;
    if(NULL == MSSP_SPI){
        ret = E_NOT_OK;
    }
    else{

        ret = E_OK;
    }
    return ret;
}
Std_ReturnType MSSP_SPI_SLAVE_READ_DATA_BLOCKING(const MSSP_SPI_T * MSSP_SPI, uint8 *data){
    Std_ReturnType ret = E_NOT_OK;
    if((NULL == MSSP_SPI) || (NULL == data)){
        ret = E_NOT_OK;
    }
    else{
        while(!SSPSTATbits.BF); // Wait until the last bit is received
        *data = SSPBUF; // Read the Data
        ret = E_OK;
    }
    return ret;
}

static inline void MSSP_SPI_MASTER_CLOCK_CONFIG(const MSSP_SPI_T *MSSP_SPI){
    SSPCON1bits.SSPM = MSSP_SPI->SPI_CONFIG.SPI_mode_cfg;
    if(MSSP_SPI_CP_IDLE_HIGH_LEVEL == MSSP_SPI->SPI_CONFIG.SPI_clock_polarity){
        SPI_CLOCK_POLARITY_IDLE_STATE_HIGH_LEVEL();  
    }
    else if(MSSP_SPI_CP_IDLE_LOW_LEVEL == MSSP_SPI->SPI_CONFIG.SPI_clock_polarity){
        SPI_CLOCK_POLARITY_IDLE_STATE_LOW_LEVEL();
    }
    else{/* Nothing */}
    if(MSSP_SPI_SAMPLE_RATE_AT_END_OF_DATA == MSSP_SPI->SPI_CONFIG.SPI_sample_cfg){
        SPI_SAMPLE_AT_END();
    }
    else if(MSSP_SPI_SAMPLE_RATE_AT_MIDDLE_OF_DATA == MSSP_SPI->SPI_CONFIG.SPI_sample_cfg){
        SPI_SAMPLE_AT_MIDDLE();
    }
    else{/* Nothing */}
}
static inline void MSSP_SPI_SLAVE_CONFIG(const MSSP_SPI_T *MSSP_SPI){
    SSPCON1bits.SSPM = MSSP_SPI->SPI_CONFIG.SPI_mode_cfg;
}
static inline void MSSP_SPI_IO_PINS_CONFIG(const MSSP_SPI_T *MSSP_SPI){
    if(MSSP_SPI_MASTER_MODE == MSSP_SPI->SPI_CONFIG.SPI_mode){
        TRISCbits.TRISC5 = 0;
        TRISCbits.TRISC3 = 0;
        TRISAbits.TRISA5 = 0; // Chip Select pin
    }
    else if(MSSP_SPI_SLAVE_MODE == MSSP_SPI->SPI_CONFIG.SPI_mode){
        TRISCbits.TRISC5 = 0;
        TRISCbits.TRISC3 = 1;
    }
    else{/* Nothing */}

}
static inline void MSSP_SPI_INTERRUPT_CONFIGURATIONS(const MSSP_SPI_T *MSSP_SPI){
#ifdef MSSP_SPI_INTERRUPT_FEATURE_ENABLE
        MSSP_SPI_INTERRUPT_ENABLE();
        MSSP_SPI_INTERRUPT_FLAG_CLEAR();
        MSSP_SPI_INTERRUPT_HANDLER = MSSP_SPI->SPI_DEFAULT_INTERRUPT_HANDLER;
        MSSP_SPI_RECIEVE_OVERFLOW_INTERRUPT_HANDLER = MSSP_SPI->SPI_REPORT_RECIEVE_OVERFLOW_INDICATOR;
#ifdef MSSP_SPI_BUS_COL_INTERRUPT_FEATURE_ENABLE
        MSSP_SPI_BUS_COL_INTERRUPT_ENABLE();
        MSSP_SPI_BUS_COL_INTERRUPT_FLAG_CLEAR();
        MSSP_SPI_BUS_COL_INTERRUPT_HANDLER = MSSP_SPI->SPI_REPORT_WRITE_COLLISION;
#if  INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE
        INTERRUPT_Priority_Level_Enable();
        if(INTERRUPT_LOW_PRIORITY == MSSP_SPI->MSSP_SPI_BUS_COL_PRIORITY){
            INTERRUPT_GlobalInterruptLowEnable();
            MSSP_SPI_BUS_COL_INTERRUPT_PRIORITY_LOW();
        }
        else if(INTERRUPT_HIGH_PRIORITY == MSSP_SPI->MSSP_SPI_BUS_COL_PRIORITY){
            INTERRUPT_GlobalInterruptHighEnable();
            MSSP_SPI_BUS_COL_INTERRUPT_PRIORITY_HIGH();
        }
        else {/*Nothing*/}        
#endif        
#endif
#if  INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE
        INTERRUPT_Priority_Level_Enable();
        if(INTERRUPT_LOW_PRIORITY == MSSP_SPI->MSSP_SPI_PRIORITY){
            INTERRUPT_GlobalInterruptLowEnable();
            MSSP_SPI_INTERRUPT_PRIORITY_LOW();
        }
        else if(INTERRUPT_HIGH_PRIORITY == MSSP_SPI->MSSP_SPI_PRIORITY){
            INTERRUPT_GlobalInterruptHighEnable();
            MSSP_SPI_INTERRUPT_PRIORITY_HIGH();
        }
        else {/*Nothing*/}
#else
        INTERRUPT_GlobalInterruptEnable();
        INTERRUPT_Peripheral_Interrupt_Enable(); 
#endif
#endif    
}


void MSSP_SPI_ISR(){
#ifdef MSSP_SPI_INTERRUPT_FEATURE_ENABLE    
    MSSP_SPI_INTERRUPT_FLAG_CLEAR();
    if(MSSP_SPI_INTERRUPT_HANDLER){
        MSSP_SPI_INTERRUPT_HANDLER();
    }
#endif    
}

void MSSP_SPI_BUS_COL_ISR(){
#ifdef MSSP_SPI_BUS_COL_INTERRUPT_FEATURE_ENABLE    
    MSSP_SPI_BUS_COL_INTERRUPT_FLAG_CLEAR();
    if(MSSP_SPI_BUS_COL_INTERRUPT_HANDLER){
        MSSP_SPI_BUS_COL_INTERRUPT_HANDLER();
    }
#endif    
}
/* 
 * File:   HAL_USART.c
 * Author: Moata
 *
 * Created on July 23, 2026, 6:54 PM
 */

#include "HAL_USART.h"

#ifdef  EUSART_ASYNCHRONOUS_TX_INTERRUPT_FEATURE_ENABLE
static void (*EUSART_TX_INTERRUPT_HANDLER)(void) = NULL;
#endif
#ifdef  EUSART_ASYNCHRONOUS_RX_INTERRUPT_FEATURE_ENABLE
static void (*EUSART_RX_INTERRUPT_HANDLER)(void) = NULL;
static void (*EUSART_FRAMING_ERROR_INTERRUPT_HANDLER)(void) = NULL;
static void (*EUSART_OVERRUN_ERROR_INTERRUPT_HANDLER)(void) = NULL;
#endif
static void EUSART_BAUDRATE_CALCULATION(const EUSART_CFG_T *EUSART_CFG);
static void EUSART_TX_INIT(const EUSART_CFG_T *EUSART_CFG);
static void EUSART_RX_INIT(const EUSART_CFG_T *EUSART_CFG);

Std_ReturnType EUSART_ASYNC_INIT(const EUSART_CFG_T *EUSART_CFG){
    Std_ReturnType ret = E_OK;
    if(NULL == EUSART_CFG){
        ret = E_NOT_OK;
    }
    else{
        EUSART_MODULE_DISABLE();
        TRISCbits.RC7 = 1;
        TRISCbits.RC6 = 1;
        EUSART_BAUDRATE_CALCULATION(EUSART_CFG);
        EUSART_TX_INIT(EUSART_CFG);
        EUSART_RX_INIT(EUSART_CFG);
        
        EUSART_MODULE_ENABLE();
    }
    return ret;
}
Std_ReturnType EUSART_ASYNC_DEINIT(const EUSART_CFG_T *EUSART_CFG){
    Std_ReturnType ret = E_OK;
    if(NULL == EUSART_CFG){
        ret = E_NOT_OK;
    }
    else{
        EUSART_MODULE_DISABLE();
#ifdef EUSART_ASYNCHRONOUS_TX_INTERRUPT_FEATURE_ENABLE
        EUSART_ASYNCHRONOUS_TX_INTERRUPT_DISABLE();
#endif
#ifdef EUSART_ASYNCHRONOUS_RX_INTERRUPT_FEATURE_ENABLE
        EUSART_ASYNCHRONOUS_RX_INTERRUPT_DISABLE();
#endif        
    }
    return ret;
}
Std_ReturnType EUSART_READ_BYTE_BLOCKING(uint8 *Data){
    Std_ReturnType ret = E_OK;
    if(NULL == Data){
        ret = E_NOT_OK;
    }
    else{
        while(!PIR1bits.RCIF);
        *Data = RCREG;
    }
    return ret;
}
Std_ReturnType EUSART_READ_BYTE_NON_BLOCKING(uint8 *Data){
    Std_ReturnType ret = E_OK;
    if(NULL == Data){
        ret = E_NOT_OK;
    }
    else{
        if(1 == PIR1bits.RCIF){
            *Data = RCREG;
        }
        else{/* Nothing */}
    }
    return ret;
}
void EUSART_READ_RESTART_ERROR(void){
    RCSTAbits.CREN = 0;
    RCSTAbits.CREN = 1;
}
Std_ReturnType EUSART_WRITE_BYTE_BLOCKING(uint8 Data){
    Std_ReturnType ret = E_OK;
    while(!TXSTAbits.TRMT);
    EUSART_ASYNCHRONOUS_TX_INTERRUPT_ENABLE();
    TXREG = Data;
    return ret;
}
Std_ReturnType EUSART_WRITE_STRING_BLOCKING(uint8 *Data, uint16 str_len){
    Std_ReturnType ret = E_OK;
    uint16 str_counter = 0;
    if(NULL == Data){
        ret = E_NOT_OK;
    }
    else{
        for(str_counter = 0; str_counter < str_len; str_counter++){
            ret = EUSART_WRITE_BYTE_BLOCKING(Data[str_counter]);
        }
    }
    return ret;
}

Std_ReturnType EUSART_WRITE_BYTE_NON_BLOCKING(uint8 Data){
    Std_ReturnType ret = E_OK;
    if(PIR1bits.TXIF){
        TXREG = Data;
        while(!PIR1bits.TXIF);
    }
    else{/* Nothing */}
    EUSART_ASYNCHRONOUS_TX_INTERRUPT_ENABLE();
    return ret;
}
Std_ReturnType EUSART_WRITE_STRING_NON_BLOCKING(uint8 *Data, uint16 str_len){
    Std_ReturnType ret = E_OK;
    uint16 str_counter = 0;
    if(NULL == Data){
        ret = E_NOT_OK;
    }
    else{
        for(str_counter = 0; str_counter < str_len; str_counter++){
            ret = EUSART_WRITE_BYTE_NON_BLOCKING(Data[str_counter]);
        }
    }
    return ret;
}
static void EUSART_BAUDRATE_CALCULATION(const EUSART_CFG_T *EUSART_CFG){
    float Baudrate_temp = 0;
    switch(EUSART_CFG->BAUDRATE_GEN_CFG){
        case EUSART_BAUDRATE_GEN_ASYN_8BIT_LOW_SPEED:
            TXSTAbits.SYNC = EUSART_ASYNCHRONOUS_MODE;
            TXSTAbits.BRGH = EUSART_ASYNCHRONOUS_LOW_SPEED;
            BAUDCONbits.BRG16 = EUSART_ASYNCHRONOUS_8_BIT_BAUDRATE_GEN;
            Baudrate_temp = ((_XTAL_FREQ / (float)EUSART_CFG->BAUDRATE) / 64) - 1;
            break;
        case EUSART_BAUDRATE_GEN_ASYN_8BIT_HIGH_SPEED:
            TXSTAbits.SYNC = EUSART_ASYNCHRONOUS_MODE;
            TXSTAbits.BRGH = EUSART_ASYNCHRONOUS_HIGH_SPEED;
            BAUDCONbits.BRG16 = EUSART_ASYNCHRONOUS_8_BIT_BAUDRATE_GEN;
            Baudrate_temp = ((_XTAL_FREQ / (float)EUSART_CFG->BAUDRATE) / 16) - 1;
            break;
        case EUSART_BAUDRATE_GEN_ASYN_16BIT_LOW_SPEED:
            TXSTAbits.SYNC = EUSART_ASYNCHRONOUS_MODE;
            TXSTAbits.BRGH = EUSART_ASYNCHRONOUS_LOW_SPEED;
            BAUDCONbits.BRG16 = EUSART_ASYNCHRONOUS_16_BIT_BAUDRATE_GEN;
            Baudrate_temp = ((_XTAL_FREQ / (float)EUSART_CFG->BAUDRATE) / 16) - 1;
            break;
        case EUSART_BAUDRATE_GEN_ASYN_16BIT_HIGH_SPEED:
            TXSTAbits.SYNC = EUSART_ASYNCHRONOUS_MODE;
            TXSTAbits.BRGH = EUSART_ASYNCHRONOUS_HIGH_SPEED;
            BAUDCONbits.BRG16 = EUSART_ASYNCHRONOUS_16_BIT_BAUDRATE_GEN;
            Baudrate_temp = ((_XTAL_FREQ / (float)EUSART_CFG->BAUDRATE) / 4) - 1;
            break;
        case EUSART_BAUDRATE_GEN_SYN_8BIT:
            TXSTAbits.SYNC = EUSART_SYNCHRONOUS_MODE;
            BAUDCONbits.BRG16 = EUSART_ASYNCHRONOUS_8_BIT_BAUDRATE_GEN;
            Baudrate_temp = ((_XTAL_FREQ / (float)EUSART_CFG->BAUDRATE) / 4) - 1;
            break;
        case EUSART_BAUDRATE_GEN_SYN_16BIT:
            TXSTAbits.SYNC = EUSART_SYNCHRONOUS_MODE;
            BAUDCONbits.BRG16 = EUSART_ASYNCHRONOUS_16_BIT_BAUDRATE_GEN;
            Baudrate_temp = ((_XTAL_FREQ / (float)EUSART_CFG->BAUDRATE) / 4) - 1;
            break;    
        default: ;    
    }
    SPBRG = (uint8)((uint32)Baudrate_temp);
    SPBRGH = (uint8)(((uint32)Baudrate_temp) >> 8);
}
static void EUSART_TX_INIT(const EUSART_CFG_T *EUSART_CFG){
    if(EUSART_ASYNCHRONOUS_TX_ENABLE == EUSART_CFG->EUSART_TX_CONFIG.eusart_tx_enable_cfg){
        TXSTAbits.TXEN = EUSART_ASYNCHRONOUS_TX_ENABLE;
        if(EUSART_ASYNCHRONOUS_TX_9TH_BIT_MODE == EUSART_CFG->EUSART_TX_CONFIG.eusart_tx_9th_bit_cfg){
            TXSTAbits.TX9 = EUSART_ASYNCHRONOUS_TX_9TH_BIT_MODE;
        }
        else if(EUSART_ASYNCHRONOUS_TX_8TH_BIT_MODE == EUSART_CFG->EUSART_TX_CONFIG.eusart_tx_9th_bit_cfg){
            TXSTAbits.TX9 = EUSART_ASYNCHRONOUS_TX_8TH_BIT_MODE;
        }
        else{/* Nothing */}
        if(EUSART_ASYNC_TX_INTERRUPT_ENABLE == EUSART_CFG->EUSART_TX_CONFIG.eusart_tx_interrupt_enable_cfg){
            EUSART_ASYNCHRONOUS_TX_INTERRUPT_ENABLE();
#if  INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE
        INTERRUPT_Priority_Level_Enable();
        if(INTERRUPT_LOW_PRIORITY == EUSART_CFG->EUSART_TX_CONFIG.Eusart_tx_priority){
            INTERRUPT_GlobalInterruptLowEnable();
            TIMER0_INTERRUPT_PRIORITY_LOW();
        }
        else if(INTERRUPT_HIGH_PRIORITY == EUSART_CFG->EUSART_TX_CONFIG.Eusart_tx_priority){
            INTERRUPT_GlobalInterruptHighEnable();
            TIMER0_INTERRUPT_PRIORITY_HIGH();
        }
        else {/*Nothing*/}
#else
        INTERRUPT_GlobalInterruptEnable();
        INTERRUPT_Peripheral_Interrupt_Enable(); 
#endif            
            EUSART_TX_INTERRUPT_HANDLER = EUSART_CFG->EUSART_TX_INTERRUPT_HANDLER;
        }
        else if(EUSART_ASYNC_TX_INTERRUPT_DISABLE == EUSART_CFG->EUSART_TX_CONFIG.eusart_tx_interrupt_enable_cfg){
            EUSART_ASYNCHRONOUS_TX_INTERRUPT_DISABLE();
        }
        else{/* Nothing */}
    }
    else{/* Nothing */}
    
}

static void EUSART_RX_INIT(const EUSART_CFG_T *EUSART_CFG){
    if(EUSART_ASYNCHRONOUS_RX_ENABLE == EUSART_CFG->EUSART_RX_CONFIG.eusart_rx_enable_cfg){
        RCSTAbits.CREN = EUSART_ASYNCHRONOUS_RX_ENABLE;
        if(EUSART_ASYNCHRONOUS_RX_9TH_BIT_MODE == EUSART_CFG->EUSART_RX_CONFIG.eusart_rx_9th_bit_cfg){
            RCSTAbits.RX9 = EUSART_ASYNCHRONOUS_RX_9TH_BIT_MODE;
        }
        else if(EUSART_ASYNCHRONOUS_RX_8TH_BIT_MODE == EUSART_CFG->EUSART_RX_CONFIG.eusart_rx_9th_bit_cfg){
            RCSTAbits.RX9 = EUSART_ASYNCHRONOUS_RX_8TH_BIT_MODE;
        }
        else{/* Nothing */}
        if(EUSART_ASYNC_RX_INTERRUPT_ENABLE == EUSART_CFG->EUSART_RX_CONFIG.eusart_rx_interrupt_enable_cfg){
            EUSART_ASYNCHRONOUS_RX_INTERRUPT_ENABLE();
#if  INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE
        INTERRUPT_Priority_Level_Enable();
        if(INTERRUPT_LOW_PRIORITY == EUSART_CFG->EUSART_RX_CONFIG.Eusart_rx_priority){
            INTERRUPT_GlobalInterruptLowEnable();
            TIMER0_INTERRUPT_PRIORITY_LOW();
        }
        else if(INTERRUPT_HIGH_PRIORITY == EUSART_CFG->EUSART_RX_CONFIG.Eusart_rx_priority){
            INTERRUPT_GlobalInterruptHighEnable();
            TIMER0_INTERRUPT_PRIORITY_HIGH();
        }
        else {/*Nothing*/}
#else
        INTERRUPT_GlobalInterruptEnable();
        INTERRUPT_Peripheral_Interrupt_Enable(); 
#endif               
            EUSART_RX_INTERRUPT_HANDLER = EUSART_CFG->EUSART_RX_INTERRUPT_HANDLER;
        }
        else if(EUSART_ASYNC_RX_INTERRUPT_DISABLE == EUSART_CFG->EUSART_RX_CONFIG.eusart_rx_interrupt_enable_cfg){
            EUSART_ASYNCHRONOUS_RX_INTERRUPT_DISABLE();
        }
        else{/* Nothing */}
    }
    else{/* Nothing */}
}
void EUSART_TX_ISR(void){
    if(EUSART_TX_INTERRUPT_HANDLER){
        EUSART_TX_INTERRUPT_HANDLER();
        EUSART_ASYNCHRONOUS_TX_INTERRUPT_DISABLE();
    }
    else{/* Nothing */}
}
void EUSART_RX_ISR(void){
    volatile uint16 temp_rx_val = 0;
    if(EUSART_RX_INTERRUPT_HANDLER){
        EUSART_RX_INTERRUPT_HANDLER();
        temp_rx_val = RCREG;
    }
    else if(EUSART_FRAMING_ERROR_INTERRUPT_HANDLER){
        EUSART_FRAMING_ERROR_INTERRUPT_HANDLER();
    }
    else if(EUSART_OVERRUN_ERROR_INTERRUPT_HANDLER){
        EUSART_OVERRUN_ERROR_INTERRUPT_HANDLER();
    }
    else{/* Nothing */}
}
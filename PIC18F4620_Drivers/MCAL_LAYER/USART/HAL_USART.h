/* 
 * File:   HAL_USART.h
 * Author: Moata
 *
 * Created on July 23, 2026, 6:54 PM
 */

#ifndef HAL_USART_H
#define	HAL_USART_H

// Section: Includes
#include "HAL_USART_CFG.h"
#include "../GPIO/HAL_GPIO.h"
#include "pic18f4620.h"
#include "../../MCAL_LAYER/Interrupt/MCAL_INTERNAL_INTERRUPT.h"
// Section: Macro Declarations

/* Serial Port Enable bit */
#define EUSART_SERIAL_PORT_ENABLE   1
#define EUSART_SERIAL_PORT_DISABLE  0

/* EUSART Mode Select bit */
#define EUSART_ASYNCHRONOUS_MODE        0
#define EUSART_SYNCHRONOUS_MODE         1

/* Baud Rate Speed Select bit */
#define EUSART_ASYNCHRONOUS_HIGH_SPEED       1
#define EUSART_ASYNCHRONOUS_LOW_SPEED        0

/* 16-bit Baud Rate Generator bit */
#define EUSART_ASYNCHRONOUS_16_BIT_BAUDRATE_GEN       1
#define EUSART_ASYNCHRONOUS_8_BIT_BAUDRATE_GEN        0

/* Transmit Enable bit */
#define EUSART_ASYNCHRONOUS_TX_ENABLE   1
#define EUSART_ASYNCHRONOUS_TX_DISABLE  0   

/* Transmit Interrupt Enable bit */
#define EUSART_ASYNC_TX_INTERRUPT_ENABLE   1
#define EUSART_ASYNC_TX_INTERRUPT_DISABLE  0   

/* Ninth bit of Transmit Data */
#define EUSART_ASYNCHRONOUS_TX_9TH_BIT_MODE    1
#define EUSART_ASYNCHRONOUS_TX_8TH_BIT_MODE    0

/* Continuous Receive Enable bit */
#define EUSART_ASYNCHRONOUS_RX_ENABLE   1
#define EUSART_ASYNCHRONOUS_RX_DISABLE  0   

/* Receiver Interrupt Enable bit */
#define EUSART_ASYNC_RX_INTERRUPT_ENABLE   1
#define EUSART_ASYNC_RX_INTERRUPT_DISABLE  0   

/* 9-bit Receive Enable bit */
#define EUSART_ASYNCHRONOUS_RX_9TH_BIT_MODE    1
#define EUSART_ASYNCHRONOUS_RX_8TH_BIT_MODE    0

/* Framing Error bit */
#define EUSART_FRAMING_ERROR_DETECT        1
#define EUSART_NO_FRAMING_ERROR_DETECT     0

/* Overrun Error bit */
#define EUSART_OVER_RUN_ERROR_DETECT        1
#define EUSART_NO_OVER_RUN_ERROR_DETECT     0

// Section: Macro Functions Declarations

/* EUSART Module Enable Bit*/
#define EUSART_MODULE_ENABLE()               (RCSTAbits.SPEN = 1)
#define EUSART_MODULE_DISABLE()              (RCSTAbits.SPEN = 0)

// Section: Data Type Declarations
typedef enum{
    EUSART_BAUDRATE_GEN_ASYN_8BIT_LOW_SPEED = 0,
    EUSART_BAUDRATE_GEN_ASYN_8BIT_HIGH_SPEED,
    EUSART_BAUDRATE_GEN_ASYN_16BIT_LOW_SPEED,
    EUSART_BAUDRATE_GEN_ASYN_16BIT_HIGH_SPEED,
    EUSART_BAUDRATE_GEN_SYN_8BIT,
    EUSART_BAUDRATE_GEN_SYN_16BIT
}EUSART_BAUDRATE_GEN_CFG_T;

typedef struct{
    uint8 eusart_tx_reserved : 5;
    uint8 eusart_tx_enable_cfg : 1;
#ifdef  EUSART_ASYNCHRONOUS_TX_INTERRUPT_FEATURE_ENABLE    
    interrupt_priority_t Eusart_tx_priority;
    uint8 eusart_tx_interrupt_enable_cfg : 1;
#endif    
    uint8 eusart_tx_9th_bit_cfg : 1;
}EUSART_TX_CONFIG_T;

typedef struct{
    uint8 eusart_rx_reserved : 5;
    uint8 eusart_rx_enable_cfg : 1;
#ifdef  EUSART_ASYNCHRONOUS_TX_INTERRUPT_FEATURE_ENABLE
    interrupt_priority_t Eusart_rx_priority;
    uint8 eusart_rx_interrupt_enable_cfg : 1;
#endif
    uint8 eusart_rx_9th_bit_cfg : 1;
}EUSART_RX_CONFIG_T;

typedef union{
    struct{
        uint8 eusart_error_reserved : 6;
        uint8 frame_error : 1;
        uint8 overrun_error : 1;
    };
    uint8 EUSART_STATUS;
}EUSART_ERROR_STATUS_T;

typedef struct{
    uint32 BAUDRATE;
    EUSART_BAUDRATE_GEN_CFG_T   BAUDRATE_GEN_CFG;
    EUSART_TX_CONFIG_T          EUSART_TX_CONFIG;
    EUSART_RX_CONFIG_T          EUSART_RX_CONFIG;
    EUSART_ERROR_STATUS_T       EUSART_ERROR_STATUS;
    void (*EUSART_TX_INTERRUPT_HANDLER)(void);
    void (*EUSART_RX_INTERRUPT_HANDLER)(void);
    void (*EUSART_FRAMING_ERROR_INTERRUPT_HANDLER)(void);
    void (*EUSART_OVERRUN_ERROR_INTERRUPT_HANDLER)(void);
}EUSART_CFG_T;

// Section: Function Declarations

Std_ReturnType EUSART_ASYNC_INIT(const EUSART_CFG_T *EUSART_CFG);
Std_ReturnType EUSART_ASYNC_DEINIT(const EUSART_CFG_T *EUSART_CFG);
Std_ReturnType EUSART_READ_BYTE_BLOCKING(uint8 *Data);
Std_ReturnType EUSART_READ_BYTE_NON_BLOCKING(uint8 *Data);
void EUSART_READ_RESTART_ERROR(void);

Std_ReturnType EUSART_WRITE_BYTE_BLOCKING(uint8 Data);
Std_ReturnType EUSART_WRITE_STRING_BLOCKING(uint8 *Data, uint16 str_len);
Std_ReturnType EUSART_WRITE_BYTE_NON_BLOCKING(uint8 Data);
Std_ReturnType EUSART_WRITE_STRING_NON_BLOCKING(uint8 *Data, uint16 str_len);
#endif	/* HAL_USART_H */


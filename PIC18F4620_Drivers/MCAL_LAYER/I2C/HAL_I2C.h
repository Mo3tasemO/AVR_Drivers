/* 
 * File:   HAL_I2C.h
 * Author: Moata
 *
 * Created on September 3, 2026, 1:55 PM
 */

#ifndef HAL_I2C_H
#define	HAL_I2C_H

// Section: Includes
#include "HAL_I2C_CFG.h"
#include "../GPIO/HAL_GPIO.h"
#include "pic18f4620.h"
#include "../../MCAL_LAYER/Interrupt/MCAL_INTERNAL_INTERRUPT.h"
// Section: Macro Declarations
/* I2C Module Enable/Disable*/
#define MSSP_I2C_MODULE_ENABLE      1
#define MSSP_I2C_MODULE_DISABLE     0
/* Slew Rate Control bit */
#define I2C_SLEW_RATE_ENABLE     0
#define I2C_SLEW_RATE_DISABLE    1
/* SMBus Select bit */
#define I2C_SMBus_ENABLE         1
#define I2C_SMBus_DISABLE        0
/* Slave mode Data/Address bit */
#define I2C_LAST_BYTE_DATA          1
#define I2C_LAST_BYTE_ADDRESS       0
/* Stop Bit Indication */
#define I2C_STOP_BIT_DETECTED       1
#define I2C_STOP_BIT_NOT_DETECTED   0
/* Start Bit Indication */
#define I2C_START_BIT_DETECTED       1
#define I2C_START_BIT_NOT_DETECTED   0
/* Slave General Call bit */
#define I2C_GENERAL_CALL_ENABLE      1
#define I2C_GENERAL_CALL_DISABLE     0
/* Synchronous Serial Port Mode Select bits */
#define I2C_SLAVE_MODE_7_BIT_ADDRESS                    0x06U
#define I2C_SLAVE_MODE_10_BIT_ADDRESS                   0x07U
#define I2C_MASTER_MODE_DEFINED_CLOCK                   0x08U
#define I2C_FIRMWARE_CONTROLLED_MASTER_MODE_SLAVE_IDLE  0x0BU
#define I2C_SLAVE_MODE_7_BIT_START_STOP_ENABLE          0x0EU
#define I2C_SLAVE_MODE_10_BIT_START_STOP_ENABLE         0x0FU
/* I2C Master/Slave Select*/
#define MSSP_I2C_MASTER_MODE        1
#define MSSP_I2C_SLAVE_MODE         0
/* Master Receive Enable bit */
#define I2C_MASTER_RECIEVE_ENABLE   1
#define I2C_MASTER_RECIEVE_DISABLE  0
/* Acknowledge Status bit (Master Transmit mode only) */
#define I2C_MASTER_RECIEVED_ACK_FROM_SLAVE         0
#define I2C_MASTER_NOT_RECIEVED_ACK_FROM_SLAVE     1
/*  Acknowledge Data bit (Master Receive mode only) */
#define I2C_MASTER_SEND_ACK     0
#define I2C_MASTER_SEND_NACK    1

// Section: Macro Functions Declarations
#define MSSP_I2C_MODULE_ENABLE_CFG()         (SSPCON1bits.SSPEN = 1)
#define MSSP_I2C_MODULE_DISABLE_CFG()        (SSPCON1bits.SSPEN = 0)

#define I2C_SLEW_RATE_ENABLE_CFG()           (SSPSTATbits.SMP = 0)
#define I2C_SLEW_RATE_DISABLE_CFG()          (SSPSTATbits.SMP = 1)

#define I2C_SMBus_ENABLE_CFG()               (SSPSTATbits.CKE = 1)
#define I2C_SMBus_DISABLE_CFG()              (SSPSTATbits.CKE = 0)

#define I2C_GENERAL_CALL_ENABLE_CFG()        (SSPCON2bits.GCEN = 1)
#define I2C_GENERAL_CALL_DISABLE_CFG()       (SSPCON2bits.GCEN = 0)

#define I2C_MASTER_RECIEVE_ENABLE_CFG()      (SSPCON2bits.RCEN = 1)
#define I2C_MASTER_RECIEVE_DISABLE_CFG()     (SSPCON2bits.RCEN = 0)

#define I2C_STOP_CONDITION_INIT()            (SSPCON2bits.PEN = 1)
#define I2C_STOP_CONDITION_IDLE()            (SSPCON2bits.PEN = 0)

#define I2C_REPEATED_START_CONDITION_INIT()  (SSPCON2bits.RSEN = 1)
#define I2C_REPEATED_START_CONDITION_IDLE()  (SSPCON2bits.RSEN = 0)

#define I2C_MASTER_START_CONDITION_INIT()    (SSPCON2bits.SEN = 1)
#define I2C_MASTER_START_CONDITION_IDLE()    (SSPCON2bits.SEN = 0)

#define I2C_SLAVE_CLOCK_STRETCHING_ENABLE()  (SSPCON2bits.SEN = 1)  // IN SLAVE MODE ONLY
#define I2C_SLAVE_CLOCK_STRETCHING_DISABLE() (SSPCON2bits.SEN = 0)  // IN SLAVE MODE ONLY

#define I2C_SLAVE_SCK_RELEASE_CONTROL_HOLD()    (SSPCON1bits.CKP = 0)
#define I2C_SLAVE_SCK_RELEASE_CONTROL_RELEASE() (SSPCON1bits.CKP = 1)

#define I2C_WRITE_COLLISION_DETECT_NO_COLLISION()    (SSPCON1bits.WCOL = 0)
#define I2C_RECIEVE_OVERFLOW_INDICATOR_NO_OVERFLOW() (SSPCON1bits.SSPOV = 0)

// Section: Data Type Declarations
typedef struct{
    uint8 I2C_mode_cfg; /* Synchronous Serial Port Mode Select bits */
    uint8 I2C_Salve_Add;
    uint8 I2C_mode : 1; /* Master/Slave Mode */
    uint8 I2C_slew_rate : 1; /* Slew Rate Enable/Disable */
    uint8 I2C_SMBus_Control : 1; /* SMBus Enable/Disable */
    uint8 I2C_General_Call : 1;/* General Call Enable/Disable*/
    uint8 I2C_Master_Recieve_Mode : 1; /* Master In Recieve Mode Enable/Disable*/
    uint8 I2C_Reserved : 3;
}I2C_CONFIG_T;
typedef struct {
    uint32 I2C_Clock;
#ifdef MSSP_I2C_INTERRUPT_FEATURE_ENABLE        
    void (*I2C_DEFAULT_INTERRUPT_HANDLER)(void);
    void (*I2C_REPORT_WRITE_COLLISION)(void);
    interrupt_priority_t MSSP_I2C_PRIORITY;
    interrupt_priority_t MSSP_I2C_BUS_COL_PRIORITY;
#endif    
    void (*I2C_REPORT_RECIEVE_OVERFLOW_INDICATOR)(void);
    I2C_CONFIG_T I2C_CONFIG;
}MSSP_I2C_T;
// Section: Function Declarations
Std_ReturnType MSSP_I2C_INIT(const MSSP_I2C_T *MSSP_I2C);
Std_ReturnType MSSP_I2C_DEINIT(const MSSP_I2C_T *MSSP_I2C);
Std_ReturnType MSSP_I2C_SEND_START_CONDITION(const MSSP_I2C_T *MSSP_I2C);
Std_ReturnType MSSP_I2C_SEND_REPEATED_START_CONDITION(const MSSP_I2C_T *MSSP_I2C);
Std_ReturnType MSSP_I2C_SEND_STOP_CONDITION(const MSSP_I2C_T *MSSP_I2C);
Std_ReturnType MSSP_I2C_MASTER_WRITE_BLOCKING(const MSSP_I2C_T *MSSP_I2C, uint8 data, uint8 *_ack);
Std_ReturnType MSSP_I2C_MASTER_READ_BLOCKING(const MSSP_I2C_T *MSSP_I2C, uint8 ack, uint8 *data);
Std_ReturnType MSSP_I2C_MASTER_WRITE_NBLOCKING(const MSSP_I2C_T *MSSP_I2C, uint8 data, uint8 *_ack);
Std_ReturnType MSSP_I2C_MASTER_READ_NBLOCKING(const MSSP_I2C_T *MSSP_I2C, uint8 ack, uint8 *data);
Std_ReturnType MSSP_I2C_SLAVE_WRITE_BLOCKING(const MSSP_I2C_T *MSSP_I2C, uint8 data, uint8 *_ack);
void MSSP_I2C_SLAVE_READ_BLOCKING(uint8 *data);

#endif	/* HAL_I2C_H */


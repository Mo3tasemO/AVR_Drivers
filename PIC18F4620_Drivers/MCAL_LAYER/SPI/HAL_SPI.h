/* 
 * File:   HAL_SPI.h
 * Author: Moata
 *
 * Created on September 17, 2026, 1:06 AM
 */

#ifndef HAL_SPI_H
#define	HAL_SPI_H


// Section: Includes
#include "HAL_SPI_CFG.h"
#include "../GPIO/HAL_GPIO.h"
#include "pic18f4620.h"
#include "../../MCAL_LAYER/Interrupt/MCAL_INTERNAL_INTERRUPT.h"
// Section: Macro Declarations
/* I2C Module Enable/Disable*/
#define MSSP_SPI_MODULE_ENABLE      1
#define MSSP_SPI_MODULE_DISABLE     0
/* I2C Master/Slave Select*/
#define MSSP_SPI_MASTER_MODE        1
#define MSSP_SPI_SLAVE_MODE         0
/* Clock Polarity Select bit */
#define MSSP_SPI_CP_IDLE_HIGH_LEVEL 1
#define MSSP_SPI_CP_IDLE_LOW_LEVEL  0
/* Clock Phase Select Bit*/
#define MSSP_SPI_OUTPUT_DATA_FROM_ACTIVE_TO_IDLE    1
#define MSSP_SPI_OUTPUT_DATA_FROM_IDLE_TO_ACTIVE    0
/* Sample Bit */
#define MSSP_SPI_SAMPLE_RATE_AT_END_OF_DATA         1
#define MSSP_SPI_SAMPLE_RATE_AT_MIDDLE_OF_DATA      0
/* Synchronous Serial Port Mode Select bits */
#define SPI_MASTER_MODE_CLK_DIV_4                          0x00U
#define SPI_MASTER_MODE_CLK_DIV_16                         0x01U
#define SPI_MASTER_MODE_CLK_DIV_64                         0x02U
#define SPI_MASTER_MODE_CLK_TMR2_OUTPUT_DIV_2              0x03U
#define SPI_SLAVE_MODE_SCK_AND_SS_CONTROL_ENABLE           0x04U
#define SPI_SLAVE_MODE_SCK_AND_SS_CONTROL_DISABLE          0x05U    // SS Can be Used as I/O Pin

// Section: Macro Functions Declarations
#define MSSP_SPI_MODULE_ENABLE_CFG()                 (SSPCON1bits.SSPEN = 1)
#define MSSP_SPI_MODULE_DISABLE_CFG()                (SSPCON1bits.SSPEN = 0)

#define SPI_WRITE_COLLISION_DETECT_NO_COLLISION()    (SSPCON1bits.WCOL = 0)
#define SPI_RECIEVE_OVERFLOW_INDICATOR_NO_OVERFLOW() (SSPCON1bits.SSPOV = 0)

#define SPI_CLOCK_POLARITY_IDLE_STATE_HIGH_LEVEL()   (SSPCON1bits.CKP = 1)
#define SPI_CLOCK_POLARITY_IDLE_STATE_LOW_LEVEL()    (SSPCON1bits.CKP = 0)   // Determine the idle case (high/low) and it's leading and trailing

#define SPI_OUT_DATA_ACTIVE_TO_IDLE()                (SSPSTATbits.CKE = 1)  // Determine When the data will be transmitted in the clock line
#define SPI_OUT_DATA_IDLE_TO_ACTIVE()                (SSPSTATbits.CKE = 0)

#define SPI_SAMPLE_AT_END()                          (SSPSTATbits.SMP = 1)
#define SPI_SAMPLE_AT_MIDDLE()                       (SSPSTATbits.SMP = 0)
// Section: Data Type Declarations
typedef struct{
    uint8 SPI_mode_cfg; /* Synchronous Serial Port Mode Select bits */
    uint8 SPI_mode : 1; /* Master/Slave Mode */
    uint8 SPI_clock_polarity : 1; /* Clock Polarity Select bit */
    uint8 SPI_clock_select : 1; /* Clock Select bit */    
    uint8 SPI_sample_cfg : 1; /* Sample bit (in the middle or end of data output time) */
    uint8 SPI_Reserved : 4;
}SPI_CONFIG_T;
typedef struct {
#ifdef MSSP_SPI_INTERRUPT_FEATURE_ENABLE        
    void (*SPI_DEFAULT_INTERRUPT_HANDLER)(void);
    void (*SPI_REPORT_WRITE_COLLISION)(void);    
    interrupt_priority_t MSSP_SPI_PRIORITY;
#endif    
    void (*SPI_REPORT_RECIEVE_OVERFLOW_INDICATOR)(void);
    SPI_CONFIG_T SPI_CONFIG;
}MSSP_SPI_T;
// Section: Function Declarations
Std_ReturnType MSSP_SPI_INIT(const MSSP_SPI_T * MSSP_SPI);
Std_ReturnType MSSP_SPI_DEINIT(const MSSP_SPI_T * MSSP_SPI);
Std_ReturnType MSSP_SPI_MASTER_SEND_DATA_BLOCKING(const MSSP_SPI_T * MSSP_SPI, uint8 data);
Std_ReturnType MSSP_SPI_MASTER_READ_DATA_BLOCKING(const MSSP_SPI_T * MSSP_SPI, uint8 *data);
Std_ReturnType MSSP_SPI_MASTER_SEND_DATA_NBLOCKING(const MSSP_SPI_T * MSSP_SPI, uint8 data);
Std_ReturnType MSSP_SPI_MASTER_READ_DATA_NBLOCKING(const MSSP_SPI_T * MSSP_SPI, uint8 *data);
Std_ReturnType MSSP_SPI_SLAVE_SEND_DATA_BLOCKING(const MSSP_SPI_T * MSSP_SPI, uint8 data);
Std_ReturnType MSSP_SPI_SLAVE_READ_DATA_BLOCKING(const MSSP_SPI_T * MSSP_SPI, uint8 *data);


#endif	/* HAL_SPI_H */


/* 
 * File:   HAL_CCP1.h
 * Author: Moata
 *
 * Created on July 5, 2026, 7:01 PM
 */

#ifndef HAL_CCP1_H
#define	HAL_CCP1_H


// Section: Includes
#include "../GPIO/HAL_GPIO.h"
#include "pic18f4620.h"
#include "../../MCAL_LAYER/Interrupt/MCAL_INTERNAL_INTERRUPT.h"
#include "HAL_CCP_CFG.h"

// Section: Macro Declarations
#define CCP_MODULE_DISABLE                           ((uint8)0x00)
#define CCP_CAPTURE_MODE_FALLING_EDGE                ((uint8)0x04)
#define CCP_CAPTURE_MODE_RISING_EDGE                 ((uint8)0x05)
#define CCP_CAPTURE_MODE_4TH_RISING_EDGE             ((uint8)0x06)
#define CCP_CAPTURE_MODE_16TH_RISING_EDGE            ((uint8)0x07)
#define CCP_COMPARE_MODE_INIT_PIN_LOW_FORCE_HIGH     ((uint8)0x08)
#define CCP_COMPARE_MODE_INIT_PIN_HIGH_FORCE_LOW     ((uint8)0x09)
#define CCP_COMPARE_MODE_GENERATE_SW_INTERRUPT       ((uint8)0x0A)
#define CCP_COMPARE_MODE_TRIGGER_SPECIAL_EVENT       ((uint8)0x0B)
#define CCP_COMPARE_MODE_TOGGLE_OUTPUT               ((uint8)0x02)
#define CCP_PWM_MODE                                 ((uint8)0x0C)

/* CCP1 Capture Mode State*/
#define CCP_CAPTURE_NOT_READY                        0x00
#define CCP_CAPTURE_READY                            0x01

/* CCP1 Compare Mode State*/
#define CCP_COMPARE_NOT_READY                        0x00
#define CCP_COMPARE_READY                            0x01

/* Timer2 Output Postscale Select bits */
#define CCP_POSTSCALE_DIV_1      1
#define CCP_POSTSCALE_DIV_2      2
#define CCP_POSTSCALE_DIV_3      3
#define CCP_POSTSCALE_DIV_4      4
#define CCP_POSTSCALE_DIV_5      5
#define CCP_POSTSCALE_DIV_6      6
#define CCP_POSTSCALE_DIV_7      7
#define CCP_POSTSCALE_DIV_8      8
#define CCP_POSTSCALE_DIV_9      9
#define CCP_POSTSCALE_DIV_10     10
#define CCP_POSTSCALE_DIV_11     11
#define CCP_POSTSCALE_DIV_12     12
#define CCP_POSTSCALE_DIV_13     13
#define CCP_POSTSCALE_DIV_14     14
#define CCP_POSTSCALE_DIV_15     15
#define CCP_POSTSCALE_DIV_16     16

/* Timer2 Input Clock Prescale Select bits */
#define CCP_PRESCALLER_DIV_1     1
#define CCP_PRESCALLER_DIV_4     4
#define CCP_PRESCALLER_DIV_16    16
// Section: Macro Functions Declarations
#define CCP1_CONFIGURATION_SELECT(_CONFIG)            (CCP1CONbits.CCP1M = _CONFIG)
#define CCP2_CONFIGURATION_SELECT(_CONFIG)            (CCP2CONbits.CCP2M = _CONFIG)
// Section: Data Type Declarations
typedef union{
    struct{
        uint8 CCP_LOW;
        uint8 CCP_HIGH;
    };
    struct{
        uint16 CCP_UINT16;
    };
}CCP_REG_T;

typedef enum{
    CCP_CAPTURE_MODE_SELECT = 0,
    CCP_COMPARE_MODE_SELECT,
    CCP_PWM_MODE_SELECT
}CCP_MODE_SELECT_T;

typedef enum{
    CCP1_SELECT = 0,
    CCP2_SELECT
}CCP_SELECT_T;

typedef enum{
    CCP1_AND_CCP2_TIMER3 = 0,
    CCP2_TIMER3_CCP1_TIMER_1,
    CCP1_AND_CCP2_TIMER1 = 0
}CCP_TIMER_SELECT_T;

typedef struct{
    CCP_SELECT_T CCP_SELECT;
    CCP_MODE_SELECT_T mode_select;
    CCP_TIMER_SELECT_T ccp_timer_select;
    uint8 CCP_mode_variant;
    uint8 CCP_POSTSCALE_VAL : 4;
    uint8 CCP_PRESCALER_VAL : 2;
    pin_config_t ccp_pin_cfg;
#if (CCP_MODE_CONFIGURATION_SELECT==CCP_CFG_PWM_MODE_SELECT)
    uint32 PWM_Frequency;
#endif
#ifdef CCP1_INTERRUPT_FEATURE_ENABLE
    void (* CCP1_INTERRUPT_HANDLER)(void);
    interrupt_priority_t CCP1_priority;
#endif
#ifdef CCP2_INTERRUPT_FEATURE_ENABLE
    void (* CCP2_INTERRUPT_HANDLER)(void);
    interrupt_priority_t CCP2_priority;
#endif
    uint8 CCP_Reserved : 2;
}CCP_T;
// Section: Function Declarations

Std_ReturnType CCP_INIT(const CCP_T *_CCP);
Std_ReturnType CCP_DEINIT(const CCP_T *_CCP);

#if (CCP_MODE_CONFIGURATION_SELECT==CCP_CFG_CAPTURE_MODE_SELECT)
Std_ReturnType CCP_IS_CAPTURE_DATA_READY(const CCP_T *_CCP, uint8 *Capture_Status);
Std_ReturnType CCP_CAPTURE_MODE_READ_VALUE(const CCP_T *_CCP, uint16 *Capture_Value);
Std_ReturnType CCP_CAPTURE_MODE_SET(const CCP_T *_CCP);
#endif
    
#if (CCP_MODE_CONFIGURATION_SELECT==CCP_CFG_COMPARE_MODE_SELECT)
Std_ReturnType CCP_IS_COMPARE_COMPLETE(const CCP_T *_CCP, uint8 *Compare_Status);
Std_ReturnType CCP_COMPARE_MODE_SET_VALUE(const CCP_T *_CCP, uint16 Compare_Value);
#endif

#if (CCP_MODE_CONFIGURATION_SELECT==CCP_CFG_PWM_MODE_SELECT)
Std_ReturnType CCP_PWM_SET_DUTY_CYCLE(const CCP_T *_CCP, const uint8 _duty);
Std_ReturnType CCP_PWM_GENERATE(const CCP_T *_CCP);
Std_ReturnType CCP_PWM_STOP(const CCP_T *_CCP);
#endif

#endif	/* HAL_CCP1_H */


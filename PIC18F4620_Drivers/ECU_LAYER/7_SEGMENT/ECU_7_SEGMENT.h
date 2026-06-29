/* 
 * File:   ECU_7_SEGMENT.h
 * Author: Moata
 *
 * Created on November 24, 2025, 11:10 PM
 */

#ifndef ECU_7_SEGMENT_H
#define	ECU_7_SEGMENT_H

// Section: Includes

#include "ECU_7_SEGMENT_CFG.h"
#include "../../MCAL_LAYER/GPIO/HAL_GPIO.h"


// Section: Data Type Declarations
uint8 CA_7_SEGMENT[10] = {0xC0, 0xF9, 0xA4, 0xB0, 0x99, 0x92, 0x82, 0xF8, 0x80, 0x90};
uint8 CC_7_SEGMENT[10] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F};
uint8 DECODER_NUMBERS[10] = {0b0000, 0b0001, 0b0010, 0b0011, 0b0100, 0b0101, 0b0110, 0b0111, 0b1000, 0b1001};

// Section: Macro Declarations
#define SEVEN_SEGMENT_PIN1 0
#define SEVEN_SEGMENT_PIN2 1
#define SEVEN_SEGMENT_PIN3 2
#define SEVEN_SEGMENT_PIN4 3


typedef enum{
    COMMON_ANODE = 0x00U,
    COMMON_CATHODE = 0x01U
}SEGMANT_TYPE_T;

typedef struct{
    pin_config_t SEGMENT_PINS[4];
    SEGMANT_TYPE_T SEGMENT_TYPE;
}SEGMENT_T;



// Section: Macro Functions Declarations


// Section: Function Declarations

Std_ReturnType SEVEN_SEGMENT_INIT(const SEGMENT_T * SEGMENT);
Std_ReturnType SEVEN_SEGMENT_WRITE_NUMBER(const SEGMENT_T * SEGMENT, uint8 number);





#endif	/* ECU_7_SEGMENT_H */


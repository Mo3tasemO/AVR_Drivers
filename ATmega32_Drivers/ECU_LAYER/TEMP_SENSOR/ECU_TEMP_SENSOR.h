/*
 * ECU_TEMP_SENSOR.h
 *
 *  Created on: Feb 6, 2026
 *      Author: Moata
 */

#ifndef ECU_LAYER_TEMP_SENSOR_ECU_TEMP_SENSOR_H_
#define ECU_LAYER_TEMP_SENSOR_ECU_TEMP_SENSOR_H_



/* Section : Includes */
#include "ECU_TEMP_SENSOR_CFG.h"
#include "../../MCAL_LAYER/GPIO/HAL_GPIO.h"




/* Section: Macro Declarations */
/* Section: Macro Functions Declarations */
/* Section: Data Type Declarations */





/* Section: Function Declarations */
Std_ReturnType LM35_Conversion(uint16 Temp_Value, uint16 *ret_temp_val);












#endif /* ECU_LAYER_TEMP_SENSOR_ECU_TEMP_SENSOR_H_ */

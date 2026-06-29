/*
 * ECU_TEMP_SENSOR.c
 *
 *  Created on: Feb 6, 2026
 *      Author: Moata
 */
#include "ECU_TEMP_SENSOR.h"



Std_ReturnType LM35_Conversion(uint16 Temp_Value, uint16 *ret_temp_val){
	Std_ReturnType ret = E_OK;
	uint16 Temperature;
	if(NULL == ret_temp_val){
		ret = E_NOT_OK;
	}
	else{
		*ret_temp_val = Temp_Value * 2.5f;	// Internal Voltage ref = 2.56V, 2560/1024 = 2.5 (1024-> 2^10)
		*ret_temp_val /= 10;
	}
	return ret;
}

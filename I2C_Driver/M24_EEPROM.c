/*
 * M24_EEPROM.c
 *
 *  Created on: Oct 25, 2022
 *      Author: markfe1
 */
#include "M24_EEPROM.h"


M24_status_t M24_init (I2C_HandleTypeDef *hi2c)
{


	if (HAL_I2C_IsDeviceReady(hi2c, 0b10101000, 10, 1000) == HAL_OK)
	{
		return M24_OK;
	}
	else
	{
		return M24_NOK;
	}


}

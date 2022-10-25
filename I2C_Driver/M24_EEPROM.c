/*
 * M24_EEPROM.c
 *
 *  Created on: Oct 25, 2022
 *      Author: markfe1
 */
#include "M24_EEPROM.h"

/*local copy of I2C handle*/
I2C_HandleTypeDef *pi2chandle = NULL;


M24_status_t M24_init(I2C_HandleTypeDef *hi2c)
{
	/*check the incoming parameters*/
	if(NULL == hi2c)
	{
		return M24_NOK;
	}


	/* copy the I2C handler for later usage*/
	pi2chandle = hi2c;


	/*check the status of the EEPROMs in the EEPROM_Dev_List. If all are available then init OK */
	int i = 0;
	do
	{
		if (HAL_I2C_IsDeviceReady(pi2chandle, EEPROM_Dev_List[i].DevAddress, I2C_TRIALS, I2C_TIMEOUT) == HAL_OK)
		{
			M24_state_flag = M24_OK;
		}
		else
		{
			M24_state_flag = M24_NOK;
		}
		i++;
	} while ((i< (sizeof(EEPROM_Dev_List)/sizeof(EEPROM_Dev_List[0]))) && (M24_OK == M24_state_flag));

	return M24_state_flag;
}

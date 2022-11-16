/*
 * M24_EEPROM.c
 *
 *  Created on: Oct 25, 2022
 *      Author: markfe1
 */
#include "M24_EEPROM.h"

/*local copy of I2C handle*/
I2C_HandleTypeDef *pi2chandle = NULL;

/*define and pointer for reset_data*/
uint8_t reset_data = 0xEE;
uint8_t *ptr_reset_data = &reset_data;


M24_status_t M24_state_flag = M24_NOK;

/*EEPROM Device List*/
EEPROM_Config_t EEPROM_Dev_List[] =
{
		{0b10101000, 400, 256, 1, 16},			/*M24C02-FMC6TG, U1 on the board*/
		{0b10101010, 400, 32000, 2, 64}, 		/*M24256-DFDW6TP, U2 on the board*/
		{0b10101100, 400, 128000, 17, 256},		/*M24M01-DFMN6TP, U3 on the board*/
};

M24_status_t M24_init(I2C_HandleTypeDef *hi2c)
{
	/*check the incoming parameters*/
	if(NULL == hi2c)
	{
		return M24_NOK;
	}

	/* copy the I2C handler for later usage*/
		pi2chandle = hi2c;

	/*Disable write in EEPROMs --> WC = 1*/
		HAL_GPIO_WritePin(GPIOA, WC_Pin, GPIO_PIN_SET);

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


M24_status_t M24_read(uint16_t DevAddress, uint32_t MemAddress, uint8_t MemAddSize, uint8_t *pData, uint32_t Size)
{



	/*check the incoming parameters*/
		if(NULL == pi2chandle)
		{
			return M24_NOK;
		}



		if(HAL_I2C_Mem_Read(pi2chandle, DevAddress, (uint16_t) MemAddress, MemAddSize, pData, Size, I2C_TIMEOUT) == HAL_OK)
		{
			return M24_OK;
		}

		return M24_NOK;
}

M24_status_t M24_clear(EEPROM_Config_t *pEEPROM)
{
	uint16_t i = START_ADDRESS;

	/*check the incoming parameters*/
			if((NULL == pEEPROM) || (NULL == pi2chandle))
			{
				return M24_NOK;
			}

	HAL_GPIO_WritePin(GPIOA, WC_Pin, GPIO_PIN_RESET);


	/*clear all the memory*/
	do
	{
	HAL_I2C_Mem_Write(pi2chandle, pEEPROM->DevAddress, i, pEEPROM->MemAddSize, ptr_reset_data, 1, I2C_TIMEOUT);
	i++;
	}while(i<pEEPROM->EepromSize);

	HAL_GPIO_WritePin(GPIOA, WC_Pin, GPIO_PIN_SET);

	return M24_OK;
}

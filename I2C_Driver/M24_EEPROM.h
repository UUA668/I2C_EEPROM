/*
 * M24_EEPROM.h
 *
 *  Created on: Oct 25, 2022
 *      Author: markfe1
 */

#ifndef M24_EEPROM_H_
#define M24_EEPROM_H_

#include "stm32g0xx_hal.h"

#define I2C_TRIALS 10
#define I2C_TIMEOUT 1000


/*M24 Status definicio*/
typedef enum {
	M24_OK = 0,
	M24_NOK,
} M24_status_t;

M24_status_t M24_state_flag = M24_NOK;

/*EEPROM kommunikacios struktura*/
typedef struct{
	uint16_t 			DevAddress;		/*Device address from Datasheet in binary form*/
	uint16_t			ClockSpeed;		/*SCL Speed in KHz*/
	uint16_t			PageSize;		/*Page Size from Datasheet in byte*/
}EEPROM_Config_t;


/*EEPROM Device List*/
EEPROM_Config_t EEPROM_Dev_List[] =
{
		{0b10101000, 400, 16},		/*M24C02-FMC6TG, U1 on the board*/
		{0b10101010, 400, 64}, 		/*M24256-DFDW6TP, U2 on the board*/
		{0b10101100, 400, 256},		/*M24M01-DFMN6TP, U3 on the board*/
};

extern M24_status_t M24_init(I2C_HandleTypeDef *hi2c);


#endif /* M24_EEPROM_H_ */

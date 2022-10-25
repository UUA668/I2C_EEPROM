/*
 * M24_EEPROM.h
 *
 *  Created on: Oct 25, 2022
 *      Author: markfe1
 */

#ifndef M24_EEPROM_H_
#define M24_EEPROM_H_

#include "stm32g0xx_hal.h"

/*M24 Status definicio*/
typedef enum {
	M24_OK = 0,
	M24_NOK,
} M24_status_t;

extern M24_status_t M24_init(I2C_HandleTypeDef *hi2c);


#endif /* M24_EEPROM_H_ */

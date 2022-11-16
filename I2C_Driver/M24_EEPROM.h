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
#define BYTE 8
#define START_ADDRESS 0x0000

#ifndef WC_Pin
#define WC_Pin GPIO_PIN_1
#endif /* WC_Pin */

/*M24 Status definicio*/
typedef enum {
	M24_OK = 0,
	M24_NOK,
} M24_status_t;

/*EEPROM kommunikacios struktura*/
typedef struct{
	uint16_t 			DevAddress;		/*Device address from Datasheet in binary form*/
	uint16_t			ClockSpeed;		/*SCL Speed in KHz*/
	uint32_t			EepromSize;		/*Memory size from Datasheet in */
	uint16_t			MemAddSize;		/*Memory Address Size*/
	uint16_t			PageSize;		/*Page Size from Datasheet in byte*/
}EEPROM_Config_t;

extern EEPROM_Config_t EEPROM_Dev_List[];


/*define name for the EEPROMs*/
#define U1 EEPROM_Dev_List[0]
#define U2 EEPROM_Dev_List[1]
#define U3 EEPROM_Dev_List[3]

extern M24_status_t M24_init(I2C_HandleTypeDef *hi2c);

extern M24_status_t M24_read(uint16_t DevAddress, uint32_t MemAddress, uint8_t MemAddSize, uint8_t *pData, uint32_t Size);

extern M24_status_t M24_clear(EEPROM_Config_t *pEEPROM);

#endif /* M24_EEPROM_H_ */

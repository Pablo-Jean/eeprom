/*
 * eeprom.h
 *
 *  Created on: Feb 25, 2024
 *      Author: pablo-jean
 */

#ifndef EEPROM_EEPROM_H_
#define EEPROM_EEPROM_H_

/*
 * Includes
 */

#include <stdint.h>
#include <stdio.h>
#include <malloc.h>
#include <string.h>

/*
 * Macros
 */

#define EEPROM_INITIALIZE_FLAG		0x45

#ifndef EEPROM_DELAY_BTW_WRITES
#define EEPROM_DELAY_BTW_WRITES		8
#endif

/*
 * Typedefs
 */

typedef enum{
	EE_OK,
	EE_ERROR,
	EE_NOT_INITIALIZED,
	EE_INVALID_VARS,
	EE_OVERFLOW,

	EE_UNKNOWN = 0xFF
}eeprom_e;

typedef eeprom_e (*ee_write_fxn)(uint32_t i2cAddress, uint32_t memAddress, uint8_t memAddrSize, uint8_t *data, uint32_t len);
typedef eeprom_e (*ee_read_fxn)(uint32_t i2cAddress, uint32_t memAddress, uint8_t memAddrSize, uint8_t *data, uint32_t len);
typedef void (*delay_ms)(uint32_t ms);

typedef struct{
	uint32_t memSize;
	uint32_t pageSize;
	uint8_t memAddrSize;
	uint8_t i2cAddress;

	ee_write_fxn EeWriteFxn;
	ee_read_fxn EeReadFxn;
	delay_ms DelayMs;
	struct{
		uint32_t actAddress;
		uint8_t initialized;
	}_intern;
}eeprom_t;

/*
 * Publics
 */

eeprom_e eeprom_init(eeprom_t *Eeprom);

eeprom_e eeprom_write(eeprom_t *Eeprom, uint32_t Address, uint8_t *data, uint32_t len);

eeprom_e eeprom_read(eeprom_t *Eeprom, uint32_t Address, uint8_t *data, uint32_t len);

eeprom_e eeprom_fill_all(eeprom_t *Eeprom, uint8_t fillByte);


#endif /* EEPROM_EEPROM_H_ */

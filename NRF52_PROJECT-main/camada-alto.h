// ring-buffer.h
#ifndef INC_RING_BUFFER_H_
#define INC_RING_BUFFER_H_

#include <stdint.h>
#include <stdbool.h>

typedef struct ring_buffer_t
{
    uint8_t  *buffer;
    uint32_t mask; // the mask should be always 2^n
    uint32_t read_index;
    uint32_t write_index;
} ring_buffer_t;

void ring_buffer_setup(ring_buffer_t *rb, uint8_t *buffer, uint32_t size);
bool ring_buffer_empty(ring_buffer_t *rb);
bool ring_buffer_read(ring_buffer_t *rb, uint8_t *byte);
bool ring_buffer_write(ring_buffer_t *rb, uint8_t byte);

#endif /* INC_RING_BUFFER_H_ */




// led_rgb.h
#ifndef INC_LED_RGB_H_
#define INC_LED_RGB_H_

#include <stdint.h>
#include <stddef.h>

typedef enum {
    LED_NONE,
    LED_RED,
    LED_GREEN,
    LED_BLUE,
    LED_COUNT
} led_color_e;

void led_rgb_setColor(led_color_e color);

#endif /* INC_LED_RGB_H_ */



// nor.h
#ifndef NOR_H_
#define NOR_H_

#include <stdint.h>

typedef enum{
	NOR_ERASE_4K, /**< NOR_ERASE_4K */
	NOR_ERASE_32K,/**< NOR_ERASE_32K */
	NOR_ERASE_64K /**< NOR_ERASE_64K */
}nor_erase_method_e;

#define NOR_SIZE_BLOCK				65536
#define NOR_SIZE_SECTOR				4096
#define NOR_SIZE_PAGE				256

#define NOR_CMD_WRITE_EN			0x06
#define NOR_CMD_WRITE_DIS			0x04
#define NOR_SECTOR_ERASE_4K			0x20
#define NOR_SECTOR_ERASE_32K		0x52
#define NOR_SECTOR_ERASE_64K		0xD8
#define NOR_CHIP_ERASE				0xC7
#define NOR_CMD_SR1					0x05
#define NOR_CMD_READFAST			0x0B
#define NOR_PAGE_PROGRAM			0x02

void nor_init(void);
void nor_waitBusy(void);

void nor_Erase_chip(void);
void NOR_EraseAddress(uint32_t Address, nor_erase_method_e method);
void NOR_EraseSector(uint32_t SectorAddr);
void NOR_EraseBlock(uint32_t BlockAddr);

void NOR_WriteBytes(uint8_t *pBuffer, uint32_t WriteAddr, uint32_t NumBytesToWrite);
void NOR_WritePage(uint8_t *pBuffer, uint32_t PageAddr, uint32_t Offset, uint32_t NumBytesToWrite);
void NOR_WriteSector(uint8_t *pBuffer, uint32_t SectorAddr, uint32_t Offset, uint32_t NumBytesToWrite);
void NOR_WriteBlock(uint8_t *pBuffer, uint32_t BlockAddr, uint32_t Offset, uint32_t NumBytesToWrite);

void NOR_ReadBytes(uint8_t *pBuffer, uint32_t ReadAddr, uint32_t NumByteToRead);
void NOR_ReadPage(uint8_t *pBuffer, uint32_t PageAddr, uint32_t Offset, uint32_t NumByteToRead);
void NOR_ReadSector(uint8_t *pBuffer, uint32_t SectorAddr, uint32_t Offset, uint32_t NumByteToRead);
void NOR_ReadBlock(uint8_t *pBuffer, uint32_t BlockAddr, uint32_t Offset, uint32_t NumByteToRead);

#endif /* NOR_H_ */



// temperature.h
#ifndef INC_TEMPERATURE_H_
#define INC_TEMPERATURE_H_

#include <stdint.h>

uint16_t temperature_get(void);

#endif /* INC_TEMPERATURE_H_ */



// cli.h
#ifndef CLI_H_
#define CLI_H_

#include <stdio.h>
#include <stdint.h>
#include <string.h>

typedef void(*function_t)(void);

typedef struct
{
    char const *name;
    function_t execute;
    char const *help;
}commandStruct_t;

void ProcessCommands(uint8_t c);
void command_update(void);

#endif /* CLI_H_ */



// status.h
#ifndef INC_STATUS_H_
#define INC_STATUS_H_

#include <stdint.h>
#include <stddef.h>

typedef enum {
    STATUS_OK,
    STATUS_FAULT
} status_e;

void status_update(void);
status_e status_read(void);

#endif /* INC_STATUS_H_ */



// storage.h
#ifndef STORAGE_H_
#define STORAGE_H_

#include <stdint.h>

#define STORAGE_SECTOR_INFO                 0
#define STORAGE_SECTOR_COPY                 512
#define STORAGE_BUFFER_SIZE                 64

typedef struct
{
    uint8_t day;
    uint8_t month;
    uint8_t year;
    uint8_t hour;
    uint8_t minute;
}storage_date_t;


uint8_t storage_getCount(void);
void    storage_updateCount(void);

void storage_clean(void);
void storage_temperatureAppend(void);
void storage_temperatureExtract(void);

#endif /* STORAGE_H_ */



// ticks.h
#ifndef INC_TICKS_H_
#define INC_TICKS_H_

#include <stdint.h>

void ticks_increment(void);
uint64_t ticks_get(void);

#endif /* INC_TICKS_H_ */
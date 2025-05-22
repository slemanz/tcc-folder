// ring-buffer.c
#include "ring-buffer.h"

void ring_buffer_setup(ring_buffer_t *rb, uint8_t *buffer, uint32_t size)
{
    rb->buffer = buffer;
    rb->read_index = 0;
    rb->write_index = 0;
    rb->mask = size - 1;
}

bool ring_buffer_empty(ring_buffer_t *rb)
{
    return (rb->read_index == rb->write_index);
}

bool ring_buffer_read(ring_buffer_t *rb, uint8_t *byte)
{
    uint32_t local_read_index = rb->read_index;
    uint32_t local_write_index = rb->write_index;

    if(local_read_index == local_write_index)
    {
        return false;
    }

    *byte = rb->buffer[local_read_index];
    local_read_index = (local_read_index + 1) & rb->mask;
    rb->read_index = local_read_index;

    return true;
}

bool ring_buffer_write(ring_buffer_t *rb, uint8_t byte)
{
    uint32_t local_write_index = rb->write_index;
    uint32_t local_read_index = rb->read_index;

    uint32_t next_write_index = (local_write_index + 1) & rb->mask;

    if(next_write_index == local_read_index)
    {
        return false;
    }

    rb->buffer[local_write_index] = byte;
    rb->write_index = next_write_index;
    return true;
}



// led_rgb.c
#include "bsp/led_rgb.h"
#include "driver_gpio.h"

#define LED_RGB_BLUE            GPIO_PIN_NO_6
#define LED_RGB_GREEN           GPIO_PIN_NO_16
#define LED_RGB_RED             GPIO_PIN_NO_24

static void led_setRed(void);
static void led_setGreen(void);
static void led_setBlue(void);
static void led_setNone(void);

static void led_setRed(void)
{
    GPIO_WriteToOutputPin(GPIOP0, LED_RGB_RED, GPIO_PIN_RESET);
    GPIO_WriteToOutputPin(GPIOP0, LED_RGB_GREEN, GPIO_PIN_SET);
    GPIO_WriteToOutputPin(GPIOP0, LED_RGB_BLUE, GPIO_PIN_SET);
}

static void led_setGreen(void)
{
    GPIO_WriteToOutputPin(GPIOP0, LED_RGB_RED, GPIO_PIN_SET);
    GPIO_WriteToOutputPin(GPIOP0, LED_RGB_GREEN, GPIO_PIN_RESET);
    GPIO_WriteToOutputPin(GPIOP0, LED_RGB_BLUE, GPIO_PIN_SET);
}
static void led_setBlue(void)
{
    GPIO_WriteToOutputPin(GPIOP0, LED_RGB_RED, GPIO_PIN_SET);
    GPIO_WriteToOutputPin(GPIOP0, LED_RGB_GREEN, GPIO_PIN_SET);
    GPIO_WriteToOutputPin(GPIOP0, LED_RGB_BLUE, GPIO_PIN_RESET);
}

static void led_setNone(void)
{
    GPIO_WriteToOutputPin(GPIOP0, LED_RGB_RED, GPIO_PIN_SET);
    GPIO_WriteToOutputPin(GPIOP0, LED_RGB_GREEN, GPIO_PIN_SET);
    GPIO_WriteToOutputPin(GPIOP0, LED_RGB_BLUE, GPIO_PIN_SET);
}

static void (*led_functions[LED_COUNT])(void) = {
    led_setNone,            // NONE
    led_setRed,             // LED_RED
    led_setGreen,           // LED_GREEN
    led_setBlue             // LED_BLUE
};

void led_rgb_setColor(led_color_e color)
{
    if (led_functions[color] != NULL)
    {
            led_functions[color]();
    }
}



// temperature.c
#include "core/ticks.h"
#include "bsp/temperature.h"
#include "driver_twi.h"

// HS300x - RENESAS

uint16_t temperature_get(void)
{
    uint8_t temperatureAddress = 0x44;
    uint16_t temperature_value = 0;
    float temperature_float = 0;
    uint8_t twi_read[4];
    uint8_t twi_send[1] = {0x00};

    TWI_MasterSendData(TWI1, twi_send, 1, temperatureAddress);
    
    // 40ms wait time to get measure
    uint64_t start_time = ticks_get();
    while((ticks_get() - start_time) <= 40); 

    TWI_MasterReceiveData(TWI1, twi_read, 4, 0x44);
    temperature_value = (((twi_read[2] << 8) | (twi_read[3]) ) >> 2 );
    temperature_float = ((temperature_value/16383.0)*165.0 - 40.0)*10;
    temperature_value = (uint16_t)temperature_float;

    return temperature_value;
}



// cli.c
#include "core/cli.h"
#include "core/storage.h"
#include "bsp/temperature.h"

#include "driver_uart.h"

static void get_temperature(void);
static void get_count(void);
static void clear(void);
static void extract(void);
static void Help(void);

commandStruct_t commands[] = {
    {"temperature", get_temperature, "Shows temperature value"},
    {"count", get_count, "Shows storage data count"},
    {"storage clear", clear, "Clear storage data"},
    {"storage extract", extract, "Extract storage data"},
    {"help", Help, "List all commands"},
};

#define COMMAND_COUNT           (sizeof(commands) / sizeof(commands[0]))
#define CLI_BUFFER_SIZE         64

static char inputBuffer[CLI_BUFFER_SIZE];
static int idx = 0;

void ProcessCommands(uint8_t c)
{

    if (c == '\r')
    {
        // do nothing
    }else if(c == '\n')
    {   // End of command
        inputBuffer[idx] = '\0'; // Null-terminate string

        for (int i = 0; i < COMMAND_COUNT; i++)
        {
            if (strcmp(inputBuffer, commands[i].name) == 0)
            {
                commands[i].execute(); // Execute the command
                break;
            }
        }
        idx = 0; // Reset index for next command
    } else if (idx < CLI_BUFFER_SIZE)
    {
        inputBuffer[idx++] = (char)c; // Store character
    }
}

void command_update(void)
{
    if(uart_data_available())
    {
            uint8_t ch = uart_rcv_byte();
            uart_write_byte(ch);
            ProcessCommands(ch);
    }
}

static void get_temperature(void)
{
    uint16_t temperature_value = temperature_get();
    printf("Temperatura: %d.%d C\n", temperature_value/10, temperature_value%10);
}

static void get_count(void)
{
    uint8_t count_data = storage_getCount();
    printf("Count: %d\n", count_data);
}

static void clear(void)
{
    printf("Begin storage clear\n");
    storage_clean();
    printf("Successeful!\n");
}

static void extract(void)
{
    storage_temperatureExtract();
}


static void Help(void)
{
	printf("===================================\n");
    for (int i = 0; i < COMMAND_COUNT; i++) {
    	printf("%s: %s\n", commands[i].name, commands[i].help);
    }
    printf("===================================\n");
}



// nor.c
#include "bsp/nor.h"
#include "driver_spi.h"
#include "driver_gpio.h"
#include "init_app.h"

#if defined (NOR_DEBUG)
#include <stdarg.h>
#include <stdio.h>
#endif

#define NOR_SPI                 SPI0
#define NOR_CS_PORT             CS_PORT
#define NOR_CS_PIN              CS_PIN

static void _nor_cs_assert(void)
{
    GPIO_WriteToOutputPin(NOR_CS_PORT, NOR_CS_PIN, GPIO_PIN_RESET);
}

static void _nor_cs_deassert(void)
{
    GPIO_WriteToOutputPin(NOR_CS_PORT, NOR_CS_PIN, GPIO_PIN_SET);
}

static void _nor_spi_tx(uint8_t *txBuf, uint32_t size)
{
    SPI_SendData(NOR_SPI, txBuf, size);
}

static void _nor_spi_rx(uint8_t *rxBuf, uint32_t size)
{
    SPI_ReceiveData(NOR_SPI, rxBuf, size);
}

static void _nor_WriteEnable(void)
{
	uint8_t WriteEnCmd = NOR_CMD_WRITE_EN;

	_nor_cs_assert();
	_nor_spi_tx(&WriteEnCmd, 1);
	_nor_cs_deassert();
}

void _nor_WriteDisable(void)
{
	uint8_t WriteDisCmd = NOR_CMD_WRITE_DIS;

	_nor_cs_assert();
	_nor_spi_tx(&WriteDisCmd, 1);
	_nor_cs_deassert();
}

void nor_waitBusy(void)
{
    uint8_t cmd = NOR_CMD_SR1;
    uint8_t statusReg;

	do{
        _nor_cs_assert();
        _nor_spi_tx((uint8_t*)&cmd, 1);
		_nor_spi_rx(&statusReg, 1);
        _nor_cs_deassert();
	}while ((statusReg & (1 << 0))); // SR1_BUSY_BIT
}

void NOR_ReadBytes(uint8_t *pBuffer, uint32_t ReadAddr, uint32_t NumByteToRead)
{
    uint8_t ReadCmd[5];

    if (NumByteToRead == 0)
    {
		return;
	}

    nor_waitBusy();
	ReadCmd[0] = NOR_CMD_READFAST;
	ReadCmd[1] = ((ReadAddr >> 16) & 0xFF);
	ReadCmd[2] = ((ReadAddr >> 8) & 0xFF);
	ReadCmd[3] = ((ReadAddr) & 0xFF);
	ReadCmd[4] = 0x00;

    _nor_cs_assert();
	_nor_spi_tx(ReadCmd, 5);
	_nor_spi_rx(pBuffer, NumByteToRead);
    _nor_cs_deassert();
}

void NOR_ReadPage(uint8_t *pBuffer, uint32_t PageAddr, uint32_t Offset, uint32_t NumByteToRead)
{
	uint32_t Address;

	while (Offset >= NOR_SIZE_PAGE)
    {
		PageAddr++;
		Offset -= NOR_SIZE_PAGE;
	}

	Address = (PageAddr * NOR_SIZE_PAGE) + Offset;
	NOR_ReadBytes(pBuffer, Address, NumByteToRead);
}

void NOR_ReadSector(uint8_t *pBuffer, uint32_t SectorAddr, uint32_t Offset, uint32_t NumByteToRead)
{
	uint32_t Address;

	while (Offset >= NOR_SIZE_SECTOR){
		SectorAddr++;
		Offset -= NOR_SIZE_SECTOR;
	}

	Address = (SectorAddr * NOR_SIZE_SECTOR) + Offset;
	NOR_ReadBytes(pBuffer, Address, NumByteToRead);
}

void NOR_ReadBlock(uint8_t *pBuffer, uint32_t BlockAddr, uint32_t Offset, uint32_t NumByteToRead)
{
	uint32_t Address;

	while (Offset >= NOR_SIZE_BLOCK){
		BlockAddr++;
		Offset -= NOR_SIZE_BLOCK;
	}

	Address = (BlockAddr * NOR_SIZE_BLOCK) + Offset;
	NOR_ReadBytes(pBuffer, Address, NumByteToRead);
}

void NOR_EraseAddress(uint32_t Address, nor_erase_method_e method){
	uint8_t EraseChipCmd[4];

	switch (method){
	case NOR_ERASE_4K:
		EraseChipCmd[0] = NOR_SECTOR_ERASE_4K;
		break;
	case NOR_ERASE_32K:
		EraseChipCmd[0] = NOR_SECTOR_ERASE_32K;
		break;
	case NOR_ERASE_64K:
		EraseChipCmd[0] = NOR_SECTOR_ERASE_64K;
		break;
	}
	EraseChipCmd[1] = ((Address >> 16) & 0xFF);
	EraseChipCmd[2] = ((Address >> 8) & 0xFF);
	EraseChipCmd[3] = ((Address) & 0xFF);

	//_nor_mtx_lock(nor);
	_nor_WriteEnable();
	_nor_cs_assert();
	_nor_spi_tx(EraseChipCmd, 4);
	_nor_cs_deassert();

	nor_waitBusy();
	_nor_WriteDisable();
}

void NOR_EraseSector(uint32_t SectorAddr){
	uint32_t Address;
	Address = SectorAddr * NOR_SIZE_SECTOR;
	return NOR_EraseAddress(Address, NOR_ERASE_4K);
}

void NOR_EraseBlock(uint32_t BlockAddr){
	uint32_t Address;
	Address = BlockAddr * NOR_SIZE_BLOCK;
	return NOR_EraseAddress(Address, NOR_ERASE_64K);
}

void NOR_WriteBytes(uint8_t *pBuffer, uint32_t WriteAddr, uint32_t NumBytesToWrite)
{
	uint8_t WriteCmd[4];
	uint32_t _BytesToWrite;

	if (NumBytesToWrite == 0){
		return;
	}

	do{
		// Wait for Busy is deasserted to write any information
		nor_waitBusy();

		if (((WriteAddr%256)+NumBytesToWrite) > 256){
            _BytesToWrite = 256 - (256); // 256 = page size
        }
        else
        {
            _BytesToWrite = NumBytesToWrite;
        }
        _nor_WriteEnable();
		nor_waitBusy();
		WriteCmd[0] = NOR_PAGE_PROGRAM;
		WriteCmd[1] = ((WriteAddr >> 16) & 0xFF);
		WriteCmd[2] = ((WriteAddr >> 8) & 0xFF);
		WriteCmd[3] = ((WriteAddr) & 0xFF);
		_nor_cs_assert();
		_nor_spi_tx(WriteCmd, sizeof(WriteCmd));
		_nor_spi_tx(pBuffer, _BytesToWrite);
		_nor_cs_deassert();
		pBuffer += _BytesToWrite;
		WriteAddr += _BytesToWrite;
		NumBytesToWrite -= _BytesToWrite;

        _nor_WriteDisable();
		nor_waitBusy();
	}while (NumBytesToWrite > 0);
	nor_waitBusy();
}

void NOR_WritePage(uint8_t *pBuffer, uint32_t PageAddr, uint32_t Offset, uint32_t NumBytesToWrite)
{
	uint32_t Address;

	while (Offset >= NOR_SIZE_PAGE)
	{
		PageAddr++;
		Offset -= NOR_SIZE_PAGE;
	}

	Address = (PageAddr * NOR_SIZE_PAGE) + Offset;
	NOR_WriteBytes(pBuffer, Address, NumBytesToWrite);
}


void NOR_WriteSector(uint8_t *pBuffer, uint32_t SectorAddr, uint32_t Offset, uint32_t NumBytesToWrite)
{
	int32_t Address;

	while (Offset >= NOR_SIZE_SECTOR)
	{
		SectorAddr++;
		Offset -= NOR_SIZE_SECTOR;
	}

	Address = (SectorAddr * NOR_SIZE_SECTOR) + Offset;
	NOR_WriteBytes(pBuffer, Address, NumBytesToWrite);
}


void NOR_WriteBlock(uint8_t *pBuffer, uint32_t BlockAddr, uint32_t Offset, uint32_t NumBytesToWrite)
{
	uint32_t Address;

	while (Offset >= NOR_SIZE_BLOCK)
	{
		BlockAddr++;
		Offset -= NOR_SIZE_BLOCK;
	}

	Address = (BlockAddr * NOR_SIZE_BLOCK) + Offset;
	NOR_WriteBytes(pBuffer, Address, NumBytesToWrite);
}


// status.c
#include "core/status.h"
#include "core/ticks.h"
#include "bsp/led_rgb.h"
#include "driver_saadc.h"

static status_e status = STATUS_OK;
static status_e last_status = STATUS_OK;
static uint64_t time = 0;
static uint8_t toggle = 0;

static void status_ledUpdate();

static void status_ledUpdate()
{
    if(status == STATUS_OK)
    {
        last_status = STATUS_OK;
        if((ticks_get() - time) >= 500)
        {
            if(!toggle)
            {
                led_rgb_setColor(LED_GREEN);
                toggle = 1;
            }else
            {
                led_rgb_setColor(LED_NONE);
                toggle = 0;
            }
            time = ticks_get();
        }
    }else if((status == STATUS_FAULT) && (last_status == STATUS_OK))
    {
        last_status = STATUS_FAULT;
        led_rgb_setColor(LED_RED);
    }
}

void status_update(void)
{
    saadc_selectInp(SAADC_PSEL_AIN1);
    uint16_t adc_value = saadc_read();
    if(adc_value >= 500)
    {
        status = STATUS_OK;
    }else
    {
        status = STATUS_FAULT;
    }
    status_ledUpdate();
}

status_e status_read(void)
{
    status_update();
    return status;
}




// storage.c
#include "core/storage.h"
#include "bsp/nor.h"
#include "bsp/temperature.h"
#include "bsp/led_rgb.h"
#include <stdio.h>

static uint8_t buffer[STORAGE_BUFFER_SIZE];
static void _storage_copySector(uint32_t sector);

static volatile uint32_t offset_temperature = 0;

static void _storage_copySector(uint32_t sector)
{
    NOR_EraseSector(STORAGE_SECTOR_COPY);

    uint32_t size = NOR_SIZE_SECTOR;
    uint32_t offset = 0;
    do
    {
        if(size >= STORAGE_BUFFER_SIZE)
        {
            NOR_WriteSector(buffer, STORAGE_SECTOR_COPY, offset, STORAGE_BUFFER_SIZE);
            size -= STORAGE_BUFFER_SIZE;
            offset += STORAGE_BUFFER_SIZE;
        }else
        {
            NOR_WriteSector(buffer, size, offset, STORAGE_BUFFER_SIZE);
            size = 0;
        }
    }while (size);
}

uint8_t storage_getCount(void)
{
    uint8_t count = 0;

    NOR_ReadSector(&count, STORAGE_SECTOR_INFO, 0, 1);

    return count;
}

void storage_updateCount(void)
{
    uint8_t count = storage_getCount() + 1;
    buffer[0] = count;

    _storage_copySector(0);
    NOR_EraseSector(STORAGE_SECTOR_INFO);
    NOR_WriteSector(buffer, STORAGE_SECTOR_INFO, 0, 1);
    
}

void storage_clean(void)
{
    led_rgb_setColor(LED_BLUE);
    uint8_t count = 0;

    for(uint16_t i = 0; i <= 255; i++)
    {
        NOR_EraseSector(i);
    }
    NOR_WriteSector(&count, STORAGE_SECTOR_INFO, 0, 1);
}


void storage_temperatureAppend(void)
{
    uint32_t sector_num = storage_getCount();
    if(sector_num == 0) return;

    uint16_t temperature_value;
    temperature_value = temperature_get();

    uint16_t temp_value = temperature_value;
    uint8_t temp[3];
    temp[0] = 0x55; // should be crc
    temp[1] = ((uint8_t*)&temp_value)[0];
    temp[2] = ((uint8_t*)&temp_value)[1];


    NOR_WriteSector(temp, sector_num, offset_temperature, 3);
    offset_temperature = offset_temperature + 3;
}


void storage_temperatureExtract(void)
{
    printf("Extract Values\n");
    uint8_t temp[3];
    uint16_t temperature_value = 0;
    uint32_t offset_temp = 0;

    uint8_t count = storage_getCount();
    for(uint32_t i = 1; i <= count; i++)
    {
        offset_temp = 0;
        printf("%ld=========\n", i);
        NOR_ReadSector(temp, i, 0, 3);
        uint8_t crc = temp[0];
        while(crc == 0x55)
        {
            ((uint8_t*)&temperature_value)[0] = temp[1];
            ((uint8_t*)&temperature_value)[1] = temp[2];

            printf("%d.%d C\n", temperature_value/10, temperature_value%10);
            offset_temp =  offset_temp + 3;
            NOR_ReadSector(temp, i, offset_temp, 3);
            crc = temp[0];
        }
    }
}


// ticks.c
#include "core/ticks.h"

static uint64_t ticks = 0;

void ticks_increment(void)
{
    ticks++;
}

uint64_t ticks_get(void)
{
    return ticks;
}
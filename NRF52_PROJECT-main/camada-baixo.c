// driver_event.c
#include "driver_event.h"

uint8_t event_read(__vo uint32_t* reg)
{
    return (*reg & (1 << 0));
}

void event_clear(__vo uint32_t* reg)
{
    *reg = 0;
}

void event_pooling(__vo uint32_t* reg)
{
    while(!(event_read(reg))); // wait event be generated
    event_clear(reg);
}



// driver_gpio.c
#include "driver_gpio.h"

void GPIO_Init(GPIO_Handle_t *pGPIOHandle)
{
    uint32_t temp = 0;
    temp |= (pGPIOHandle->GPIO_PinConfig.GPIO_PinPuPd << 2) | (pGPIOHandle->GPIO_PinConfig.GPIO_InpBuf << 1) |
            (pGPIOHandle->GPIO_PinConfig.GPIO_PinDir << 0); 

    pGPIOHandle->pGPIOx->PIN_CNF[pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber] = temp;

    if(pGPIOHandle->GPIO_PinConfig.GPIO_PinDir == GPIO_DIR_OUT)
    {
        GPIO_WriteToOutputPin(pGPIOHandle->pGPIOx, pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber, pGPIOHandle->GPIO_PinConfig.GPIO_PinState);
    }
}

uint8_t GPIO_ReadFromInputPin(GPIOP_RegDef_t *pGPIOx, uint8_t PinNumber)
{
    if(pGPIOx->IN & (1 << PinNumber))
    {
        return GPIO_PIN_SET;
    }
    return GPIO_PIN_RESET;
}

void GPIO_WriteToOutputPin(GPIOP_RegDef_t *pGPIOx, uint8_t PinNumber, uint8_t value)
{
    if(value == GPIO_PIN_SET)
    {
        pGPIOx->OUT |= (1 << PinNumber);
    }else
    {
        pGPIOx->OUT &= ~(1 << PinNumber);
    }
}

void GPIO_ToggleOutputPin(GPIOP_RegDef_t *pGPIOx, uint8_t PinNumber)
{
        pGPIOx->OUT ^= (1 << PinNumber);
}



// driver_interrupt.c
#include "driver_interrupt.h"

void interrupt_config(uint8_t IRQNumber, uint8_t EnorDi)
{
	if(EnorDi == ENABLE)
	{
		if(IRQNumber <= 31)
		{
			*NVIC_ISER0 |= ( 1 << IRQNumber );
		}else if(IRQNumber > 31 && IRQNumber < 64 ) //32 to 63
		{
			*NVIC_ISER1 |= ( 1 << (IRQNumber % 32) );
		}
		else if(IRQNumber >= 64 && IRQNumber < 96 )
		{
			*NVIC_ISER2 |= ( 1 << (IRQNumber % 64) );
		}
	}else
	{
		if(IRQNumber <= 31)
		{
			*NVIC_ICER0 |= ( 1 << IRQNumber );
		}else if(IRQNumber > 31 && IRQNumber < 64 )
		{
			*NVIC_ICER1 |= ( 1 << (IRQNumber % 32) );
		}
		else if(IRQNumber >= 64 && IRQNumber < 96 )
		{
			*NVIC_ICER2 |= ( 1 << (IRQNumber % 64) );
		}
	}
}

void interrupt_priorityConfig(uint8_t IRQNumber,uint32_t IRQPriority)
{
	uint8_t iprx = IRQNumber / 4;
	uint8_t iprx_section  = IRQNumber %4 ;
	uint8_t shift_amount = ( 8 * iprx_section) + ( 8 - NO_PR_BITS_IMPLEMENTED) ;
	*(  NVIC_PR_BASE_ADDR + iprx ) |=  ( IRQPriority << shift_amount );
}



// driver_saadc.c
#include "driver_saadc.h"

volatile int16_t result_adc = 0;

void saadc_init(SAADC_Handle_t *pSAADCHandle)
{
    uint32_t temp = 0;
    temp =  (pSAADCHandle->GAIN << SAADC_CH_CONFIG_GAIN_BIT) |
            (pSAADCHandle->MODE << SAADC_CH_CONFIG_MODE_BIT) |
            (pSAADCHandle->REFSEL << SAADC_CH_CONFIG_REFSEL_BIT) |
            (pSAADCHandle->RESN << SAADC_CH_CONFIG_RESN_BIT) |
            (pSAADCHandle->RESP << SAADC_CH_CONFIG_RESP_BIT) |
            (pSAADCHandle->TACQ << SAADC_CH_CONFIG_TACQ_BIT);

    SAADC->CH[pSAADCHandle->CHANNEL].CONFIG = temp;
    SAADC->CH[pSAADCHandle->CHANNEL].PSELP  = pSAADCHandle->PSELP;
    SAADC->CH[pSAADCHandle->CHANNEL].PSELN  = pSAADCHandle->PSELN;

    SAADC->RESOLUTION = pSAADCHandle->RESOLUTION;

    SAADC->RESULT.MAXCNT = 1;
    SAADC->RESULT.PTR   = (uint32_t)&result_adc;

    SAADC->ENABLER = 1;
    saadc_calibrate();
}

 void saadc_calibrate(void)
 {
    SAADC->TASKS_CALIBRATEOFFSET = 1;
    while(SAADC->EVENTS_CALIBRATEDONE == 0);
    SAADC->EVENTS_CALIBRATEDONE = 0;
    while(SAADC->STATUS == (1 << 0));
 }

uint16_t saadc_read(void)
{
   SAADC->TASKS_START = 1;
   while (SAADC->EVENTS_STARTED == 0);
   SAADC->EVENTS_STARTED = 0;

   while (SAADC->EVENTS_RESULTDONE == 0);
   SAADC->EVENTS_RESULTDONE = 0;

   // Do a SAADC sample, will put the result in the configured RAM buffer.
   SAADC->TASKS_SAMPLE = 1;
   while (SAADC->EVENTS_END == 0);
   SAADC->EVENTS_END = 0;

   if( result_adc & (1 << 15)) return 0;
   return result_adc;
}


 void saadc_selectInp(uint8_t psel)
 {
    SAADC->ENABLER = 0;
    SAADC->CH[0].PSELP  = psel;
    SAADC->ENABLER = 1;
 }



// driver_spi.c
#include "driver_spi.h"

void SPI_PeriControl(SPI_RegDef_t *pSPIx, uint8_t EnorDi)
{
    if(EnorDi == ENABLE)
    {
        pSPIx->ENABLER = 1;
    }else
    {
        pSPIx->ENABLER = 0;
    }
}

void SPI_Init(SPI_Handle_t *pSPIHandle)
{
    SPI_PeriControl(pSPIHandle->pSPIx, DISABLE);

    uint8_t psel_port = 0;
    uint32_t temp = 0;

    if(pSPIHandle->SCK.port == GPIOP1) psel_port = 1;
    temp = ((0 << SPI_PSEL_CONNECT) | (psel_port << SPI_PSEL_PORT) | (pSPIHandle->SCK.pin << SPI_PSEL_PIN));
    pSPIHandle->pSPIx->PSEL.SCK = temp;

    psel_port = 0;
    if(pSPIHandle->MISO.port == GPIOP1) psel_port = 1;
    temp = ((0 << SPI_PSEL_CONNECT) | (psel_port << SPI_PSEL_PORT) | (pSPIHandle->MISO.pin << SPI_PSEL_PIN));
    pSPIHandle->pSPIx->PSEL.MISO = temp;

    psel_port = 0;
    if(pSPIHandle->MOSI.port == GPIOP1) psel_port = 1;
    temp = ((0 << SPI_PSEL_CONNECT) | (psel_port << SPI_PSEL_PORT) | (pSPIHandle->MOSI.pin << SPI_PSEL_PIN));
    pSPIHandle->pSPIx->PSEL.MOSI = temp;

    temp = (pSPIHandle->SPI_Config.CPOL << 2) | (pSPIHandle->SPI_Config.CPHA << 1);
    pSPIHandle->pSPIx->CONFIG = temp;
    pSPIHandle->pSPIx->FREQUENCY = pSPIHandle->SPI_Config.Frequency;
    SPI_PeriControl(pSPIHandle->pSPIx, ENABLE);
}

void SPI_SendData(SPI_RegDef_t *pSPIx, uint8_t *pTxBuffer, uint32_t Len)
{
    uint8_t temp = 0;

    pSPIx->EVENTS_READY = 0;
    while(Len)
    {
        pSPIx->TXD = *(pTxBuffer++);
        event_pooling(&pSPIx->EVENTS_READY);
        temp = pSPIx->RXD;

        (void)temp;
        Len--;
    }
}

void SPI_ReceiveData(SPI_RegDef_t *pSPIx, uint8_t *pRxBuffer, uint32_t Len)
{
    uint8_t temp = 0xFF;

    pSPIx->EVENTS_READY = 0;
    while(Len)
    {
        pSPIx->TXD = temp;
        event_pooling(&pSPIx->EVENTS_READY);
        *(pRxBuffer++) = pSPIx->RXD;

        (void)temp;
        Len--;
    }
}



// driver_systick.c
#include "driver_systick.h"

void systick_set_frequency(uint32_t freq, uint32_t cpu_freq)
{
    SYSTICK->LOAD   = (cpu_freq/freq) - 1;
    SYSTICK->VAL = 0;
}

void systick_counter_enable(void)
{
    SYSTICK->CTRL = CTRL_ENABLE | CTRL_CLKSRC;
}

void systick_interrupt_enable(void)
{
    SYSTICK->CTRL |= CTRL_TICKINT;
}



// driver_twi.c
#include "driver_twi.h"

void TWI_Init(TWI_Handle_t *pTWIHandle)
{
    uint8_t psel_port = 0;
    uint32_t temp = 0;
    pTWIHandle->pTWIx->ENABLER = 0;

    if(pTWIHandle->SDA.port == GPIOP1) psel_port = 1;
    temp = ((0 << PSEL_CONNECT) | (psel_port << PSEL_PORT) | (pTWIHandle->SDA.pin << PSEL_PIN));
    pTWIHandle->pTWIx->PSEL.SDA = temp;

    psel_port = 0;
    if(pTWIHandle->SCL.port == GPIOP1) psel_port = 1;
    temp = ((0 << PSEL_CONNECT) | (psel_port << PSEL_PORT) | (pTWIHandle->SCL.pin << PSEL_PIN));
    pTWIHandle->pTWIx->PSEL.SCL = temp;
    pTWIHandle->pTWIx->FREQUENCY = pTWIHandle->config.FREQUENCY;
    pTWIHandle->pTWIx->ENABLER = 6;
}

void TWI_MasterSendData(TWI_RegDef_t *pTWIx, uint8_t *pTxBuffer, uint32_t Len, uint8_t SlaveAddr)
{
    pTWIx->ADDRESS = SlaveAddr;
    pTWIx->SHORTS = (1 << 9);

    pTWIx->TXD.MAXCNT = Len;
    pTWIx->TXD.PTR = (uint32_t)pTxBuffer;

    pTWIx->EVENTS_STOPPED = 0;
    pTWIx->TASKS_STARTTX = 1;
    while (pTWIx->EVENTS_STOPPED == 0);
}

void TWI_MasterReceiveData(TWI_RegDef_t *pTWIx, uint8_t *pRxBuffer, uint8_t Len, uint8_t SlaveAddr)
{
    pTWIx->ADDRESS = SlaveAddr;
    pTWIx->SHORTS = (1 << 12);

    pTWIx->RXD.MAXCNT = Len;
    pTWIx->RXD.PTR = (uint32_t)pRxBuffer;

    pTWIx->EVENTS_STOPPED = 0;
    pTWIx->TASKS_STARTRX = 1;
    while (pTWIx->EVENTS_STOPPED == 0);
    
}



// driver_uart.c
#include "driver_uart.h"
#include "ring-buffer.h"

#define RING_BUFFER_SIZE		(128)
static ring_buffer_t rb = {0U};
static uint8_t data_buffer[RING_BUFFER_SIZE] = {0U};

void UART_PeriClockControl(uint8_t EnorDi)
{
    if(EnorDi == ENABLE)
    {
        UART->ENABLER = (4 << 0);
    }else
    {
        UART->ENABLER = 0;
    }
}

void UART_Init(UART_Handle_t* pUARTHandle)
{
    ring_buffer_setup(&rb, data_buffer, RING_BUFFER_SIZE);
    UART_PeriClockControl(DISABLE);

    uint8_t psel_port = 0;
    uint32_t temp = 0;
    if(pUARTHandle->UART_Config.Mode == UART_MODE_ONLY_TX)
    {
        if(pUARTHandle->Tx.port == GPIOP1) psel_port = 1;
        temp = ((0 << UART_PSEL_CONNECT) | (psel_port << UART_PSEL_PORT) | (pUARTHandle->Tx.pin << UART_PSEL_PIN));
        UART->PSEL.TXD = temp;
    }else if(pUARTHandle->UART_Config.Mode == UART_MODE_ONLY_RX)
    {
        if(pUARTHandle->Rx.port == GPIOP1) psel_port = 1;
        temp = ((0 << UART_PSEL_CONNECT) | (psel_port << UART_PSEL_PORT) | (pUARTHandle->Rx.pin << UART_PSEL_PIN));
        UART->PSEL.RXD = temp;

    }else if(pUARTHandle->UART_Config.Mode == UART_MODE_TXRX)
    {
        if(pUARTHandle->Tx.port == GPIOP1) psel_port = 1;
        temp = ((0 << UART_PSEL_CONNECT) | (psel_port << UART_PSEL_PORT) | (pUARTHandle->Tx.pin << UART_PSEL_PIN));
        UART->PSEL.TXD = temp;

        psel_port = 0;
        if(pUARTHandle->Rx.port == GPIOP1) psel_port = 1;
        temp = ((0 << UART_PSEL_CONNECT) | (psel_port << UART_PSEL_PORT) | (pUARTHandle->Rx.pin << UART_PSEL_PIN));
        UART->PSEL.RXD = temp;
    }
    
    UART_PeriClockControl(ENABLE);
    UART->BAUDRATE = pUARTHandle->UART_Config.Baud;

    if(pUARTHandle->UART_Config.Mode == UART_MODE_ONLY_TX)
    {
        uart_tx_start();
    }else if(pUARTHandle->UART_Config.Mode == UART_MODE_ONLY_RX)
    {
        uart_rx_start();

    }else if(pUARTHandle->UART_Config.Mode == UART_MODE_TXRX)
    {
        uart_tx_start();
        uart_rx_start();
    }
}

void uart_write_byte(uint8_t ch)
{
    UART->TXD = (ch);
    event_pooling(&UART->EVENTS_TXDRDY);
}

uint8_t uart_read_byte(void)
{
    return (uint8_t)UART->RXD;
}

void uart_write(uint8_t* buffer, uint32_t Len)
{
    for(uint32_t i = 0; i < Len; i++)
    {
        uart_write_byte(buffer[i]);
    }
}

void uart_tx_start(void){ UART->TASKS_STARTTX |= 1; }
void uart_tx_stop(void) { UART->TASKS_STOPTX |= 1; }
void uart_rx_start(void){ UART->TASKS_STARTRX |= 1; }
void uart_rx_stop(void) { UART->TASKS_STOPRX |= 1; }

void uart_interruptConfig(uint32_t interrupts, uint8_t EnorDi)
{
    if(EnorDi == ENABLE)
    {
        UART->INTENSET |= interrupts;
    }else
    {
        UART->INTENCLR |= interrupts;
    }
}

bool uart_data_available(void)
{
    return !ring_buffer_empty(&rb);
}

uint32_t uart_rcv(uint8_t *data, const uint32_t length)
{
    if(length == 0)
	{
		return 0;
	}
	
	for(uint32_t bytes_read = 0; bytes_read < length; bytes_read++)
	{
		if(!ring_buffer_read(&rb, &data[bytes_read]))
		{
			return bytes_read;
		}
	}

	return length;
}

uint8_t uart_rcv_byte(void)
{
    uint8_t byte = 0;
	
	(void)uart_rcv(&byte, 1);

	return byte;
}

void UART_IRQHandler(void)
{
    if(UART_EVENT_RXDRDY)
    {
        event_clear(&UART_EVENT_RXDRDY);
        if(ring_buffer_write(&rb, uart_read_byte()))
		{
			// handle some error/failure
		}
    }
}
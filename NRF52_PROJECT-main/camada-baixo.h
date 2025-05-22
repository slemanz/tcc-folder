// driver_event.h
#ifndef INC_DRIVER_EVENT_H_
#define INC_DRIVER_EVENT_H_

#include "nrf52.h"

uint8_t event_read(__vo uint32_t* reg);
void event_clear(__vo uint32_t* reg);
void event_pooling(__vo uint32_t* reg);

#endif /* INC_DRIVER_EVENT_H_ */

// driver_gpio.h
#ifndef INC_DRIVER_GPIO_H_
#define INC_DRIVER_GPIO_H_

#include "nrf52.h"

typedef struct
{
	uint8_t GPIO_PinNumber;
	uint8_t GPIO_PinDir;
	uint8_t GPIO_PinPuPd;
	uint8_t GPIO_PinState;
	uint8_t GPIO_InpBuf;
}GPIO_PinConfig_t;

typedef struct
{
	GPIOP_RegDef_t *pGPIOx;
	GPIO_PinConfig_t GPIO_PinConfig; 
}GPIO_Handle_t;

// @GPIO_PIN_NUMBER
#define GPIO_PIN_NO_0		0
#define GPIO_PIN_NO_1		1
#define GPIO_PIN_NO_2		2
#define GPIO_PIN_NO_3		3
#define GPIO_PIN_NO_4		4
#define GPIO_PIN_NO_5		5
#define GPIO_PIN_NO_6		6
#define GPIO_PIN_NO_7		7
#define GPIO_PIN_NO_8		8
#define GPIO_PIN_NO_9		9
#define GPIO_PIN_NO_10		10
#define GPIO_PIN_NO_11		11
#define GPIO_PIN_NO_12		12
#define GPIO_PIN_NO_13		13
#define GPIO_PIN_NO_14		14
#define GPIO_PIN_NO_15		15
#define GPIO_PIN_NO_16		16
#define GPIO_PIN_NO_17		17
#define GPIO_PIN_NO_18		18
#define GPIO_PIN_NO_19		19
#define GPIO_PIN_NO_20		20
#define GPIO_PIN_NO_21		21
#define GPIO_PIN_NO_22		22
#define GPIO_PIN_NO_23		23
#define GPIO_PIN_NO_24		24
#define GPIO_PIN_NO_25		25
#define GPIO_PIN_NO_26		26
#define GPIO_PIN_NO_27		27
#define GPIO_PIN_NO_28		28
#define GPIO_PIN_NO_29		29
#define GPIO_PIN_NO_30		30
#define GPIO_PIN_NO_31		31

// @GPIO_PIN_DIR
#define GPIO_DIR_IN 		0
#define GPIO_DIR_OUT 		1

//@GPIO_PIN_PUPD
#define GPIO_PIN_NO_PUPD	0
#define GPIO_PIN_PD 		1
#define GPIO_PIN_PU 		3

//@GPIO_PIN_STATE
#define GPIO_PIN_SET				1
#define GPIO_PIN_RESET				0

//@GPIO_INPUT_BUFFER
#define GPIO_INP_BUF_CONNECT		0
#define GPIO_INP_BUF_DISCONNECT		1

// functions
void GPIO_Init(GPIO_Handle_t *pGPIOHandle);
void GPIO_DeInit(GPIOP_RegDef_t *pGPIOx); // not implemented yet
uint8_t  GPIO_ReadFromInputPin(GPIOP_RegDef_t *pGPIOx, uint8_t PinNumber);
void GPIO_WriteToOutputPin(GPIOP_RegDef_t *pGPIOx, uint8_t PinNumber, uint8_t value);
void GPIO_ToggleOutputPin(GPIOP_RegDef_t *pGPIOx, uint8_t PinNumber);

#endif /* INC_DRIVER_GPIO_H_ */


// driver_interrupt.h
#ifndef INC_DRIVER_INTERRUPT_H_
#define INC_DRIVER_INTERRUPT_H_

#include "nrf52.h"

void interrupt_config(uint8_t IRQNumber, uint8_t EnorDi);
void interrupt_priorityConfig(uint8_t IRQNumber,uint32_t IRQPriority);

#endif /* INC_DRIVER_INTERRUPT_H_ */


// driver_saadc.h
#ifndef DRIVER_SAADC_H_
#define DRIVER_SAADC_H_

#include "nrf52.h"

typedef struct
{
    uint8_t CHANNEL;
    uint8_t RESP;
    uint8_t RESN;
    uint8_t GAIN;
    uint8_t REFSEL;
    uint8_t TACQ;
    uint8_t MODE;
    uint8_t BURST;
    uint8_t PSELP;
    uint8_t PSELN;
    uint8_t RESOLUTION;
}SAADC_Handle_t;

//@SAADC_CHANNEL
#define SAADC_CHANNEL_0                 0
#define SAADC_CHANNEL_1                 1
#define SAADC_CHANNEL_2                 2
#define SAADC_CHANNEL_3                 3
#define SAADC_CHANNEL_4                 4
#define SAADC_CHANNEL_5                 5
#define SAADC_CHANNEL_6                 6
#define SAADC_CHANNEL_7                 7

//@SAADC_RES
#define SAADC_RES_BYPASS               0
#define SAADC_RES_PULLDOWN             1
#define SAADC_RES_PULLUP               2
#define SAADC_RES_VDD1_2               3

//@SAADC_GAIN
#define SAADC_GAIN_1_6                 0
#define SAADC_GAIN_1_5                 1
#define SAADC_GAIN_1_4                 2
#define SAADC_GAIN_1_3                 3
#define SAADC_GAIN_1_2                 4
#define SAADC_GAIN_1                   5
#define SAADC_GAIN_2                   6
#define SAADC_GAIN_4                   7

//@SAADC_REFSEL
#define SAADC_REFSEL_INTERNAL           0
#define SAADC_REFSEL_VDD_1_4            1

//@SAADC_TACQ
#define SAADC_TACQ_3US                  0
#define SAADC_TACQ_5US                  1
#define SAADC_TACQ_10US                 2
#define SAADC_TACQ_15US                 3
#define SAADC_TACQ_20US                 4
#define SAADC_TACQ_40US                 5

//@SAADC_MODE
#define SAADC_MODE_SE                   0
#define SAADC_MODE_DIFF                 1

//@SAADC_BURST
#define SAADC_BURST_DIS                 0
#define SAADC_BURST_EN                  1

//@SAADC_PSEL
#define SAADC_PSEL_NC                  0
#define SAADC_PSEL_AIN0                1
#define SAADC_PSEL_AIN1                2
#define SAADC_PSEL_AIN2                3
#define SAADC_PSEL_AIN3                4
#define SAADC_PSEL_AIN4                5
#define SAADC_PSEL_AIN5                6
#define SAADC_PSEL_AIN6                7
#define SAADC_PSEL_AIN7                8
#define SAADC_PSEL_VDD                 9
#define SAADC_PSEL_VDDHDIV5            0xD

//@SAADC_RESOLUTION
#define SAADC_RESOLUTION_8BIT           0
#define SAADC_RESOLUTION_10BIT          1
#define SAADC_RESOLUTION_12BIT          2
#define SAADC_RESOLUTION_14BIT          3

//@SAADC_OVERSAMPLE
#define SAADC_OVERSAMPLE_BYPASS        0
#define SAADC_OVERSAMPLE_2X            1
#define SAADC_OVERSAMPLE_4X            2
#define SAADC_OVERSAMPLE_8X            3
#define SAADC_OVERSAMPLE_16X           4
#define SAADC_OVERSAMPLE_32X           5
#define SAADC_OVERSAMPLE_64X           6
#define SAADC_OVERSAMPLE_128X          7
#define SAADC_OVERSAMPLE_256X          8

//SAADC Register bits
#define SAADC_CH_CONFIG_RESP_BIT        0
#define SAADC_CH_CONFIG_RESN_BIT        4
#define SAADC_CH_CONFIG_GAIN_BIT        8
#define SAADC_CH_CONFIG_REFSEL_BIT      12
#define SAADC_CH_CONFIG_TACQ_BIT        16
#define SAADC_CH_CONFIG_MODE_BIT        20
#define SAADC_CH_CONFIG_BURST_BIT       24

//functions
void saadc_init(SAADC_Handle_t *pSAADCHandle);
void saadc_calibrate(void);
void saadc_selectInp(uint8_t psel); // works only when channel 0 is been used
uint16_t saadc_read(void);

#endif /* DRIVER_SAADC_H_ */



// driver_spi.h
#ifndef INC_DRIVER_SPI_H_
#define INC_DRIVER_SPI_H_

#include "nrf52.h"

typedef struct
{
	uint8_t CPHA;
	uint8_t CPOL;
	uint32_t Frequency;
}SPI_Config_t;

typedef struct{
	SPI_Config_t SPI_Config;
	SPI_RegDef_t *pSPIx;
    PSEL_t MOSI;
    PSEL_t MISO;
    PSEL_t SCK;
}SPI_Handle_t;

//@SPI_CPHA
#define SPI_CPHA_HIGH	1
#define SPI_CPHA_LOW	0

//@SPI_CPOL
#define SPI_CPOL_HIGH	1
#define SPI_CPOL_LOW	0

//@SPI_FREQUENCY
#define SPI_FREQUENCY_K125      0x02000000U
#define SPI_FREQUENCY_K250      0x04000000U
#define SPI_FREQUENCY_K500      0x08000000U
#define SPI_FREQUENCY_M1        0x10000000U
#define SPI_FREQUENCY_M2        0x20000000U
#define SPI_FREQUENCY_M4        0x40000000U
#define SPI_FREQUENCY_M8        0x80000000U

//SPI Registers 
#define SPI_PSEL_PIN           0
#define SPI_PSEL_PORT          5
#define SPI_PSEL_CONNECT       31

// functions
void SPI_PeriControl(SPI_RegDef_t *pSPIx, uint8_t EnorDi);
void SPI_Init(SPI_Handle_t *pSPIHandle);
void SPI_DeInit(SPI_RegDef_t *pSPIx);
void SPI_SendData(SPI_RegDef_t *pSPIx, uint8_t *pTxBuffer, uint32_t Len);
void SPI_ReceiveData(SPI_RegDef_t *pSPIx, uint8_t *pRxBuffer, uint32_t Len);

#endif /* INC_DRIVER_SPI_H_ */



// driver_systick.h
#ifndef INC_DRIVER_SYSTICK_H_
#define INC_DRIVER_SYSTICK_H_

#include "nrf52.h"

#define SYSTICK_LOAD_VAL            16000
#define CTRL_ENABLE                 (1U << 0)
#define CTRL_CLKSRC                 (1U << 2)
#define CTRL_COUNTFLAG              (1U << 16)
#define CTRL_TICKINT                (1U << 1)
#define ONE_SEC_LOAD                16000000

void systick_set_frequency(uint32_t freq, uint32_t cpu_freq);
void systick_counter_enable(void);
void systick_interrupt_enable(void);

#endif



// driver_twi.h
#ifndef DRIVER_TWI_H_
#define DRIVER_TWI_H_

#include "nrf52.h"

typedef struct
{
	uint32_t FREQUENCY;
}TWI_Config_t;

typedef struct{
    TWI_RegDef_t *pTWIx;
    TWI_Config_t config;
    PSEL_t SCL;
    PSEL_t SDA;
}TWI_Handle_t;

//@TWI_FREQUENCY
#define TWI_FREQUENCY_K100      0x01980000U
#define TWI_FREQUENCY_K250      0x04000000U
#define TWI_FREQUENCY_K400      0x06680000U

// functions
void TWI_Init(TWI_Handle_t *pTWIHandle);
void TWI_MasterSendData(TWI_RegDef_t *pTWIx, uint8_t *pTxBuffer, uint32_t Len, uint8_t SlaveAddr);
void TWI_MasterReceiveData(TWI_RegDef_t *pTWIx, uint8_t *pRxBuffer, uint8_t Len, uint8_t SlaveAddr);

#endif /* DRIVER_I2C_H_ */



// driver_uart.h
#ifndef INC_DRIVER_UART_H_
#define INC_DRIVER_UART_H_

#include "nrf52.h"

typedef struct
{
	uint8_t Mode;
	uint32_t Baud;
}UART_Config_t;

typedef struct{
	UART_Config_t UART_Config;
    PSEL_t Tx;
    PSEL_t Rx;
}UART_Handle_t;

//@UART_Mode
#define UART_MODE_ONLY_TX		0
#define UART_MODE_ONLY_RX		1
#define UART_MODE_TXRX			2

//@UART_Baud
#define UART_STD_BAUD_9600			0x00275000U
#define UART_STD_BAUD_115200		0x01D7E000U

//UART Registers 
#define UART_PSEL_PIN           0
#define UART_PSEL_PORT          5
#define UART_PSEL_CONNECT       31

//UART Interrupts
#define UART_INTERRUPT_CTS		(1 << 0)
#define UART_INTERRUPT_NCTS		(1 << 1)
#define UART_INTERRUPT_RXRDY	(1 << 2)
#define UART_INTERRUPT_TXRDY	(1 << 7)
#define UART_INTERRUPT_ERROR	(1 << 9)
#define UART_INTERRUPT_TXTO		(1 << 17)

//UART Events
#define UART_IRQ_NO				2
#define UART_EVENT_RXDRDY		(UART->EVENTS_RXDRDY)

// functions
void UART_PeriClockControl(uint8_t EnorDi);
void UART_Init(UART_Handle_t* pUARTHandle);
void uart_write_byte(uint8_t ch);
void uart_write(uint8_t* buffer, uint32_t Len);
uint8_t uart_read_byte(void);
void uart_tx_start(void);
void uart_tx_stop(void);
void uart_rx_start(void);
void uart_rx_stop(void);
void uart_interruptConfig(uint32_t interrupts, uint8_t EnorDi);
bool uart_data_available(void);
uint32_t uart_rcv(uint8_t *data, const uint32_t length);
uint8_t uart_rcv_byte(void);

#endif


// nrf52.h
#ifndef INC_NRF52_H_
#define INC_NRF52_H_

// this header file describes the microcontroller
#include <stdint.h>
#include <stdbool.h>

#define __vo volatile
#define MMIO32(addr) (*(volatile uint32_t *)(addr))


/*******************START: Processor Specific Details *************************/

#define NVIC_ISER0 						((__vo uint32_t*)0xE000E100UL)
#define NVIC_ISER1 						((__vo uint32_t*)0xE000E104UL)
#define NVIC_ISER2 						((__vo uint32_t*)0xE000E108UL)
#define NVIC_ISER3 						((__vo uint32_t*)0xE000E10CUL)

#define NVIC_ICER0 						((__vo uint32_t*)0xE000E180UL)
#define NVIC_ICER1 						((__vo uint32_t*)0xE000E184UL)
#define NVIC_ICER2 						((__vo uint32_t*)0xE000E188UL)
#define NVIC_ICER3 						((__vo uint32_t*)0xE000E18CUL)

#define NVIC_PR_BASE_ADDR	((__vo uint32_t*)0xE000E400UL)
#define NO_PR_BITS_IMPLEMENTED 		4

/******************* Memory and Peripherals address *************************/
#define FLASH_BASEADDR						0x00000000U
#define SRAM1_BASEADDR						0x20000000U
#define SCS_BASE            				(0xE000E000UL)
#define SYSTICK_BASEADDR					(SCS_BASE + 0x0010UL)
#define GPIOP0_BASEADDR						(0x50000000UL)
#define GPIOP1_BASEADDR						(0x50000300UL)
#define UART_BASEADDR 						(0x40002000UL)
#define SPI0_BASEADDR 						(0x40003000UL)
#define SPI1_BASEADDR 						(0x40004000UL)
#define SPI2_BASEADDR 						(0x40023000UL)
#define TWI0_BASEADDR                   	(0x40003000UL)
#define TWI1_BASEADDR                   	(0x40004000UL)
#define SAADC_BASEADDR                  	(0x40007000UL)
#define RCC_BASEADDR						(AHB1PERIPH_BASE + 0x3800U)

/*******************peripheral register definition structures*******************/

typedef struct
{
  	__vo uint32_t  RESERVED0[321];
	__vo uint32_t  OUT;             
	__vo uint32_t  OUTSET;          
	__vo uint32_t  OUTCLR;          
	__vo uint32_t  IN;              
	__vo uint32_t  DIR;             
	__vo uint32_t  DIRSET;          
	__vo uint32_t  DIRCLR;          
	__vo uint32_t  LATCH;           
	__vo uint32_t  DETECTMODE;      
	__vo uint32_t  RESERVED1[118];
	__vo uint32_t  PIN_CNF[32];  
}GPIOP_RegDef_t;

typedef struct
{
	__vo uint32_t CTRL; 
	__vo uint32_t LOAD; 
	__vo uint32_t VAL;  
	__vo uint32_t CALIB;
}SYSTICK_RegDef_t;

typedef struct {
	__vo uint32_t  RTS;             
	__vo uint32_t  TXD;             
	__vo uint32_t  CTS;             
	__vo uint32_t  RXD;             
} UART_PSEL_T;

typedef struct
{
	__vo uint32_t  TASKS_STARTRX;
	__vo uint32_t  TASKS_STOPRX; 
	__vo uint32_t  TASKS_STARTTX;
	__vo uint32_t  TASKS_STOPTX; 
	__vo uint32_t  RESERVED0[3];
	__vo uint32_t  TASKS_SUSPEND;
	__vo uint32_t  RESERVED1[56];
	__vo uint32_t  EVENTS_CTS;   
	__vo uint32_t  EVENTS_NCTS;  
	__vo uint32_t  EVENTS_RXDRDY;
	__vo uint32_t  RESERVED2[4];
	__vo uint32_t  EVENTS_TXDRDY;
	__vo uint32_t  RESERVED3;
	__vo uint32_t  EVENTS_ERROR; 
	__vo uint32_t  RESERVED4[7];
	__vo uint32_t  EVENTS_RXTO;  
	__vo uint32_t  RESERVED5[46];
	__vo uint32_t  SHORTS;       
	__vo uint32_t  RESERVED6[64];
	__vo uint32_t  INTENSET;     
	__vo uint32_t  INTENCLR;     
	__vo uint32_t  RESERVED7[93];
	__vo uint32_t  ERRORSRC;     
	__vo uint32_t  RESERVED8[31];
	__vo uint32_t  ENABLER;      
	__vo uint32_t  RESERVED9;
	UART_PSEL_T    PSEL;                        
	__vo uint32_t  RXD;                         
	__vo uint32_t  TXD;                         
	__vo uint32_t  RESERVED10;
	__vo uint32_t  BAUDRATE;                    
	__vo uint32_t  RESERVED11[17];
	__vo uint32_t  CONFIG; 
}UART_RegDef_t;

typedef struct {
	__vo uint32_t  SCK;                         
	__vo uint32_t  MOSI;                        
	__vo uint32_t  MISO;                        
} SPI_PSEL_T;

typedef struct {                             
  __vo uint32_t  RESERVED0[66];
  __vo uint32_t  EVENTS_READY;               
  __vo uint32_t  RESERVED1[126];
  __vo uint32_t  INTENSET;                   
  __vo uint32_t  INTENCLR;                   
  __vo uint32_t  RESERVED2[125];
  __vo uint32_t  ENABLER;                    
  __vo uint32_t  RESERVED3;
  SPI_PSEL_T     PSEL;                       
  __vo uint32_t  RESERVED4;
  __vo uint32_t  RXD;                        
  __vo uint32_t  TXD;                        
  __vo uint32_t  RESERVED5;
  __vo uint32_t  FREQUENCY;                  
  __vo uint32_t  RESERVED6[11];
  __vo uint32_t  CONFIG;                     
} SPI_RegDef_t;

typedef struct {
	__vo uint32_t  SCL;                         
	__vo uint32_t  SDA;                         
} TWIM_PSEL_T;

typedef struct {
  __vo uint32_t  PTR;                        
  __vo uint32_t  MAXCNT;                     
  __vo uint32_t  AMOUNT;                     
  __vo uint32_t  LIST;                       
} TWIM_RXD_Type;

typedef struct {
  __vo uint32_t  PTR;                        
  __vo uint32_t  MAXCNT;                     
  __vo uint32_t  AMOUNT;                     
  __vo uint32_t  LIST;                       
} TWIM_TXD_Type;

typedef struct {                             
	__vo uint32_t  TASKS_STARTRX;               
	__vo uint32_t  RESERVED0;
	__vo uint32_t  TASKS_STARTTX;               
	__vo uint32_t  RESERVED1[2];
	__vo uint32_t  TASKS_STOP;                  
	__vo uint32_t  RESERVED2;
	__vo uint32_t  TASKS_SUSPEND;                     
	__vo uint32_t  TASKS_RESUME;                      
	__vo uint32_t  RESERVED3[56];
	__vo uint32_t  EVENTS_STOPPED;                    
	__vo uint32_t  RESERVED4[7];
	__vo uint32_t  EVENTS_ERROR;                      
	__vo uint32_t  RESERVED5[8];
	__vo uint32_t  EVENTS_SUSPENDED; 
	__vo uint32_t  EVENTS_RXSTARTED; 
	__vo uint32_t  EVENTS_TXSTARTED; 
	__vo uint32_t  RESERVED6[2];
	__vo uint32_t  EVENTS_LASTRX;    
	__vo uint32_t  EVENTS_LASTTX;    
	__vo uint32_t  RESERVED7[39];
	__vo uint32_t  SHORTS;       
	__vo uint32_t  RESERVED8[63];
	__vo uint32_t  INTEN;        
	__vo uint32_t  INTENSET;     
	__vo uint32_t  INTENCLR;     
	__vo uint32_t  RESERVED9[110];
	__vo uint32_t  ERRORSRC;      
	__vo uint32_t  RESERVED10[14];
	__vo uint32_t  ENABLER;       
	__vo uint32_t  RESERVED11;
	TWIM_PSEL_T    PSEL;          
	__vo uint32_t  RESERVED12[5];
	__vo uint32_t  FREQUENCY;     
	__vo uint32_t  RESERVED13[3];
	TWIM_RXD_Type RXD;            
	TWIM_TXD_Type TXD;            
	__vo uint32_t  RESERVED14[13];
	__vo uint32_t  ADDRESS;  
} TWI_RegDef_t;

typedef struct
{
	GPIOP_RegDef_t* port;
	uint8_t pin;
}PSEL_t;

typedef struct
{
	__vo uint32_t  LIMITH;                            
	__vo uint32_t  LIMITL;                           
} SAADC_EVENTS_CH_T;

typedef struct 
{
	__vo uint32_t  PSELP;                          
	__vo uint32_t  PSELN;                       
	__vo uint32_t  CONFIG;                       
	__vo uint32_t  LIMIT;                       
} SAADC_CH_T;

typedef struct 
{
	__vo uint32_t  PTR;                       
	__vo uint32_t  MAXCNT;                    
	__vo uint32_t  AMOUNT;                      
                                                	
} SAADC_RESULT_T;

typedef struct {                               
	__vo uint32_t  TASKS_START;                 
	__vo uint32_t  TASKS_SAMPLE;                
	__vo uint32_t  TASKS_STOP;                     
	__vo uint32_t  TASKS_CALIBRATEOFFSET;          
	__vo uint32_t  RESERVED0[60];
	__vo uint32_t  EVENTS_STARTED;              
	__vo uint32_t  EVENTS_END;                    
	__vo uint32_t  EVENTS_DONE;                   
	__vo uint32_t  EVENTS_RESULTDONE;              
	__vo uint32_t  EVENTS_CALIBRATEDONE;          
	__vo uint32_t  EVENTS_STOPPED;                
	SAADC_EVENTS_CH_T EVENTS_CH[8];              
	__vo uint32_t  RESERVED1[106];
	__vo uint32_t  INTEN;                          
	__vo uint32_t  INTENSET;                        
	__vo uint32_t  INTENCLR;                       
	__vo uint32_t  RESERVED2[61];
	__vo uint32_t  STATUS;                           
	__vo uint32_t  RESERVED3[63];
	__vo uint32_t  ENABLER;                          
	__vo uint32_t  RESERVED4[3];
	SAADC_CH_T 	   CH[8];                            
	__vo uint32_t  RESERVED5[24];
	__vo uint32_t  RESOLUTION;                        
	__vo uint32_t  OVERSAMPLE;                       
  	__vo uint32_t  SAMPLERATE;                        
  	__vo uint32_t  RESERVED6[12];
	SAADC_RESULT_T RESULT;                         
} SAADC_RegDef_t;

#define PSEL_PIN           0
#define PSEL_PORT          5
#define PSEL_CONNECT       31

/* ================================================================================ */
/* ================             Peripheral declaration             ================ */
/* ================================================================================ */
#define SYSTICK         	((SYSTICK_RegDef_t*)SYSTICK_BASEADDR) 
#define GPIOP0				((GPIOP_RegDef_t*)	(GPIOP0_BASEADDR))
#define GPIOP1				((GPIOP_RegDef_t*)	(GPIOP1_BASEADDR))
#define UART 				((UART_RegDef_t*)	(UART_BASEADDR))
#define SPI0 				((SPI_RegDef_t*)	(SPI0_BASEADDR))
#define SPI1 				((SPI_RegDef_t*)	(SPI1_BASEADDR))
#define SPI2 				((SPI_RegDef_t*)	(SPI2_BASEADDR))
#define TWI0				((TWI_RegDef_t*)	(TWI0_BASEADDR))
#define TWI1				((TWI_RegDef_t*)	(TWI1_BASEADDR))
#define SAADC               ((SAADC_RegDef_t*) 	(SAADC_BASEADDR))

#define ENABLE 						1
#define	DISABLE 					0
#define _SET						ENABLE
#define _RESET						DISABLE
#define FLAG_SET					_SET
#define FLAG_RESET					_RESET

#define NVIC_IRQ_PRI0		0
#define NVIC_IRQ_PRI15		15

#define SCB_BASE 			(0xE000ED00UL)
#define VTOR_OFFSET      	MMIO32(SCB_BASE + 0x08U)

// Drivers includes
#include "driver_event.h"
#include "driver_interrupt.h"
#include "driver_gpio.h"
#include "driver_systick.h"
#include "driver_uart.h"
#include "driver_spi.h"
#include "driver_twi.h"
#include "driver_saadc.h"

#endif
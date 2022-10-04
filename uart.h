/*
 * uart.h
 *
 * Created: 2/6/2022 3:59:14 PM
 *  Author: shambhu kumar
 */

#ifndef UART_H_
#define UART_H_

#define F_CPU				11059200UL

#include "avr/io.h"
#include "avr/interrupt.h"
#include "stdint.h"
#include "util/delay.h"

// U for unsigned, UL for unsigned long, ULL for unsigned long long  int
#define BAUD_RATE			9600U
#define MAX_UART_BUFF_SIZE	50

#define BAUD_REG_VALUE		(uint8_t)((F_CPU/16)/BAUD_RATE - 1)

#define SET_BIT(bit)		(1<<bit)
//#define POLL_BIT(reg,bit)	(reg & (1<<bit))

#define ENABLE_TX				(UCSRB |= (1<<TXEN))
#define ENABLE_RX				(UCSRB |= (1<<RXEN))
#define ENABLE_TX_INTERRUPT		(UCSRB |= (1<<UDRIE))
#define ENABLE_RX_INTERRUPT		(UCSRB |= (1<<RXCIE))
#define DISABLE_TX_INTERRUPT	(UCSRB &= ~(1<<UDRIE))
#define DISABLE_RX_INTERRUPT	(UCSRB &= ~(1<<RXCIE))

#define RX					DDD0
#define TX					DDD1
#define OUTPUT				1
#define INPUT				0
#define HIGH				1
#define LOW					0

// 1, output
#define IO_REGISTER_BIT_MODE(reg,pin,io)	{if(io == 1){reg |= (1<<pin);}\
											else{reg &= ~(1<<pin);}} 

#define IO_REGISTER_MODE(reg,io)			{if(io == 1){reg = 0xff;}\
											else{reg = 0x00;}}
												
#define  PULL_UP_PORT(reg)					{reg = 0xff}
#define  PULL_UP_PORT_BIT(reg,bit)			{reg |= (1<<bit)}
	


struct{
	
	volatile uint8_t uart_rx_index;
	volatile uint8_t uart_tx_index;
	volatile uint8_t uart_rxc_ready_flag			:1;
	//volatile uint8_t uart_txc_ready_flag			:1;
	volatile uint8_t uart_char_received_flag		:1;
	//volatile uint8_t uart_link_txc_buffer_flag		:1;
	//volatile uint8_t uart_txc_buff_clear_flag		:1;
	//volatile uint8_t uart_boot_up_flag				:1;
	volatile uint8_t uart_receive_buffer[MAX_UART_BUFF_SIZE+1];
	volatile uint8_t uart_transmit_buffer[MAX_UART_BUFF_SIZE+1];
}uart_matter;

volatile uint8_t i, temp_data;

// initiallise uart settings
void uart_init(void);

//uint8_t uart_rx(void);

//void uart_tx(uint8_t);

// receive string from uart
void uart_rx_string(uint8_t*);

// receive ascii characters serially UART, return "1" if success else return "0"
//uint8_t uart_scanf(uint8_t*);


void uart_tx_string(uint8_t*);

//transmit a character to uart
void uart_tx_char(uint8_t);

// transmit string serially UART
void uart_printf(char*);

// copy source to destination string
void string_copy(uint8_t*,uint8_t*);

//count characters in given string except NULL
//uint8_t string_length(uint8_t*);

//clears given buffer
void clear_uart_buffer(uint8_t*);

// convert decimal value to string and store it to passed string
void uart_decimal_to_string(uint32_t,uint8_t*);

//transmit decimal values to UART
void print_decimal(uint32_t);

void bt_cmd_check(uint8_t*);

//void link_string(uint8_t*,uint8_t*);

#endif /* UART_H_ */
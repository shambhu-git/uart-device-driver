/*
 * uart.c
 *
 * Created: 2/6/2022 3:59:31 PM
 *  Author: shambhu kumar
 */ 

#include "uart.h"

void uart_init(void){

	ENABLE_RX;					// enable receiver
	ENABLE_TX;					//enable transmitter
	//ENABLE_TX_INTERRUPT;
	ENABLE_RX_INTERRUPT;
	//8 data bit, 1 stop bit, no parity
	UCSRC |= SET_BIT(UCSZ0) | SET_BIT(UCSZ1) | SET_BIT(URSEL); 
	UBRRH = BAUD_REG_VALUE >> 8;//high 8 bit to UBRRH
	UBRRL = BAUD_REG_VALUE;		//low 8 bit to UBRRL
	UCSRA &= ~SET_BIT(UDRE);	//clear transmit flag: for interrupt
}


/*
uint8_t uart_rx(void){
	
	while(!(POLL_BIT(UCSRA,RXC)));
	return UDR;
}*/


/*
void uart_tx(uint8_t uart_tx_byte){
	
	while(!(POLL_BIT(UCSRA,UDRE)));
	UDR = uart_tx_byte;
}*/


/*
uint8_t uart_scanf(uint8_t* rx_word)
{
	
	uart_rx_string(rx_word);
	
	if (uart_matter.uart_txc_ready_flag == 1)
	{
		uart_matter.uart_txc_ready_flag = 0;
		return 1;
	}
	else
	{
		return 0;
	}
}*/

void uart_rx_string(uint8_t* uart_rxc_string){
	
	DISABLE_TX_INTERRUPT;
//	_delay_ms(500);
	if (uart_matter.uart_rxc_ready_flag == 1)
	{
 		uart_matter.uart_rxc_ready_flag = 0;
		/*uart_printf("$");
		for (uint8_t i = 0;i<20;i++)
		{
			uart_tx_char(uart_matter.uart_receive_buffer[i]);
		}
		uart_printf("$");*/
		//uart_printf(uart_matter.uart_receive_buffer);
		string_copy(uart_rxc_string,(uint8_t*)uart_matter.uart_receive_buffer);
		clear_uart_buffer((uint8_t*)uart_matter.uart_receive_buffer);
		uart_printf((char*)uart_rxc_string);
		//uart_matter.uart_txc_ready_flag = 1;
	}
}

void string_copy(uint8_t* dest,uint8_t* source)
{
	while(*source != '\0')
	{
		*dest = *source;
		dest++;
		source++;
	}
	*dest = '\0';
	//*(dest + 1) = 0;
}

/*
void link_string(uint8_t* str1, uint8_t* str2)
{
	uint8_t lenght_of_str1 = 0;
	
	while(*str1 != '\0')
	{
		str1++;
		lenght_of_str1++;
	}
	while(*str2 != '\0')
	{
		*(str1 + lenght_of_str1) = *str2;
		str2++;
		lenght_of_str1++;
	}
	*(str1 + lenght_of_str1) = '\0';
}*/


/*
uint8_t string_length(uint8_t* str_len)
{
	uint8_t character_count = 0;
	while(*str_len != '\0')
	{
		character_count += 1;
		str_len += 1;
	}
	return character_count;
}*/

void clear_uart_buffer(uint8_t* buffer_to_clear)
{
	//Hi, I am Bluetooth Device Driver\n
	
	while(/*(*buffer_to_clear != '\n') || (*buffer_to_clear != '\r') ||*/ (*buffer_to_clear != '\0'))
	{
		*(buffer_to_clear++) = 0;
	}
	*buffer_to_clear = 0;
	
	//*(buffer_to_clear + 1) = 0;
}

//uart_matter.uart_char_received_flag = 1;

void uart_tx_char(uint8_t character)
{
	uint8_t byte[2] = {0};
	DISABLE_RX_INTERRUPT;
	byte[0] = character;
	byte[1] = '\0';
	uart_tx_string(byte);
// 	DISABLE_RX_INTERRUPT;
// 	_delay_us(1);
// 	ENABLE_TX_INTERRUPT;
	//clear_uart_buffer((uint8_t*)uart_matter.uart_transmit_buffer);
// 	uart_matter.uart_transmit_buffer[0] = character;
// 	uart_matter.uart_transmit_buffer[1] = '\0';
}

void uart_tx_string(uint8_t* uart_udre_string){
	//uint8_t length = 0;
	//uint8_t tx_string[100] = {0};
	
	//length = string_length(uart_udre_string);
	//string_copy(tx_string, uart_udre_string);
// 	if (uart_matter.uart_txc_buff_clear_flag == 1)
// 	{
// 		uart_matter.uart_txc_buff_clear_flag = 0;
		clear_uart_buffer((uint8_t*)uart_matter.uart_transmit_buffer);
//	}
// 	*(tx_string + length) = '\n';
// 	*(tx_string + length + 1) = '\r';
// 	*(tx_string + length + 2) = '\0';
	
	string_copy((uint8_t*)uart_matter.uart_transmit_buffer,uart_udre_string);
	ENABLE_TX_INTERRUPT;
}

void uart_printf(char* tx_word)
{
	DISABLE_RX_INTERRUPT;
	uart_tx_string((uint8_t*)tx_word);
	_delay_ms(100);
}



void uart_decimal_to_string(uint32_t decimal, uint8_t* value)
{
	uint8_t remainder = 0, i = 0, no_of_zeros = 0;
	uint32_t result = 0, dividend = 0;
	
	dividend = decimal;
	
	
	while((dividend % 10) == 0)
	{
		if (decimal == 0)
		{
			value[0] = 48;
			break;
		}
		dividend /= 10;
		no_of_zeros += 1;
	}
	while(decimal != 0)
	{
		remainder = decimal % 10;
		decimal /= 10;
		result = result * 10 + remainder;
	}
	while(result != 0)
	{
		remainder = result % 10;
		result /= 10;
		value[i++] = remainder + 48;
	}
	for (result = 0;result < no_of_zeros;result++)
	{
		value[i+result] = 48;
	}
	i = 0;
}

void print_decimal(uint32_t integer)
{
	uint8_t value[10] = {0};
	
	uart_decimal_to_string(integer,value);
	uart_printf((char*)value);
}

void bt_cmd_check(uint8_t* command_buffer)
{
	if (command_buffer[0] == '1')
	{
		PORTB = 0xff;
		uart_printf("\nLED ON\n");
	}
	else if(command_buffer[0] == '0')
	{
		PORTB = 0x00;
		uart_printf("\nLED OFF\n");
	}
	clear_uart_buffer(command_buffer);
}

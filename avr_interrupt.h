/*
 * avr_interrupt.h
 *
 * Created: 7/10/2022 7:09:29 AM
 *  Author: shambhu kumar
 */ 


#ifndef AVR_INTERRUPT_H_
#define AVR_INTERRUPT_H_

//#include <avr/interrupt.h>
#include "adc.h"
#include "hcsr05.h"

//set global interrupt flag
#define ENABLE_GLOBAL_INTERRUPT		sei()

ISR(TIMER1_CAPT_vect)
{
	CLEAR_TIMER_COUNTER1;
	icp_register_value = ICR1;
	CAPTURE_ON_FALLING_EDGE;
	input_capture_ready += 1;
	if (input_capture_ready == 1)
	{
		icp_rising_value = icp_register_value;
	}
	if (input_capture_ready >= 2)
	{
		//uart_printf("\ntwo");
		input_capture_ready = 0;
		CAPTURE_ON_RISING_EDGE;
		captured_time_in_us = icp_register_value - icp_rising_value;
	}
// 	if (input_capture_ready == 1)
// 	{
// 		uart_printf("\none");
// 		icp_rising_value = icp_register_value;
// 	}
}

//ADC interrupt when conversion completes
ISR(ADC_vect)
{
	TIFR |= (1<<OCF1B);	//clear compare flag for next conversion to start
	TCNT1 = 0;			//reset counter for next round
	
	//read ADC digital value
	adc_digital_value = ADCW * 4.88;	//in millivolts, step size => 4.88mV
	adc_read_flag = 1;
}

ISR(USART_RXC_vect)
{
	
	temp_data = UDR;
	//uart_matter.uart_rxc_ready_flag = 1;
	
	if (uart_matter.uart_rx_index >= MAX_UART_BUFF_SIZE)
	{
		uart_matter.uart_rx_index = 0;
	}
	uart_matter.uart_receive_buffer[uart_matter.uart_rx_index++] = temp_data;
	if ((uart_matter.uart_receive_buffer[uart_matter.uart_rx_index-1] == '\r') || (uart_matter.uart_receive_buffer[uart_matter.uart_rx_index-1] == '\n'))
	{
		uart_matter.uart_rxc_ready_flag = 1;
		uart_matter.uart_receive_buffer[uart_matter.uart_rx_index - 1] = '\0';
		//uart_matter.uart_receive_buffer[uart_matter.uart_rx_index] = '\0';
		//uart_matter.uart_receive_buffer[uart_matter.uart_rx_index + 1] = '\0';
		uart_matter.uart_rx_index = 0;	
	}
}

ISR(USART_UDRE_vect)
{
	UDR = uart_matter.uart_transmit_buffer[uart_matter.uart_tx_index++];
	if (uart_matter.uart_transmit_buffer[uart_matter.uart_tx_index] == '\0')
	{
		uart_matter.uart_tx_index = 0;
		//uart_matter.uart_txc_buff_clear_flag = 1;
		DISABLE_TX_INTERRUPT;
		ENABLE_RX_INTERRUPT;
	}
}

#endif /* AVR_INTERRUPT_H_ */

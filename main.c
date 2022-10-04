/*
 * driver_code.c
 *
 * Created: 3/10/2022 8:27:23 PM
 * Author : shambhu kumar
 */ 

//#include "adc.h"
#include "avr_interrupt.h"

int main(void)
{
// 	uint8_t bt_rx_buffer[50] = {0};
// 		
// 	IO_REGISTER_MODE(DDRB,OUTPUT);
	IO_REGISTER_BIT_MODE(DDRD,TRIGGER_PIN,OUTPUT);
	IO_REGISTER_BIT_MODE(DDRD,ECHO_PIN,INPUT);
    uart_init();
	//init_timer_icp();
//	adc_init();
	ENABLE_GLOBAL_INTERRUPT;
	TIMER_NORMAL_MODE;
	// 	ENABLE_NOISE_CANCELAR;
	// 	CAPTURE_ON_RISING_EDGE;
	//PRESCALAR_8_FOSC;
	TCCR1B = 0x42;
	ENABLE_EXT_EVENT_CAPTURE_PIN;
	//ENABLE_ICP_INTERRUPT;
	CLEAR_TIMER1_ICP_FLAG;
	CLEAR_TIMER_COUNTER1;
	
    while (1) 
    {
		//calculate_distance_from_icp();
// 		uart_printf("\nicp_rising_value => ");
// 		print_decimal(icp_rising_value);
// 		uart_printf("\nicp_register_value => ");
// 		print_decimal(icp_register_value);
// 		uart_printf("\ncaptured_time_in_us => ");
// 		print_decimal(captured_time_in_us);
		IO_REGISTER_BIT_MODE(PORTD,TRIGGER_PIN,HIGH);
		_delay_us(12);
		IO_REGISTER_BIT_MODE(PORTD,TRIGGER_PIN,LOW);
		
		while(TIFR & (1<<ICF1));
		icp_register_value = ICR1;
		TCCR1B = 0x02;
		CLEAR_TIMER1_ICP_FLAG;
		CLEAR_TIMER_COUNTER1;
		
		while(TIFR & (1<<ICF1));
		captured_time_in_us = ICR1 - icp_register_value;
		TCCR1B = 0x42;
		CLEAR_TIMER1_ICP_FLAG;
		CLEAR_TIMER_COUNTER1;
		distance_in_cm = ((captured_time_in_us * SPEED_OF_SOUND * 0.723) / 200000UL);
		uart_printf("\nDistance => ");
		print_decimal(distance_in_cm);
		uart_printf(" cm");
		//_delay_ms(1000);
// 		uart_rx_string(bt_rx_buffer);
// 		bt_cmd_check(bt_rx_buffer);
// 		if (adc_read())		//set read time in macro "TIME_TO_GET_ADC_VOLT"
// 		{
// 			print_adc();
// 		}
// 		_delay_ms(100);
    }
}
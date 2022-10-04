/*
 * hcsr05.c
 *
 * Created: 07-08-2022 19:08:57
 *  Author: ShambhuKumar
 */ 
#include "hcsr05.h"


void calculate_distance_from_icp(void)
{
	uart_printf("\ninput_capture_ready => ");
	print_decimal(input_capture_ready);
	
	IO_REGISTER_BIT_MODE(PORTD,TRIGGER_PIN,HIGH);
	_delay_us(14);
	IO_REGISTER_BIT_MODE(PORTD,TRIGGER_PIN,LOW);
	uart_printf("\n1icp_rising_value => ");
	print_decimal(icp_rising_value);
	uart_printf("\n1icp_register_value => ");
	print_decimal(icp_register_value);
	uart_printf("\n1captured_time_in_us => ");
	print_decimal(captured_time_in_us);
	distance_in_cm = ((captured_time_in_us * SPEED_OF_SOUND * 0.723) / 200000UL);
}
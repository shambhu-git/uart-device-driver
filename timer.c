/*
 * timer.c
 *
 * Created: 07-08-2022 11:40:12
 *  Author: ShambhuKumar
 */ 
#include "timer.h"

void init_timer_icp(void)
{
	TIMER_NORMAL_MODE;
// 	ENABLE_NOISE_CANCELAR;
// 	CAPTURE_ON_RISING_EDGE;
	//PRESCALAR_8_FOSC;
	TCCR1B = 0x42;
	ENABLE_EXT_EVENT_CAPTURE_PIN;
	ENABLE_ICP_INTERRUPT;
	CLEAR_TIMER1_ICP_FLAG;
	CLEAR_TIMER_COUNTER1;
	uart_printf("\nicp_rising_value => ");
	print_decimal(icp_rising_value);
	uart_printf("\nicp_register_value => ");
	print_decimal(icp_register_value);
	uart_printf("\ncaptured_time_in_us => ");
	print_decimal(captured_time_in_us);
}
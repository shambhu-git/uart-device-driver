/*
 * adc.c
 *
 * Created: 3/10/2022 8:28:27 PM
 *  Author: shambhu kukmar
 */ 

#include "adc.h"

void adc_init(void)
{
	ADMUX = ADC_CHANNEL;		// ADC channel 0 
	ADCSRA = 0x80;				// enable ADC
	ADCSRA |= 0x07;				// prescalar (Fosc / 128)
	ADMUX |= (1<<REFS0);		//AVCC as reference voltage
	ADCSRA |= 0x08;				//ADC interrupt enable
	ADCSRA |= 0x20;				//auto trigger enable
	SFIOR = 0xA0;				//OCR1B as source of auto trigger
	OCR1B = ADC_READ_PERIOD;	// exactly 10.8 => for 1 ms,
	TCNT1 = 0;					//initial counter value 0
	TCCR1A = 0;
	TCCR1B = 0x0D;				//compare match mode with prescalar (Fosc / 1024)
}

uint8_t adc_read(void)
{
	//print_decimal(ADCW);
	if (adc_read_flag == 1)
	{
		adc_read_flag = 0;
		total_milli_volt += adc_digital_value;
		time_in_second += 1;
		if (time_in_second >= TIME_TO_GET_ADC_VOLT)
		{
			total_milli_volt /= time_in_second;
			millivolt_value = total_milli_volt;	//get average of value by time_in_second
			total_milli_volt = 0;
			time_in_second = 0;
			//adc_ready_flag = 1;	//set to let user use the value
			return 1;
		}
	}
	return 0;
}

void print_adc(void)
{
	volatile uint8_t bat_percent = 0;
	
	uart_printf("\nVoltage => ");
	print_decimal(millivolt_value);
	uart_printf(" mV");
	
	bat_percent = adc_battery_percent();
	if (bat_percent == OVER_CHARGE)
	{
		uart_printf("\nOver charging\n");
	}
	else if (bat_percent == DEEP_DISCHARGE)
	{
		uart_printf("\nDeep discharge\n");
	}
	else
	{
		uart_printf("\nBattery => ");
		print_decimal(bat_percent);
		uart_printf(" %");
	}
}

uint8_t adc_battery_percent(void)
{
	if (millivolt_value < MIN_VOLT_LIMIT)
	{
		return DEEP_DISCHARGE;	
	}
	else if(millivolt_value > MAX_VOLT_LIMIT)
	{
		return OVER_CHARGE;	
	}
	else
	{
		return (((millivolt_value - MIN_VREF) * 100UL) / MAX_MIN_VREF_DIFF);
	}
}

/*
void print_volt(volatile uint16_t volt)
{
	uint8_t voltage[6] = {0};
	static uint8_t avg_count = 0;
	static uint16_t total_volt = 0;
	
	total_volt += volt;
	if (avg_count++ >= 30)
	{
		total_volt /= avg_count;
		adc_decimal_to_float(volt,voltage);
		uart_printf("Voltage: ");
		uart_printf((char*)voltage);
		uart_printf(" V\n");
		total_volt = 0;
		avg_count = 0;
	}
}*/

/*
uint16_t adc_decimal_to_float(volatile uint16_t volt_decimal, uint8_t* volt_string)
{
	uint8_t temp_volt_string[6] = {0};
		
	volt_decimal = (volt_decimal * 2.56 * 4.6875 * 100) / 1024;
	uart_decimal_to_string(volt_decimal,volt_string);

	if (volt_decimal <= 99)
	{
		temp_volt_string[0] = '0';
		temp_volt_string[1] = '.';
		temp_volt_string[2] = volt_string[0];
		temp_volt_string[3] = volt_string[1];
	}
	else if (volt_decimal <= 999)
	{
		temp_volt_string[0] = volt_string[0];
		temp_volt_string[1] = '.';
		temp_volt_string[2] = volt_string[1];
		temp_volt_string[3] = volt_string[2];
	} 
	else
	{
		temp_volt_string[0] = volt_string[0];
		temp_volt_string[1] = volt_string[1];
		temp_volt_string[2] = '.';
		temp_volt_string[3] = volt_string[2];
		temp_volt_string[4] = volt_string[3];
	}
	string_copy(volt_string,temp_volt_string);
	
	return (volt_decimal * 10);
}*/
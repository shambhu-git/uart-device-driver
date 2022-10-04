/*
 * adc.h
 *
 * Created: 3/10/2022 8:28:46 PM
 *  Author: shambhu kumar
 */ 


#ifndef ADC_H_
#define ADC_H_

#include "uart.h"

#define ENABLE_ADC			adc_init()
#define DISABLE_ADC			(ADCSRA &= ~(1<<ADEN))
// step size => Vref / 2^(adc bit size)

#define ADC_CHANNEL			0x00

//in milli volts
#define MAX_VREF			5000U
#define MIN_VREF			1000U
#define MAX_MIN_VREF_DIFF	(MAX_VREF - MIN_VREF)
#define MIN_VOLT_LIMIT		((MAX_MIN_VREF_DIFF / 20) + MIN_VREF)
#define MAX_VOLT_LIMIT		((MAX_MIN_VREF_DIFF / 5) + MAX_MIN_VREF_DIFF)

//10.81 => for 1ms, 10810 => 1s
#define ADC_READ_PERIOD			10810U

//give ADC voltage every 10s, maximum 255 seconds allowed
#define TIME_TO_GET_ADC_VOLT	10

#define DEEP_DISCHARGE	200	//error code for deep discharge
#define OVER_CHARGE		250	//error code for over charge

volatile uint16_t adc_digital_value, millivolt_value,total_milli_volt;
volatile uint8_t time_in_second,adc_read_flag;

void adc_init(void);

uint8_t adc_read(void);

void print_adc(void);

uint8_t adc_battery_percent(void);

//void print_volt(volatile uint16_t);

//uint16_t adc_decimal_to_float(volatile uint16_t, uint8_t*);

#endif /* ADC_H_ */
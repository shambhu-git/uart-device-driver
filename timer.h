/*
 * timer.h
 *
 * Created: 07-08-2022 11:40:31
 *  Author: ShambhuKumar
 */ 


#ifndef TIMER_H_
#define TIMER_H_

#include "uart.h"


// icp - input capture
#define ENABLE_ICP_INTERRUPT			(TIMSK |= (1<<TICIE1))
#define ENABLE_EXT_EVENT_CAPTURE_PIN	(ACSR |= 0x80)
#define ENABLE_NOISE_CANCELAR			(TCCR1B |= 0x80)
#define CAPTURE_ON_RISING_EDGE			(TCCR1B |= 0x40)
#define CAPTURE_ON_FALLING_EDGE			(TCCR1B &= ~(0x40))
#define TIMER_NORMAL_MODE				(TCCR1A = 0)
#define PRESCALAR_64_FOSC				(TCCR1B = (TCCR1B | 0x03) & (~(1<<2)))
#define PRESCALAR_8_FOSC				(TCCR1B = (TCCR1B | 0x02) & (~(0x05)))
#define CLEAR_TIMER_COUNTER1			(TCNT1 = 0)
#define CLEAR_TIMER_COUNTER0			(TCNT0 = 0)
#define CLEAR_TIMER_COUNTER2			(TCNT2 = 0)
#define CLEAR_TIMER1_OVERFLOW_FLAG		(TIFR |= (1<<TOV1))
#define CLEAR_TIMER1_ICP_FLAG			(TIFR |= (1<<ICF1))

#define SPEED_OF_SOUND					34500U

volatile uint8_t input_capture_ready;
volatile uint16_t icp_register_value,icp_rising_value,captured_time_in_us;

void init_timer_icp(void);

#endif /* TIMER_H_ */
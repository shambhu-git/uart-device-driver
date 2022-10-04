/*
 * hcsr05.h
 *
 * Created: 07-08-2022 19:02:40
 *  Author: ShambhuKumar
 */ 


#ifndef HCSR05_H_
#define HCSR05_H_

#include "uart.h"
#include "timer.h"

#define TRIGGER_PIN		PD5
#define ECHO_PIN		PD6

uint16_t distance_in_cm,temp;

void calculate_distance_from_icp(void);


#endif /* HCSR05_H_ */
/*
 * knobs.h
 *
 * Created: 09/07/2021 14:50:09
 *  Author: william
 */ 


#ifndef KNOB_H_
#define KNOB_H_
#include <stdint.h>

#define KNOB0_SHIFT PINC3
#define KNOB0_MASK (1<<KNOB0_SHIFT)
#define KNOB0_PORT PORTC
#define KNOB0_DDR DDRC
#define KNOB0_PIN PINC

#define KNOB1_SHIFT PINC4
#define KNOB1_MASK (1<<KNOB1_SHIFT)
#define KNOB1_PORT PORTC
#define KNOB1_DDR DDRC
#define KNOB1_PIN PINC


//initialize the knobs
void knob_init();


/*! @brief polling to get adc value of the knobs.
	
	@in knob shift

	if the funtion gets called, it return the value of the asked for 
	
	@return a value between 0 and 1024
*/
uint16_t knob_getPos(uint8_t knob_shift);


#endif /* KNOBS_H_ */
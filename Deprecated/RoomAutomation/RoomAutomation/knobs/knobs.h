/*
 * knobs.h
 *
 * Created: 09/07/2021 14:50:09
 *  Author: william
 */ 


#ifndef KNOBS_H_
#define KNOBS_H_
#include <stdint.h>

//initialize the knobs
void knobs_init();

uint16_t knobs_getPos1(void);
uint16_t knobs_getPos2(void);

#endif /* KNOBS_H_ */
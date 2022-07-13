/*
 * math_map.c
 *
 * Created: 10/07/2021 17:21:24
 *  Author: william
 */ 
#include "math_map.h"
#include <stdint.h>

int mapi(int value, int fromLow, int fromHigh, int toLow, int toHigh){
	//this function maps a value with a certain range to another range perspectively
	float result;
	if (value > fromHigh){
		value = fromHigh;
	}
	if (value < fromLow){
		value = fromLow;
	}
	
	result = (float)(toHigh-toLow);
	result = result *  (((float)value-(float)fromLow) / ((float)fromHigh-(float)fromLow));
	result += (float)toLow;
	
	return (int)result;
}


uint16_t mapui(uint16_t value, uint16_t fromLow, uint16_t fromHigh, uint16_t toLow, uint16_t toHigh){
	//this function maps a value with a certain range to another range perspectively
	uint32_t result;
	if (value > fromHigh){
		value = fromHigh;
	}
	if (value < fromLow){
		value = fromLow;
	}
	
	result = ((value - fromLow) * (toHigh - toLow)) / (fromHigh-fromLow);
	
	return (uint16_t)result;
}
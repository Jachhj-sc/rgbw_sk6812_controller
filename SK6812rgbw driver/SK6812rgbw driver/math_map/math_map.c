/*
 * math_map.c
 *
 * Created: 10/07/2021 17:21:24
 *  Author: william
 */ 
#include "math_map.h"

int mapi(int value, int fromLow, int fromHigh, int toLow, int toHigh){
	//this function maps a value with a certain range to another range perspectively
	int32_t result;
	if (value > fromHigh){
		value = fromHigh;
	}
	if (value < fromLow){
		value = fromLow;
	}
	
	result = ((value - fromLow) * (toHigh - toLow)) / (fromHigh-fromLow);
	
	return (int)result;
}


uint16_t mapui(uint16_t value, uint16_t fromLow, uint16_t fromHigh, uint16_t toLow, uint16_t toHigh){
	//this function maps a value with a certain range to another range perspectively
	volatile uint32_t result = 0;
	volatile float ratio; //
	
	//make sure the boundaries are not crossed.
	if (value > fromHigh){
		value = fromHigh;
	}
	if (value < fromLow){
		value = fromLow;
	}
	
	//zero values
	value = value - fromLow;
	fromHigh = fromHigh - fromLow;
	
	toHigh = toHigh - fromLow;
	
	//calculate ratio
	ratio = (float)((float)value / (float)fromHigh);
	
	result = (uint16_t)(ratio * toHigh);
	result = result + toLow;
	
	
	return (uint16_t)result;
} 
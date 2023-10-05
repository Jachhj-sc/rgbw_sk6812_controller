/*
 * math_map.c
 *
 * Created: 10/07/2021 17:21:24
 *  Author: william
 */ 
#include "math_map.h"

// int mapi(int value, int fromLow, int fromHigh, int toLow, int toHigh){
// 	//this function maps a value with a certain range to another range perspectively
// 	int32_t result = 0;
// 	int32_t fromVal = 0;
// 	
// 	if (value > fromHigh){
// 		value = fromHigh;
// 	}
// 	if (value < fromLow){
// 		value = fromLow;
// 	}
// 	
// 	fromVal = fromHigh-fromLow;
// 	if(!fromVal){
// 		fromVal = 1;
// 	}
// 	
// 	result = ((value - fromLow) * (toHigh - toLow)) / fromVal;
// 	
// 	return (int)result;
// }

int32_t mapi(int32_t value, int32_t fromLow, int32_t fromHigh, int32_t toLow, int32_t toHigh) {
	// Clamp value to [fromLow, fromHigh]
	value = (value < fromLow) ? fromLow : (value > fromHigh) ? fromHigh : value;

	// Calculate denominator, set to 1 if zero to prevent division by zero
	int32_t fromRange = fromHigh - fromLow;
	if (fromRange == 0) {
		fromRange = 1;
	}

	// Use int64_t to avoid overflow during multiplication
	int64_t scaled_diff = (int64_t)(value - fromLow) * (int64_t)(toHigh - toLow);

	// Map and scale the value, then add toLow for correct offset
	int32_t result = (int32_t)(scaled_diff / fromRange) + toLow;
	
	return result;
}

uint16_t mapui(uint16_t value, uint16_t fromLow, uint16_t fromHigh, uint16_t toLow, uint16_t toHigh){
	//this function maps a value with a certain range to another range perspectively
	volatile uint32_t result = 0;
	volatile double ratio;
	
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
	
	//safeguard for division by 0 error
	if(fromHigh == 0){
		fromHigh = 1;
	}
	
	//calculate ratio
	ratio = (double)((double)value / (double)fromHigh);
	
	result = (uint16_t)(ratio * toHigh);
	result = result + toLow;
	
	
	return (uint16_t)result;
} 
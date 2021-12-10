/*
 * math_map.c
 *
 * Created: 10/07/2021 17:21:24
 *  Author: william
 */ 
#include "math_map.h"

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



unsigned int mapui(unsigned int value, unsigned int fromLow, unsigned int fromHigh, unsigned int toLow, unsigned int toHigh){
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
	
	return (unsigned int)result;
}
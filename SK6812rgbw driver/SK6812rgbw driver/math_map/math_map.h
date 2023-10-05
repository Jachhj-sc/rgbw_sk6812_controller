/*
 * math_map.h
 *
 * Created: 10/07/2021 17:21:35
 *  Author: william
 */ 


#ifndef MATH_MAP_H_
#define MATH_MAP_H_
#include <stdint.h>

int32_t mapi(int32_t value, int32_t fromLow, int32_t fromHigh, int32_t toLow, int32_t toHigh);

uint16_t mapui(uint16_t value, uint16_t fromLow, uint16_t fromHigh, uint16_t toLow, uint16_t toHigh);

#endif /* MATH_MAP_H_ */
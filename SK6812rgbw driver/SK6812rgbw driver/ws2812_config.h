/*
 *	WS2812_CONFIG.h
 *
 * Created: 13/07/2021 16:20:40
 *  Author: william
 */ 


#ifndef WS2812_CONFIG_H
#define WS2812_CONFIG_H

#define ws2812_resettime    80

///////////////////////////////////////////////////////////////////////
// Define I/O pin
///////////////////////////////////////////////////////////////////////

#define ws2812_port C   // Data port
#define ws2812_pin  5   // Data out pin

#define LEDPIXELCOUNT (180)/*46*/

#define POT_DEADZONE (50) //10 max 1024
#define HUEKNOB_UPDATE_DURATION (1000)//ms

#endif /* WS2812_CONFIG_H_ */
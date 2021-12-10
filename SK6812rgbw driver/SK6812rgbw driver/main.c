/*
 * Light_WS2812 library example - RGBW_blinky
 *
 * cycles one LED through red, green, blue, white
 *
 * This example does only work with the SK6812RGBW LEDs
 *
 * Please make sure to set your configuration in "WS2812_config.h" first
 * 
 * EXTRA NOTE: functions are standalone, you don't need to send to strip, this will be handled by the theme functions
 */

/* CONNECTION PIN-OUT
 * - see: ws2812_config.h for the data pin
 * - the power pins are logical
 * - the knobs are not connected yet
 *
 *
 */

/*

TODO: implement delay with the build timer in timer.h in the function "effect_pulse_nb" in "ledcontrol.h"


*/
#define F_CPU 16000000UL
#include <util/delay.h>
#include <avr/io.h>
#include <stdlib.h>
#include <avr/interrupt.h>

#include "ledcontrol/ledcontrol.h"
#include "ws2812_config.h" // config data for the led strip
#include "ledcontrol/colors.h"
#include "timer.h"

int randomrange(int lower, int upper);
void recursiveFlowHue(int colorLength, int hueSpeedPMS);

uint32_t colors[20] = {
	COLOR_BLACK,
	COLOR_RED,
	COLOR_GREEN,
	COLOR_BLUE,
	COLOR_WHITE,     
	COLOR_CYAN,       
	COLOR_MAGENTA,    
	COLOR_YELLOW,     
	COLOR_CHARTREUSE, 
	COLOR_ORANGE,     
	COLOR_AQUAMARINE, 
	COLOR_PINK,       
	COLOR_TURQUOISE,  
	COLOR_REALWHITE,  
	COLOR_INDIGO,     
	COLOR_VIOLET,     
	COLOR_MAROON,     
	COLOR_BROWN,     
	COLOR_CRIMSON,    
	COLOR_PURPLE,     
};

int main(void)
{
	init_timer0();
	
	//setRGBW_ExBounds(12,30);
	setRGBW_Brightness(255);
	setRGBW_clear();
	RGBW_send();

	//setRGBW_all(color32(255,255,0,0));
	//RGBW_send();
	uint16_t hue = 0;
	static	uint8_t	 i	 = 0;
	static  uint8_t  f   = 0;

	sei();//enable interrupts

	while(1)
	{

// 		RGBW_send();
		
// 		effect_snake_nb(5, color32(2,2,2,2));
// 		effect_snakeGrowHue_nb(10, 300);
// 		effect_snake_nb(pixelcount-5, gamma32(ColorHSV(hue+=550 , 255, 255, 155)));
// 		effect_snakeBounce_nb(10, color32(50,10,10,10));



		
		setRGBW_all(color32(50,50,50,255));
		RGBW_send();
				
//		recursiveFlowHue(10, 51);
		//effect_pulse(0, 255, color32(0, 255, 255, 50))
//		effect_pulse_nb(0, 255, color32(255, 255, 255, 255));
	}	
}

void effect_scrollingHue(){
	
	
}

int randomrange(int lower, int upper){
// Generates and prints 'count' random
// numbers in range [lower, upper].
	static unsigned int seed = 0;
	int num = (rand() % (upper - lower + 1)) + lower;
	srand(seed+=3);
	return num;
}

#define DELAY 20

void recursiveFlowHue(int colorLength, int hueSpeedPMS) {
	static uint16_t hue = 0;
		
	for (int i = 0; i < LEDpixelcount + colorLength; i++) {
		if (i <= LEDpixelcount)
		//doe huespeed * delayy zodat het hue speed getal per milliseconden is en niet
		//afhankelijk is van de snelheid van de strip dus als je strip sneller gaat
		//gaat de kleurverandering niet sneller.
		
		setRGBW_pixel(i, gamma32(ColorHSV(hue += hueSpeedPMS * (DELAY+14), 255,255,0)));
		if (i - colorLength >= 0)
		setRGBW_pixel(i - colorLength, color32(0, 0, 0, 0));

		RGBW_send();
		_delay_ms(DELAY);
	}

	for (int i = LEDpixelcount; i > 0 - colorLength;i--) {


		if (i >= 0)
		setRGBW_pixel(i, gamma32(ColorHSV(hue += hueSpeedPMS * (DELAY+14),255,255,0)));

		if (i + colorLength <= LEDpixelcount)
		setRGBW_pixel(i + colorLength, color32(0, 0, 0, 0));

		RGBW_send();
		_delay_ms(DELAY);
	}
}
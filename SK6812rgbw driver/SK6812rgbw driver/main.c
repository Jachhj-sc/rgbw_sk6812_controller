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
#include "buttons/buttons.h"

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



/************************************************************************/
/* Control part setup													*/
/************************************************************************/

typedef enum
{
	S_INIT = 0,
	S_ledOFF,
	S_EQ_ON,
	S_ALL_ON,
	S_EFFECT_ON,
	S_ledERR
} state_e;

typedef enum
{
	E_NO = 0,
	E_BUTTONPRESSED,
	E_ADCchange
	
} event_e;

typedef enum
{
	EF_NO = 0			,
	EF_snake_nb			,
	EF_snakeBounce_nb   ,
	EF_snakeGrowHue_nb  ,
	EF_snakeGrow_nb     ,
	EF_amountn,
	
	EF_pulse_b			,
	EF_snakeBounce_b    ,
	EF_chase_b		    ,
	EF_snakeGrowHue_b   ,
	EF_snakeGrow_b	    ,
	
	
} effect_e;

//flags and state variables
typedef struct
{
	uint8_t strip_on;
	effect_e current_ef;
	uint32_t current_color32;
	state_e currentstate;
	state_e nextstate;
	event_e currentevent;
} sys_statusflags_t;

sys_statusflags_t systemstate_f = {0};


event_e update();
state_e state_act(state_e state, event_e eventn);

int main(void)
{	
	systemstate_f.currentstate = S_INIT;
	systemstate_f.nextstate = S_ledOFF;
	
	init_timer0();
	setRGBW_ExBounds(0, 36);
	//setRGBW_ExBounds(12,30);
	setRGBW_Brightness(255);
	setRGBW_clear();
	RGBW_send();
	buttons_init();

	//setRGBW_all(color32(255,255,0,0));
	//RGBW_send();
	uint16_t hue = 0;
	static	uint8_t	 i = 0;
	static  uint8_t  f = 0;

	sei();//enable interrupts
	
	systemstate_f.current_color32 = color32(255, 255, 230, 100);
	
	while(1)
	{
/************************************************************************/
/* control part that needs to be integrated in real system later		*/
/************************************************************************/
				
		//state
		systemstate_f.currentstate = systemstate_f.nextstate; //update currrentstate 
		update();
		systemstate_f.nextstate = state_act(systemstate_f.currentstate, systemstate_f.currentevent);//do actions
		
/************************************************************************/
/* end of control														*/
/************************************************************************/
		
	//debug purposes
// 		RGBW_send();
		
// 		effect_snake_nb(5, color32(2,2,2,2));
// 		effect_snakeGrowHue_nb(10, 300);
// 		effect_snake_nb(pixelcount-5, gamma32(ColorHSV(hue+=550 , 255, 255, 155)));
// 		effect_snakeBounce_nb(10, color32(50,10,10,10));

// 		for(int i = 0; i < LEDpixelcount; i++){
// 			if(i % 2 == 0){//if perfectly devisible by 2
// 				setRGBW_pixel(i, color32(0,0,255,0));	
// 				RGBW_send();
// 			}		
// 		}
		
//		recursiveFlowHue(10, 51);
		//effect_pulse(0, 255, color32(0, 255, 255, 50))
//		effect_pulse_nb(0, 255, color32(255, 255, 255, 255));
	}	
}




/************************************************************************/
/* control part that needs to be integrated in real system later		*/
/************************************************************************/
event_e update(){
	if(buttonflag.button0){
		systemstate_f.strip_on ^= 1;		
		systemstate_f.currentstate = S_EFFECT_ON;
		systemstate_f.current_ef = EF_NO;
		buttonflag.button0 = 0;
	}
	if(buttonflag.button1){
		systemstate_f.strip_on = 1;
		systemstate_f.currentstate = S_EFFECT_ON;
		
		if(systemstate_f.current_ef < EF_amountn) systemstate_f.current_ef += 1;//go through the list of effects
		else systemstate_f.current_ef = 0;
		
		buttonflag.button1 = 0;
	}
	if(buttonflag.button2){

		buttonflag.button2 = 0;
	}
}

state_e state_act(state_e state, event_e eventn){
	state_e nxtstate = 0;
	
	if (!systemstate_f.strip_on) state = nxtstate = S_ledOFF;
	
	switch(state){
	case S_ledOFF:
		setRGBW_clear();
		RGBW_send();
		if (systemstate_f.strip_on) nxtstate = S_EFFECT_ON;
		else nxtstate = S_ledOFF;
		break;
		
	case S_EQ_ON:
	//eq code
		nxtstate = S_EQ_ON;
		break;
		
	case S_EFFECT_ON:	//effect types
		switch (systemstate_f.current_ef){
/************************************************************************/
/* add test code										                */
/************************************************************************/		
			case EF_NO:
				setRGBW_all(systemstate_f.current_color32);
				RGBW_send();
				break;
/************************************************************************/
/* end test code										                */
/************************************************************************/
			case EF_snake_nb:
				effect_snake_nb(10, systemstate_f.current_color32);
				break;

			case EF_snakeBounce_b:
				effect_snakeBounce_b(10, systemstate_f.current_color32);
				break;
			
			case EF_snakeBounce_nb:
				effect_snakeBounce_nb(10, systemstate_f.current_color32);
				break;
			
			case EF_chase_b:
				effect_chase_b(systemstate_f.current_color32);
				break;
			
			case EF_snakeGrowHue_b:
				effect_snakeGrowHue_b(5,5);
				break;
			
			case EF_snakeGrowHue_nb:
				effect_snakeGrowHue_nb(5,5);
				break;
			
			case EF_snakeGrow_b:
				effect_snakeGrow_b(10, systemstate_f.current_color32);
				break;
			
			case EF_snakeGrow_nb:
				effect_snakeGrow_nb(10, systemstate_f.current_color32);
				break;
			
			case EF_pulse_b:
				effect_pulse_b(10, 255, systemstate_f.current_color32);
				break;
		}
		nxtstate = S_EFFECT_ON;
		break;
	
	case S_ledERR:
	//effect code
		setRGBW_all(color32(10,0,0,0));
		RGBW_send();
		nxtstate = S_ledERR;
		break;
	
	default:
	//error
		nxtstate = S_ledERR;
		break;
	}
	


	return nxtstate;
}

/************************************************************************/
/* end of control														*/
/************************************************************************/



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
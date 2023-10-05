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


/*use this define in project setup to determine for what board to compile for*/
#undef Nastuus
#define HOME

#define F_CPU 16000000UL

#include <util/delay.h>
#include <avr/io.h>
#include <stdlib.h>
#include <avr/interrupt.h>

#include "ledcontrol/ledcontrol.h"
#include "ws2812_config.h" // config data for the led strip
#include "timer.h"
#include "buttons/buttons.h"
#include "knob/knob.h"
#include "math_map/math_map.h"


#define default_COLOR color32(255, 255, 230, 100)


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
	S_ledERR,
	S_HALT
} state_e;

//not used
typedef enum
{
	E_NO = 0,
	E_BUTTONPRESSED,
	E_ADCchange
	
} event_e;

typedef enum
{
	EF_NO = 0			,
	EF_HUEKNOB			,
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
	effect_e currentEffect;
	uint32_t current_color32;
	state_e currentState;
	state_e nextState;
	event_e currentEvent;
	uint8_t updateStrip;
	uint16_t prevStateAndPrevEffect;
} sys_status_t;

sys_status_t systemStatusHandler = {0};

void update();
state_e state_act(state_e state, event_e eventn);

int main(void)
{	
	systemStatusHandler.currentState = S_INIT;
	systemStatusHandler.nextState = S_EFFECT_ON;
	systemStatusHandler.currentEffect = EF_NO;
	
	buttonFlag.button0 = 0;
	buttonFlag.button1 = 0;
	buttonFlag.button2 = 0;
	
	init_timer0();
	

	setRGBW_clear();
	RGBW_send();	
	setRGBW_ExBounds(0, 36);
	
	buttons_init();
	knob_init();


	sei();//enable interrupts
	
	DDRB |= (1<<PINB5);
	PORTB &= ~(1<<PINB5);
		
	uint16_t knob1_pos;
	knob1_pos = knob_getPos(KNOB1_SHIFT);
	knob1_pos = (uint16_t)mapi(knob1_pos, 0, 1024, 255, 0);
	setRGBW_Brightness(knob1_pos);
	
	while(1)
	{
/************************************************************************/
/* control part that needs to be integrated in real system later		*/
/************************************************************************/

		systemStatusHandler.currentState = systemStatusHandler.nextState; //update currrentstate 
		update();
		systemStatusHandler.nextState = state_act(systemStatusHandler.currentState, systemStatusHandler.currentEvent);//do actions
		
/************************************************************************/
/* end of control														*/
/************************************************************************/
		
	//debug purposes
	
////# DEBUG
// 		//state
// 		if(systemstate_f.strip_on == 1){
// 			PORTB |= (1<<PINB5);
// 		}else{
// 			PORTB &= ~(1<<PINB5);
// 		}
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
void update(){
	if(buttonFlag.button0){
		systemStatusHandler.strip_on ^= 1;		
		systemStatusHandler.currentState = S_EFFECT_ON;
		systemStatusHandler.currentEffect = EF_NO;
		systemStatusHandler.updateStrip = 1;
		buttonFlag.button0 = 0;
	}
	if(buttonFlag.button1){
		systemStatusHandler.strip_on = 1;
		systemStatusHandler.currentState = S_EFFECT_ON;

		if(systemStatusHandler.currentEffect < EF_amountn) systemStatusHandler.currentEffect += 1;//go through the list of effects
		else systemStatusHandler.currentEffect = 0;
		
		systemStatusHandler.updateStrip = 1;
		buttonFlag.button1 = 0;
	}
	if(buttonFlag.button2){
		uint16_t knob1_pos;
		knob1_pos = knob_getPos(KNOB1_SHIFT);
		knob1_pos = (uint16_t)mapi(knob1_pos, 0, 1024, 255, 0);
		setRGBW_Brightness(knob1_pos);
		
		systemStatusHandler.updateStrip = 1;
		buttonFlag.button2 = 0;
	}

}



state_e state_act(state_e state, event_e eventn){
	state_e _nextState = 0;
	uint16_t knob_pos;
	
	if (!systemStatusHandler.strip_on) state = _nextState = S_ledOFF;
	
	switch(state){
		case S_ledOFF:
			if (systemStatusHandler.updateStrip){
				systemStatusHandler.updateStrip = 0;
				setRGBW_clear();
				RGBW_send();
			}

			if (systemStatusHandler.strip_on) _nextState = S_EFFECT_ON;
			else _nextState = S_ledOFF;
			break;
		
		case S_EQ_ON:
		//eq code
			_nextState = S_EQ_ON;
			break;
		
		case S_EFFECT_ON:	//effect types
			switch (systemStatusHandler.currentEffect){
	/************************************************************************/
	/* add test code										                */
	/************************************************************************/		
				case EF_NO:
					if (systemStatusHandler.updateStrip){
						systemStatusHandler.updateStrip = 0;
						setRGBW_all(default_COLOR);
						RGBW_send();
					}
					break;
			
				case EF_HUEKNOB:
					knob_pos = knob_getPos(KNOB0_SHIFT);
					knob_pos = (uint16_t)mapi(knob_pos, 0, 1024, 0, 65534);

					systemStatusHandler.current_color32 = ColorHSV((uint16_t)knob_pos, 255, 255, 0);
					
					setRGBW_all(systemStatusHandler.current_color32);
					RGBW_send();
					break;
	/************************************************************************/
	/* end test code										                */
	/************************************************************************/
				case EF_snake_nb:
					effect_snake_nb(10, systemStatusHandler.current_color32);
					break;

				case EF_snakeBounce_b:
					effect_snakeBounce_b(10, systemStatusHandler.current_color32);
					break;
			
				case EF_snakeBounce_nb:
					effect_snakeBounce_nb(70, systemStatusHandler.current_color32);
					break;
			
				case EF_chase_b:
					effect_chase_b(systemStatusHandler.current_color32);
					break;
			
				case EF_snakeGrowHue_b:
					effect_snakeGrowHue_b(5,5);
					break;
			
				case EF_snakeGrowHue_nb:
					effect_snakeGrowHue_nb(5,50);
					break;
			
				case EF_snakeGrow_b:
					effect_snakeGrow_b(10, systemStatusHandler.current_color32);
					break;
			
				case EF_snakeGrow_nb:
					effect_snakeGrow_nb(10, systemStatusHandler.current_color32);
					break;
			
				case EF_pulse_b:
					effect_pulse_b(10, 255, systemStatusHandler.current_color32);
					break;
				
				case EF_amountn:
				default:
					_nextState = S_ledERR;
					break;
			}
			_nextState = S_EFFECT_ON;
			break;
	
		case S_ledERR:
		//effect code
			setRGBW_all(0);
			RGBW_send();
		
			_nextState = S_HALT;
			break;
	
		case S_HALT:
			while(1);
			_nextState = S_HALT;
		break;
	
		default:
		//error
			_nextState = S_ledERR;
			break;
	}
	
	return _nextState;
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
		
	for (int i = 0; i < LEDPIXELCOUNT + colorLength; i++) {
		if (i <= LEDPIXELCOUNT)
			setRGBW_pixel(i, gamma32(ColorHSV(hue += hueSpeedPMS * (DELAY+14), 255,255,0)));
		//doe huespeed * delayy zodat het hue speed getal per milliseconden is en niet
		//afhankelijk is van de snelheid van de strip dus als je strip sneller gaat
		//gaat de kleurverandering niet sneller.
		
		if (i - colorLength >= 0)
			setRGBW_pixel(i - colorLength, color32(0, 0, 0, 0));

		RGBW_send();
		_delay_ms(DELAY);
	}

	for (int i = LEDPIXELCOUNT; i > 0 - colorLength;i--) {


		if (i >= 0)
		setRGBW_pixel(i, gamma32(ColorHSV(hue += hueSpeedPMS * (DELAY+14),255,255,0)));

		if (i + colorLength <= LEDPIXELCOUNT)
		setRGBW_pixel(i + colorLength, color32(0, 0, 0, 0));

		RGBW_send();
		_delay_ms(DELAY);
	}
}
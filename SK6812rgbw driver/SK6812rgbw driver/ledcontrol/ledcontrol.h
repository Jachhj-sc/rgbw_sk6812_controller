/*
 * ledcontrol.h
 *
 * Created: 13/07/2021 17:12:57
 *  Author: william
 */ 


#ifndef LEDCONTROL_H_
#define LEDCONTROL_H_

void setRGBW_ExBounds(uint16_t low, uint16_t high);
void setRGBW_Brightness(uint8_t bright);

void setRGBW_all(uint32_t color);
void setRGBW_pixel(uint16_t pixel, uint32_t color);
void setRGBW_clear();

void calcBrightness(uint32_t *color, uint8_t _brightness);

void RGBW_send();

uint32_t ColorHSV(uint16_t hue, uint8_t sat, uint8_t val, uint8_t whiteness);
uint32_t color32(uint8_t r, uint8_t g, uint8_t b, uint8_t w);
uint8_t	 gamma8(uint8_t x);
uint32_t gamma32(uint32_t x);
uint8_t	 sine8(uint8_t x);


void effect_snake_nb(int length, uint32_t color);

void effect_snakeBounce_b(int length, uint32_t color);
void effect_snakeBounce_nb(int length, uint32_t color);

void effect_chase_b(uint32_t color);

void effect_snakeGrowHue_b(int growSpd, int hueSpd);
void effect_snakeGrowHue_nb(int growSpd, int hueSpd);

void effect_snakeGrow_b(int growSpd, uint32_t color);
void effect_snakeGrow_nb(int growSpd, uint32_t color);

void effect_pulse(int delay, int maxBrightness, uint32_t color);

 
 
  
#endif /* LEDCONTROL_H_ */
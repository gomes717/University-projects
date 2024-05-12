#ifndef __GPIO__
#define __GPIO__

#include <stdint.h>

void GPIO_Init(void);
void BtnInterrupt_Init(void);
void YellowON(uint8_t pos);
void RedON(uint8_t pos);
void GreenON(uint8_t pos);
void LED_OFF(void);
uint8_t getButton1(void);
uint8_t getButton2(void);
void binToLED(uint8_t binary);
void toggleLED(void);

#endif
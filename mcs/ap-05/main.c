// main.c
// Desenvolvido para a placa EK-TM4C1294XL


#include <stdint.h>
#include "tm4c1294ncpdt.h"

void PLL_Init(void);
void SysTick_Init(void);
void SysTick_Wait1ms(uint32_t delay);
void GPIO_Init(void);
void BtnInterrupt_Init(void);
void YellowON(uint8_t pos);
void RedON(uint8_t pos);
void GreenON(uint8_t pos);
void LED_OFF(void);
uint8_t getButton1(void);
uint8_t getButton2(void);
void binToLED(uint8_t binary);
void TIMER_Init(void);
void toggleLED(void);


int main(void)
{
	PLL_Init();
	SysTick_Init();
	GPIO_Init();
	BtnInterrupt_Init();
	TIMER_Init();
	while (1)
	{
	}
}

void GPIOPortJ_Handler()
{
	TIMER2_CTL_R ^= (uint8_t)((1&GPIO_PORTJ_AHB_RIS_R));
	GPIO_PORTJ_AHB_ICR_R |= (3<<0);
}

void Timer2A_Handler()
{
	TIMER2_ICR_R |= 1;
	toggleLED();
}


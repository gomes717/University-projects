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
void writeUART(char* data);
void UART_Init();
char readUART(void);


#define T_PWM 133333  //numero de ticks para o pwm, calculado para 1.667 ms

int8_t duty = 1;
uint8_t state_led = 0;


int main(void)
{
  PLL_Init();
	SysTick_Init();
	GPIO_Init();
	TIMER_Init();
	UART_Init();
	char* message = "\r\nStart 1%";
	char messageR;
	while (1)
	{
		writeUART(message);
		messageR = readUART();
		
		if(messageR == '0'){
			duty = 1;
			message = "\r\nLED a 1%";
		}
		else if (messageR == '1')
		{
			duty = 20;
			message = "\r\nLED a 20%";
		}
		else if (messageR == '2')
		{
			duty = 40;
			message = "\r\nLED a 40%";
		}
		else if (messageR == '3')
		{
			duty = 60;
			message = "\r\nLED a 60%";
		}
		else if (messageR == '4')
		{
			duty = 80;
			message = "\r\nLED a 80%";
		}
		else if (messageR == '5')
		{
			duty = 99;
			message = "\r\nLED a 99%";
		}
	}
}


void Timer2A_Handler()
{
	if(state_led){
		TIMER2_TAILR_R = T_PWM*(100 - duty)/100;
		state_led = 0;
	}
	else
	{
		TIMER2_TAILR_R = T_PWM*duty/100;	
		state_led = 1;
	}
	toggleLED();
	TIMER2_ICR_R |= 1;
}


// main.c
// Desenvolvido para a placa EK-TM4C1294XL


#include <stdint.h>

void PLL_Init(void);
void SysTick_Init(void);
void SysTick_Wait1ms(uint32_t delay);
void GPIO_Init(void);
void YellowON(uint8_t pos);
void RedON(uint8_t pos);
void GreenON(uint8_t pos);
void LED_OFF(uint8_t pos);
uint8_t getButton(void);


#define TIME_TICK 10
#define TIME_YELLOW 2000
#define TIME_RED 10000
#define TIME_GREEN 6000
#define TIME_CONC 1000
#define TIME_WALK 5000
#define TIME_TOGGLE 500

#define MAX_STATE 6
#define STATE_RED1 0
#define STATE_RED2 3
#define STATE_GREEN1 1
#define STATE_GREEN2 4
#define STATE_YELLOW1 2
#define STATE_YELLOW2 5

int main(void)
{
	PLL_Init();
	SysTick_Init();
	GPIO_Init();
	uint8_t state = 0, flag = 0, toggle = 0;
	uint16_t time = 0;
	while (1)
	{
		if(state == STATE_RED1 || state == STATE_RED2)
	  {
			if(flag && state == STATE_RED1)
			{
				if(toggle%2)
				{
					GreenON(1);
					GreenON(0);
				}
				else
				{
					YellowON(1);
					YellowON(0);
				}
				toggle = time/(TIME_TOGGLE/TIME_TICK);
				flag = 1 - time/(TIME_WALK/TIME_TICK);
				state += time/(TIME_WALK/TIME_TICK);
				time %= (TIME_WALK/TIME_TICK);
			}
			else
			{
			
				RedON(0);
				RedON(1);
				state += time/(TIME_CONC/TIME_TICK);
				time %= (TIME_CONC/TIME_TICK);
			}
		}
		else if(state == STATE_GREEN1)
		{
			RedON(1);
			GreenON(0);
			state += time/(TIME_GREEN/TIME_TICK);
			time %= (TIME_GREEN/TIME_TICK);
		}
		else if(state == STATE_YELLOW1)
		{
			RedON(1);
			YellowON(0);
			state += time/(TIME_YELLOW/TIME_TICK);
			time %= (TIME_YELLOW/TIME_TICK);
		}
		else if(state == STATE_GREEN2)
		{
			RedON(0);
			GreenON(1);
			state += time/(TIME_GREEN/TIME_TICK);
			time %= (TIME_GREEN/TIME_TICK);
		}
		else if(state == STATE_YELLOW2)
		{
			RedON(0);
			YellowON(1);
			state += time/(TIME_YELLOW/TIME_TICK);
			time %= (TIME_YELLOW/TIME_TICK);
		}
		if(!flag && !(state == STATE_RED1))
		{
			flag = getButton();
		}
		state %= MAX_STATE;
		SysTick_Wait1ms(TIME_TICK);
		time ++;
	}
}



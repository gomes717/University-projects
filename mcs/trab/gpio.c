// gpio.c
// Desenvolvido para a placa EK-TM4C1294XL
// Inicializa as portas J e N
// Prof. Guilherme Peron
// Alunos Guilherme Gomes e Hadryan Salles


#include <stdint.h>

#include "tm4c1294ncpdt.h"
#include "gpio.h"

  
// -------------------------------------------------------------------------------
// Função GPIO_Init
// Inicializa os ports 
// Parâmetro de entrada: Não tem
// Parâmetro de saída: Não tem
void GPIO_Init(void)
{
	SYSCTL_RCGCGPIO_R |= (1<<8)|(1<<12)|(1<<5);
	while(!(SYSCTL_PRGPIO_R&((1<<8)|(1<<12)|(1<<5))));
	GPIO_PORTJ_AHB_AMSEL_R &= 0;
	GPIO_PORTF_AHB_AMSEL_R &= 0;
	GPIO_PORTN_AMSEL_R &= 0;
	GPIO_PORTJ_AHB_PCTL_R &= 0;
	GPIO_PORTF_AHB_PCTL_R &= 0;
	GPIO_PORTN_PCTL_R &= 0;
	GPIO_PORTJ_AHB_DIR_R |= 0;
	GPIO_PORTF_AHB_DIR_R |= ((1<<4)|(1<<0));
	GPIO_PORTN_DIR_R |= (3<<0);
	GPIO_PORTJ_AHB_AFSEL_R &= 0;
	GPIO_PORTF_AHB_AFSEL_R &= 0;
	GPIO_PORTN_AFSEL_R &= 0;
	GPIO_PORTJ_AHB_DEN_R |= (3<<0);
	GPIO_PORTF_AHB_DEN_R |= (1<<4)|(1<<0);
	GPIO_PORTN_DEN_R |= (3<<0);
	GPIO_PORTJ_AHB_PUR_R |= (3<<0);
}	

void BtnInterrupt_Init(void)
{
	GPIO_PORTJ_AHB_IM_R &= ~(2<<0);
	GPIO_PORTJ_AHB_IS_R &= ~(2<<0);
	GPIO_PORTJ_AHB_IBE_R &= ~(2<<0); //only one level
	GPIO_PORTJ_AHB_IEV_R &= ~(2<<0); //high to low
	GPIO_PORTJ_AHB_ICR_R &= ~(2<<0);
	GPIO_PORTJ_AHB_IM_R |= (2<<0);
	NVIC_EN1_R |= (1<<19);
	NVIC_PRI12_R|= (5<<NVIC_PRI12_INT51_S);
}
	
void YellowON(uint8_t pos)
{
	if(pos)
	{
		GPIO_PORTN_DATA_R &= ~(3<<0);
		GPIO_PORTN_DATA_R |= (1<<0);
	}
	else
	{
		GPIO_PORTF_AHB_DATA_R &= ~((1<<4)|(1<<0));
		GPIO_PORTF_AHB_DATA_R |= (1<<0);
	}
}

void RedON(uint8_t pos)
{
	if(pos)
	{
		GPIO_PORTN_DATA_R &= ~(3<<0);
		GPIO_PORTN_DATA_R |= (3<<0);
	}
	else
	{
		GPIO_PORTF_AHB_DATA_R &= ~((1<<4)|(1<<0));
		GPIO_PORTF_AHB_DATA_R |= ((1<<4)|(1<<0));
	}
}

void GreenON(uint8_t pos)
{
	if(pos)
	{
		GPIO_PORTN_DATA_R &= ~(3<<0);
		GPIO_PORTN_DATA_R |= (1<<1);
	}
	else
	{
		GPIO_PORTF_AHB_DATA_R &= ~((1<<4)|(1<<0));
		GPIO_PORTF_AHB_DATA_R |= (1<<4);
	}
}

void LED_OFF(void)
{
	GPIO_PORTN_DATA_R &= ~(3<<0);
	GPIO_PORTF_AHB_DATA_R &= ~((1<<4)|(1<<0));
}

uint8_t getButton1(void)
{
	return (uint8_t)((1&(~GPIO_PORTJ_AHB_DATA_R)));
}
uint8_t getButton2(void)
{
	return (uint8_t)((1&(~(GPIO_PORTJ_AHB_DATA_R>>1))));
}

void binToLED(uint8_t binary)
{
	
	uint8_t low = binary&3;
	uint8_t high = (binary>>2)&3;
	LED_OFF();
	GPIO_PORTF_AHB_DATA_R |= (1&low)|((2&low)<<3);
	GPIO_PORTN_DATA_R |= high;
}

void toggleLED()
{
	GPIO_PORTN_DATA_R ^= (3<<0);
	GPIO_PORTF_AHB_DATA_R ^= ((1<<4)|(1<<0));
}

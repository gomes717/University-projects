// gpio.c
// Desenvolvido para a placa EK-TM4C1294XL
// Inicializa as portas J e N
// Prof. Guilherme Peron
// Alunos Guilherme Gomes e Hadryan Salles


#include <stdint.h>

#include "tm4c1294ncpdt.h"

  
// -------------------------------------------------------------------------------
// Função GPIO_Init
// Inicializa os ports 
// Parâmetro de entrada: Não tem
// Parâmetro de saída: Não tem
void GPIO_Init(void)
{
	//uint32_t RCGCGPIO = SYSCTL_RCGCGPIO_R;
	SYSCTL_RCGCGPIO_R |= (1<<8)|(1<<12)|(1<<5);
	//uint32_t PRGPIO = SYSCTL_PRGPIO_R;
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

void LED_OFF(uint8_t pos)
{
	if(pos)
		GPIO_PORTN_DATA_R &= ~(3<<0);
	else
		GPIO_PORTF_AHB_DATA_R &= ~((1<<4)|(1<<0));
}

uint8_t getButton(void)
{
	return (uint8_t)((1&(~GPIO_PORTJ_AHB_DATA_R)));
}





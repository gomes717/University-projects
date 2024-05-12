// timer.c
// Desenvolvido para a placa EK-TM4C1294XL
// Inicializa o timer B
// Prof. Guilherme Peron
// Alunos Guilherme Gomes e Hadryan Salles


#include <stdint.h>
#include "tm4c1294ncpdt.h"
#include "timer.h"

#define CLOCK 80000000
#define TIMER0_TICKS 10*CLOCK
#define TIME 55999999

void TIMER2A_Init(void)
{
	SYSCTL_RCGCTIMER_R |= (1<<2);
	while(!(SYSCTL_PRTIMER_R&(1<<2)));
	TIMER2_CTL_R  &= ~(1<<0);
	TIMER2_CFG_R  &= ~(7<<0);
	TIMER2_TAMR_R |= (1<<1);
	TIMER2_TAILR_R = TIME;
	TIMER2_TAPR_R = 0;
	TIMER2_ICR_R |= 1;
	TIMER2_IMR_R |= 1;
	TIMER2_CTL_R |= 1;
	NVIC_EN0_R |= (1<<23);
	NVIC_PRI5_R |= (4<<NVIC_PRI5_INT23_S);
}

void TIMER0A_Init(void)
{
	//fazer toda a configuração do timer0A
	//sendo que ele é single-shot
	SYSCTL_RCGCTIMER_R |= 0x1;
	while(!SYSCTL_PRTIMER_R&(0x1));
	TIMER0_CTL_R  &= ~0x1;
	TIMER0_CFG_R  &= ~0x100;
	TIMER0_TAMR_R |= 0x2;
	TIMER0_TAILR_R = TIMER0_TICKS;
	TIMER0_TAPR_R  = 0;
	TIMER0_ICR_R  |= 0x1;
	TIMER0_IMR_R  |= 0x1;
	// interrupt number for TIMER0A = 19
	// the priority register for interrupt number 16-19 is the PRI4
 	NVIC_PRI4_R |= (4<<29);
	// the enable register for intterupt number 0-31 is the EN0
	NVIC_EN0_R   |= (1<<19);
	TIMER0_CTL_R |= 0x1;
}
	

void TIMER0A_Stop()
{
	//fazer toda a configuração do timer0A
	//sendo que ele é single-shot
	SYSCTL_RCGCTIMER_R &= ~(0x01);
	while(!SYSCTL_PRTIMER_R&(~0x1));
	//TIMER0_CTL_R  &= ~0x1;
	//TIMER0_CFG_R  &= ~0x0;
	//TIMER0_TAMR_R |= 0x0;
	//TIMER0_TAILR_R = 0;
	//TIMER0_TAPR_R  = 0;
	//TIMER0_ICR_R  |= 0x0;
	//TIMER0_IMR_R  |= 0x0;
	// interrupt number for TIMER0A = 19
	// the priority register for interrupt number 16-19 is the PRI4
 	//NVIC_PRI4_R |= (4<<29);
	// the enable register for intterupt number 0-31 is the EN0
	//NVIC_EN0_R   |= (1<<19);
	//TIMER0_ICR_R = 1;
	//TIMER0_CTL_R &= ~0x1;
}
// timer.c
// Desenvolvido para a placa EK-TM4C1294XL
// Inicializa o timer B
// Prof. Guilherme Peron
// Alunos Guilherme Gomes e Hadryan Salles


#include <stdint.h>
#include "tm4c1294ncpdt.h"

#define TIME 55999999

void TIMER_Init(void)
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
	NVIC_EN0_R |= (1<<23);
	NVIC_PRI5_R |= (4<<NVIC_PRI5_INT23_S);
}


// uart.c
// Desenvolvido para a placa EK-TM4C1294XL
// Driver para UART
// Prof. Guilherme Peron
// Alunos Guilherme Gomes e Hadryan Salles


#include <stdint.h>
#include "tm4c1294ncpdt.h"


//baud-rate utilizado 9600
//80Mhz/(16*9600) = 520,833333
//UARTIBRD = 520
//UARTFBRD = 0,83333*64 = 53,333333 = 53

void UART_Init(void)
{
	SYSCTL_RCGCUART_R |= (1<<0);
	while(!(SYSCTL_PRUART_R&(1<<0)));
	UART0_CTL_R &= ~(1<<0);
	UART0_FBRD_R = 53;
	UART0_IBRD_R = 520;
	UART0_LCRH_R |= (3<<5);      //1 stop bit, sem paridade, 8-bits data, sem FIFO
	UART0_CC_R &= ~(15<<0);			 //zerar os 4 bits para pegar o clock do sistema
	UART0_CTL_R |= (1<<0);
	SYSCTL_RCGCGPIO_R |= (1<<0);
	while(!(SYSCTL_PRGPIO_R&(1<<0)));
	GPIO_PORTA_AHB_AMSEL_R &= ~(3<<0);
	GPIO_PORTA_AHB_PCTL_R |= (1<<4)|(1<<0);
	GPIO_PORTA_AHB_AFSEL_R |= (3<<0);
	GPIO_PORTA_AHB_DEN_R |= (3<<0);
	UART0_DR_R = 0;
}


void writeUART(char* data)
{
	int i;
	for(i = 0; data[i] != '\0';i++){
		while((UART0_FR_R&(1<<5)));
		UART0_DR_R = data[i];
	}
}

char readUART()
{
	while((UART0_FR_R&(1<<4)));
	return (char)UART0_DR_R;
}

// main.c
// Desenvolvido para a placa EK-TM4C1294XL


#include <stdint.h>
#include <stdio.h>
#include "tm4c1294ncpdt.h"

void PLL_Init(void);
void SysTick_Init(void);
void SysTick_Wait1ms(uint32_t delay);

#include "timer.h"
#include "uart.h"
#include "gpio.h"
#define SIZE 25
#define BUFFER 50
#define BUFFER_NOME 20
#define RANK_SIZE 3
static uint8_t flagInit = 0;
static const char LUT[15] = {'1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};
static uint8_t acabouTempo = 0;

int main(void)
{
	PLL_Init();
	SysTick_Init();
	GPIO_Init();
	BtnInterrupt_Init();
	TIMER2A_Init();
	UART_Init();
	TIMER2_CTL_R |= 1;
	uint8_t ledBin[SIZE], pos_rank=0;
	char message[BUFFER] ;
	char nome[BUFFER_NOME];
	char rankNome[RANK_SIZE][BUFFER_NOME];
	uint16_t rankPoints[RANK_SIZE];
	
	writeUART("\f");

	writeUART("------------------------- O JOGO -------------------------\n\n\r");

	while (1)
	{
		flagInit = 0;
		writeUART("Pressione o botao USR_SW2 comecar um novo jogo...\n\r");		

		while(!flagInit){};
		
		//regiao acessada quando clica o botao e come�a uma nova partida para printar ranking, e digitar o nome
		writeUART("\r\n------------------------- RANKING ------------------------\n\r");
		if(pos_rank == 0)
		{
			writeUART("Ninguem quis jogar ainda... :(\n\r");
		}
		else
		{
			uint8_t printados[RANK_SIZE];
			for(int i = 0; i < pos_rank; i++)
			{
				printados[i] = 0;
			}
			int i = 0;
			while(i < pos_rank)
			{
				int best = 0;
				for(int j=0; j < pos_rank; j++)
				{
					if(printados[j] == 0)
					{
						best = j;
						break;
					}
				}
				for(int j=0; j< pos_rank; j++)
				{
					if(printados[j] == 0 && rankPoints[best] < rankPoints[j])
					{
						best = j;
					}
				}
				printados[best] = 1;
				sprintf(message, "%d) Jogador: %s \t Pontos %d\n\r",i+1,rankNome[best], rankPoints[best]);
				writeUART(message);
				i += 1;
			}
		}
		writeUART("----------------------------------------------------------\n\n\r");
		writeUART("Digite seu nome: ");
		readLineUART(nome);
		
		writeUART("\n\n\rIniciando a partida...\n\r");
		writeUART("\n\r----------------------------------------------------------\n\r");
	
		uint8_t perdeu = 0;
		uint8_t rodada = 0;
		
		while(!perdeu)
		{
			rodada += 1;
			//encontra o valor randomico e liga os led's
			//leitura de dados do jogador
			sprintf(message, "\r\nRodada  %d\r\nOlhe para a placa!\n\r", rodada);
			writeUART(message);
			for(int i = 0; i < rodada; i++)
			{
				ledBin[i] = TIMER2_TAR_R%15 + 1;		
				SysTick_Wait1ms(2000);
				binToLED(ledBin[i]);
				SysTick_Wait1ms(3000);
				LED_OFF();
			}
			writeUART("Digite a sequencia:");
			//inicia o timer0
			TIMER0A_Init();
			readLineUART(message);
			//desativa timer0
			TIMER0A_Stop();
			uint8_t errou = 0;
			//verificacao se foi acertado a sequencia
			for(int i = 0; message[i] != '\0'; i++)
			{
				if(LUT[ledBin[i]-1] != message[i])
				{
					errou = 1;
					break;
				}
			}

			writeUART("\n\n\r----------------------------------------------------------\n\r");
			
			if(errou || acabouTempo)
			{
				flagInit = 0;
				sprintf(message, "Sua pontuacao foi: %d\n\r", rodada-1);
				//desenvolver o ranking, por enquanto ta, perdeu entrou no ranking, sem nenhuma ordena��o
				if(pos_rank < RANK_SIZE)
				{
					for(int i = 0; nome[i] != '\0'; i++)
					{
						rankNome[pos_rank][i] = nome[i];
					}	
					rankPoints[pos_rank] = rodada-1;
					pos_rank++;
				} else
				{
					// encontra a pior pontuacao
					int pior = 0;
					for(int i = 0; i < pos_rank; i++) 
					{
						if(rankPoints[i] < rankPoints[pior])
						{
							pior = i;
						}
					}
					for(int i = 0; nome[i] != '\0'; i++)
					{
						rankNome[pior][i] = nome[i];
					}	
					rankPoints[pior] = rodada-1;
				}
				if(acabouTempo)
				{
					writeUART("\n\rSeu tempo acabou! Voce perdeu!\n\r");
				}
				if(errou)
				{
					writeUART("\n\rVoce errou! Voce perdeu!\n\r");	
				}		
				writeUART("\n\r----------------------------------------------------------\n\r");
				writeUART(message);
				writeUART("----------------------------------------------------------\n\n\r");
				perdeu = 1;
			}
			
			acabouTempo = 0;
		}
	}
}

void Timer2A_Handler()
{
	TIMER2_ICR_R |= 1;
}

void StopTimer0()
{
	//fazer toda a configura��o do timer0A
	//sendo que ele � single-shot
	SYSCTL_RCGCTIMER_R = 0x0;
	while(!SYSCTL_PRTIMER_R&(0x0));
	TIMER0_CTL_R  &= ~0x0;
	TIMER0_CFG_R  &= ~0x0;
	TIMER0_TAMR_R |= 0x0;
	TIMER0_TAILR_R = 0;
	TIMER0_TAPR_R  = 0;
	TIMER0_ICR_R  |= 0x0;
	TIMER0_IMR_R  |= 0x0;
	// interrupt number for TIMER0A = 19
	// the priority register for interrupt number 16-19 is the PRI4
 	NVIC_PRI4_R |= (4<<29);
	// the enable register for intterupt number 0-31 is the EN0
	NVIC_EN0_R   |= (1<<19);
}

//interrup��o do timer0 gerar flag de jogo perdido

void GPIOPortJ_Handler()
{
	flagInit = 1;
	GPIO_PORTJ_AHB_ICR_R |= (3<<0);
}

void Timer0A_Handler() 
{
	acabouTempo = 1;
	TIMER0_ICR_R = 1;
	TIMER0_CTL_R &= ~0x1;
}

char readUART()
{
	while((UART0_FR_R&(1<<4))&&!acabouTempo);
	return (char)UART0_DR_R;
}

void readLineUART(char* message)
{
	uint16_t pos = 0;
	char retChar;
	while(retChar != 13)
	{
		retChar = readUART();
		message[pos++] = retChar;
		if(retChar == 0x7F)
		{
			message[--pos] = ' ';
			message[--pos] = ' ';
		}
	}
	message[pos-1] = '\0';
}
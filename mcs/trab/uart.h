#ifndef __UART__
#define __UART__


void writeUART(char* data);
void UART_Init();
char readUART(void);
void readLineUART(char* message);

#endif
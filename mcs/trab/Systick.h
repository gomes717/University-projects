#ifndef __SYSTICK__
#define __SYSTICK__

#include <stdint.h>

void SysTick_Init(void);
void SysTick_Wait1ms(uint32_t delay);

#endif
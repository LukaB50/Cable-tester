#include "lpc17xx.h"
#include "timers.h"

#define TICK_FREQ  1000000 //1us

extern uint32_t SystemCoreClock;
uint32_t msTicks;
uint32_t usTicks;

void timers_init(void) {
	
	SystemCoreClockUpdate();
	SysTick_Config(SystemCoreClock / TICK_FREQ);
	
	//NVIC_EnableIRQ(SysTick_IRQn);
	NVIC_SetPriority(SysTick_IRQn, 0);
}

void SysTick_Handler(void)
{
    usTicks++;
		msTicks=usTicks/1000;
}

void ms_delay(uint32_t delayTicks)
{
    uint32_t currentTicks;
    currentTicks = msTicks;
    while ((msTicks-currentTicks)<delayTicks);
}

void us_delay(uint32_t delayTicks)
{
    uint32_t currentTicks;
    currentTicks = usTicks;
    while ((usTicks-currentTicks)<delayTicks);
}

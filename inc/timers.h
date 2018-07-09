#ifndef __TIMERS_H
#define __TIMERS_H

void timers_init(void);
void SysTick_Handler(void);
void ms_delay(uint32_t delayTicks);

#endif

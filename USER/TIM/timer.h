#ifndef __TIMER_H__
#define __TIMER_H__

#include "bsp.h"

void TimerInit(void);
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim);

#endif /* __TIMER_H__ */
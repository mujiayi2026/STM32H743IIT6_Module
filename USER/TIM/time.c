#include "timer.h"

void TimerInit()
{
    //打开定时器6中断
    HAL_TIM_Base_Start_IT(&htim6);
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
    if (htim->Instance == TIM6) {
        //定时器6中断回调函数
        //这里可以添加定时器中断处理代码

        
    }
}
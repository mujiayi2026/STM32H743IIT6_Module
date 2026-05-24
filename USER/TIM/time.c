/**
 * @file time.c
 * @brief 定时器6模块驱动程序
 * @author mujiayi
 * @date 2026-05-24
 *
 * 功能说明：
 * 初始化并启动定时器6中断
 * 用于系统定时任务处理
 */

#include "timer.h"

/**
 * @brief 定时器初始化函数
 * @details 打开定时器6中断
 * @return void
 */
void TimerInit(void)
{
  HAL_TIM_Base_Start_IT(&htim6);
}

/**
 * @brief 定时器周期溢出回调函数
 * @details 在定时器计数溢出时被调用，处理定时中断任务
 * @param htim 定时器句柄指针
 * @return void
 */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  if (htim->Instance == TIM6) {
    /* 定时器6中断处理代码 */
  }
}
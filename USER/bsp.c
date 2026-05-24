/**
 * @file bsp.c
 * @brief 板级支持包（BSP）- 系统初始化和运行
 * @author mujiayi
 * @date 2026-05-24
 *
 * 功能说明：
 * 初始化所有硬件模块（LED、按键、定时器、UART）
 * 提供系统主循环入口
 */

#include "bsp.h"

/**
 * @brief 系统硬件初始化函数
 * @details 初始化LED、定时器、UART等硬件模块
 *          在系统启动时调用一次
 * @return void
 */
void Sys_Init(void)
{
  LedInit();
  TimerInit();
  UartInit();
}

/**
 * @brief 系统主循环函数
 * @details 周期性扫描按键、处理UART接收数据
 *          需要在main函数中循环调用
 * @return void
 */
void Sys_Run(void)
{
  KeyScan();
  UartProc();
}
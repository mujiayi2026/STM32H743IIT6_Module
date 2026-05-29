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


static uint32_t g_fac_us = 480;       /* us延时倍乘数 */

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
	SensorInit();
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
  Hcsr04Read();
}

void delay_us(uint32_t nus)
{
    uint32_t ticks;
    uint32_t told, tnow, tcnt = 0;
    uint32_t reload = SysTick->LOAD;        /* LOAD的值 */
    ticks = nus * g_fac_us;                 /* 需要的节拍数 */

    told = SysTick->VAL;                    /* 刚进入时的计数器值 */
    while (1)
    {
        tnow = SysTick->VAL;
        if (tnow != told)
        {
            if (tnow < told)
            {
                tcnt += told - tnow;        /* 这里注意一下SYSTICK是一个递减的计数器就可以了 */
            }
            else
            {
                tcnt += reload - tnow + told;
            }
            told = tnow;
            if (tcnt >= ticks) 
            {
                break;                      /* 时间超过/等于要延迟的时间,则退出 */
            }
        }
    }
} 

void delay_ms(uint16_t nms)
{
    delay_us((uint32_t)(nms * 1000));                   /* 普通方式延时 */
}

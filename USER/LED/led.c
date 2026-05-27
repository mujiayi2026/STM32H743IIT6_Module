/**
 * @file led.c
 * @brief LED模块驱动程序
 * @author mujiayi
 * @date 2026-05-24
 *
 * 硬件配置：
 * - LED_RED:   PB0
 * - LED_GREEN: PB1
 */

#include "led.h"

/**
 * @brief LED初始化函数
 * @details 将LED引脚初始化为高电平（熄灭状态）
 * @return void
 */
void LedInit(void)
{
  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, GPIO_PIN_RESET);
  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1, GPIO_PIN_RESET);
}

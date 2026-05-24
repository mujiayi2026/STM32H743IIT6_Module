/**
 * @file key.h
 * @brief 按键扫描模块头文件
 * @author mujiayi
 * @date 2026-05-24
 */

#ifndef __KEY_H__
#define __KEY_H__

#include "bsp.h"

/* GPIO读取宏定义 */
#define WK HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_0)
#define K0 HAL_GPIO_ReadPin(GPIOH, GPIO_PIN_3)
#define K1 HAL_GPIO_ReadPin(GPIOH, GPIO_PIN_2)
#define K2 HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_13)

void KeyScan(void);

#endif /* __KEY_H__ */
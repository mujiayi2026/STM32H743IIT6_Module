/**
 * @file bsp.h
 * @brief 板级支持包（BSP）头文件
 * @author mujiayi
 * @date 2026-05-24
 */

#ifndef __BSP_H__
#define __BSP_H__

#include "main.h"
#include "dma.h"
#include "i2c.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"


#include "led.h"
#include "key.h"
#include "timer.h"
#include "uart.h"

#include "shtx.h"
#include "hcsr04.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>

void Sys_Init(void);
void Sys_Run(void);
void delay_us(uint32_t nus);
void delay_ms(uint16_t nms);

#endif /* __BSP_H__ */
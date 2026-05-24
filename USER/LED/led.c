// Created by Mujiayi on 2026/5/24.
// Led 引脚 PB0 PB1

#include "led.h"

void LedInit()
{
	//灯灭,设置低电平
	HAL_GPIO_WritePin(GPIOB,GPIO_PIN_0,GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOB,GPIO_PIN_1,GPIO_PIN_SET);
}


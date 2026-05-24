// Led 引脚 PB0 PB1

#include "led.h"

void LedInit()
{
	//灯灭,设置低电平
	HAL_GPIO_WritePin(GPIOB,GPIO_PIN_0,GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOB,GPIO_PIN_1,GPIO_PIN_SET);
}


//LED操作函数
//HAL_GPIO_WritePin(GPIOB,GPIO_PIN_0,GPIO_PIN_RESET);   //将PB0置低
//HAL_GPIO_WritePin(GPIOB,GPIO_PIN_0,GPIO_PIN_SET);     //将PB0置高
//HAL_GPIO_TogglePin(GPIOB,GPIO_PIN_0);                 //将PB0取反
//GPIOB->ODR                                            //PB端口的寄存器，可进行位操作

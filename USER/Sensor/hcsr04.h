#ifndef __HCSR04_H
#define __HCSR04_H

#include "bsp.h"

#define Hcsr04_Trig_High() HAL_GPIO_WritePin(GPIOB,GPIO_PIN_14,GPIO_PIN_SET)
#define Hcsr04_Trig_Low() HAL_GPIO_WritePin(GPIOB,GPIO_PIN_14,GPIO_PIN_RESET)
#define Hcsr04_Echo() HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_15)

void Hcsr04Start(void);
void Hcsr04Read(void);

#endif
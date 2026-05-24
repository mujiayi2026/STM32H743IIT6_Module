#ifndef __BSP_H__
#define __BSP_H__

#include "main.h"
#include "gpio.h"

#include "led.h"
#include "key.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>

void Sys_Init(void);
void Sys_Run(void);

#endif /* __BSP_H__ */
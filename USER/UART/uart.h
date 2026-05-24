/**
 * @file uart.h
 * @brief UART1串口通信模块头文件
 * @author mujiayi
 * @date 2026-05-24
 */

#ifndef __UART_H__
#define __UART_H__

#include "bsp.h"

void UartInit(void);
void UartProc(void);
void HAL_UARTEx_RxEventCallback(UART_HandleTypeDef *huart, uint16_t Size);

#endif /* __UART_H__ */
#ifndef __UART_H__
#define __UART_H__

#include "bsp.h"

void UartInit(void);
void UartProc(void);
void HAL_UARTEx_RxEventCallback(UART_HandleTypeDef *huart, uint16_t Size);

#endif /* __UART_H__ */
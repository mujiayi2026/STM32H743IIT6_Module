#include "uart.h"

volatile uint8_t uart_flag = 0;
volatile uint16_t uart1_rx_len = 0;
uint8_t Rx[64] __attribute__((aligned(32))) = {0};


//重定义fputc函数，使printf函数能够通过UART发送数据
int fputc(int ch, FILE *f)
{
    // 发送一个字符到 UART
    HAL_UART_Transmit(&huart1, (uint8_t *)&ch, 1, HAL_MAX_DELAY);
    return ch;
}

void UartInit()
{
    //开启UART接收DMA中断
    HAL_UARTEx_ReceiveToIdle_DMA(&huart1, Rx, sizeof(Rx));
}

void UartProc()
{
	if (!uart_flag) return;
	uart_flag = 0;
	SCB_InvalidateDCache_by_Addr((uint32_t*)Rx, sizeof(Rx));
	//处理字符串Rx
	printf("%s",Rx);
	printf("\r\n");
	memset(Rx, 0, sizeof(Rx));
	uart1_rx_len = 0;
	HAL_UARTEx_ReceiveToIdle_DMA(&huart1, Rx, sizeof(Rx));
}

void HAL_UARTEx_RxEventCallback(UART_HandleTypeDef *huart, uint16_t Size)
{
    if (huart == &huart1)
    {
        uart1_rx_len = Size;
        uart_flag = 1;
    }
}
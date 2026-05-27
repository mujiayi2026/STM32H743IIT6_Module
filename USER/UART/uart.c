/**
 * @file uart.c
 * @brief UART1串口通信驱动程序
 * @author mujiayi
 * @date 2026-05-24
 *
 * 功能说明：
 * - 使用DMA接收模式，提高接收效率
 * - 重定向printf函数到UART1输出
 * - H7系列MCU带Cache，需要处理DCache一致性
 *
 * 硬件配置：
 * - UART1接收缓冲区：64字节，32字节对齐（Cache要求）
 */

#include "uart.h"

volatile uint8_t uart_flag = 0;
volatile uint16_t uart1_rx_len = 0;
/* H7系列带Cache，使用DMA的时候需要32字节对齐 */
uint8_t Rx[64] __attribute__((aligned(32))) = {0};

/**
 * @brief 重定义fputc函数，使printf能够通过UART1输出
 * @details 将单个字符发送到UART1
 * @param ch 要发送的字符
 * @param f 文件指针（由库提供）
 * @return 返回发送的字符
 */
int fputc(int ch, FILE *f)
{
  HAL_UART_Transmit(&huart1, (uint8_t *)&ch, 1, HAL_MAX_DELAY);
  return ch;
}

/**
 * @brief UART初始化函数
 * @details 配置UART1为DMA接收模式，使用空闲中断触发接收
 * @return void
 */
void UartInit(void)
{
  HAL_UARTEx_ReceiveToIdle_DMA(&huart1, Rx, sizeof(Rx));
	printf("UART Success\r\n");
}

/**
 * @brief UART处理函数
 * @details 处理接收到的数据，通过printf输出
 *          需要定期调用以处理接收缓冲区数据
 * @return void
 */
void UartProc(void)
{
  if (!uart_flag)
    return;

  uart_flag = 0;

  /* H7系列带Cache，使用DMA的时候需要清除Cache保证数据一致性 */
  SCB_InvalidateDCache_by_Addr((uint32_t *)Rx, sizeof(Rx));

  printf("%s", Rx);
  printf("\r\n");

  /* 清空接收缓冲区 */
  memset(Rx, 0, sizeof(Rx));
  uart1_rx_len = 0;

  /* 重新启动DMA接收 */
  HAL_UARTEx_ReceiveToIdle_DMA(&huart1, Rx, sizeof(Rx));
}

/**
 * @brief UART空闲中断回调函数
 * @details 当UART接收到空闲条件（一段时间未收到数据）时被调用
 *          设置接收完成标志，通知主程序处理数据
 * @param huart UART句柄指针
 * @param Size 本次接收的字节数
 * @return void
 */
void HAL_UARTEx_RxEventCallback(UART_HandleTypeDef *huart, uint16_t Size)
{
  if (huart == &huart1) {
    uart1_rx_len = Size;
    uart_flag = 1;
  }
}
#ifndef __USARTDMA_H
#define __USARTDMA_H

#include "stm32f10x.h"
#include <stdio.h>

// ڹ궨
#define DEBUG_USARTx USART1
#define DEBUG_USART_CLK RCC_APB2Periph_USART1
#define DEBUG_USART_APBxClkCmd RCC_APB2PeriphClockCmd
#define DEBUG_USART_BAUDRATE 115200

// USART GPIO ź궨
#define DEBUG_USART_GPIO_CLK (RCC_APB2Periph_GPIOA)
#define DEBUG_USART_GPIO_APBxClkCmd RCC_APB2PeriphClockCmd

#define DEBUG_USART_TX_GPIO_PORT GPIOA
#define DEBUG_USART_TX_GPIO_PIN GPIO_Pin_9
#define DEBUG_USART_RX_GPIO_PORT GPIOA
#define DEBUG_USART_RX_GPIO_PIN GPIO_Pin_10

// ڶӦDMAͨ
#define USART_TX_DMA_CHANNEL DMA1_Channel4
// Ĵַ
#define USART_DR_ADDRESS (USART1_BASE + 0x04)
// һη͵
// #define SENDBUFF_SIZE 32 * 4  // 删除这行

// 串口DMA传输相关宏定义
#define USART_TX_DMA_FLAG_TC DMA1_FLAG_TC4 // 串口1 TX对应DMA1通道4
#define USART_TX_DMA_CHANNEL DMA1_Channel4 // 串口1 TX对应DMA1通道4
#define BUFFER_SIZE 32                     // 与main.c中定义保持一致
#define SENDBUFF_SIZE (BUFFER_SIZE * 4)    // 发送缓冲区大小(字节)

// 声明为外部变量
extern uint8_t SendBuff[SENDBUFF_SIZE];

void USART_Config(void);
void USARTx_DMA_Config(void);

#endif /* __USARTDMA_H */

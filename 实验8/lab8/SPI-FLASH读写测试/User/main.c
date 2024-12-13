/**
 ******************************************************************************
 * @file    main.c
 * @brief   SPI FLASH测试，测试信息通过USART1打印在电脑串口调试助手
 ******************************************************************************
 */

#include "stm32f10x.h"
#include "./led/bsp_led.h"
#include "./usart/bsp_usart.h"
#include "./flash/bsp_spi_flash.h"
#include <string.h>

typedef enum
{
	FAILED = 0,
	PASSED = !FAILED
} TestStatus;

/* 获取缓冲区的长度 */
#define BufferSize 100

#define FLASH_WriteAddress 0x00000
#define FLASH_ReadAddress FLASH_WriteAddress
#define FLASH_SectorToErase FLASH_WriteAddress

__IO TestStatus TransferStatus1 = FAILED;

/* 发送缓冲区初始化 */
uint8_t readBuff[BufferSize];
uint8_t writeBuff[BufferSize];

// 函数原型声明
TestStatus Buffercmp(uint8_t *pBuffer1, uint8_t *pBuffer2, uint16_t BufferLength);

/**
 * @brief  主函数
 * @param  无
 * @retval 无
 */
int main(void)
{

	uint32_t id;
	uint16_t i;

	LED_GPIO_Config();

	LED_BLUE;
	/* 串口初始化 */
	USART_Config();

	printf("\r\n 这是一个SPI-FLASH读写测试例程 \r\n");

	SPI_FLASH_Init();

	id = SPI_Read_ID();

	printf("\r\n id =0x%x \r\n", id);

	SPI_Erase_Sector(0);

	for (i = 0; i < BufferSize; i++)
	{
		writeBuff[i] = i + 0x30;
	}

	SPI_Write_Data(0, writeBuff, BufferSize);
	printf("\r\n 写入的数据为：%s \r\t", writeBuff);

	SPI_Read_Data(0, readBuff, BufferSize);
	printf("\r\n 读出的数据为： \r\n");
	for (i = 0; i < BufferSize; i++)
	{
		printf("0x%x ", readBuff[i]);
		if (i % 10 == 9)
			printf("\r\n");
	}

	/* 检查写入的数据与读出的数据是否相等 */
	TransferStatus1 = Buffercmp(readBuff, writeBuff, BufferSize);

	if (PASSED == TransferStatus1)
	{
		LED_GREEN;
		printf("\r\n 8M串行flash(W25Q64)测试成功!\n\r");
	}
	else
	{
		LED_RED;
		printf("\r\n 8M串行flash(W25Q64)测试失败!\n\r");
	}

	while (1)
	{
	}
}

/*
 * 函数名：Buffercmp
 * 描述  ：比较两个缓冲区中的数据是否相等
 * 输入  ：-pBuffer1     src缓冲区指针
 *         -pBuffer2     dst缓冲区指针
 *         -BufferLength 缓冲区长度
 * 输出  ：无
 * 返回  ：-PASSED pBuffer1 等于   pBuffer2
 *         -FAILED pBuffer1 不同于 pBuffer2
 */
TestStatus Buffercmp(uint8_t *pBuffer1, uint8_t *pBuffer2, uint16_t BufferLength)
{
	while (BufferLength--)
	{
		if (*pBuffer1 != *pBuffer2)
		{
			return FAILED;
		}

		pBuffer1++;
		pBuffer2++;
	}
	return PASSED;
}

/*********************************************END OF FILE**********************/

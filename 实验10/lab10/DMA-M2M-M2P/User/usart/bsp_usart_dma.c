#include "bsp_usart_dma.h"

uint8_t SendBuff[SENDBUFF_SIZE];

/**
 * @brief  USART GPIO 配置,工作参数配置
 * @param  无
 * @retval 无
 */
void USART_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;

	// 打开串口GPIO的时钟
	DEBUG_USART_GPIO_APBxClkCmd(DEBUG_USART_GPIO_CLK, ENABLE);

	// 打开串口外设的时钟
	DEBUG_USART_APBxClkCmd(DEBUG_USART_CLK, ENABLE);

	// 将USART Tx的GPIO配置为推挽复用模式
	GPIO_InitStructure.GPIO_Pin = DEBUG_USART_TX_GPIO_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(DEBUG_USART_TX_GPIO_PORT, &GPIO_InitStructure);

	// 将USART Rx的GPIO配置为浮空输入模式
	GPIO_InitStructure.GPIO_Pin = DEBUG_USART_RX_GPIO_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(DEBUG_USART_RX_GPIO_PORT, &GPIO_InitStructure);

	// 配置串口的工作参数
	// 配置波特率
	USART_InitStructure.USART_BaudRate = DEBUG_USART_BAUDRATE;
	// 配置 针数据字长
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	// 配置停止位
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	// 配置校验位
	USART_InitStructure.USART_Parity = USART_Parity_No;
	// 配置硬件流控制
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	// 配置工作模式，收发一起
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	// 完成串口的初始化配置
	USART_Init(DEBUG_USARTx, &USART_InitStructure);

	// 使能串口
	USART_Cmd(DEBUG_USARTx, ENABLE);
}

/*****************  发送一个字节 **********************/
void Usart_SendByte(USART_TypeDef *pUSARTx, uint8_t ch)
{
	/* 发送一个字节数据到USART */
	USART_SendData(pUSARTx, ch);

	/* 等待发送数据寄存器为空 */
	while (USART_GetFlagStatus(pUSARTx, USART_FLAG_TXE) == RESET)
		;
}

/**
 * @brief  USARTx TX DMA 配置，内存到外设(USART1->DR)
 * @param  无
 * @retval 无
 */
void USARTx_DMA_Config(void)
{
	DMA_InitTypeDef DMA_InitStructure;

	// 开启DMA时钟
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);

	// 源数据地址：SendBuff
	DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)&DEBUG_USARTx->DR;
	DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)SendBuff;
	// 方向：存储器到外设
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralDST;
	// 传输大小
	DMA_InitStructure.DMA_BufferSize = BUFFER_SIZE * 4; // 32个uint32_t = 128字节
	// 外设地址固定
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
	// 内存地址递增
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
	// 外设数据单位
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
	// 内存数据单位
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
	// DMA模式：一次传输
	DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;
	// 优先级：高
	DMA_InitStructure.DMA_Priority = DMA_Priority_High;
	// 禁止内存到内存的传输
	DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;

	// 配置DMA通道
	DMA_Init(USART_TX_DMA_CHANNEL, &DMA_InitStructure);

	// 使能串口的DMA发送
	USART_DMACmd(DEBUG_USARTx, USART_DMAReq_Tx, ENABLE);
}

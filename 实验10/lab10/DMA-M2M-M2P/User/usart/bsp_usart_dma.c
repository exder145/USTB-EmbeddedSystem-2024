#include "bsp_usart_dma.h"

uint8_t SendBuff[SENDBUFF_SIZE];

/**
 * @brief  USART GPIO ����,������������
 * @param  ��
 * @retval ��
 */
void USART_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;

	// �򿪴���GPIO��ʱ��
	DEBUG_USART_GPIO_APBxClkCmd(DEBUG_USART_GPIO_CLK, ENABLE);

	// �򿪴��������ʱ��
	DEBUG_USART_APBxClkCmd(DEBUG_USART_CLK, ENABLE);

	// ��USART Tx��GPIO����Ϊ���츴��ģʽ
	GPIO_InitStructure.GPIO_Pin = DEBUG_USART_TX_GPIO_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(DEBUG_USART_TX_GPIO_PORT, &GPIO_InitStructure);

	// ��USART Rx��GPIO����Ϊ��������ģʽ
	GPIO_InitStructure.GPIO_Pin = DEBUG_USART_RX_GPIO_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(DEBUG_USART_RX_GPIO_PORT, &GPIO_InitStructure);

	// ���ô��ڵĹ�������
	// ���ò�����
	USART_InitStructure.USART_BaudRate = DEBUG_USART_BAUDRATE;
	// ���� �������ֳ�
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	// ����ֹͣλ
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	// ����У��λ
	USART_InitStructure.USART_Parity = USART_Parity_No;
	// ����Ӳ��������
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	// ���ù���ģʽ���շ�һ��
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	// ��ɴ��ڵĳ�ʼ������
	USART_Init(DEBUG_USARTx, &USART_InitStructure);

	// ʹ�ܴ���
	USART_Cmd(DEBUG_USARTx, ENABLE);
}

/*****************  ����һ���ֽ� **********************/
void Usart_SendByte(USART_TypeDef *pUSARTx, uint8_t ch)
{
	/* ����һ���ֽ����ݵ�USART */
	USART_SendData(pUSARTx, ch);

	/* �ȴ��������ݼĴ���Ϊ�� */
	while (USART_GetFlagStatus(pUSARTx, USART_FLAG_TXE) == RESET)
		;
}

/**
 * @brief  USARTx TX DMA ���ã��ڴ浽����(USART1->DR)
 * @param  ��
 * @retval ��
 */
void USARTx_DMA_Config(void)
{
	DMA_InitTypeDef DMA_InitStructure;

	// ����DMAʱ��
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);

	// Դ���ݵ�ַ��SendBuff
	DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)&DEBUG_USARTx->DR;
	DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)SendBuff;
	// ���򣺴洢��������
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralDST;
	// �����С
	DMA_InitStructure.DMA_BufferSize = BUFFER_SIZE * 4; // 32��uint32_t = 128�ֽ�
	// �����ַ�̶�
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
	// �ڴ��ַ����
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
	// �������ݵ�λ
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
	// �ڴ����ݵ�λ
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
	// DMAģʽ��һ�δ���
	DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;
	// ���ȼ�����
	DMA_InitStructure.DMA_Priority = DMA_Priority_High;
	// ��ֹ�ڴ浽�ڴ�Ĵ���
	DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;

	// ����DMAͨ��
	DMA_Init(USART_TX_DMA_CHANNEL, &DMA_InitStructure);

	// ʹ�ܴ��ڵ�DMA����
	USART_DMACmd(DEBUG_USARTx, USART_DMAReq_Tx, ENABLE);
}

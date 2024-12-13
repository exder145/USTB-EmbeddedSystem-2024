/**
 ******************************************************************************
 * @file    bsp_i2c_ee.c
 * @author  STMicroelectronics
 * @version V1.0
 * @date    2013-xx-xx
 * @brief   SPI-FLASH
 ******************************************************************************
 */

#include "./flash/bsp_spi_flash.h"
#include "./usart/bsp_usart.h"

static __IO uint32_t SPITimeout = SPIT_LONG_TIMEOUT;

static uint32_t SPI_TIMEOUT_UserCallback(uint8_t errorCode);

/**
 * @brief  SPII/O
 * @param
 * @retval
 */
static void SPI_GPIO_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;

	/* ʹSPI йصʱ */
	FLASH_SPI_APBxClock_FUN(FLASH_SPI_CLK, ENABLE);
	FLASH_SPI_GPIO_APBxClock_FUN(FLASH_SPI_GPIO_CLK, ENABLE);

	/* MISO MOSI SCK*/
	GPIO_InitStructure.GPIO_Pin = FLASH_SPI_SCK_PIN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_Init(FLASH_SPI_SCK_PORT, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = FLASH_SPI_MOSI_PIN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_Init(FLASH_SPI_MOSI_PORT, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = FLASH_SPI_MISO_PIN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(FLASH_SPI_MISO_PORT, &GPIO_InitStructure);

	// ʼCSţʹƣֱó
	GPIO_InitStructure.GPIO_Pin = FLASH_SPI_CS_PIN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(FLASH_SPI_CS_PORT, &GPIO_InitStructure);

	FLASH_SPI_CS_HIGH;
}

/**
 * @brief  SPI 模式配置
 * @param  CPOL: 时钟极性
 * @param  CPHA: 时钟相位
 * @retval None
 */
static void SPI_Mode_Config(uint8_t CPOL, uint8_t CPHA)
{
	SPI_InitTypeDef SPI_InitStructure;

	SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_128; // 降低波特率
	SPI_InitStructure.SPI_CPHA = CPHA;									 // 设置CPHA
	SPI_InitStructure.SPI_CPOL = CPOL;									 // 设置CPOL
	SPI_InitStructure.SPI_CRCPolynomial = 0;							 // CRC值
	SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;
	SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex; // 全双工
	SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;
	SPI_InitStructure.SPI_Mode = SPI_Mode_Master;
	SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;

	SPI_Init(FLASH_SPIx, &SPI_InitStructure); // 初始化SPI
	SPI_Cmd(FLASH_SPIx, ENABLE);			  // 使能SPI
}

/**
 * @brief  SPI ʼ
 * @param
 * @retval
 */
void SPI_FLASH_Init(void)
{

	SPI_Mode_Config(1, 0);
}

// Ͳһֽ
uint8_t SPI_FLASH_Send_Byte(uint8_t data)
{
	SPITimeout = SPIT_FLAG_TIMEOUT;
	// 鲢ȴTXΪǿ
	while (SPI_I2S_GetFlagStatus(FLASH_SPIx, SPI_I2S_FLAG_TXE) == RESET)
	{
		if ((SPITimeout--) == 0)
			return SPI_TIMEOUT_UserCallback(0);
	}

	// ִе˴TXѿ
	SPI_I2S_SendData(FLASH_SPIx, data);

	SPITimeout = SPIT_FLAG_TIMEOUT;
	// 鲢ȴRXΪǿ
	while (SPI_I2S_GetFlagStatus(FLASH_SPIx, SPI_I2S_FLAG_RXNE) == RESET)
	{
		if ((SPITimeout--) == 0)
			return SPI_TIMEOUT_UserCallback(0);
	}

	// ִе˴˵ݷϣյһֽ
	return SPI_I2S_ReceiveData(FLASH_SPIx);
}

uint8_t SPI_FLASH_Read_Byte(void)
{
	return SPI_FLASH_Send_Byte(DUMMY);
}

// ȡID
uint32_t SPI_Read_ID(void)
{
	uint32_t flash_id;

	// Ƭѡʹ
	FLASH_SPI_CS_LOW;
	SPI_FLASH_Send_Byte(READ_JEDEC_ID);

	flash_id = SPI_FLASH_Send_Byte(DUMMY);

	flash_id <<= 8;

	flash_id |= SPI_FLASH_Send_Byte(DUMMY);

	flash_id <<= 8;

	flash_id |= SPI_FLASH_Send_Byte(DUMMY);

	FLASH_SPI_CS_HIGH;

	return flash_id;
}

// FLASHдʹ
void SPI_Write_Enable(void)
{
	// Ƭѡʹ
	FLASH_SPI_CS_LOW;
	SPI_FLASH_Send_Byte(WRITE_ENABLE);
	FLASH_SPI_CS_HIGH;
}

// FLASHָ
void SPI_Erase_Sector(uint32_t addr)
{
	SPI_Write_Enable();
	// Ƭѡʹ
	FLASH_SPI_CS_LOW;
	SPI_FLASH_Send_Byte(ERASE_SECTOR);

	SPI_FLASH_Send_Byte((addr >> 16) & 0xff);

	SPI_FLASH_Send_Byte((addr >> 8) & 0xff);

	SPI_FLASH_Send_Byte(addr & 0xff);

	FLASH_SPI_CS_HIGH;

	SPI_WaitForWriteEnd();
}

// ȡFLASH
void SPI_Read_Data(uint32_t addr, uint8_t *readBuff, uint32_t numByteToRead)
{
	SPI_Write_Enable(); // 使能写操作
	FLASH_SPI_CS_LOW;	// 选择Flash芯片

	SPI_FLASH_Send_Byte(READ_DATA); // 发送读取命令

	// 发送地址
	SPI_FLASH_Send_Byte((addr >> 16) & 0xff);
	SPI_FLASH_Send_Byte((addr >> 8) & 0xff);
	SPI_FLASH_Send_Byte(addr & 0xff);

	// 读取数据
	while (numByteToRead--)
	{
		*readBuff = SPI_FLASH_Send_Byte(DUMMY); // 发送虚拟字节以读取数据
		readBuff++;
	}

	FLASH_SPI_CS_HIGH;	   // 取消选择Flash芯片
	SPI_WaitForWriteEnd(); // 等待写入结束
}

// FLASHд
// ȡFLASH
void SPI_Write_Data(uint32_t addr, uint8_t *writeBuff, uint32_t numByteToWrite)
{
	SPI_Write_Enable();
	// Ƭѡʹ
	FLASH_SPI_CS_LOW;
	SPI_FLASH_Send_Byte(WRITE_DATA);

	SPI_FLASH_Send_Byte((addr >> 16) & 0xff);

	SPI_FLASH_Send_Byte((addr >> 8) & 0xff);

	SPI_FLASH_Send_Byte(addr & 0xff);

	while (numByteToWrite--)
	{
		SPI_FLASH_Send_Byte(*writeBuff);
		writeBuff++;
	}

	FLASH_SPI_CS_HIGH;
	SPI_WaitForWriteEnd();
}

// ȴFLASHڲʱ
void SPI_WaitForWriteEnd(void)
{
	uint8_t status_reg = 0;

	// Ƭѡʹ
	FLASH_SPI_CS_LOW;

	SPI_FLASH_Send_Byte(READ_STATUS);

	do
	{
		status_reg = SPI_FLASH_Send_Byte(DUMMY);
	} while ((status_reg & 0x01) == 1);

	FLASH_SPI_CS_HIGH;
}

/**
 * @brief  Basic management of the timeout situation.
 * @param  errorCode룬λĸڳ.
 * @retval 0ʾSPIȡʧ.
 */
static uint32_t SPI_TIMEOUT_UserCallback(uint8_t errorCode)
{
	/* Block communication and all processes */
	FLASH_ERROR("SPI ȴʱ!errorCode = %d", errorCode);

	return 0;
}

void SPI_Flash_Read(uint32_t address, uint8_t *buffer, uint16_t length); // 声明读取函数

/*********************************************END OF FILE**********************/

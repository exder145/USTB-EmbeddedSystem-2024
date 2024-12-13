#include "bsp_i2c.h"

/**
 * @brief  IIC EEPROM  ,
 * @param
 * @retval
 */
void I2C_EE_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	I2C_InitTypeDef I2C_InitStructure;

	// IIC GPIOʱ
	EEPROM_I2C_GPIO_APBxClkCmd(EEPROM_I2C_SCL_GPIO_CLK | EEPROM_I2C_SDA_GPIO_CLK, ENABLE);

	// IIC ʱ
	EEPROM_I2C_APBxClkCmd(EEPROM_I2C_CLK, ENABLE);

	// IIC SCLGPIOΪ츴ģʽ
	GPIO_InitStructure.GPIO_Pin = EEPROM_I2C_SCL_GPIO_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_OD;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(EEPROM_I2C_SCL_GPIO_PORT, &GPIO_InitStructure);

	// IIC SDAGPIOΪģʽ
	GPIO_InitStructure.GPIO_Pin = EEPROM_I2C_SDA_GPIO_PIN;
	GPIO_Init(EEPROM_I2C_SDA_GPIO_PORT, &GPIO_InitStructure);

	// IICĹ
	I2C_InitStructure.I2C_Ack = I2C_Ack_Enable;								  // ʹӦ
	I2C_InitStructure.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit; // ʹ7λַģʽ
	I2C_InitStructure.I2C_ClockSpeed = EEPROM_I2_BAUDRATE;					  // SCLʱƵ
	I2C_InitStructure.I2C_DutyCycle = I2C_DutyCycle_2;
	I2C_InitStructure.I2C_Mode = I2C_Mode_I2C;
	I2C_InitStructure.I2C_OwnAddress1 = STM32_I2C_OWN_ADDR; // STM32 IIC豸ַֻҪΨһ

	I2C_Init(EEPROM_I2C, &I2C_InitStructure);

	// ʹܴ
	I2C_Cmd(EEPROM_I2C, ENABLE);
}

// EEPROMдһֽ

void EEPROM_Byte_Write(uint8_t addr, uint8_t data)
{
	// ʼź
	I2C_GenerateSTART(EEPROM_I2C, ENABLE);

	while (I2C_CheckEvent(EEPROM_I2C, I2C_EVENT_MASTER_MODE_SELECT) == ERROR)
		;

	// EV5¼⵽豸ַ
	I2C_Send7bitAddress(EEPROM_I2C, EEPROM_ADDR, I2C_Direction_Transmitter);

	while (I2C_CheckEvent(EEPROM_I2C, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED) == ERROR)
		;

	// EV6¼⵽ҪĴ洢Ԫַ
	I2C_SendData(EEPROM_I2C, addr);

	while (I2C_CheckEvent(EEPROM_I2C, I2C_EVENT_MASTER_BYTE_TRANSMITTING) == ERROR)
		;

	// EV8¼⵽Ҫ洢
	I2C_SendData(EEPROM_I2C, data);

	while (I2C_CheckEvent(EEPROM_I2C, I2C_EVENT_MASTER_BYTE_TRANSMITTED) == ERROR)
		;

	// ݴ
	I2C_GenerateSTOP(EEPROM_I2C, ENABLE);
}

// EEPROMдֽڣҳд룩ÿд벻ܳ8ֽ

void EEPROM_Page_Write(uint8_t addr, uint8_t *data, uint8_t numByteToWrite)
{
	// ʼź
	I2C_GenerateSTART(EEPROM_I2C, ENABLE);

	while (I2C_CheckEvent(EEPROM_I2C, I2C_EVENT_MASTER_MODE_SELECT) == ERROR)
		;

	// EV5¼⵽豸ַ
	I2C_Send7bitAddress(EEPROM_I2C, EEPROM_ADDR, I2C_Direction_Transmitter);

	while (I2C_CheckEvent(EEPROM_I2C, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED) == ERROR)
		;

	// EV6¼⵽ҪĴ洢Ԫַ
	I2C_SendData(EEPROM_I2C, addr);

	while (I2C_CheckEvent(EEPROM_I2C, I2C_EVENT_MASTER_BYTE_TRANSMITTING) == ERROR)
		;

	while (numByteToWrite)
	{
		// EV8¼⵽Ҫ洢
		I2C_SendData(EEPROM_I2C, *data);

		while (I2C_CheckEvent(EEPROM_I2C, I2C_EVENT_MASTER_BYTE_TRANSMITTED) == ERROR)
			;

		data++;
		numByteToWrite--;
	}
	// ݴ
	I2C_GenerateSTOP(EEPROM_I2C, ENABLE);
}

// EEPROMȡ

void EEPROM_Read(uint8_t addr, uint8_t *data, uint8_t numByteToRead)
{
	// 1. 发送起始信号
	I2C_GenerateSTART(EEPROM_I2C, ENABLE);
	while (I2C_CheckEvent(EEPROM_I2C, I2C_EVENT_MASTER_MODE_SELECT) == ERROR)
		;

	// 2. 发送设备地址(写模式)
	I2C_Send7bitAddress(EEPROM_I2C, EEPROM_ADDR, I2C_Direction_Transmitter);
	while (I2C_CheckEvent(EEPROM_I2C, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED) == ERROR)
		;

	// 3. 发送要读取的EEPROM内部存储单元地址
	I2C_SendData(EEPROM_I2C, addr);
	while (I2C_CheckEvent(EEPROM_I2C, I2C_EVENT_MASTER_BYTE_TRANSMITTED) == ERROR)
		;

	// 4. 发送重复起始信号
	I2C_GenerateSTART(EEPROM_I2C, ENABLE);
	while (I2C_CheckEvent(EEPROM_I2C, I2C_EVENT_MASTER_MODE_SELECT) == ERROR)
		;

	// 5. 发送设备地址(读模式)
	I2C_Send7bitAddress(EEPROM_I2C, EEPROM_ADDR, I2C_Direction_Receiver);
	while (I2C_CheckEvent(EEPROM_I2C, I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED) == ERROR)
		;

	// 6. 接收数据
	while (numByteToRead)
	{
		if (numByteToRead == 1)
		{
			// 最后一个字节时，要发送非应答信号
			I2C_AcknowledgeConfig(EEPROM_I2C, DISABLE);
		}

		// 等待接收到一个字节
		while (I2C_CheckEvent(EEPROM_I2C, I2C_EVENT_MASTER_BYTE_RECEIVED) == ERROR)
			;

		// 读取接收到的数据
		*data = I2C_ReceiveData(EEPROM_I2C);

		data++;
		numByteToRead--;
	}

	// 7. 发送停止信号
	I2C_GenerateSTOP(EEPROM_I2C, ENABLE);

	// 8. 重新使能应答信号，为下一次通信做准备
	I2C_AcknowledgeConfig(EEPROM_I2C, ENABLE);
}

// ȴEEPROMڲʱ
void EEPROM_WaitForWriteEnd(void)
{

	do
	{
		// ʼź
		I2C_GenerateSTART(EEPROM_I2C, ENABLE);

		while (I2C_GetFlagStatus(EEPROM_I2C, I2C_FLAG_SB) == RESET)
			;

		// EV5¼⵽豸ַ
		I2C_Send7bitAddress(EEPROM_I2C, EEPROM_ADDR, I2C_Direction_Transmitter);
	} while (I2C_GetFlagStatus(EEPROM_I2C, I2C_FLAG_ADDR) == RESET);

	// EEPROMڲʱɴ
	I2C_GenerateSTOP(EEPROM_I2C, ENABLE);
}

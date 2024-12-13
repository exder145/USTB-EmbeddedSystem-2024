/**
  ******************************************************************************
  * @file    main.c
  * @brief   IIC通信实验-读写EEPROM测试
  ******************************************************************************
  ******************************************************************************
  */ 
 
 
#include "stm32f10x.h"
#include "bsp_usart.h"
#include "./i2c/bsp_i2c.h"

//1.初始化IIC相关的GPIO
//2.配置IIC外设的工作模式
//3.编写IIC写入EEPROM的Byte write函数
//4.编写IIC读取EEPROM的RANDOM Read函数
//5.使用read函数及write函数进行读写校验

//6.编写page write 及seq read函数并校验

#define readBufSize 13

uint8_t readData[readBufSize]={0};
uint8_t writeData[8]={4,5,6,7,8,9,10,11};
/**
  * @brief  主函数
  * @param  无
  * @retval 无
  */
int main(void)
{	
	
	uint8_t i=0;
  /*初始化USART 配置模式为 115200 8-N-1，中断接收*/
  USART_Config();
	
	/* 发送一个字符串 */
	printf("这是一个IIC通讯实验\n");
	
	//初始化IIC
	I2C_EE_Config();

	//写入一个字节
	EEPROM_Byte_Write(11,55);
	
	//等待写入操作完成
	EEPROM_WaitForWriteEnd();
	
	//写入一个字节
	EEPROM_Byte_Write(12,52);
	
	//等待写入操作完成
	EEPROM_WaitForWriteEnd();
	
	//addr%8 == 0 ,即为地址对齐
	EEPROM_Page_Write(16,writeData,8);
	
	//等待写入操作完成
	EEPROM_WaitForWriteEnd();
	
	//读取数据
	EEPROM_Read(11,readData,13);
	//EEPROM_Read(16,readData,8);
	
	
	for(i=0;i<readBufSize;i++)
	{	
		printf("%d ",readData[i]);	
	}
	printf("111111111111111111");
	
  while(1)
	{	
		
	}	
}
/*********************************************END OF FILE**********************/

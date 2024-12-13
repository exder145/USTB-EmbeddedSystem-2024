/**
  ******************************************************************************
  * @file    main.c
  * @brief   IICͨ��ʵ��-��дEEPROM����
  ******************************************************************************
  ******************************************************************************
  */ 
 
 
#include "stm32f10x.h"
#include "bsp_usart.h"
#include "./i2c/bsp_i2c.h"

//1.��ʼ��IIC��ص�GPIO
//2.����IIC����Ĺ���ģʽ
//3.��дIICд��EEPROM��Byte write����
//4.��дIIC��ȡEEPROM��RANDOM Read����
//5.ʹ��read������write�������ж�дУ��

//6.��дpage write ��seq read������У��

#define readBufSize 13

uint8_t readData[readBufSize]={0};
uint8_t writeData[8]={4,5,6,7,8,9,10,11};
/**
  * @brief  ������
  * @param  ��
  * @retval ��
  */
int main(void)
{	
	
	uint8_t i=0;
  /*��ʼ��USART ����ģʽΪ 115200 8-N-1���жϽ���*/
  USART_Config();
	
	/* ����һ���ַ��� */
	printf("����һ��IICͨѶʵ��\n");
	
	//��ʼ��IIC
	I2C_EE_Config();

	//д��һ���ֽ�
	EEPROM_Byte_Write(11,55);
	
	//�ȴ�д��������
	EEPROM_WaitForWriteEnd();
	
	//д��һ���ֽ�
	EEPROM_Byte_Write(12,52);
	
	//�ȴ�д��������
	EEPROM_WaitForWriteEnd();
	
	//addr%8 == 0 ,��Ϊ��ַ����
	EEPROM_Page_Write(16,writeData,8);
	
	//�ȴ�д��������
	EEPROM_WaitForWriteEnd();
	
	//��ȡ����
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

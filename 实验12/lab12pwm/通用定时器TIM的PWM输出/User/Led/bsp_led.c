/**
 ******************************************************************************
 * @file    bsp_led.c
 * @author  fire
 * @version V1.0
 * @date    2013-xx-xx
 * @brief   ledӦ�ú����ӿ�
 ******************************************************************************
 */

#include "bsp_led.h"

/**
 * @brief  ��ʼ������LED��IO
 * @param  ��
 * @retval ��
 */
void LED_GPIO_Config(void)
{
	/*����һ��GPIO_InitTypeDef���͵Ľṹ��*/
	GPIO_InitTypeDef GPIO_InitStructure;

	/*����LED��ص�GPIO����ʱ��*/
	RCC_APB2PeriphClockCmd(LED1_GPIO_CLK | LED2_GPIO_CLK | LED3_GPIO_CLK, ENABLE);
	/*ѡ��Ҫ���Ƶ�GPIO����*/
	GPIO_InitStructure.GPIO_Pin = LED1_GPIO_PIN;

	/*��������ģʽΪͨ���������*/
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;

	/*������������Ϊ50MHz */
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;

	/*���ÿ⺯������ʼ��GPIO*/
	GPIO_Init(LED1_GPIO_PORT, &GPIO_InitStructure);

	/*ѡ��Ҫ���Ƶ�GPIO����*/
	GPIO_InitStructure.GPIO_Pin = LED2_GPIO_PIN;

	/*���ÿ⺯������ʼ��GPIO*/
	GPIO_Init(LED2_GPIO_PORT, &GPIO_InitStructure);

	/*ѡ��Ҫ���Ƶ�GPIO����*/
	GPIO_InitStructure.GPIO_Pin = LED3_GPIO_PIN;

	/*���ÿ⺯������ʼ��GPIOF*/
	GPIO_Init(LED3_GPIO_PORT, &GPIO_InitStructure);

	/* 关闭所有led灯 */
	LED_RGBOFF; // 使用已定义的宏
}

/*********************************************END OF FILE**********************/

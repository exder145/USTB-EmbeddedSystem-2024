//bsp_led.c
#include "bsp_led.h" 
void LED_GPIO_Config(void){
GPIO_InitTypeDef GPIO_InitStructure; /*����һ��GPIO_InitTypeDef���͵Ľṹ��*/
/*����LED��ص�GPIO����ʱ��*/
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);  
/*������������Ϊ50MHz */ 
GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
/*ѡ��Ҫ���Ƶ�GPIO����*/
GPIO_InitStructure.GPIO_Pin = LED1_GPIO_PIN;
/*��������ģʽΪͨ���������*/
GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 
/*���ÿ⺯������ʼ��GPIO*/
GPIO_Init(LED1_GPIO_PORT, &GPIO_InitStructure);
GPIO_InitStructure.GPIO_Pin = LED2_GPIO_PIN;/*ѡ��Ҫ���Ƶ�GPIO����*/
GPIO_Init(LED2_GPIO_PORT, &GPIO_InitStructure);/*���ÿ⺯������ʼ��GPIO*/
GPIO_InitStructure.GPIO_Pin = LED3_GPIO_PIN;/*ѡ��Ҫ���Ƶ�GPIO����*/
GPIO_Init(LED3_GPIO_PORT, &GPIO_InitStructure);/*���ÿ⺯������ʼ��GPIOF*/
/* �ر�����led�� */
GPIO_SetBits(LED1_GPIO_PORT, LED1_GPIO_PIN);
GPIO_SetBits(LED2_GPIO_PORT, LED2_GPIO_PIN);
GPIO_SetBits(LED3_GPIO_PORT, LED3_GPIO_PIN);
}
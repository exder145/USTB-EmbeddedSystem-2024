//bsp.h
/** the macro definition to trigger the led on or off */
#ifndef __LED_H
#define __LED_H
#include "stm32f10x.h"
/* ����LED���ӵ�GPIO�˿�, �û�ֻ��Ҫ�޸�����Ĵ��뼴�ɸı���Ƶ�LED���� */
// R-��ɫ
#define LED1_GPIO_PORT GPIOB /* GPIO�˿� */
#define LED1_GPIO_CLK RCC _APB2Periph_GPIOB /* GPIO�˿�ʱ�� */
#define LED1_GPIO_PIN GPIO_Pin_5 /* ���ӵ�SCLʱ���ߵ�GPIO */
// G-��ɫ
#define LED2_GPIO_PORT GPIOB /* GPIO�˿� */
#define LED2_GPIO_CLK RCC_APB2Periph_GPIOB /* GPIO�˿�ʱ�� */
#define LED2_GPIO_PIN GPIO_Pin_0 /* ���ӵ�SCLʱ���ߵ�GPIO */
// B-��ɫ
#define LED3_GPIO_PORT GPIOB /* GPIO�˿� */
#define LED3_GPIO_CLK RCC_APB2Periph_GPIOB /* GPIO�˿�ʱ�� */
#define LED3_GPIO_PIN GPIO_Pin_1 /* ���ӵ�SCLʱ���ߵ�GPIO */


#define ON 0
#define OFF 1
/* ʹ�ñ�׼�Ĺ̼������IO*/
#define LED1(a) if (a) GPIO_SetBits(LED1_GPIO_PORT,LED1_GPIO_PIN);\
else GPIO_ResetBits(LED1_GPIO_PORT,LED1_GPIO_PIN)
#define LED2(a) if (a) GPIO_SetBits(LED2_GPIO_PORT,LED2_GPIO_PIN);\
else GPIO_ResetBits(LED2_GPIO_PORT,LED2_GPIO_PIN)
#define LED3(a) if (a) GPIO_SetBits(LED3_GPIO_PORT,LED3_GPIO_PIN);\
else GPIO_ResetBits(LED3_GPIO_PORT,LED3_GPIO_PIN)
/* �������IO�ĺ� */
#define LED1_OFF LED1(ON)
#define LED1_ON LED1(OFF)

#define LED2_OFF LED2(ON)
#define LED2_ON LED2(OFF)

#define LED3_OFF LED3(ON)
#define LED3_ON LED3(OFF)

void LED_GPIO_Config(void);
#endif /* __LED_H */ 

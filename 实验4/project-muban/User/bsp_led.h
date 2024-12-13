//bsp.h
/** the macro definition to trigger the led on or off */
#ifndef __LED_H
#define __LED_H
#include "stm32f10x.h"
/* 定义LED连接的GPIO端口, 用户只需要修改下面的代码即可改变控制的LED引脚 */
// R-红色
#define LED1_GPIO_PORT GPIOB /* GPIO端口 */
#define LED1_GPIO_CLK RCC _APB2Periph_GPIOB /* GPIO端口时钟 */
#define LED1_GPIO_PIN GPIO_Pin_5 /* 连接到SCL时钟线的GPIO */
// G-绿色
#define LED2_GPIO_PORT GPIOB /* GPIO端口 */
#define LED2_GPIO_CLK RCC_APB2Periph_GPIOB /* GPIO端口时钟 */
#define LED2_GPIO_PIN GPIO_Pin_0 /* 连接到SCL时钟线的GPIO */
// B-蓝色
#define LED3_GPIO_PORT GPIOB /* GPIO端口 */
#define LED3_GPIO_CLK RCC_APB2Periph_GPIOB /* GPIO端口时钟 */
#define LED3_GPIO_PIN GPIO_Pin_1 /* 连接到SCL时钟线的GPIO */


#define ON 0
#define OFF 1
/* 使用标准的固件库控制IO*/
#define LED1(a) if (a) GPIO_SetBits(LED1_GPIO_PORT,LED1_GPIO_PIN);\
else GPIO_ResetBits(LED1_GPIO_PORT,LED1_GPIO_PIN)
#define LED2(a) if (a) GPIO_SetBits(LED2_GPIO_PORT,LED2_GPIO_PIN);\
else GPIO_ResetBits(LED2_GPIO_PORT,LED2_GPIO_PIN)
#define LED3(a) if (a) GPIO_SetBits(LED3_GPIO_PORT,LED3_GPIO_PIN);\
else GPIO_ResetBits(LED3_GPIO_PORT,LED3_GPIO_PIN)
/* 定义控制IO的宏 */
#define LED1_OFF LED1(ON)
#define LED1_ON LED1(OFF)

#define LED2_OFF LED2(ON)
#define LED2_ON LED2(OFF)

#define LED3_OFF LED3(ON)
#define LED3_ON LED3(OFF)

void LED_GPIO_Config(void);
#endif /* __LED_H */ 

// bsp_exti.h
#ifndef __BSP_EXTI_H
#define __BSP_EXTI_H
#include "stm32f10x.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_exti.h"
#include "misc.h"

// 定义按键的 GPIO 引脚、端口和时钟
#define KEY1_INT_GPIO_PIN GPIO_Pin_0
#define KEY1_INT_GPIO_PORT GPIOA
#define KEY1_INT_GPIO_CLK RCC_APB2Periph_GPIOA

// 声明全局变量 i
extern int i; // 使用 volatile 声明 i

void EXIT_Key_Config(void);

#endif /* __BSP_EXTI_H */

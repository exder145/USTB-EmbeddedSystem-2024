// bsp_exti .c
#include "stm32f10x.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_exti.h"
#include "misc.h"
#include "bsp_exti.h"

// 定义按键的 GPIO 引脚、端口和时钟
#define KEY1_INT_GPIO_PIN GPIO_Pin_0
#define KEY1_INT_GPIO_PORT GPIOA
#define KEY1_INT_GPIO_CLK RCC_APB2Periph_GPIOA

// 定义全局变量 i
int i = 0; // 初始化 i 为 0

void EXIT_Key_Config(void)
{
    // 在这里声明所有变量
    GPIO_InitTypeDef GPIO_InitStruct;
    EXTI_InitTypeDef EXTI_InitStruct;
    NVIC_InitTypeDef NVIC_InitStructure; // 将 NVIC_InitTypeDef 的声明移到函数开头

    // 初始化GPIO
    RCC_APB2PeriphClockCmd(KEY1_INT_GPIO_CLK, ENABLE);
    GPIO_InitStruct.GPIO_Pin = KEY1_INT_GPIO_PIN;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(KEY1_INT_GPIO_PORT, &GPIO_InitStruct);

    // 初始化EXTI
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
    GPIO_EXTILineConfig(GPIO_PortSourceGPIOA, GPIO_PinSource0); /* 选择 EXTI 的信号源 */
    EXTI_InitStruct.EXTI_Line = EXTI_Line0;
    EXTI_InitStruct.EXTI_Mode = EXTI_Mode_Interrupt;    /* EXTI 为中断模式 */
    EXTI_InitStruct.EXTI_Trigger = EXTI_Trigger_Rising; /* 上升沿中断 */
    EXTI_InitStruct.EXTI_LineCmd = ENABLE;              /* 使能中断 */
    EXTI_Init(&EXTI_InitStruct);

    // NVIC 配置
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);           // 配置 NVIC 为优先级组 1
    NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn;          // 配置中断源：按键 1
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1; // 配置抢占优先级：1
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;        // ��置子优先级：1
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;           // 使能中断通道
    NVIC_Init(&NVIC_InitStructure);
}

void EXTI0_IRQHandler(void)
{
    // 检查是否是 EXTI0 触发的中断
    if (EXTI_GetITStatus(EXTI_Line0) != RESET)
    {
        // 增加 i 的值
        i++; // 每次按下按键，i 增加 1

        // 清除中断标志
        EXTI_ClearITPendingBit(EXTI_Line0);
    }
}

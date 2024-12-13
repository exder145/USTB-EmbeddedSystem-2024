#ifndef __BSP_ADC_H
#define __BSP_ADC_H

#include "stm32f10x.h"

#define ADC_APBxClock_FUN RCC_APB2PeriphClockCmd
#define ADC_CLK RCC_APB2Periph_ADC1

#define ADC_GPIO_APBxClock_FUN RCC_APB2PeriphClockCmd
#define ADC_GPIO_CLK RCC_APB2Periph_GPIOC
#define ADC_PORT GPIOC

// 修改为2个通道
#define NOFCHANEL 2

// PC0
#define ADC_PIN1 GPIO_Pin_0
#define ADC_CHANNEL1 ADC_Channel_10

// 新增PC1
#define ADC_PIN2 GPIO_Pin_1
#define ADC_CHANNEL2 ADC_Channel_11

#define ADC_x ADC1
#define ADC_DMA_CHANNEL DMA1_Channel1
#define ADC_DMA_CLK RCC_AHBPeriph_DMA1

void ADCx_Init(void);

#endif /* __BSP_ADC_H */

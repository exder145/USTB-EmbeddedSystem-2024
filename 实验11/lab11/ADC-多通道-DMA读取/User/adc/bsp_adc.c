#include "bsp_adc.h"

__IO uint16_t ADC_ConvertedValue[NOFCHANEL] = {0};

static void ADCx_GPIO_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;

	//  ADC IO˿ʱ
	ADC_GPIO_APBxClock_FUN(ADC_GPIO_CLK, ENABLE);

	//  ADC IO ģʽ
	GPIO_InitStructure.GPIO_Pin = ADC_PIN1 | ADC_PIN2;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;

	// ʼ ADC IO
	GPIO_Init(ADC_PORT, &GPIO_InitStructure);
}

// ANSI C׼C89 ׼
// C99
// C11 2011

static void ADCx_Mode_Config(void)
{
	DMA_InitTypeDef DMA_InitStructure;
	RCC_AHBPeriphClockCmd(ADC_DMA_CLK, ENABLE);

	DMA_DeInit(ADC_DMA_CHANNEL);
	DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)(&(ADC_x->DR));
	DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)ADC_ConvertedValue;
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;
	DMA_InitStructure.DMA_BufferSize = NOFCHANEL;
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
	DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;
	DMA_InitStructure.DMA_Priority = DMA_Priority_High;
	DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
	DMA_Init(ADC_DMA_CHANNEL, &DMA_InitStructure);
	DMA_Cmd(ADC_DMA_CHANNEL, ENABLE);
	/*----------------------------------------------------------------------*/

	ADC_InitTypeDef ADC_InitStruct;
	ADC_APBxClock_FUN(ADC_CLK, ENABLE);
	ADC_InitStruct.ADC_Mode = ADC_Mode_Independent;
	ADC_InitStruct.ADC_ScanConvMode = ENABLE;
	ADC_InitStruct.ADC_ContinuousConvMode = ENABLE;
	ADC_InitStruct.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
	ADC_InitStruct.ADC_DataAlign = ADC_DataAlign_Right;
	ADC_InitStruct.ADC_NbrOfChannel = NOFCHANEL;
	ADC_Init(ADC_x, &ADC_InitStruct);

	RCC_ADCCLKConfig(RCC_PCLK2_Div8);

	ADC_RegularChannelConfig(ADC_x, ADC_CHANNEL1, 1, ADC_SampleTime_55Cycles5);
	ADC_RegularChannelConfig(ADC_x, ADC_CHANNEL2, 2, ADC_SampleTime_55Cycles5);

	// ʹADC DMA
	ADC_DMACmd(ADC_x, ENABLE);

	ADC_Cmd(ADC_x, ENABLE);
	// ADCʼУ׼
	ADC_StartCalibration(ADC_x);
	// ȴУ׼
	while (ADC_GetCalibrationStatus(ADC_x))
		;

	ADC_SoftwareStartConvCmd(ADC_x, ENABLE);
}

void ADCx_Init(void)
{
	ADCx_GPIO_Config();
	ADCx_Mode_Config();
}

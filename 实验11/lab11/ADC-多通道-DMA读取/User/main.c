/**
 ******************************************************************************
 * @file    main.c
 * @version V1.0
 * @date    2024-xx-xx
 * @brief   ADC
 ******************************************************************************
 */

#include "stm32f10x.h"
#include "bsp_usart.h"
#include "bsp_adc.h"

extern __IO uint16_t ADC_ConvertedValue[NOFCHANEL];

// ֲڱתĵѹֵ
float ADC_ConvertedValueLocal[NOFCHANEL];

// ʱ
void Delay(__IO uint32_t nCount)
{
  for (; nCount != 0; nCount--)
    ;
}

/**
 * @brief
 * @param
 * @retval
 */
int main(void)
{
  /*ʼUSART ģʽΪ 115200 8-N-1жϽ*/
  USART_Config();
  printf("ADC-ͨ-DMAȡ\n\n\n\n");

  ADCx_Init();

  while (1)
  {
    ADC_ConvertedValueLocal[0] = (float)ADC_ConvertedValue[0] / 4096 * 3.3;
    ADC_ConvertedValueLocal[1] = (float)ADC_ConvertedValue[1] / 4096 * 3.3;

    printf("\r\n CH0 value = 0x%04X, voltage = %.2f V",
           ADC_ConvertedValue[0], ADC_ConvertedValueLocal[0]);
    printf("\r\n CH1 value = 0x%04X, voltage = %.2f V\r\n",
           ADC_ConvertedValue[1], ADC_ConvertedValueLocal[1]);

    Delay(0xffffee);
  }
}

/*********************************************END OF FILE**********************/

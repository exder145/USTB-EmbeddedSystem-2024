// DMA 存储器->存储器->外设（串口）数据传输实验

#include "stm32f10x.h"
#include "bsp_usart_dma.h"
#include "bsp_led.h"

// 当使用存储器到存储器模式时候，通道可以随便选，没有硬性的规定
#define DMA_CHANNEL DMA1_Channel6
#define DMA_CLOCK RCC_AHBPeriph_DMA1

// 传输完成标志
#define DMA_FLAG_TC DMA1_FLAG_TC6

// 要发送的数据大小
#define BUFFER_SIZE 32

/* 定义aSRC_Const_Buffer数组作为DMA传输数据源 */
const uint32_t aSRC_Const_Buffer[BUFFER_SIZE] = {
    0x01020304, 0x05060708, 0x090A0B0C, 0x0D0E0F10,
    0x11121314, 0x15161718, 0x191A1B1C, 0x1D1E1F20,
    0x21222324, 0x25262728, 0x292A2B2C, 0x2D2E2F30,
    0x31323334, 0x35363738, 0x393A3B3C, 0x3D3E3F40,
    0x41424344, 0x45464748, 0x494A4B4C, 0x4D4E4F50,
    0x51525354, 0x55565758, 0x595A5B5C, 0x5D5E5F60,
    0x61626364, 0x65666768, 0x696A6B6C, 0x6D6E6F70,
    0x71727374, 0x75767778, 0x797A7B7C, 0x7D7E7F80};

/* 定义DMA传输目标存储器 */
uint32_t *aDST_Buffer;

#define SOFT_DELAY Delay(0x0FFFFF);

/* 函数声明 */
static void Delay(__IO u32 nCount);
void DMA_Config(void);
uint8_t Buffercmp(const uint32_t *pBuffer, uint32_t *pBuffer1, uint16_t BufferLength);

/* 函数定义 */
void DMA_Config(void)
{
  DMA_InitTypeDef DMA_InitStructure;
  // 开启DMA时钟
  RCC_AHBPeriphClockCmd(DMA_CLOCK, ENABLE);
  // 源数据地址
  DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)aSRC_Const_Buffer;
  // 目标地址
  DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)aDST_Buffer;
  // 方向：外设到存储器（这里的外设是内部的FLASH）
  DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;
  // 传输大小
  DMA_InitStructure.DMA_BufferSize = BUFFER_SIZE;
  // 外设（内部的FLASH）地址递增
  DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Enable;
  // 内存地址递增
  DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
  // 外设数据单位
  DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Word;
  // 内存数据单位
  DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Word;
  // DMA模式，一次或者循环模式
  DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;
  // 优先级：高
  DMA_InitStructure.DMA_Priority = DMA_Priority_High;
  // 使能内存到内存的传输
  DMA_InitStructure.DMA_M2M = DMA_M2M_Enable;
  // 配置DMA通道
  DMA_Init(DMA_CHANNEL, &DMA_InitStructure);
  // 清除DMA数据流传输完成标志位
  DMA_ClearFlag(DMA_FLAG_TC);
  // 使能DMA
  DMA_Cmd(DMA_CHANNEL, ENABLE);
}

uint8_t Buffercmp(const uint32_t *pBuffer, uint32_t *pBuffer1, uint16_t BufferLength)
{
  while (BufferLength--)
  {
    if (*pBuffer != *pBuffer1)
    {
      return 0;
    }
    pBuffer++;
    pBuffer1++;
  }
  return 1;
}

static void Delay(__IO u32 nCount)
{
  for (; nCount != 0; nCount--)
    ;
}

int main(void)
{
  /*********
  M2M code
  *************/
  /* 定义存放比较结果变量 */
  uint8_t TransferStatus;

  /* 将目标存储器指向SendBuff */
  aDST_Buffer = (uint32_t *)SendBuff;

  /* LED 端口初始化 */
  LED_GPIO_Config();

  /* 设置RGB彩色灯为紫色 */
  LED_PURPLE;

  /* 简单延时函数 */
  Delay(0xFFFFFF);

  /* DMA传输配置 */
  DMA_Config();

  /* 等待DMA传输完成 */
  while (DMA_GetFlagStatus(DMA_FLAG_TC) == RESET)
  {
  }

  /* 比较源数据与传输后数据 */
  TransferStatus = Buffercmp(aSRC_Const_Buffer, aDST_Buffer, BUFFER_SIZE);

  /* 判断源数据与传输后数据比较结果*/
  if (TransferStatus == 0)
  {
    /* 源数据与传输后数据不相等时RGB彩色灯显示红色 */
    LED_RED;
  }
  else
  {
    /* 源数据与传输后数据相等时RGB彩色灯显示蓝色 */
    LED_BLUE;
  }

  /*********
  M2P code
  *************/
  /* 初始化USART */
  USART_Config();

  /* 配置串口DMA发送 */
  USARTx_DMA_Config();

  /* 使能DMA发送通道 */
  DMA_Cmd(USART_TX_DMA_CHANNEL, ENABLE);

  /* 等待DMA传输完成 */
  while (DMA_GetFlagStatus(USART_TX_DMA_FLAG_TC) == RESET)
  {
  }

  /* 清除DMA传输完成标志 */
  DMA_ClearFlag(USART_TX_DMA_FLAG_TC);

  /* 此时CPU是空闲的，可以干其他的事情 */
  while (1)
  {
    Delay(0xFFFFF);
  }
}

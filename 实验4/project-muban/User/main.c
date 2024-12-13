//main.c
#include "stm32f10x.h"
#include "bsp_led.h"
#define SOFT_DELAY Delay(0x0FFFFF);
void Delay(__IO u32 nCount); 
int main(void){
LED_GPIO_Config(); /* LED 端口初始化 */
while (1) {
LED1_ON; // 亮
SOFT_DELAY;
LED1_OFF; // 灭
LED2_ON; // 亮
SOFT_DELAY;
LED2_OFF; // 灭
LED3_ON; // 亮
SOFT_DELAY;
LED3_OFF; // 灭
}
}
void Delay(__IO uint32_t nCount) //简单的延时函数
{ for(; nCount != 0; nCount--);}
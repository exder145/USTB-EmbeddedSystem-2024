
void delay(unsigned int cnt){
  
	while(cnt>=1)(cnt--);

  }


void SystemInit(void)
{
	// 此函数会被startup文件调用；
	// 函数体为空，目的是为了骗过编译器不报错
}



int main(void) {
    // 打开 GPIOB 端口的时钟
    *(unsigned int *)0x40021018 |= (1 << 3);

    // 配置IO口PB0、PB1和PB2为输出
    *(unsigned int *)0x40010C00 |= (1 << (4 * 0)); // PB0配置为输出


    // 点亮PB0引脚上的Green灯
    *(unsigned int *)0x40010C0C &= ~(1 << 0);
    delay(1000000); // 延时
	
    // 关闭PB0引脚上的Green灯
    *(unsigned int *)0x40010C0C |= (1 << 0);
    delay(1000000); // 延时
	
    // 点亮PB1引脚上的Blue灯
	  *(unsigned int *)0x40010C00 |= (1 << (4 * 1)); // PB1配置为输出
	
    *(unsigned int *)0x40010C0C &= ~(1 << 1);
    delay(1000000); // 延时
	
    // 关闭PB1引脚上的Blue灯
    *(unsigned int *)0x40010C0C |= (1 << 1);
    delay(1000000); // 延时
		
		// 点亮PB2引脚上的Red灯
		*(unsigned int *)0x40010C00 |= (1 << (4 * 5)); // PB2配置为输出
				
    *(unsigned int *)0x40010C0C &= ~(1 << 5);
    delay(1000000); // 延时
		
    // 关闭PB2引脚上的Red灯
    *(unsigned int *)0x40010C0C |= (1 << 5);
    delay(1000000); // 延时
		
    return 0;
}




// 学会以下两项技能：
// 1） 从数据手册查找寄存器的绝对地址
// 2） 学会对寄存器的特定位进行置1(也称置位、set)和置0(也称清0,clr)操作，置位:   |= （mask)   ，清0: &=~（mask)

// 1、点亮/熄灭其他的两个LED灯

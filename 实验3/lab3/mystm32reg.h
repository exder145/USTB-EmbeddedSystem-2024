// 用来存放STM32寄存器映射的代码

// 外设  perirhral

#define  PERIPH_BASE               ((unsigned int)0x40000000)
#define  APB1PERIPH_BASE           PERIPH_BASE
#define  APB2PERIPH_BASE          (PERIPH_BASE + 0x10000)
#define  AHBPERIPH_BASE           (PERIPH_BASE + 0x20000)


#define  RCC_BASE                (AHBPERIPH_BASE + 0x1000)
#define  RCC_APB2ENR            *(unsigned int*)(RCC_BASE + 0x18)
	
//添加代码

// 添加 GPIOA 的定义
#define GPIOA_BASE               (APB2PERIPH_BASE + 0x0800)  // GPIOA 基地址
#define GPIOA_CRL                *(unsigned int *)(GPIOA_BASE + 0x00)  // 控制寄存器
#define GPIOA_IDR                *(unsigned int *)(GPIOA_BASE + 0x08)  // 输入数据寄存器

//添加 GPIOB 的定义
#define GPIOB_BASE              (APB2PERIPH_BASE + 0x0C00)  // GPIOB 基地址
#define GPIOB_CRL               *(unsigned int *)(GPIOB_BASE + 0x00)  // 控制寄存器
#define GPIOB_ODR               *(unsigned int *)(GPIOB_BASE + 0x0C)  // 输出数据寄存器

	




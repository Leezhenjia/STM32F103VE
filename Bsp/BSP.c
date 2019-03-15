#include "includes.h"


/*
 *	函数名	:	SysTick_init
 *	描述	:	配置 SysTick 定时器
 *	输入	:	无
 *	输出	:	无
 */

void SysTick_init(void)
{
	SysTick_Config(SystemCoreClock/OS_TICKS_PER_SEC);	//初始化并使能	SysTick	定时器SystemFrequency
}

/*
 *	函数名	:	BSPInit
 *	描述	:	时钟初始化,硬件初始化
 *	输入	:	无
 *	输出	:	无
 */
 
void BSPInit(void)
{
	SystemInit();		//配置系统时钟为72M
	SysTick_init();;	//初始化并使能 Systick 定时器
	LED_GPIO_Config();	//LED端口初始化
    ILI9341_Init();    //LCD 初始化
	USART_Config();     //串口初始化
    ILI9341_GramScan(6);//显示屏模式
}


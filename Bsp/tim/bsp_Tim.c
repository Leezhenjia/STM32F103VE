
// 基本定时器TIMx,x[6,7]定时初始化函数

#include "bsp_tim.h"

// 中断优先级配置
static void BASIC_TIM7_NVIC_Config(void)
{
    NVIC_InitTypeDef NVIC_InitStructure; 
    // 设置中断组为0
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);		
		// 设置中断来源
    NVIC_InitStructure.NVIC_IRQChannel = BASIC_TIM7_IRQ ;	
		// 设置主优先级为 0
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;	 
	  // 设置抢占优先级为4
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 4;	
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
}


//设置0.52ms产生一次中断,即0.5字符时间

static void BASIC_TIM7_Mode_Config(void)
{
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
		
		// 开启定时器时钟,即内部时钟CK_INT=72M
    BASIC_TIM7_APBxClock_FUN(BASIC_TIM7_CLK, ENABLE);
	
		// 自动重装载寄存器的值，累计TIM_Period+1个频率后产生一个更新或者中断
    TIM_TimeBaseStructure.TIM_Period = BASIC_TIM7_Period;	

	  // 时钟预分频数为
    TIM_TimeBaseStructure.TIM_Prescaler= BASIC_TIM7_Prescaler;
	
	
	  // 初始化定时器
    TIM_TimeBaseInit(BASIC_TIM7, &TIM_TimeBaseStructure);
		
		// 清除计数器中断标志位
    TIM_ClearFlag(BASIC_TIM7, TIM_FLAG_Update);
	 
		// 开启计数器中断
    TIM_ITConfig(BASIC_TIM7,TIM_IT_Update,ENABLE);
		
		// 使能计数器
    TIM_Cmd(BASIC_TIM7, ENABLE);	
    
    //暂时关闭定时器时钟,等待使用
	BASIC_TIM7_APBxClock_FUN(BASIC_TIM7_CLK, DISABLE);	
}



void TIM7Init(void)
{
	BASIC_TIM7_NVIC_Config();
	BASIC_TIM7_Mode_Config();
}
/*********************************************END OF FILE**********************/

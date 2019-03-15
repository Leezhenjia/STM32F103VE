/**
  ******************************************************************************
  * @file    Project/STM32F10x_StdPeriph_Template/stm32f10x_it.c 
  * @author  MCD Application Team
  * @version V3.5.0
  * @date    08-April-2011
  * @brief   Main Interrupt Service Routines.
  *          This file provides template for all exceptions handler and 
  *          peripherals interrupt service routine.
  ******************************************************************************
  * @attention
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTI
  
  AL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2011 STMicroelectronics</center></h2>
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
//#include "stm32f10x_it.h"
#include "includes.h"


extern OS_EVENT *Usart_Send_Mbox;
extern OS_EVENT *Tim6_Analysis_Mbox;
volatile uint32_t time = 0; //字符时间计数

/** @addtogroup STM32F10x_StdPeriph_Template
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/******************************************************************************/
/*            Cortex-M3 Processor Exceptions Handlers                         */
/******************************************************************************/

/**
  * @brief  This function handles NMI exception.
  * @param  None
  * @retval None
  */
void NMI_Handler(void)
{
}

/**
  * @brief  This function handles Hard Fault exception.
  * @param  None
  * @retval None
  */
void HardFault_Handler(void)
{
  /* Go to infinite loop when Hard Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Memory Manage exception.
  * @param  None
  * @retval None
  */
void MemManage_Handler(void)
{
  /* Go to infinite loop when Memory Manage exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Bus Fault exception.
  * @param  None
  * @retval None
  */
void BusFault_Handler(void)
{
  /* Go to infinite loop when Bus Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Usage Fault exception.
  * @param  None
  * @retval None
  */
void UsageFault_Handler(void)
{
  /* Go to infinite loop when Usage Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles SVCall exception.
  * @param  None
  * @retval None
  */
void SVC_Handler(void)
{
}

/**
  * @brief  This function handles Debug Monitor exception.
  * @param  None
  * @retval None
  */
void DebugMon_Handler(void)
{
}

/**
  * @brief  This function handles PendSVC exception.
  * @param  None
  * @retval None
  */
void PendSV_Handler(void)
{
}

/**
  * @brief  This function handles SysTick Handler.
  * @param  None
  * @retval None
  */
void SysTick_Handler(void)
{
	OSIntEnter();
	OSTimeTick();
	OSIntExit();
}

/************************************************************************
    作者： lizhenjia 
    创建日期：2019.3.15 
    函数功能说明： USART中断函数,唤醒接收任务
    输入参数： 无
    参数名称：无
    输出参数： 接收数据
    参数名称：ucTemp
    返回值： 无
    函数扇出清单： 
    函数扇入清单： 
    函数体中用到的公共资源：
    更新后的上述资源： 
*************************************************************************/
void DEBUG_USART_IRQHandler(void)
{
    uint8_t ucTemp;
    
    OSIntEnter();
	if (USART_GetITStatus(DEBUG_USARTx,USART_IT_RXNE) != RESET)
	{		
		ucTemp = USART_ReceiveData(DEBUG_USARTx);//读取接收到的字节
        OSMboxPost(Usart_Send_Mbox, (void *)&ucTemp);   //发送给接收任务
	}	
    OSIntExit();    
}

/************************************************************************
    作者： lizhenjia 
    创建日期：2019.3.15 
    函数功能说明： 字符时间定时
    输入参数： 无
    参数名称：无
    输出参数： 无
    参数名称：无
    返回值： 无
    函数扇出清单： 
    函数扇入清单： 
    函数体中用到的公共资源：
    更新后的上述资源： 
*************************************************************************/
void  BASIC_TIM6_IRQHandler(void)
{
    OSIntEnter();
	if (TIM_GetITStatus(BASIC_TIM6, TIM_IT_Update) != RESET )
	{
		TIM_ClearITPendingBit(BASIC_TIM6, TIM_FLAG_Update);
		time++;
        LED1_ON;
		if (time > 7)
		{
			BASIC_TIM6_APBxClock_FUN(BASIC_TIM6_CLK, DISABLE);//超过3.5字符时间不再接收,关闭字符累计计时
			time = 0;
            OSMboxPost(Tim6_Analysis_Mbox, (void *)1);   //发送给解析任务
		}
	}
    OSIntExit();
}
/******************************************************************************/
/*                 STM32F10x Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_stm32f10x_xx.s).                                            */
/******************************************************************************/

/**
  * @brief  This function handles PPP interrupt request.
  * @param  None
  * @retval None
  */
/*void PPP_IRQHandler(void)
{
}*/

/**
  * @}
  */ 


/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/

/***************************************************************************
    版权所有：lizhenjia
    版本号： 1.00 
    文件名： app.c 
    生成日期：2019.3.15 
    作者： lizhenjia 
    功能说明：uCOS II 任务
    与所属工程文件的关系： 任务文件
    其它说明：无
    修改记录：
            2019-03-19 lizhenjia
            增加触摸屏选择功能码功能
***************************************************************************/

#include "includes.h"

//定义五个函数栈
//TODO: 栈大小后续修改
OS_STK send_task_stk[SEND_TASK_STK_SIZE]; 
OS_STK receive_task_stk[RECEIVE_TASK_STK_SIZE]; 
OS_STK analysis_task_stk[ANALYSIS_TASK_STK_SIZE]; 
OS_STK disp_task_stk[DISP_TASK_STK_SIZE]; 
OS_STK touch_task_stk[TOUCH_TASK_STK_SIZE];
 
//邮箱,将USART收到数据发送到Receive任务
OS_EVENT *Usart_Send_Mbox;  
//邮箱,定时器7通知Analysis任务开始解析数据
OS_EVENT *Tim7_Analysis_Mbox;  


uint16_t RX_CNT = 0;    //接收字节计数


void Task_Start(void *p_arg)
{
	(void)p_arg;	//规避编译器警告
    
    Usart_Send_Mbox = OSMboxCreate((void *)0);
    Tim7_Analysis_Mbox = OSMboxCreate((void *)0);
    
#if OS_STK_GROWTH == 1
    OSTaskCreate(Task_Send, (void *)0, &send_task_stk[SEND_TASK_STK_SIZE - 1], SEND_TASK_PRIO);
    OSTaskCreate(Task_Receive, (void *)0, &receive_task_stk[RECEIVE_TASK_STK_SIZE - 1], RECEIVE_TASK_PRIO);
    OSTaskCreate(Task_Analysis, (void *)0, &analysis_task_stk[ANALYSIS_TASK_STK_SIZE - 1], ANALYSIS_TASK_PRIO);
    OSTaskCreate(Task_Disp, (void *)0, &disp_task_stk[DISP_TASK_STK_SIZE - 1], DISP_TASK_PRIO);
    OSTaskCreate(Task_Touch, (void *)0, &touch_task_stk[TOUCH_TASK_STK_SIZE - 1], TOUCH_TASK_PRIO);
#else
    OSTaskCreate(Task_Send, (void *)0, &send_task_stk[0], SEND_TASK_PRIO);
    OSTaskCreate(Task_Receive, (void *)0, &receive_task_stk[0], RECEIVE_TASK_PRIO);
    OSTaskCreate(Task_Analysis, (void *)0, &analysis_task_stk[0], ANALYSIS_TASK_PRIO);
    OSTaskCreate(Task_Disp, (void *)0, &disp_task_stk[0], DISP_TASK_PRIO);
    OSTaskCreate(Task_Touch, (void *)0, &touch_task_stk[0], TOUCH_TASK_PRIO);
#endif
    
	OSTaskDel(OS_PRIO_SELF);   //删除起始任务
}

void Task_Send(void *p_arg)
{
	(void)p_arg;	//规避编译器警告
	
	while (1)
	{
        if (page != 0)
        {
            ModbusRTU();    //开始发送指令
        }
		OSTimeDlyHMSM(0, 0, 2, 0);  //挂起2s等待接收解析发送
	}
}

void Task_Receive(void *p_arg)
{
	uint8_t *Temp;
    uint8_t err = 0;
    
    
    (void)p_arg;	//规避编译器警告 

    
	while (1)
	{
        Temp = (uint8_t *)OSMboxPend(Usart_Send_Mbox, 0, &err); //等待接收USART中断的邮箱消息
        if (RX_CNT < 2047 && time <= 3)
        {
            if (0 == RX_CNT)
            {
                BASIC_TIM7_APBxClock_FUN(BASIC_TIM7_CLK, ENABLE);//开启TIM6计时,累计帧间断时间
            }
            RX_BUFF[RX_CNT] = *Temp;
            RX_CNT++;
            time = 0;
        }
	}
}

void Task_Analysis(void *p_arg)
{
    uint8_t err;
    
    
	(void)p_arg;	//规避编译器警告
	
    
	while (1)
	{
        OSMboxPend(Tim7_Analysis_Mbox, 0, &err);    //接收数据完成
        MasterAnalyService();   //开始解析 
	}
}

void Task_Disp(void *p_arg)
{
	(void)p_arg;	//规避编译器警告
	
    
	while (1)
	{
        Display();
        OSTimeDlyHMSM(0, 0, 0, 900);
	}
}
void Task_Touch(void *p_arg)
{
    (void)p_arg;    //规避编译器警告
    
    
    while (1)
    {
        //触摸检测函数，本函数至少10ms调用一次
        buttonRenew();
        XPT2046_TouchEvenHandler();
    }
}

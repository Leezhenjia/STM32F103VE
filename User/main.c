/***************************************************************************
    版权所有：lizhenjia 
    版本号： 1.00 
    文件名： main.c 
    生成日期：2019.3.15 
    作者： lizhenjia 
    功能说明：MDOBUS主机规约实现,与PC模拟从机进行通信 
    与所属工程文件的关系： 主文件
    其它说明：无
    修改记录：无
***************************************************************************/
	
#include "includes.h"

OS_STK start_task_stk[STARTUP_TASK_STK_SIZE]; 


/**
  * @brief  主函数
  * @param  无  
  * @retval 无
  */
int main(void)
{	
	BSPInit();  //外设初始化
	OSInit();   //系统初始化
	
#if OS_STK_GROWTH == 1  //自适应栈向上向下生长
	OSTaskCreate(Task_Start, (void *)0, &start_task_stk[STARTUP_TASK_STK_SIZE - 1], START_TASK_PRIO);
#else 
	OSTaskCreate(Task_Start, (void *)0, &start_task_stk[0], START_TASK_PRIO);
#endif
	
	OSStart();  //开始多任务调度
    return 0;
}


/*********************************************END OF FILE**********************/

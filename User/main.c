/***************************************************************************
    ��Ȩ���У�lizhenjia 
    �汾�ţ� 1.00 
    �ļ����� main.c 
    �������ڣ�2019.3.15 
    ���ߣ� lizhenjia 
    ����˵����MDOBUS������Լʵ��,��PCģ��ӻ�����ͨ�� 
    �����������ļ��Ĺ�ϵ�� ���ļ�
    ����˵������
    �޸ļ�¼����
***************************************************************************/
	
#include "includes.h"

OS_STK start_task_stk[STARTUP_TASK_STK_SIZE]; 


/**
  * @brief  ������
  * @param  ��  
  * @retval ��
  */
int main(void)
{	
	BSPInit();  //�����ʼ��
	OSInit();   //ϵͳ��ʼ��
	
#if OS_STK_GROWTH == 1  //����Ӧջ������������
	OSTaskCreate(Task_Start, (void *)0, &start_task_stk[STARTUP_TASK_STK_SIZE - 1], START_TASK_PRIO);
#else 
	OSTaskCreate(Task_Start, (void *)0, &start_task_stk[0], START_TASK_PRIO);
#endif
	
	OSStart();  //��ʼ���������
    return 0;
}


/*********************************************END OF FILE**********************/

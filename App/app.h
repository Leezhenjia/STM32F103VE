#ifndef __APP_H__
#define __APP_H__
/**************用户任务声明************/
void Task_Start(void *p_arg);
void Task_Send(void *p_arg);
void Task_Receive(void *p_arg);
void Task_Analysis(void *p_arg);
void Task_Disp(void *p_arg);

#endif	//_APP_H_


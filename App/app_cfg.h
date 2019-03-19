#ifndef __APP_CFG_H__
#define __APP_CFG_H__

/***************设置任务优先级*****************/
#define START_TASK_PRIO 3
#define SEND_TASK_PRIO 4
#define RECEIVE_TASK_PRIO 5
#define ANALYSIS_TASK_PRIO 6
#define DISP_TASK_PRIO 7
#define TOUCH_TASK_PRIO 8

/***************设置栈大小(单位为 OS_STK	)**************/
#define STARTUP_TASK_STK_SIZE 80
#define SEND_TASK_STK_SIZE 80
#define RECEIVE_TASK_STK_SIZE 80
#define ANALYSIS_TASK_STK_SIZE 80
#define DISP_TASK_STK_SIZE 80
#define TOUCH_TASK_STK_SIZE 80

#endif

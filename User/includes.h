#ifndef __INCLUDES_H__
#define __INCLUDES_H__

#include "stm32f10x.h"
#include "stm32f10x_it.h"   //中断相关
#include "stm32f10x_rcc.h"	//定时器相关

#include "ucos_ii.h"		//ucosii系统函数头文件

#include "BSP.h"			//开发板相关函数
#include "app.h"			//用户任务函数
#include "bsp_led.h"		//led驱动函数
#include "bsp_ili9341_lcd.h"//LCD显示屏驱动函数
#include "bsp_usart.h"      //usart驱动函数
#include "Modbus_m.h"       //MODBUS规约函数
#include "CRC.h"            //CRC冗余检验函数
#include "bsp_tim.h"     //定时器函数

#endif //__INCLUDES_H__

#ifndef __DISPLAY_H__
#define __DISPLAY_H__

extern uint8_t   SlaverAddr;    //从机地址
extern uint8_t   Fuction;      // 功能码
extern uint16_t  StartAddr;    //起始地址
extern uint16_t  ValueOrLenth;  //数据or长度
extern uint8_t page;            //页数

void Display(void);
void DisplayPage0(void);
void DisplayPage1(void);
void DisplayPage2(void);
void ILI9341_DispVariable_EN(uint16_t line, char * words, uint16_t variable	);//变量显示

#endif /*__DISPLAY_H__*/

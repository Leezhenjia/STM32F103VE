#ifndef __DISPLAY_H__
#define __DISPLAY_H__

extern uint8_t   SlaverAddr;    //�ӻ���ַ
extern uint8_t   Fuction;      // ������
extern uint16_t  StartAddr;    //��ʼ��ַ
extern uint16_t  ValueOrLenth;  //����or����
extern uint8_t page;            //ҳ��

void Display(void);
void DisplayPage0(void);
void DisplayPage1(void);
void DisplayPage2(void);
void ILI9341_DispVariable_EN(uint16_t line, char * words, uint16_t variable	);//������ʾ

#endif /*__DISPLAY_H__*/

/***************************************************************************
    ��Ȩ���У�lizhenjia 
    �汾�ţ� 1.00 
    �ļ����� touchapp.c 
    �������ڣ�2019.3.19 
    ���ߣ� lizhenjia 
    ����˵�������ɴ����尴ť,�������¼�
    �����������ļ��Ĺ�ϵ�� ������Ӧ�ú���
    ����˵������
    �޸ļ�¼����
***************************************************************************/

#include "includes.h"
 
/*��ť�ṹ������*/
Touch_Button button[PAGE_NUM][BUTTON_LARGEST_NUM];

//ҳ��
//0: Modbus������; 1: 03���������; 2: 06���ܽ���
uint8_t page = 0;


static void Draw_Button_Rectangle(void *btn);
static void Command_Enter03(void *btn);
static void Command_Enter06(void *btn);
static void Command_Add_Slaver(void *btn);
static void Command_Sub_Slaver(void *btn);
static void Command_Add_Start_Addr(void *btn);
static void Command_Sub_Start_Addr(void *btn);
static void Command_Add_Num(void *btn);
static void Command_Sub_Num(void *btn);
static void Command_Return(void *btn);


/**
* @brief  Palette_HomeInit Modbus�����滭���ʼ��
* @param  ��
* @retval ��
*/
void Palette_HomeInit(uint8_t LCD_Mode)
{   
	ILI9341_GramScan ( LCD_Mode );

    /* ��ʼ����ť */
    Touch_Button_Init();
  
    /* ��水ť */
    buttonRenew();
}

/**
* @brief  buttonRenew ���°�ť
* @param  ��
* @retval ��
*/
void buttonRenew(void)
{
  
    uint8_t i;

  
    /* ��水ť */
    switch (page)
    {
        case 0:
            for (i = 0; i < BUTTON_HOME_NUM; i++)
            {
                button[page][i].draw_btn(&button[page][i]);
            }
            break;
        case 1:
            for (i = 0; i < BUTTON_03_NUM; i++)
            {
                button[page][i].draw_btn(&button[page][i]);
            }
            break;
        case 2:
            for (i = 0; i < BUTTON_06_NUM; i++)
            {
                button[page][i].draw_btn(&button[page][i]);
            }
            break;
        default:
            break;
    }
    
    
}

/**
* @brief  Touch_Button_Init ��ʼ����ť����
* @param  ��
* @retval ��
*/
void Touch_Button_Init(void)
{
    /*�������һ�а�ť*/
    button[0][0].start_x = BUTTON_START_X;
    button[0][0].start_y = BUTTON_BLOCK_HEIGHT * 2;
    button[0][0].end_x = BUTTON_START_X + BUTTON_BLOCK_WIDTH;
    button[0][0].end_y = BUTTON_BLOCK_HEIGHT * 3;
    button[0][0].para = CL_BUTTON_GREY;
    button[0][0].touch_flag = 0;  
    button[0][0].draw_btn = Draw_Button_Rectangle ;
    button[0][0].btn_command = Command_Enter03 ;//����03����
  
    button[0][1].start_x = BUTTON_START_X;
    button[0][1].start_y = BUTTON_BLOCK_HEIGHT * 3;
    button[0][1].end_x = BUTTON_START_X + BUTTON_BLOCK_WIDTH;
    button[0][1].end_y = BUTTON_BLOCK_HEIGHT * 4;
    button[0][1].para = CL_BUTTON_GREY;
    button[0][1].touch_flag = 0;  
    button[0][1].draw_btn = Draw_Button_Rectangle ;
    button[0][1].btn_command = Command_Enter06 ;//����06����

    /*������ڶ��а�ť*/
    button[0][2].start_x = BUTTON_START_X + BUTTON_BLOCK_WIDTH;
    button[0][2].start_y = BUTTON_BLOCK_HEIGHT * 1;
    button[0][2].end_x = BUTTON_START_X + BUTTON_BLOCK_WIDTH * 2;
    button[0][2].end_y = BUTTON_BLOCK_HEIGHT * 2;
    button[0][2].para = CL_BUTTON_GREY;
    button[0][2].touch_flag = 0;  
    button[0][2].draw_btn = Draw_Button_Rectangle ;
    button[0][2].btn_command = Command_Add_Slaver ;//�ӻ���ַ��1
  
    button[0][3].start_x = BUTTON_START_X + BUTTON_BLOCK_WIDTH * 2;
    button[0][3].start_y = BUTTON_BLOCK_HEIGHT * 1;
    button[0][3].end_x = BUTTON_START_X + BUTTON_BLOCK_WIDTH * 3;
    button[0][3].end_y = BUTTON_BLOCK_HEIGHT * 2;
    button[0][3].para = CL_BUTTON_GREY;
    button[0][3].touch_flag = 0;  
    button[0][3].draw_btn = Draw_Button_Rectangle ;
    button[0][3].btn_command = Command_Sub_Slaver ;//�ӻ���ַ��1
  
    /*������03�����һ�а�ť*/
    button[1][0].start_x = BUTTON_START_X + BUTTON_BLOCK_WIDTH;
    button[1][0].start_y = BUTTON_BLOCK_HEIGHT * 1;
    button[1][0].end_x = BUTTON_START_X + BUTTON_BLOCK_WIDTH * 2;
    button[1][0].end_y = BUTTON_BLOCK_HEIGHT * 2;
    button[1][0].para = CL_BUTTON_GREY;
    button[1][0].touch_flag = 0;  
    button[1][0].draw_btn = Draw_Button_Rectangle ;
    button[1][0].btn_command = Command_Add_Start_Addr ;//��ʼ��ַ��1
  
    button[1][1].start_x = BUTTON_START_X + BUTTON_BLOCK_WIDTH * 2;
    button[1][1].start_y = BUTTON_BLOCK_HEIGHT * 1;
    button[1][1].end_x = BUTTON_START_X + BUTTON_BLOCK_WIDTH * 3;
    button[1][1].end_y = BUTTON_BLOCK_HEIGHT * 2;
    button[1][1].para = CL_BUTTON_GREY;
    button[1][1].touch_flag = 0;  
    button[1][1].draw_btn = Draw_Button_Rectangle ;
    button[1][1].btn_command = Command_Sub_Start_Addr ;//��ʼ��ַ��1
  
    /*������03����ڶ��а�ť*/
    button[1][2].start_x = BUTTON_START_X + BUTTON_BLOCK_WIDTH;
    button[1][2].start_y = BUTTON_BLOCK_HEIGHT * 2;
    button[1][2].end_x = BUTTON_START_X + BUTTON_BLOCK_WIDTH * 2;
    button[1][2].end_y = BUTTON_BLOCK_HEIGHT * 3;
    button[1][2].para = CL_BUTTON_GREY;
    button[1][2].touch_flag = 0;  
    button[1][2].draw_btn = Draw_Button_Rectangle ;
    button[1][2].btn_command = Command_Add_Num ;//�Ĵ���������1
  
    button[1][3].start_x = BUTTON_START_X + BUTTON_BLOCK_WIDTH * 2;
    button[1][3].start_y = BUTTON_BLOCK_HEIGHT * 2;
    button[1][3].end_x = BUTTON_START_X + BUTTON_BLOCK_WIDTH * 3;
    button[1][3].end_y = BUTTON_BLOCK_HEIGHT * 3;
    button[1][3].para = CL_BUTTON_GREY;
    button[1][3].touch_flag = 0;  
    button[1][3].draw_btn = Draw_Button_Rectangle ;
    button[1][3].btn_command = Command_Sub_Num ;//�Ĵ���������1
    
    /*������03���淵�ذ�ť*/
    button[1][4].start_x = BUTTON_START_X + BUTTON_BLOCK_WIDTH * 4;
    button[1][4].start_y = BUTTON_BLOCK_HEIGHT * 12;
    button[1][4].end_x = BUTTON_START_X + BUTTON_BLOCK_WIDTH * 5;
    button[1][4].end_y = BUTTON_BLOCK_HEIGHT * 13;
    button[1][4].para = CL_BUTTON_GREY;
    button[1][4].touch_flag = 0;  
    button[1][4].draw_btn = Draw_Button_Rectangle ;
    button[1][4].btn_command = Command_Return;//���������� 
  

    /*������06�����һ�а�ť*/
    button[2][0].start_x = BUTTON_START_X + BUTTON_BLOCK_WIDTH;
    button[2][0].start_y = BUTTON_BLOCK_HEIGHT * 1;
    button[2][0].end_x = BUTTON_START_X + BUTTON_BLOCK_WIDTH * 2;
    button[2][0].end_y = BUTTON_BLOCK_HEIGHT * 2;
    button[2][0].para = CL_BUTTON_GREY;
    button[2][0].touch_flag = 0;  
    button[2][0].draw_btn = Draw_Button_Rectangle ;
    button[2][0].btn_command = Command_Add_Start_Addr ;//��ʼ��ַ��1
  
    button[2][1].start_x = BUTTON_START_X + BUTTON_BLOCK_WIDTH * 2;
    button[2][1].start_y = BUTTON_BLOCK_HEIGHT * 1;
    button[2][1].end_x = BUTTON_START_X + BUTTON_BLOCK_WIDTH * 3;
    button[2][1].end_y = BUTTON_BLOCK_HEIGHT * 2;
    button[2][1].para = CL_BUTTON_GREY;
    button[2][1].touch_flag = 0;  
    button[2][1].draw_btn = Draw_Button_Rectangle ;
    button[2][1].btn_command = Command_Sub_Start_Addr ;//��ʼ��ַ��1
  
    /*������06����ڶ��а�ť*/
    button[2][2].start_x = BUTTON_START_X + BUTTON_BLOCK_WIDTH;
    button[2][2].start_y = BUTTON_BLOCK_HEIGHT * 2;
    button[2][2].end_x = BUTTON_START_X + BUTTON_BLOCK_WIDTH * 2;
    button[2][2].end_y = BUTTON_BLOCK_HEIGHT * 3;
    button[2][2].para = CL_BUTTON_GREY;
    button[2][2].touch_flag = 0;  
    button[2][2].draw_btn = Draw_Button_Rectangle ;
    button[2][2].btn_command = Command_Add_Num ;//�Ĵ���������1
  
    button[2][3].start_x = BUTTON_START_X + BUTTON_BLOCK_WIDTH * 2;
    button[2][3].start_y = BUTTON_BLOCK_HEIGHT * 2;
    button[2][3].end_x = BUTTON_START_X + BUTTON_BLOCK_WIDTH * 3;
    button[2][3].end_y = BUTTON_BLOCK_HEIGHT * 3;
    button[2][3].para = CL_BUTTON_GREY;
    button[2][3].touch_flag = 0;  
    button[2][3].draw_btn = Draw_Button_Rectangle ;
    button[2][3].btn_command = Command_Sub_Num ;//�Ĵ���������1
    
    /*������06���淵�ذ�ť*/
    button[2][4].start_x = BUTTON_START_X + BUTTON_BLOCK_WIDTH * 4;
    button[2][4].start_y = BUTTON_BLOCK_HEIGHT * 12;
    button[2][4].end_x = BUTTON_START_X + BUTTON_BLOCK_WIDTH * 5;
    button[2][4].end_y = BUTTON_BLOCK_HEIGHT * 13;
    button[2][4].para = CL_BUTTON_GREY;
    button[2][4].touch_flag = 0;  
    button[2][4].draw_btn = Draw_Button_Rectangle ;
    button[2][4].btn_command = Command_Return;//����������
}

/**
* @brief  Touch_Button_Down ����������ʱ���õĺ������ɴ���������
* @param  x ����λ�õ�x����
* @param  y ����λ�õ�y����
* @retval ��
*/
void Touch_Button_Down(uint16_t x,uint16_t y)
{
    uint8_t i;
    uint8_t num;
    
    
    switch (page)
    {
        case 0:
            num = BUTTON_HOME_NUM;
            break;
        case 1:
            num = BUTTON_03_NUM;
            break;
        case 2:
            num = BUTTON_06_NUM;
        break;
    }
    for (i = 0; i < num; i++)
    {
        /* �������˰�ť */
        if (x <= button[page][i].end_x && y <= button[page][i].end_y && y >= button[page][i].start_y && x >= button[page][i].start_x )
        {
            if (button[page][i].touch_flag == 0)     /*ԭ����״̬Ϊû�а��£������״̬*/
            {
                button[page][i].touch_flag = 1;         /* ��¼���±�־ */
      
                button[page][i].draw_btn(&button[page][i]);  /*�ػ水ť*/
            }        
      
        }
        else if (button[page][i].touch_flag == 1) /* �����Ƴ��˰����ķ�Χ��֮ǰ�а��°�ť */
        {
            button[page][i].touch_flag = 0;         /* ������±�־���ж�Ϊ�����*/
      
            button[page][i].draw_btn(&button[page][i]);   /*�ػ水ť*/
        }

    }

}

/**
* @brief  Touch_Button_Up �������ͷ�ʱ���õĺ������ɴ���������
* @param  x ��������ͷ�ʱ��x����
* @param  y ��������ͷ�ʱ��y����
* @retval ��
*/
void Touch_Button_Up(uint16_t x,uint16_t y)
{
    uint8_t i;
    uint8_t num;
    
    
    switch (page)
    {
        case 0:
            num = BUTTON_HOME_NUM;
            break;
        case 1:
            num = BUTTON_03_NUM;
            break;
        case 2:
            num = BUTTON_06_NUM;
        break;
    }   
    for (i = 0; i < num; i++)
    {
        /* �����ڰ�ť�����ͷ� */
        if ((x < button[page][i].end_x && x > button[page][i].start_x && y < button[page][i].end_y && y > button[page][i].start_y))
        {        
            button[page][i].touch_flag = 0;       /*�ͷŴ�����־*/
        
            button[page][i].draw_btn(&button[page][i]); /*�ػ水ť*/        
      
            button[page][i].btn_command(&button[page][i]);  /*ִ�а����Ĺ�������*/
        
            break;
        }
    }  

}


/**
* @brief  Draw_Button_Rectangle ������ť����溯��
* @param  btn Touch_Button ���͵İ�������
* @retval ��
*/
static void Draw_Button_Rectangle(void *btn)
{
    Touch_Button *ptr = (Touch_Button *)btn;
//    LCD_SetColors(CL_BLUE4, CL_WHITE);
//    ILI9341_DrawRectangle(ptr->start_x, ptr->start_y, ptr->end_x - ptr->start_x, ptr->end_y - ptr->start_y, 0);
}



/**
* @brief  Command_Enter03 ���빦����03ѡ�����
* @param  btn Touch_Button ���͵İ�������
* @retval ��
*/
static void Command_Enter03(void *btn)
{
    (void)btn;
    page = 1;
    Fuction = 0x03;
    buttonRenew();
}

/**
* @brief  Command_Enter06 ���빦����06ѡ�����
* @param  btn Touch_Button ���͵İ�������
* @retval ��
*/
static void Command_Enter06(void *btn)
{
    (void)btn;
    page = 2;
    Fuction = 0x06;
    buttonRenew();
}


/**
* @brief  Command_Add_Slaver �ӻ���ַ+1
* @param  btn Touch_Button ���͵İ�������
* @retval ��
*/
static void Command_Add_Slaver(void *btn)
{
    (void)btn;
    SlaverAddr++;
}

/**
* @brief  Command_Sub_Slaver �ӻ���ַ-1
* @param  btn Touch_Button ���͵İ�������
* @retval ��
*/
static void Command_Sub_Slaver(void *btn)
{
    (void)btn;
    SlaverAddr--;
}

/**
* @brief  Command_Add_Start_Addr ��ʼ��ַ+1
* @param  btn Touch_Button ���͵İ�������
* @retval ��
*/
static void Command_Add_Start_Addr(void *btn)
{
    (void)btn;
    StartAddr++;
}

/**
* @brief  Command_Sub_Start_Addr ��ʼ��ַ-1
* @param  btn Touch_Button ���͵İ�������
* @retval ��
*/
static void Command_Sub_Start_Addr(void *btn)
{
    (void)btn;
    StartAddr--;
}

/**
* @brief  Command_Add_Num ����+1
* @param  btn Touch_Button ���͵İ�������
* @retval ��
*/
static void Command_Add_Num(void *btn)
{
    (void)btn;
    ValueOrLenth++;
}

/**
* @brief  Command_Sub_Num ����-1
* @param  btn Touch_Button ���͵İ�������
* @retval ��
*/
static void Command_Sub_Num(void *btn)
{
    (void)btn;
    ValueOrLenth--;
}


/**
* @brief  Command_Return ����������
* @param  btn Touch_Button ���͵İ�������
* @retval ��
*/
static void Command_Return(void *btn)
{
    (void)btn;
    page = 0;
}
/* ------------------------------------------end of file---------------------------------------- */




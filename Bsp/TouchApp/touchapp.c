/***************************************************************************
    版权所有：lizhenjia 
    版本号： 1.00 
    文件名： touchapp.c 
    生成日期：2019.3.19 
    作者： lizhenjia 
    功能说明：生成触摸板按钮,处理触摸事件
    与所属工程文件的关系： 触摸板应用函数
    其它说明：无
    修改记录：无
***************************************************************************/

#include "includes.h"
 
/*按钮结构体数组*/
Touch_Button button[PAGE_NUM][BUTTON_LARGEST_NUM];

//页面
//0: Modbus主界面; 1: 03功能码界面; 2: 06功能界面
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
* @brief  Palette_HomeInit Modbus主界面画板初始化
* @param  无
* @retval 无
*/
void Palette_HomeInit(uint8_t LCD_Mode)
{   
	ILI9341_GramScan ( LCD_Mode );

    /* 初始化按钮 */
    Touch_Button_Init();
  
    /* 描绘按钮 */
    buttonRenew();
}

/**
* @brief  buttonRenew 更新按钮
* @param  无
* @retval 无
*/
void buttonRenew(void)
{
  
    uint8_t i;

  
    /* 描绘按钮 */
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
* @brief  Touch_Button_Init 初始化按钮参数
* @param  无
* @retval 无
*/
void Touch_Button_Init(void)
{
    /*主界面第一列按钮*/
    button[0][0].start_x = BUTTON_START_X;
    button[0][0].start_y = BUTTON_BLOCK_HEIGHT * 2;
    button[0][0].end_x = BUTTON_START_X + BUTTON_BLOCK_WIDTH;
    button[0][0].end_y = BUTTON_BLOCK_HEIGHT * 3;
    button[0][0].para = CL_BUTTON_GREY;
    button[0][0].touch_flag = 0;  
    button[0][0].draw_btn = Draw_Button_Rectangle ;
    button[0][0].btn_command = Command_Enter03 ;//进入03界面
  
    button[0][1].start_x = BUTTON_START_X;
    button[0][1].start_y = BUTTON_BLOCK_HEIGHT * 3;
    button[0][1].end_x = BUTTON_START_X + BUTTON_BLOCK_WIDTH;
    button[0][1].end_y = BUTTON_BLOCK_HEIGHT * 4;
    button[0][1].para = CL_BUTTON_GREY;
    button[0][1].touch_flag = 0;  
    button[0][1].draw_btn = Draw_Button_Rectangle ;
    button[0][1].btn_command = Command_Enter06 ;//进入06界面

    /*主界面第二列按钮*/
    button[0][2].start_x = BUTTON_START_X + BUTTON_BLOCK_WIDTH;
    button[0][2].start_y = BUTTON_BLOCK_HEIGHT * 1;
    button[0][2].end_x = BUTTON_START_X + BUTTON_BLOCK_WIDTH * 2;
    button[0][2].end_y = BUTTON_BLOCK_HEIGHT * 2;
    button[0][2].para = CL_BUTTON_GREY;
    button[0][2].touch_flag = 0;  
    button[0][2].draw_btn = Draw_Button_Rectangle ;
    button[0][2].btn_command = Command_Add_Slaver ;//从机地址加1
  
    button[0][3].start_x = BUTTON_START_X + BUTTON_BLOCK_WIDTH * 2;
    button[0][3].start_y = BUTTON_BLOCK_HEIGHT * 1;
    button[0][3].end_x = BUTTON_START_X + BUTTON_BLOCK_WIDTH * 3;
    button[0][3].end_y = BUTTON_BLOCK_HEIGHT * 2;
    button[0][3].para = CL_BUTTON_GREY;
    button[0][3].touch_flag = 0;  
    button[0][3].draw_btn = Draw_Button_Rectangle ;
    button[0][3].btn_command = Command_Sub_Slaver ;//从机地址减1
  
    /*功能码03界面第一行按钮*/
    button[1][0].start_x = BUTTON_START_X + BUTTON_BLOCK_WIDTH;
    button[1][0].start_y = BUTTON_BLOCK_HEIGHT * 1;
    button[1][0].end_x = BUTTON_START_X + BUTTON_BLOCK_WIDTH * 2;
    button[1][0].end_y = BUTTON_BLOCK_HEIGHT * 2;
    button[1][0].para = CL_BUTTON_GREY;
    button[1][0].touch_flag = 0;  
    button[1][0].draw_btn = Draw_Button_Rectangle ;
    button[1][0].btn_command = Command_Add_Start_Addr ;//起始地址加1
  
    button[1][1].start_x = BUTTON_START_X + BUTTON_BLOCK_WIDTH * 2;
    button[1][1].start_y = BUTTON_BLOCK_HEIGHT * 1;
    button[1][1].end_x = BUTTON_START_X + BUTTON_BLOCK_WIDTH * 3;
    button[1][1].end_y = BUTTON_BLOCK_HEIGHT * 2;
    button[1][1].para = CL_BUTTON_GREY;
    button[1][1].touch_flag = 0;  
    button[1][1].draw_btn = Draw_Button_Rectangle ;
    button[1][1].btn_command = Command_Sub_Start_Addr ;//起始地址减1
  
    /*功能码03界面第二行按钮*/
    button[1][2].start_x = BUTTON_START_X + BUTTON_BLOCK_WIDTH;
    button[1][2].start_y = BUTTON_BLOCK_HEIGHT * 2;
    button[1][2].end_x = BUTTON_START_X + BUTTON_BLOCK_WIDTH * 2;
    button[1][2].end_y = BUTTON_BLOCK_HEIGHT * 3;
    button[1][2].para = CL_BUTTON_GREY;
    button[1][2].touch_flag = 0;  
    button[1][2].draw_btn = Draw_Button_Rectangle ;
    button[1][2].btn_command = Command_Add_Num ;//寄存器数量加1
  
    button[1][3].start_x = BUTTON_START_X + BUTTON_BLOCK_WIDTH * 2;
    button[1][3].start_y = BUTTON_BLOCK_HEIGHT * 2;
    button[1][3].end_x = BUTTON_START_X + BUTTON_BLOCK_WIDTH * 3;
    button[1][3].end_y = BUTTON_BLOCK_HEIGHT * 3;
    button[1][3].para = CL_BUTTON_GREY;
    button[1][3].touch_flag = 0;  
    button[1][3].draw_btn = Draw_Button_Rectangle ;
    button[1][3].btn_command = Command_Sub_Num ;//寄存器数量减1
    
    /*功能码03界面返回按钮*/
    button[1][4].start_x = BUTTON_START_X + BUTTON_BLOCK_WIDTH * 4;
    button[1][4].start_y = BUTTON_BLOCK_HEIGHT * 12;
    button[1][4].end_x = BUTTON_START_X + BUTTON_BLOCK_WIDTH * 5;
    button[1][4].end_y = BUTTON_BLOCK_HEIGHT * 13;
    button[1][4].para = CL_BUTTON_GREY;
    button[1][4].touch_flag = 0;  
    button[1][4].draw_btn = Draw_Button_Rectangle ;
    button[1][4].btn_command = Command_Return;//返回主界面 
  

    /*功能码06界面第一行按钮*/
    button[2][0].start_x = BUTTON_START_X + BUTTON_BLOCK_WIDTH;
    button[2][0].start_y = BUTTON_BLOCK_HEIGHT * 1;
    button[2][0].end_x = BUTTON_START_X + BUTTON_BLOCK_WIDTH * 2;
    button[2][0].end_y = BUTTON_BLOCK_HEIGHT * 2;
    button[2][0].para = CL_BUTTON_GREY;
    button[2][0].touch_flag = 0;  
    button[2][0].draw_btn = Draw_Button_Rectangle ;
    button[2][0].btn_command = Command_Add_Start_Addr ;//起始地址加1
  
    button[2][1].start_x = BUTTON_START_X + BUTTON_BLOCK_WIDTH * 2;
    button[2][1].start_y = BUTTON_BLOCK_HEIGHT * 1;
    button[2][1].end_x = BUTTON_START_X + BUTTON_BLOCK_WIDTH * 3;
    button[2][1].end_y = BUTTON_BLOCK_HEIGHT * 2;
    button[2][1].para = CL_BUTTON_GREY;
    button[2][1].touch_flag = 0;  
    button[2][1].draw_btn = Draw_Button_Rectangle ;
    button[2][1].btn_command = Command_Sub_Start_Addr ;//起始地址减1
  
    /*功能码06界面第二行按钮*/
    button[2][2].start_x = BUTTON_START_X + BUTTON_BLOCK_WIDTH;
    button[2][2].start_y = BUTTON_BLOCK_HEIGHT * 2;
    button[2][2].end_x = BUTTON_START_X + BUTTON_BLOCK_WIDTH * 2;
    button[2][2].end_y = BUTTON_BLOCK_HEIGHT * 3;
    button[2][2].para = CL_BUTTON_GREY;
    button[2][2].touch_flag = 0;  
    button[2][2].draw_btn = Draw_Button_Rectangle ;
    button[2][2].btn_command = Command_Add_Num ;//寄存器数量加1
  
    button[2][3].start_x = BUTTON_START_X + BUTTON_BLOCK_WIDTH * 2;
    button[2][3].start_y = BUTTON_BLOCK_HEIGHT * 2;
    button[2][3].end_x = BUTTON_START_X + BUTTON_BLOCK_WIDTH * 3;
    button[2][3].end_y = BUTTON_BLOCK_HEIGHT * 3;
    button[2][3].para = CL_BUTTON_GREY;
    button[2][3].touch_flag = 0;  
    button[2][3].draw_btn = Draw_Button_Rectangle ;
    button[2][3].btn_command = Command_Sub_Num ;//寄存器数量减1
    
    /*功能码06界面返回按钮*/
    button[2][4].start_x = BUTTON_START_X + BUTTON_BLOCK_WIDTH * 4;
    button[2][4].start_y = BUTTON_BLOCK_HEIGHT * 12;
    button[2][4].end_x = BUTTON_START_X + BUTTON_BLOCK_WIDTH * 5;
    button[2][4].end_y = BUTTON_BLOCK_HEIGHT * 13;
    button[2][4].para = CL_BUTTON_GREY;
    button[2][4].touch_flag = 0;  
    button[2][4].draw_btn = Draw_Button_Rectangle ;
    button[2][4].btn_command = Command_Return;//返回主界面
}

/**
* @brief  Touch_Button_Down 按键被按下时调用的函数，由触摸屏调用
* @param  x 触摸位置的x坐标
* @param  y 触摸位置的y坐标
* @retval 无
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
        /* 触摸到了按钮 */
        if (x <= button[page][i].end_x && y <= button[page][i].end_y && y >= button[page][i].start_y && x >= button[page][i].start_x )
        {
            if (button[page][i].touch_flag == 0)     /*原本的状态为没有按下，则更新状态*/
            {
                button[page][i].touch_flag = 1;         /* 记录按下标志 */
      
                button[page][i].draw_btn(&button[page][i]);  /*重绘按钮*/
            }        
      
        }
        else if (button[page][i].touch_flag == 1) /* 触摸移出了按键的范围且之前有按下按钮 */
        {
            button[page][i].touch_flag = 0;         /* 清除按下标志，判断为误操作*/
      
            button[page][i].draw_btn(&button[page][i]);   /*重绘按钮*/
        }

    }

}

/**
* @brief  Touch_Button_Up 按键被释放时调用的函数，由触摸屏调用
* @param  x 触摸最后释放时的x坐标
* @param  y 触摸最后释放时的y坐标
* @retval 无
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
        /* 触笔在按钮区域释放 */
        if ((x < button[page][i].end_x && x > button[page][i].start_x && y < button[page][i].end_y && y > button[page][i].start_y))
        {        
            button[page][i].touch_flag = 0;       /*释放触摸标志*/
        
            button[page][i].draw_btn(&button[page][i]); /*重绘按钮*/        
      
            button[page][i].btn_command(&button[page][i]);  /*执行按键的功能命令*/
        
            break;
        }
    }  

}


/**
* @brief  Draw_Button_Rectangle 清屏按钮的描绘函数
* @param  btn Touch_Button 类型的按键参数
* @retval 无
*/
static void Draw_Button_Rectangle(void *btn)
{
    Touch_Button *ptr = (Touch_Button *)btn;
//    LCD_SetColors(CL_BLUE4, CL_WHITE);
//    ILI9341_DrawRectangle(ptr->start_x, ptr->start_y, ptr->end_x - ptr->start_x, ptr->end_y - ptr->start_y, 0);
}



/**
* @brief  Command_Enter03 进入功能码03选择界面
* @param  btn Touch_Button 类型的按键参数
* @retval 无
*/
static void Command_Enter03(void *btn)
{
    (void)btn;
    page = 1;
    Fuction = 0x03;
    buttonRenew();
}

/**
* @brief  Command_Enter06 进入功能码06选择界面
* @param  btn Touch_Button 类型的按键参数
* @retval 无
*/
static void Command_Enter06(void *btn)
{
    (void)btn;
    page = 2;
    Fuction = 0x06;
    buttonRenew();
}


/**
* @brief  Command_Add_Slaver 从机地址+1
* @param  btn Touch_Button 类型的按键参数
* @retval 无
*/
static void Command_Add_Slaver(void *btn)
{
    (void)btn;
    SlaverAddr++;
}

/**
* @brief  Command_Sub_Slaver 从机地址-1
* @param  btn Touch_Button 类型的按键参数
* @retval 无
*/
static void Command_Sub_Slaver(void *btn)
{
    (void)btn;
    SlaverAddr--;
}

/**
* @brief  Command_Add_Start_Addr 起始地址+1
* @param  btn Touch_Button 类型的按键参数
* @retval 无
*/
static void Command_Add_Start_Addr(void *btn)
{
    (void)btn;
    StartAddr++;
}

/**
* @brief  Command_Sub_Start_Addr 起始地址-1
* @param  btn Touch_Button 类型的按键参数
* @retval 无
*/
static void Command_Sub_Start_Addr(void *btn)
{
    (void)btn;
    StartAddr--;
}

/**
* @brief  Command_Add_Num 数量+1
* @param  btn Touch_Button 类型的按键参数
* @retval 无
*/
static void Command_Add_Num(void *btn)
{
    (void)btn;
    ValueOrLenth++;
}

/**
* @brief  Command_Sub_Num 数量-1
* @param  btn Touch_Button 类型的按键参数
* @retval 无
*/
static void Command_Sub_Num(void *btn)
{
    (void)btn;
    ValueOrLenth--;
}


/**
* @brief  Command_Return 返回主界面
* @param  btn Touch_Button 类型的按键参数
* @retval 无
*/
static void Command_Return(void *btn)
{
    (void)btn;
    page = 0;
}
/* ------------------------------------------end of file---------------------------------------- */




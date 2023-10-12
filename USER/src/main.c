/*********************************************************************************************************************
 *     COPYRIGHT NOTICE
 *     Copyright (c) 2023,CNU_W.PIE
 *     All rights reserved.
 *
 *     除注明出处外，以下所有内容版权均属胖胖个人所有，未经允许，不得用于商业用途，
 *     修改内容时必须保留PP的版权声明。
 *     Except where indicated, the copyright of all the contents below is owned by PP
 *     and can not be used for commercial purposes without permission.
 *     The copyright notice of PP must be preserved when modifying the content.
 *
 * @file       main.h
 * @brief      lv0
 * @author     刘臆杨
 * @version    v1.0
 * @note       NULL
 * @date       2023-07-26
 ********************************************************************************************************************/

#include "main.h"                                                // 调用“图书馆”
#if !defined(__C251__) && !defined(__C51__) && defined(__VSCODE) // 只用于消除vscode报错，对程序执行无影响
#include "../debug/debug.h"
#endif

int i;
int j;
int k;
int auth1 = 0;

int touch_count1 = 0;
int touch_count2 = 0;
int time_count = 0;

int n = 4;

int cha_p[] = {5, 5, 6, 6}; // 控制开启位势
int cha_pin[] = {8, 1, 2, 8};

uint8_t dis_numbers[4] = {0}; // 选择显示数字

static uint8_t vol[4][4] = {
    {0, 1, 1, 1}, // 打开第一位
    {1, 0, 1, 1}, // 打开第二位
    {1, 1, 0, 1}, // 打开第三位
    {1, 1, 1, 0}, // 打开第四位
};

uint8_t numbers[10][8] = {
    {1, 1, 1, 1, 1, 1, 0, 0}, // 0
    {0, 1, 1, 0, 0, 0, 0, 0}, // 1
    {1, 1, 0, 1, 1, 0, 1, 0}, // 2
    {1, 1, 1, 1, 0, 0, 1, 0}, // 3
    {0, 1, 1, 0, 0, 1, 1, 0}, // 4
    {1, 0, 1, 1, 0, 1, 1, 0}, // 5
    {1, 0, 1, 1, 1, 1, 1, 0}, // 6
    {1, 1, 1, 0, 0, 0, 0, 0}, // 7
    {1, 1, 1, 1, 1, 1, 1, 0}, // 8
    {1, 1, 1, 1, 0, 1, 1, 0}  // 9
};

// 初始化
void setup()
{
    Board_Init();
    for (k = 0; k < 4; k++)
        GPIO_Init(cha_p[k], cha_pin[k], 3);
    for (i = 0; i < 8; i++)
        GPIO_Init(7, 1 << i, 3);
    GPIO_Init(GPIO_P0, GPIO_Pin_6, GPIO_PullUp);
    GPIO_Init(GPIO_P0, GPIO_Pin_7, GPIO_PullUp);
    GPIO_EXTI_Init(GPIO_P0, GPIO_Pin_6, FALLING_EDGE);
    GPIO_EXTI_Init(GPIO_P0, GPIO_Pin_7, FALLING_EDGE);
    GPIO_EXTI_Open(GPIO_P0, GPIO_Pin_6);
    GPIO_EXTI_Open(GPIO_P0, GPIO_Pin_7);
}

// 开启指定位选
void open_bit(int k)
{
    for (i = 0; i < 4; i++)
        GPIO_Write_Bit(cha_p[i], cha_pin[i], vol[k][i]);
}

// 为指定位写入数字
void write_number(int k)
{
    for (i = 0; i < 8; i++)
        GPIO_Write_Bit(7, 1 << i, numbers[dis_numbers[k]][i]);
    Ms_Delay(1);
}

// 普通中断，检查按钮是否被按下，被按下时显示数组++--
// 长按连加功能待实现
void P0_INT_7(void) interrupt P0INT_VECTOR
{
    GPIO_EXTI_Flag_Read(GPIO_P0);
    if (Port_Exti_Flag[0])
    {
        GPIO_EXTI_Flag_Clear(GPIO_P0);
        // p07实现加
        if (Port_Exti_Flag[0] & Port_Pin_7)
        {
            // 检查是否为长按

            // 进位器
            if (dis_numbers[3] == 9)
            {
                dis_numbers[3] = 0;
                if (dis_numbers[2] == 9)
                {
                    dis_numbers[2] = 0;
                    if (dis_numbers[1] == 9)
                    {
                        dis_numbers[1] = 0;
                        if (dis_numbers[0] == 9)
                        {
                            dis_numbers[0] = 0;
                            goto end1;
                        }
                        dis_numbers[0] += 1;
                        goto end1;
                    }
                    dis_numbers[1] += 1;
                    goto end1;
                }
                dis_numbers[2] += 1;
                goto end1;
            }
            dis_numbers[3] += 1;
            goto end1;
        }

        // p06实现减
        if (Port_Exti_Flag[0] & Port_Pin_6)
        {
            if (dis_numbers[3] == 0)
            {
                dis_numbers[3] = 9;
                if (dis_numbers[2] == 0)
                {
                    dis_numbers[2] = 9;
                    if (dis_numbers[1] == 0)
                    {
                        dis_numbers[1] = 9;
                        if (dis_numbers[0] == 0)
                        {
                            dis_numbers[0] = 9;
                            goto end1;
                        }
                        dis_numbers[0] -= 1;
                        goto end1;
                    }
                    dis_numbers[1] -= 1;
                    goto end1;
                }
                dis_numbers[2] -= 1;
                goto end1;
            }
            dis_numbers[3] -= 1;
            goto end1;
        }
    }
end1:;
}

// 定时中断，定时使显示数组++
void P0_Timer(void) interrupt TMR0_VECTOR
{
    PIT_Timer_Clear(TIM0);
    time_count++;
    // 将间隔时间延长至1s
    if (time_count % 100 == 0)
    {
        // 进位器
        if (dis_numbers[3] == 9)
        {
            dis_numbers[3] = 0;
            if (dis_numbers[2] == 9)
            {
                dis_numbers[2] = 0;
                if (dis_numbers[1] == 9)
                {
                    dis_numbers[1] = 0;
                    if (dis_numbers[0] == 9)
                    {
                        dis_numbers[0] = 0;
                        goto end2;
                    }
                    dis_numbers[0] += 1;
                    goto end2;
                }
                dis_numbers[1] += 1;
                goto end2;
            }
            dis_numbers[2] += 1;
            goto end2;
        }
        dis_numbers[3] += 1;
        goto end2;
    }

end2:;
}

// 定时中断开关
void P0_INT_4(void) interrupt P4INT_VECTOR
{
    GPIO_EXTI_Flag_Read(GPIO_P4);
    if (Port_Exti_Flag[0])
    {
        GPIO_EXTI_Flag_Clear(GPIO_P4);
        if (auth1 == 1)
        {
            ET0 = 0;
            auth1 = 0;
        }

        else if (auth1 == 0)
        {
            ET0 = 1;
            auth1 = 1;
        }
    }
}

void main()  // 必要的主函数
{            // 主函数大括号
    setup(); // 培训底板初始化
    PIT_Timer_Ms(TIM0, 10);
    while (1)
    {
        for (k = 0; k < 4; k++)
        {
            open_bit(k);
            write_number(k);
            Ms_Delay(1);
        }
    }
} // 主函数大括号
  // _REENTRANT
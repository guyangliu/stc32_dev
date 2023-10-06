/*********************************************************************************************************************
 *     COPYRIGHT NOTICE
 *     Copyright (c) 2023,CNU_W.PIE
 *     All rights reserved.
 *
 *     ��ע�������⣬�����������ݰ�Ȩ�������ָ������У�δ����������������ҵ��;��
 *     �޸�����ʱ���뱣��PP�İ�Ȩ������
 *     Except where indicated, the copyright of all the contents below is owned by PP
 *     and can not be used for commercial purposes without permission.
 *     The copyright notice of PP must be preserved when modifying the content.
 *
 * @file       main.h
 * @brief      lv3
 * @author     ������
 * @version    v1.0
 * @note       NULL
 * @date       2023-07-26
 ********************************************************************************************************************/

#include "main.h" //���á�ͼ��ݡ�

int i;
int j;
int k;
int auth1 = 0;
int auth2 = 0;
int touch_count = 0;

int n = 4;

int cha_p[] = {5, 5, 6, 6}; // ���ƿ���λ��
int cha_pin[] = {8, 1, 2, 8};

uint8_t dis_numbers[4] = {0}; // ѡ����ʾ����

static uint8_t vol[4][4] = {
    {0, 1, 1, 1}, // �򿪵�һλ
    {1, 0, 1, 1}, // �򿪵ڶ�λ
    {1, 1, 0, 1}, // �򿪵���λ
    {1, 1, 1, 0}, // �򿪵���λ
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

// ��ʼ��
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

// ����ָ��λѡ
void open_bit(int k)
{
    for (i = 0; i < 4; i++)
        GPIO_Write_Bit(cha_p[i], cha_pin[i], vol[k][i]);
}

// Ϊָ��λд������
void write_number(int k)
{
    for (i = 0; i < 8; i++)
        GPIO_Write_Bit(7, 1 << i, numbers[dis_numbers[k]][i]);
    Ms_Delay(1);
}

void P0_INT_7(void) interrupt P0INT_VECTOR
{
    GPIO_EXTI_Flag_Read(GPIO_P0);
    if (Port_Exti_Flag[0])
    {
        GPIO_EXTI_Flag_Clear(GPIO_P0);
        if (Port_Exti_Flag[0] & Port_Pin_7)
        {
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

void main()  // ��Ҫ��������
{            // ������������
    setup(); // ��ѵ�װ��ʼ��
    while (1)
    {
        for (k = 0; k < 4; k++)
        {
            open_bit(k);
            write_number(k);
            Ms_Delay(1);
        }
    }
} // ������������

// interrupt 37
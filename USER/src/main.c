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
int auth = 0;
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
    GPIO_Init(GPIO_P0, GPIO_Pin_7, GPIO_PullUp);
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

// ��鿪��״̬
int check_switch()
{
    if (GPIO_Read_Bit(GPIO_P0, GPIO_Pin_7) == 0)
    {
        if (auth == 1) // ������
        {
            touch_count++;
            if (touch_count == 10)
            {
                touch_count = 0;
                auth = 2;
                goto out;
            }
            touch_count = 0;
            return 0;
        }
    out:
        if (auth == 0)
            auth = 1;
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
                        return 0;
                    }
                    dis_numbers[0] += 1;
                    return 0;
                }
                dis_numbers[1] += 1;
                return 0;
            }
            dis_numbers[2] += 1;
            return 0;
        }
        dis_numbers[3] += 1;
        return 0;
    }
}

// ��������״̬
void reauth()
{
    if (GPIO_Read_Bit(GPIO_P0, GPIO_Pin_7) == 1)
        auth = 0;
}

void main()  // ��Ҫ��������
{            // ������������
    setup(); // ��ѵ�װ��ʼ��
    while (1)
    {
        check_switch();
        for (k = 0; k < 4; k++)
        {
            open_bit(k);
            write_number(k);
            Ms_Delay(1);
            reauth();
        }
    }
} // ������������

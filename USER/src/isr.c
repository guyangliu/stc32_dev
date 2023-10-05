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
 * @file       isr.c
 * @brief      �жϷ���
 * @author     ����
 * @version    v1.0
 * @note       NULL
 * @date       2023-07-26
 ********************************************************************************************************************/
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "isr.h"
#include "common.h"

#include "CNU_PIE_UART.h"
#include "CNU_PIE_EXTI.h"
void UART1_Isr() interrupt 4
{
    if(UART1_GET_TX_FLAG)
    {
        UART1_CLEAR_TX_FLAG;
        UART_BUSY[1] = 0;
    }
    if(UART1_GET_RX_FLAG)
    {
        UART1_CLEAR_RX_FLAG;
			//�������ݼĴ���Ϊ��SBUF
    }
}
void UART2_Isr() interrupt 8
{
	if(UART2_GET_TX_FLAG)
	{
    UART2_CLEAR_TX_FLAG;
		UART_BUSY[2] = 0;
	}
  if(UART2_GET_RX_FLAG)
	{
    UART2_CLEAR_RX_FLAG;
		//�������ݼĴ���Ϊ��S2BUF
	}
}
void UART3_Isr() interrupt 17
{
	if(UART3_GET_TX_FLAG)
	{
    UART3_CLEAR_TX_FLAG;
		UART_BUSY[3] = 0;
	}
  if(UART3_GET_RX_FLAG)
	{
     UART3_CLEAR_RX_FLAG;
		//�������ݼĴ���Ϊ��S3BUF
	}
}
void UART4_Isr() interrupt 18
{
	if(UART4_GET_TX_FLAG)
	{
    UART4_CLEAR_TX_FLAG;
		UART_BUSY[4] = 0;
	}
  if(UART4_GET_RX_FLAG)
	{
    UART4_CLEAR_RX_FLAG;
		//�������ݼĴ���Ϊ��S4BUF;
	}
}



//void INT0_Isr() interrupt 0
//{
//}
//void INT1_Isr() interrupt 2
//{
//}
//void INT2_Isr() interrupt 10
//{
//}
//void INT3_Isr() interrupt 11
//{
//}
//void INT4_Isr() interrupt 16
//{
//}
//void TM1_Isr() interrupt 3
//{
//}
//void TM2_Isr() interrupt 12
//{
//}

//void TM4_Isr() interrupt 20
//{
//}
//void DMA_ADC_ISR_Handler (void) interrupt ADCDMA_VECTOR
//{
//}
//void  INT0_Isr()  interrupt 0;
//void  TM0_Isr()   interrupt 1;
//void  INT1_Isr()  interrupt 2;id  TM1_Isr()   interrupt 3;
//void  UART1_Isr() interrupt 4;
//void  ADC_Isr()   interrupt 5;
//void  LVD_Isr()   interrupt 6;
//void  PCA_Isr()   interrupt 7;
//void  UART2_Isr() interrupt 8;
//void  SPI_Isr()   interrupt 9;
//void  INT2_Isr()  interrupt 10;
//void  INT3_Isr()  interrupt 11;
//void  TM2_Isr()   interrupt 12;
//void  INT4_Isr()  interrupt 16;
//void  UART3_Isr() interrupt 17;
//void  UART4_Isr() interrupt 18;
//void  TM3_Isr()   interrupt 19;
//void  TM4_Isr()   interrupt 20;
//void  CMP_Isr()   interrupt 21;
//void  I2C_Isr()   interrupt 24;
//void  USB_Isr()   interrupt 25;
//void  PWM1_Isr()  interrupt 26;
//void  PWM2_Isr()  interrupt 27;
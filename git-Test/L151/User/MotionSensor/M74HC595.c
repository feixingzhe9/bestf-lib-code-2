/*****************************************************************************
�ļ��� m74hc595.c
˵���� m74hc595��������ʵ���ļ�
���룺 Keil uVision4 V4.54.0.0
�汾�� v1.0
��д�� linwuzhang
���ڣ� 2013.10.21
*****************************************************************************/

#include "m74hc595.h"

#include "sys.h"
#include "delay.h"
INT16U data_temp = 0;
/****************************************
�� �� ��:  m74hc595_init(void);
����˵��:  ��ʼ��74hc595���IO�ܽ�
��    ��:            
�� �� ֵ:  
*****************************************/
void m74hc595_init(void)
{
	GPIOx_Cfg(_SDA_PORT,  _SDA_PIN,  OUT_PP_2M);
	GPIOx_Cfg(OUT_PORT,  OUT_PIN,  	 OUT_PP_2M);
	GPIOx_Cfg(LOCK_PORT, LOCK_PIN, 	 OUT_PP_2M);
	GPIOx_Cfg(SCK_PORT,  SCK_PIN,  	 OUT_PP_2M);
	GPIOx_Cfg(RST_PORT,  RST_PIN, 	 OUT_PP_2M);
//	M74HC595_OUTPUT_EN(1);	//���迹���ر�����LED
//	M74HC595_RST(0);		//����Ĵ���ֵ
//	M74HC595_LATCH(0);
//	delay_us(10);
//	M74HC595_LATCH(1);
}

/****************************************
�� �� ��: void m74hc595_output(unsigned short data);
����˵��: ��dataͨ��m74hc595���
��    ��: data��ʾ595������16��IO�����data�ĵ�15λ������16��LED�ƣ�data�ĵ�0λ������1��LED��
		  ��Ӧλ��0������LED����LED=0x4001,    ��ʾ������14���͵�1��LED��      
�� �� ֵ:  
*****************************************/
void m74hc595_output(INT16U data,INT8U cmd)
{
	INT8U i;
	
//	M74HC595_OUTPUT_EN(1);	//���迹���ر�����LED
	M74HC595_LATCH(0);		//���״̬�Ĵ�������
    M74HC595_RST(1);	
	if(cmd)
	{
		data_temp |= 1<<data;
	}
	else
	{
		data_temp &= ~(1<<data);
	}
	
	for(i=16;i>0;i--)
	{
		M74HC595_SCLK(0);
		if(data_temp&(1<<(i-1)))
		{
			M74HC595_SDA(1);
		}
		else
		{
			M74HC595_SDA(0);	
		}
		M74HC595_SCLK(1);
	}
	M74HC595_LATCH(1);		 //����λ�Ĵ�����ֵ���浽����Ĵ�����
	M74HC595_OUTPUT_EN(0);	//�����Ч������LED��
}
void m74hc595_All(INT16U data)
{
	INT8U i;
//	M74HC595_OUTPUT_EN(1);	//���迹���ر�����LED
	M74HC595_LATCH(0);		//���״̬�Ĵ�������
	
    M74HC595_RST(1);	
	for(i=16;i>0;i--)
	{
		M74HC595_SCLK(0);
		if(data&(1<<(i-1)))
		{
			M74HC595_SDA(1);
		}
		else
		{
			M74HC595_SDA(0);	
		}
		M74HC595_SCLK(1);
	}
	M74HC595_LATCH(1);		 //����λ�Ĵ�����ֵ���浽����Ĵ�����
	M74HC595_OUTPUT_EN(0);	//�����Ч������LED��
}
/****************************************
�� �� ��: void m74hc595_reset(unsigned short data);
����˵��: ���M74HC595��λ�Ĵ���
��    ��:            
�� �� ֵ:  
*****************************************/
void m74hc595_reset(void)
{
	M74HC595_RST(0);
	delay_us(1);
	M74HC595_RST(1);
}


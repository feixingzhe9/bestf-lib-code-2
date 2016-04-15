/*****************************************************************************
�ļ��� m74hc595.h
˵���� m74hc595��������ͷ�ļ�
���룺 Keil uVision4 V4.54.0.0
�汾�� v1.0
��д�� linwuzhang
���ڣ� 2013.10.21
*****************************************************************************/

#ifndef __M74HC595_H
#define __M74HC595_H

#include "GPIO.h"

extern INT16U data_temp;

/*	  
              METHOD1 
M74HC595����˵��
1��2��3��4��5��6��7��15(Q0~Q7)---------- Data Outputs
9(QH��)---------------------------------- serial data outputs
10��SCLR��------------------------------ Shift Register Clear Input
11(SCK)	-------------------------------- Shift Register Clock Input
13(G)----------------------------------- Output Enable Input
14(SI)---------------------------------- Serial Data Input
12(RCK)--------------------------------- Storage Register Clock Input

M74HC595 ��STM32 ���ŵ�����
14<------------->PA5	����������������
12<------------->PA7	�洢�Ĵ���ʱ�����룬�����ؽ���λ�Ĵ���״ֵ̬���浽����Ĵ���
11<------------->PB1	��λ�Ĵ���ʱ�����룬 ��������λ
13<------------->PA6	���ʹ��
10<------------->PB0	��������Ϊ�Ĵ���
*/

#define _SDA_PORT    GPIO_A    
#define _SDA_PIN     pin_12    

#define OUT_PORT    GPIO_A  
#define OUT_PIN     pin_11  
									
#define LOCK_PORT    GPIO_A  
#define LOCK_PIN     pin_10

#define SCK_PORT    GPIO_A 
#define SCK_PIN     pin_9

#define RST_PORT    GPIO_A   
#define RST_PIN     pin_8


#ifndef	IO_STATUS
#define IO_STATUS0(GPIOx, pin)  GPIOx_Rst(GPIOx, pin) //��Ӧ�ܽ���0
#define IO_STATUS1(GPIOx, pin)  GPIOx_Set(GPIOx, pin) //��Ӧ�ܽ���1) 
#endif

#define M74HC595_SDA(str)   IO_STATUS##str(_SDA_PORT, _SDA_PIN)		//������A
#define M74HC595_LATCH(str)	 IO_STATUS##str(LOCK_PORT, LOCK_PIN)		   //�����ؽ���λ�Ĵ���״ֵ̬���浽����Ĵ���
#define M74HC595_RST(str)	 IO_STATUS##str(RST_PORT, RST_PIN)		   //�����λ�Ĵ���
#define M74HC595_OUTPUT_EN(str)	 IO_STATUS##str(OUT_PORT, OUT_PIN)	   //�͵�ƽ�����״ֵ̬���ߵ�ƽ��������迹	str=0,���
#define M74HC595_SCLK(str)	 IO_STATUS##str(SCK_PORT, SCK_PIN)		   //��λ�Ĵ�����λʱ���źţ���������λ


/****************************************
�� �� ��:  m74hc595_init(void);
����˵��:  ��ʼ��74hc595���IO�ܽ�
��    ��:            
�� �� ֵ:  
*****************************************/
extern void m74hc595_init(void);

/****************************************
�� �� ��: void m74hc595_reset(unsigned short data);
����˵��: ���M74HC595��λ�Ĵ���
��    ��:            
�� �� ֵ:  
*****************************************/
extern void m74hc595_reset(void);
void m74hc595_output(INT16U data,INT8U cmd);
void m74hc595_All(INT16U data);
#endif 


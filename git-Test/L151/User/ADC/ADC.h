#ifndef __ADC_H
#define __ADC_H	

#include "sys.h"

#define PORT_ADC	GPIO_A
#define PIN_ADC		pin_2
#define ADC_CH0		0  
	 	       									   
void  ADC_Init(u8 ch);
u8 Get_ADC(u16 *ADC_Result) ; 						//���ĳ��ͨ��ֵ 
u8 Get_ADC_Average(u8 times,u16 *Average_Voltage);	//�õ�ĳ��ͨ��10�β�����ƽ��ֵ 

#endif 
















/*******************************************************************
��	����delay.h
˵	����ʹ��SysTick����ͨ����ģʽ���ӳٽ��й���
��	�룺Keil uVision4 V4.54.0.0
��	����v1.0
��	д��Unarty
��	�ڣ�
********************************************************************/
#ifndef __LPM_H
#define __LPM_H 

#include "stm32l1xx.h"			   
#include "BF_type.h"
#include "core_cm3.h"

extern INT8U In_Lpm_Flag;


typedef enum
{
	SLEEP 			= 0,	//˯��ģʽ
	Low_Power_Run	= 1,
	Low_Power_Sleep = 2,
	Stop 			= 3,
	Standby 		= 4 	//����ģʽ
}Low_Power_Mode;  


void Low_Power_Select(INT8U LPM);
void LP_Run_Mode(void);
void Sleep_Mode(void);
void Stop_Mode(void);
void Standby_Mode(void);

void Close_device(void);


void CheckStandbyMode(void);
void WKUP_Port_Init(void);
void Get_WKUP_State(void);

#endif	//LPM.h end


/**************************FILE*END********************************/






























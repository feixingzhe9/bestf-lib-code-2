/*******************************************************************
��	����    Voltage.h
˵	����    Voltage�߼�����ͷ�ļ�
��	�룺    Keil uVision4 V4.54.0.0
��	����    v1.0
��	д��    ������
��	�ڣ�    2013-11-22
********************************************************************/
#ifndef __BATTERY_H
#define __BATTERY_H

#include "BF_TYPE.h"

extern  u8 BattVoltageLev;

//INT8U VoltageExeCmd(MsgCmd_st *str);
//INT8U Voltage_Get_Attr(MsgCmd_st *str);

u8 Battery_Power_Instruct(void);
void Battery_Power_Instruct_success(void);

u8 Battery_GetVoltage(u16 *Voltage);
u8 Battery_GetPower(u8 *VoltageLev);

#endif //Battery.h
/******************* (C) COPYRIGHT 2013 BestFu *****END OF FILE****/


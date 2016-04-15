/*******************************************************************
��	����    Battery.c
˵	����    Voltage�߼�����
��	�룺    Keil uVision4 V4.54.0.0
��	����    v1.0
��	д��    Seven
��	�ڣ�    2014.07.10

﮵�ص�ѹ��Χ��  3.0V ~ 4.2V

�ŵ��ѹ�� 3.5V  �����ͷ� 95%


********************************************************************/
#include "gpio.h"
#include "Unitcfg.h"
#include "Battery.h"
#include "adc.h"
                     // 90   80  70  60  50  40  30  20  10  1  %
const u16 VoltageTab[]={403,397,390,383,378,373,369,365,362,340};

//��ѹ����ֵ
u8 BattVoltageLev;


//��ȡ��ѹֵ
u8 Battery_GetVoltage(u16 *Voltage)
{
	u16 ADC_Value;
	u32 tmp_voltage=0;
	GPIOx_Set(PORT_ADC_SWITCH, PIN_ADC_SWITCH);	
	if(!Get_ADC_Average(10,&ADC_Value))
	{
		//Voltage = ADC_Result *330 / 4096
		tmp_voltage = ADC_Value*132;		//����200��    0����330   ��ѹ���� 1/2
		*Voltage    = tmp_voltage/819;
		GPIOx_Rst(PORT_ADC_SWITCH, PIN_ADC_SWITCH);		
		return 0;
	}
	GPIOx_Rst(PORT_ADC_SWITCH, PIN_ADC_SWITCH);		
	return 1;
}
//��ѹ�ּ�
u8 Battery_GetPower(u8 * VoltageLev)
{
	u16  vtg=0;
	u8	 precent=0;
	if(!Battery_GetVoltage(&vtg))
	{
		if(vtg>=VoltageTab[0])		//90%
		{
			precent=90;
		}
		else if(vtg>=VoltageTab[1])//80%
		{
			precent=80;
		}
		else if(vtg>=VoltageTab[2])//70%
		{
			precent=70;
		}
		else if(vtg>=VoltageTab[3])//60%
		{
			precent=60;
		}
		else if(vtg>=VoltageTab[4])//50%
		{
			precent=50;
		}
		else if(vtg>=VoltageTab[5])//40%
		{
			precent=40;
		}
		else if(vtg>=VoltageTab[6])//30%
		{
			precent=30;
		}
		else if(vtg>=VoltageTab[7])//20%
		{
			precent=20;
		}
		else if(vtg>=VoltageTab[8])//10%
		{
			precent=10;
		}
		else if(vtg>=VoltageTab[9])//1%
		{
			precent=1;
		}
		*VoltageLev = precent;
		return  0;
	}
	else return 1;
}

//INT8U VoltageExeCmd(MsgCmd_st *str)
//{
//    
//	INT8U  flag;
//	switch (str->Cmd)
//	{
//		case 0xFF:	flag = Voltage_Get_Attr(str);
//					break;
//		default:	str->ucDataLen = 0;
//					flag = FALSE;
//					break;
//	}
//	return flag;
//}

/*******************************************************************
�� �� ���� 	IAP_Ready_Attr  
����˵����  ����׼������
��	  ��:   *str--����ִ�в���       
�� �� ֵ��  TRUE/FALSE
********************************************************************/
//INT8U Voltage_Get_Attr(MsgCmd_st *str)
//{
//	if(Battery_Power_Instruct())
//	{
//		return TRUE;
//	}
//	return FALSE;
//}

u8 Battery_Power_Instruct(void)
{
	
//	COM_STR Battery_Power_CMD;
//	if(!Battery_GetPower(&BattVoltageLev))
//	{
//		Battery_Power_CMD.Version              = PROTOCOL_VER; 			// �汾��
//		*(u32*)&Battery_Power_CMD.ClientNum    = *(u32*)&g_stEeEx.Sys.Board.ClientNum;	// �û���
//		Battery_Power_CMD.DesObjectType        = 0x01; 			// Ŀ������
//		*(u32*)&Battery_Power_CMD.DesObjectID  = 0x00000000; 	// Ŀ���ַ
//		Battery_Power_CMD.DesObjectTypeID      = 0xFF; 			// �㲥���ͺ�
//		*(u32*)&Battery_Power_CMD.SrcObjectID  = *(u32*)&g_var.DeviceID; // Դ��ַ
//		Battery_Power_CMD.SerialNum            = 0x00;       	// ��ˮ��
//		Battery_Power_CMD.MsgTypeNum           = WRITEWITHACK; 	// ��Ϣ������
//		Battery_Power_CMD.UnitID               = 0x00;     		// ��ԪID
//		Battery_Power_CMD.Cmd                  = 0xFF;			// ������
//		Battery_Power_CMD.DataLength           = 0x01;     		// ��������
//		Battery_Power_CMD.Parameter[0] = BattVoltageLev; 		    //����
//		AnswerCommand(&Battery_Power_CMD, 1);
//	}
//	else 
//	{
//		return 0;
//	}
	return 1;
}
void Battery_Power_Instruct_success(void)
{
	static u8 Get_voltage_success = 1;
	if(Get_voltage_success )
		{
			if(Battery_Power_Instruct())
			{
				Get_voltage_success =0;
			}
		}
}


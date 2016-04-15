/*******************************************************************************
**	��    ��: Cube20ExeAttr.c
**  ��    �ܣ�20������������ӿ�
**  ��    �룺Keil uVision5 V5.10.0.2	
**  ��    ����V1.0.0
**  ��    д��Seven
**  �������ڣ�2014/05/26
**  �޸����ڣ�2014/05/26
**  ˵    ����
********************************************************************************/

#include "Unitcfg.h"	
#include "KeyUnitExeAttr.h"	

#include "Thread.h"	
#include "LowPower.h"	
#include "USART2.h"	
#include "Battery.h"
#include "ADC.h"
#include "wtc6216.h"
#include "m74hc595.h"
#include "keyunit.h"
#include "led_light.h"
#include "power.h"
//�����Զ�д�Ľӿ��б�
const AttrExe_st Cube6AttrOperatTab[] = 
{
	{0x01, LEVEL_0, NULL					, Get_Touch_Attr  },
	{0x02, LEVEL_0, NULL					, Get_Touch_Attr  },
	{0x03, LEVEL_0, NULL					, Get_Touch_Attr  },
	{0x04, LEVEL_0, NULL					, Get_Touch_Attr  },
	{0x05, LEVEL_0, NULL					, Get_Touch_Attr  },
	{0x06, LEVEL_0, NULL					, Get_Touch_Attr  },
	{0x07, LEVEL_0, NULL					, Get_Touch_Attr  },
	{0x08, LEVEL_0, NULL					, Get_Touch_Attr  },
	{0x09, LEVEL_0, NULL					, Get_Touch_Attr  },
	{0x0a, LEVEL_0, NULL					, Get_Touch_Attr  },
	{0x0b, LEVEL_0, NULL					, Get_Touch_Attr  },
	{0x0c, LEVEL_0, NULL					, Get_Touch_Attr  },
	{0x0d, LEVEL_0, NULL					, Get_Touch_Attr  },
	{0x0e, LEVEL_0, NULL					, Get_Touch_Attr  }

};


/*******************************************************************************
**��	��:  	Cube20Init()
**��	��:  	ģ���ʼ��
**��    ��:  	unitID		--��Ԫ��
**��	��:  		
********************************************************************************/
void Cube6Init(INT8U unitID)
{
	WTC6216_Port_Init();
	POWER_PIN_INIT();
	POWER_ON();
	m74hc595_init();
		
	Thread_Login(FOREVER, 0, 1, &KeyScan);		
//	Thread_Login(FOREVER, 0, 1000, &CheckStandbyMode);		
	Thread_Login(FOREVER, 0, 1000, &Run_Led);	
	Upload();	
}
/*******************************************************************************
**��	��:  	Cube20EepromInit()
**��	��:  	ģ������ eeprom ��ʼ��
**��    ��:  	unitID		-��Ԫ��
**��	��:  		
********************************************************************************/
void Cube6EepromInit(INT8U unitID)
{
	
}


/*******************************************************************************
**��	��:  	Get_Cube20_Face_Attr()
**��	��:  	��ȡ��ֵ
**��    ��:  	pdata[0]:   --��Ԫ��
				*rlen		--���ز�������
				*rpara		--���ز�����ŵ�ַ
**��	��:  	TRUE/FALSE
**˵	����	
********************************************************************************/
MsgResult_t Get_Touch_Attr(UnitPara_t *pdata, INT8U *rlen, INT8U *rpara)
{
	*rlen    = 1;
	rpara[0] = Touch_Value;
	return COMPLETE;
}


void Cube6Checking_Attr(void)
{
	
}

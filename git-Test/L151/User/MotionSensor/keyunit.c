#include "keyunit.h"
#include "UnitCfg.h"
#include "wtc6216.h"
#include "m74hc595.h"
#include "led_light.h"

#if KEY_UPLOAD
#include "MsgPackage.h"
#endif

KeyTable keypara;


/*****************************************************************************
�� �� ��:  void KeyScan(void)
����˵��:  ����ɨ�裬��ȡ����ǰ�İ���ֵ������һ�αȽϣ������һ��˵���б仯������
��    ��:  ��
�� �� ֵ:  ��
*****************************************************************************/
void KeyScan(void)
{
	INT16U key=0,keytmp=0;
	static INT16U keyold=0;
	Get_Key(&key);
	keytmp = key^ keyold; 		//���Ϊ1��λ˵�����а������µĻ������ͷ�
	if(keytmp)
	{
		KeyDeal(key, keytmp);
	}
	keyold = key;
	KeyTimeCnt();
	led_light_scan();
}

/*****************************************************************************
�� �� ��:  void KeyTimeCnt(void)
����˵��:  ������ʱ��ÿ·������������������ÿ10����һ�μ�ʱ�е��á�
��    ��:  ��
�� �� ֵ:  ��
*****************************************************************************/
void KeyTimeCnt(void)
{
	INT8U i,j;
	for(i=0;i<KEY_MAX_CHN;i++)
	{
		if(keypara.key[i].KeyLvl == KEY_VALID_LVL)//�а�������
		{
			if(keypara.key[i].Lstartf)// ������ʼ��־��1��ʾ��ʼ��0��ʾû��ʼ
			{
				if((++keypara.key[i].LTimecnt % 1000) == 0) 
				{
					PropEventFifo(1, i+1, 1, KEY_LONG_BEGIN);
#if  KEY_UPLOAD	
					Touch_Value = KEY_LONG_BEGIN;
					Msg_Upload(1, i +1, 1, &Touch_Value);
#endif
					data_temp = 0;
					m74hc595_All(0);
					for(j=0;j<KEY_MAX_CHN;j++)
					{
						if(j==i)
						{
							keypara.key[j].KeyLOCK = KEY_LOCK;
							led_flag = 0;
						}
						else
						{
							keypara.key[j].KeyLOCK = KEY_UNLOCK;						
						}				
					}

				}
				if(keypara.key[i].LTimecnt == 2000)
				{
//					PropEventFifo(KEY_START_NUM, i+1, SRCEVENT, KEY_LONG_3S);

				}
			}
			else
			{
				if(++keypara.key[i].Time >= 500)//�а�������һֱ��ʱ��ֱ���Ͽ�
				{
					//����������ʼ�¼�
					PropEventFifo(1, i+1, 1, KEY_LONG_BEGIN);
#if  KEY_UPLOAD					
					Touch_Value = KEY_LONG_BEGIN;			
					Msg_Upload(1, i +1, 1, &Touch_Value);
#endif						
					keypara.key[i].LTimecnt   = 0;//�������ִ�����������0
					keypara.key[i].Lstartf    = 1;
					keypara.key[i].KeyLOCK = KEY_LOCK;
					data_temp = 0;
					m74hc595_All(0);
					for(j=0;j<KEY_MAX_CHN;j++)
					{
						if(j==i)
						{
							keypara.key[j].KeyLOCK = KEY_LOCK;
							led_flag=0;
						}
						else
						{
							keypara.key[j].KeyLOCK = KEY_UNLOCK;						
						}				
					}
					
				}
			}
		}
		else//û�а������£�������ʱ����
		{
			keypara.key[i].Time = 0;
			
		}
	}
}
/*****************************************************************************
�� �� ��:  void KeyDeal(INT8U key, INT8U keytmp)
����˵��:  ��������ÿ·��Ԫ�����жϣ��̰�������״̬��
��    ��:  key-��ǰÿ·����״ֵ̬����ϳ��ֽ�
           keytmp-ÿ·�����Ƿ��б仯ֵ����ϳ������ֽ�
�� �� ֵ:  ��
*****************************************************************************/
void KeyDeal(INT16U key, INT16U keytmp)
{
	INT8U i,j;
	for(i=0;i<KEY_MAX_CHN;i++)//KEY_MAX_CHN����ͨ����
	{
		if(keytmp & (1<<i))
		{
			if(keypara.key[i].KeyLvl == KEY_VALID_LVL)                // ������Ч��ƽ������ť���µ�ʵ���ź�
			{
				//�ͷ�
				if(keypara.key[i].Time < 500 && keypara.key[i].Time > 0)
				{
					//�����̰��Ͷ̰��ͷ��¼�
				data_temp &= 3<<9;
				m74hc595_All(data_temp);
				for(j=0;j<KEY_MAX_CHN;j++)
				{
					if(j==i)
					{
						keypara.key[j].KeyLOCK = KEY_LOCK;
						led_flag=0;
					}
					else
					{
						keypara.key[j].KeyLOCK = KEY_UNLOCK;						
					}				
				}
//				PropEventFifo(KEY_START_NUM, i+1, SRCEVENT, KEY_SHORT); //KEY_START_NUM        0 // ������Ԫ��ʼ����
				PropEventFifo(1, i+1, 1, KEY_SHORT);
#if  KEY_UPLOAD					
				Touch_Value = KEY_SHORT;
				Msg_Upload(1, i +1, 1, &Touch_Value);
#endif			
				}
				if(keypara.key[i].Lstartf)
				{
					//���������ͷ��¼�
					PropEventFifo(1, i+1, 1, KEY_LONG_END);
#if  KEY_UPLOAD						
					Touch_Value = KEY_LONG_END;
					Msg_Upload(1, i +1, 1, &Touch_Value);
#endif				
					keypara.key[i].LTimecnt   = 0;//�������ִ�����������0
					keypara.key[i].Lstartf    = 0;	
				}
				keypara.key[i].KeyLvl = KEY_INVALID_LVL;   //KEY_INVALID_LVL    !KEY_VALID_LVL    // ������Ч��ƽ���ް���ʱ�ĵ�ƽ״̬
			}
			else
			{
				//�պ�
				keypara.key[i].KeyLvl = KEY_VALID_LVL;
				keypara.key[i].Time   = 0;
				
			}
			break;
		}
	}
}


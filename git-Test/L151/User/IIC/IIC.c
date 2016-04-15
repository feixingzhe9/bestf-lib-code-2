/***************************************************************
**	��    ��: IIC.c
**  ƽ    ̨��CPU:STM32L151C8T6	
**  ��    �ߣ�Seven
**  ��    �䣺huai_email@126.com
**  �������ڣ�2014/03/21
**  �޸����ڣ�2014/05/27
**  ��    ����V2.0
**  ��    ����ģ��IICЭ��
**
****************************************************************
**  V2.0
**			���к��������Ż���ɾ���������
**			�Ż���ֲ�ӿ�
***************************************************************/


#include "IIC.h"
#include "delay.h"
	
																		
/***************************************************************
**	��	��:		IICʱ����ʱ  -- ����IIC�����ٶ�
**	��  ��:		��
**	��	��:		��	
**	Readme:		1bit cost double delay
				if delay is 5us , IIC Speed is 100k
***************************************************************/
static void IIC_delay(void) 
{
	delay_us(5);	
}

//��ʼ��IIC
void IIC_Init_PORT(void)
{					     
    GPIOx_Cfg(PORT_IIC_SCL, PIN_IIC_SCL, OUT_PU_40M);	
    GPIOx_Cfg(PORT_IIC_SDA, PIN_IIC_SDA, OUT_PU_40M);
}
/***************************************************************
**	��	��:		IIC��ʼ�ź�
**  When SCL is high , SDA change form high to low.
***************************************************************/
void IIC_Start(void)
{
	SDA1;
	SCL1;
	IIC_delay();
	SDA0;
	IIC_delay();
	SCL0;
	IIC_delay();
}
/***************************************************************
**	��	��:		IICֹͣ�ź�
**  When SCL is high , SDA change form low to high.
***************************************************************/
void IIC_Stop(void)
{
   SDA0;
   SCL1;
   IIC_delay();
   SDA1;
   IIC_delay();
}
/***************************************************************
**	��	��:		IIC�ȴ�ACK�ź�
**	��	�أ�	0������
**				1���ȴ���ʱ
**	˵	����	�ú�������ȴ���ʱ������ֹ����
***************************************************************/
u8 IIC_WaitAck(void)
{
    u16 undead = 10000;
	SDA1;
    SDA_IN();  		//����
	SCL1; 
	IIC_delay();
	while(undead--)
	{   
		if(0 == Get_SDA())
	    {
        	SCL0; 
			SDA_OUT();
			SDA1;			
			IIC_delay();			
        	return 0;
	    } 
	}
   	SCL0;	
	SDA_OUT();
	SDA1;
	IIC_delay();		
    return 1;	    
}
/***************************************************************
**	��	��:		IIC����ACK�ź�
***************************************************************/
void IIC_ACK(void)                       
{
	SDA0;			// ACK
	SCL1;	
	IIC_delay();
	SCL0;
	SDA0;
	IIC_delay();
}
/***************************************************************
**	��	��:		IIC����NACK�ź�
***************************************************************/
void IIC_NACK(void)                       
{
	SDA1;			//NO ACK
	SCL1;	
	IIC_delay();
	SCL0;
	SDA0;
	IIC_delay();
}
/***************************************************************
**	��	��:		IIC����һ�ֽ�����
**	��	����	dat	 	���͵�����
***************************************************************/
void IIC_SendByte(u8 dat)
{
    u8 i;
  	for(i=0;i<8;i++)
	{	
	   	if(dat&0x80)    SDA1;
		else    		SDA0;
		dat<<=1;
		SCL1;
		IIC_delay();
		SCL0;
		IIC_delay();	
	}
}
/***************************************************************
**	��	��:		IIC����һ�ֽ�����
**	��	�أ�	���յ�����
***************************************************************/
u8 IIC_GetByte(void)
{	
    u8 i,dat=0;
	SDA_IN();	
    for(i=0;i<8;i++)
	{	
	   SCL1;
	   IIC_delay();
	   dat=dat<<1;
	   if(Get_SDA())	dat |= 0x01;
	   SCL0;
	   IIC_delay();
	}	
    SDA_OUT();   
	SDA1;	
	return dat;  	
}

/***************************************************************
**	��	��:		IIC��ָ����ַдһ�ֽ�����
**	��	����	Addr	��ַ
**				data 	���͵�����
**	��	�أ�	��
***************************************************************/
void IIC_WriteByte(u8 Addr,u8 data)   
{
  	IIC_Start();
	IIC_SendByte(DEVICE_ADDR);	//WriteDeviceAddr
	IIC_WaitAck();
	IIC_SendByte(Addr);
	IIC_WaitAck();
	IIC_SendByte(data);   
	IIC_WaitAck();	
	IIC_Stop(); 
}
/***************************************************************
**	��	��:		IIC��ָ����ַ�ֽ�����
**	��	����	Addr	��ַ
**	��	�أ�	���յ�����
***************************************************************/
u8 IIC_ReadByte(u8 Addr)         
{      
    u8 data;
  	IIC_Start();
	IIC_SendByte(DEVICE_ADDR);
	IIC_WaitAck();
	IIC_SendByte(Addr); 
	IIC_WaitAck();	
	IIC_Start();
	IIC_SendByte(DEVICE_ADDR+1);	//ReadDeviceAddr
	IIC_WaitAck();
	data=IIC_GetByte();
	IIC_NACK();
	IIC_Stop();
	return data;  
}

/***************************************************************
**	��	��:		IIC��ָ����ַ����дN������
**	��	����	Addr	��ַ
**				pData 	��������ָ��   ���ݳ���Ҫ���ݾ���оƬҪ��
**	��	�أ�	��
***************************************************************/
void IIC_WriteDataN(u8 Addr,u8 *pData , u8 Number)
{
	u8 i,*pTemp= pData;
  	IIC_Start();
	IIC_SendByte(DEVICE_ADDR);
	IIC_WaitAck();
	IIC_SendByte(Addr);
	IIC_WaitAck();
    for(i=0;i<Number;i++)  
	{
		IIC_SendByte(*pTemp);
		IIC_WaitAck();
		pTemp++	;
	}
	IIC_Stop(); 
}
																
/***************************************************************
**	��	��:		IIC��ָ����ַ������N������
**	��	����	Addr	��ַ
**				*pData	������ָ��
**				Number 	��������ָ��
**	��	�أ�	��������ָ��
***************************************************************/
void IIC_ReadDataN(u8 Addr,u8 *pData,u8 Number)         
{      
    u8 i,*pTemp= pData;
  	IIC_Start();
	IIC_SendByte(DEVICE_ADDR);
	IIC_WaitAck();	
	IIC_SendByte(Addr);
	IIC_WaitAck();	
	IIC_Start();
	IIC_SendByte(DEVICE_ADDR+1);
	IIC_WaitAck();
    for(i=0;i<Number-1;i++)  
    {    
	    *(pTemp++) = IIC_GetByte();
		IIC_ACK();  
    }
    *(pTemp++) = IIC_GetByte();
	IIC_NACK();
	IIC_Stop();
}





/***************************Copyright BestFu 2014-05-14*************************
文	件：    SysHard.c
说	明：    系统硬件相关函数
编	译：    Keil uVision4 V4.54.0.0
版	本：    v2.0
编	写：    Unarty
日	期：    2014.06.26
修　改：	暂无
*******************************************************************************/
#include "SysHard.h"
#include "sys.h"
#include "SysTick.h"
#include "SI4432.h"
#include "I2C.h"
#include "UserData.h"
																				
/*******************************************************************************
函 数 名：	SysHard_Init
功能说明： 	初始化系统硬件相关内容
参	  数： 	无
返 回 值：	无
*******************************************************************************/
void SysHard_Init(void)
{
	SysTick_Init(32);		//初始化系统时钟
	I2C_Init();				//IIC初始化
	Si4432_Init();			//433无线模块初始化
}

/*******************************************************************************
函 数 名：	HardID_Check
功能说明： 	硬件地址核对
参	  数： 	id: 传入匹配ID
返 回 值：	0（地址匹配成功)/否则返回设备真实ID
*******************************************************************************/
u32 HardID_Check(u32 id)
{
	if((RE_DEVICE_ID_FLAG == (*(u16 *)(RE_DEVICE_ID_START_ADDR)))&&
       (RE_DEVICE_ID != 0xffffffff)&&
       (RE_DEVICE_ID != 0x00000000)&& 
       (RE_DEVICE_ID != 0x44444444)&& 
       (RE_DEVICE_ID != 0x88888888)&&  
       (RE_DEVICE_ID != 0x54534542)&&
       (RE_DEVICE_ID == ~RE_DEVICE_ID_ANTI))                     /**> 如果设置的地址合法 **/
    {
        if(RE_DEVICE_ID != id)
        {
            return RE_DEVICE_ID;
        }
    }
    else
    {
        if (DEVICE_ID != id)
        {
            return DEVICE_ID;
        }
    }
	return 0;
}

/*******************************************************************************
函 数 名：	void HardID_Change(void)
功能说明： 	用于新旧地址的更新
参	  数： 	无
返 回 值：	无
*******************************************************************************/
void HardID_Change(void)			/**> 用于新旧地址更新，Jay Add 2015.11.13 **/
{
	if((RE_DEVICE_ID_FLAG == (*(u16 *)(RE_DEVICE_ID_START_ADDR)))&&
	   (RE_DEVICE_ID != 0xffffffff)&&
	   (RE_DEVICE_ID != 0x00000000)&& 
	   (RE_DEVICE_ID != 0x44444444)&& 
	   (RE_DEVICE_ID != 0x88888888)&&  
	   (RE_DEVICE_ID != 0x54534542)&&
	   (RE_DEVICE_ID == ~RE_DEVICE_ID_ANTI))                     /**> 如果设置的地址合法 **/
	{
		gSysData.deviceID = RE_DEVICE_ID;
	}
}

/**************************Copyright BestFu 2014-05-14*************************/

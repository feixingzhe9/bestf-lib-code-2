/***************************Copyright BestFu 2014-05-14*************************
文	件：	Flash.h
说	明：	STM32F103_Flash操作头文件
编	译：	Keil uVision4 V4.54.0.0
版	本：	v1.0
编	写：	Unarty
日	期：	2013-11-21
修  改:     暂无
*******************************************************************************/
#ifndef __FLASH_H
#define __FLASH_H

#include "BF_type.h"



typedef enum
{
    BUSY     = 0x01,
    PGERR    = 0x04,
    WRITEERR = 0x10,
    EOP      = 0x20
}Flash_SR;

/* Flash Control Register bits */
#define CR_PG                ((u32)0x00000001)
#define CR_PER               ((u32)0x00000002)
#define CR_MER               ((u32)0x00000004)
#define CR_OPTPG             ((u32)0x00000010)
#define CR_OPTER             ((u32)0x00000020)
#define CR_STRT              ((u32)0x00000040)
#define CR_LOCK              ((u32)0x00000080)


void Flash_Unlock(void);
void Flash_lock(void);
u8 FLASH_ErasePage(u32 page_add);
u8 Flash_ProgramHalfWord(u32 add, u16 data);
u8 Flash_Write(u32 add, u32 len, u8 *data);
u8 Flash_WriteProtect(u32 addr, u8 sta);
u8 Flash_EraseOptionByte(void);
u8 Flash_WriteOptionByte(u32 addr, u8 data);

#endif /*FLASH_H */

/**************************Copyright BestFu 2014-05-14*************************/

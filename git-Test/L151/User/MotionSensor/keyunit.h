#ifndef __KEYUNIT_H
#define __KEYUNIT_H

#include "gpio.h"
#include "stdio.h"	 
#include "BF_type.h"	

#define KEY_UPLOAD			1	//����ʵʱ�ϱ�ʹ�ܱ��

#define KEY_MAX_CHN  	14
#define KEY_START_NUM 	1

#define  KEY_SHORT              1
//#define  KEY_SHORT_END          2
#define  KEY_LONG_BEGIN         3
#define  KEY_LONG_KEEP          4
#define  KEY_LONG_END           5
#define  KEY_LONG_3S            6      
#define  KEY_LONG               2





typedef struct
{
	u8  KeyLvl;    // ������ƽ��1��ʾ��Ч��0��ʾ��Ч
	u8  Lstartf;   // ������ʼ��־��1��ʾ��ʼ��0��ʾû��ʼ
	u16  Time;      // ʱ�������������ȷ���̰����ǳ���
	u16  LTimecnt;  // �������֣��������
	u8 KeyLOCK;
	u16 count;
}KeyItem;

typedef struct
{
	KeyItem   key[KEY_MAX_CHN];
}KeyTable;

extern KeyTable keypara;

#define  KEY_VALID_LVL             1          // ������Ч��ƽ������ť���µ�ʵ���ź�
#define  KEY_INVALID_LVL    !KEY_VALID_LVL    // ������Ч��ƽ���ް���ʱ�ĵ�ƽ״̬

#define KEY_LOCK 1
#define KEY_UNLOCK !KEY_LOCK 
#define LOCK_TIME 150  

void KeyDeal(u16 key, u16 keytmp);
void KeyTimeCnt(void);
void KeyScan(void);



#endif	   

















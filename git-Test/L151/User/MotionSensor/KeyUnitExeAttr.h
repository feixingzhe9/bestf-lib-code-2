/***************************************************************
**	��    ��: Cube20ExeAttr.c
**  ƽ    ̨��MDK V5.10	
**  ��    �ߣ�Seven
**  �������ڣ�2014/05/26
**  �޸����ڣ�2014/05/26
**  ��    ����V1.0
**  ��    ����20����Ӧ�ò�ӿ�
***************************************************************/
#ifndef		_CUBE20_EXE_ATTR_H_
#define		_CUBE20_EXE_ATTR_H_

#include "BF_type.h"
#include "UnitCfg.h"

extern const AttrExe_st Cube6AttrOperatTab[];

void  Cube6Init(INT8U unitID);
void  Cube6EepromInit(INT8U unitID);


MsgResult_t Get_Touch_Attr(UnitPara_t *pdata, INT8U *rlen, INT8U *rpara);

void Cube6Checking_Attr(void);

#endif

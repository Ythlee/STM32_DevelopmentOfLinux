#ifndef _TSENSOR_H
#define _TSENSOR_H

#include "sys.h"

short Get_Temprate(void);			//��ȡ�ڲ��¶ȴ��������¶�ֵ

void T_Adc_Init(void);				//ADCͨ����ʼ��

u16 T_Get_Adc(u8 ch);				//���ĳ��ͨ����ֵ

u16 T_Get_Adc_Average(u8 ch, u8 times);		//���ĳ��ͨ����ƽ������ֵ






#endif

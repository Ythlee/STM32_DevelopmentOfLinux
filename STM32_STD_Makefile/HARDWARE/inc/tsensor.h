#ifndef _TSENSOR_H
#define _TSENSOR_H

#include "sys.h"

short Get_Temprate(void);			//获取内部温度传感器的温度值

void T_Adc_Init(void);				//ADC通道初始化

u16 T_Get_Adc(u8 ch);				//获得某个通道的值

u16 T_Get_Adc_Average(u8 ch, u8 times);		//获得某个通道的平均采样值






#endif

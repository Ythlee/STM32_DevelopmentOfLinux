#ifndef _RTC_H
#define _RTC_H

#include "sys.h"

typedef struct
{
	vu8 hour;
	vu8 min;
	vu8 sec;
	// 公立日月年周
	vu16 w_year;
	vu8  w_month;
	vu8  w_date;
	vu8  week;
}_calendar_obj;

extern _calendar_obj calendar;	//日历结构体
extern u8 const mon_table[12];	//月份日期数据表

void Disp_Time(u8 x, u8 y, u8 size);		//在定制的位置开始显示时间
void Disp_Week(u8 x, u8 y, u8 size, u8 lang);		//在指定的位置显示星期

u8 RTC_Init(void);		//RTC初始化
u8 Is_Leap_Year(u16 year);	//平年闰年判断
u8 RTC_Alarm_Set(u16 syear, u8 smon, u8 sday, u8 hour, u8 min, u8 sec);	
u8 RTC_Get(void);	//跟新时间
u8 RTC_Get_Week(u16 year, u8 month, u8 day);
u8 RTC_Set(u16 syear,u8 smon, u8 sday, u8 hour, u8 min, u8 sec);	//设置时间




#endif



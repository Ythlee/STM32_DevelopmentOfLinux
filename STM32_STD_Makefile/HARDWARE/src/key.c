#include "sys.h"
#include "key.h"
#include "delay.h"

void KEY_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOE, ENABLE);

	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPD;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStruct);

	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_2;
	GPIO_Init(GPIOE, &GPIO_InitStruct);
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_3;
	GPIO_Init(GPIOE, &GPIO_InitStruct);
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_4;
	GPIO_Init(GPIOE, &GPIO_InitStruct);
}


u8 KEY_Scan(void)
{
	if(KEY0==1 || KEY1==0 || KEY2==0 || KEY3==0)	//有按键按下
	{
		delay_ms(10);	//去抖动
		if(KEY0 == 1)
			return KEY0_PRESS;
		else if(KEY1 == 0)
			return KEY1_PRESS;
		else if(KEY2 == 0)
			return KEY2_PRESS;
		else if(KEY3 == 0)
			return KEY3_PRESS;
	}
	return 0;
}



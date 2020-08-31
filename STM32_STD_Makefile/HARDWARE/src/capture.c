#include "sys.h"
#include "capture.h"

u8 TIM5_CH1_CAPTHURE_STA = 0;	//���벶��״̬
u16 TIM5_CH1_CAPTHURE_VAL;	//���벶��ֵ

void TIM5_Cap_Init(u16 arr, u16 psc)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
	TIM_ICInitTypeDef TIM_ICInitStruct;
	NVIC_InitTypeDef NVIC_InitStruct;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPD;
	GPIO_Init(GPIOA, &GPIO_InitStruct);
	GPIO_ResetBits(GPIOA, GPIO_Pin_0);

	TIM_TimeBaseInitStruct.TIM_Period = arr;
	TIM_TimeBaseInitStruct.TIM_Prescaler = psc;
	TIM_TimeBaseInitStruct.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM5, &TIM_TimeBaseInitStruct);

	TIM_ICInitStruct.TIM_Channel = TIM_Channel_1;
	TIM_ICInitStruct.TIM_ICFilter = 0x00;
	TIM_ICInitStruct.TIM_ICPolarity = TIM_ICPolarity_Rising;
	TIM_ICInitStruct.TIM_ICSelection = TIM_ICSelection_DirectTI;
	TIM_ICInitStruct.TIM_ICPrescaler = TIM_ICPSC_DIV1;

	TIM_ICInit(TIM5, &TIM_ICInitStruct);

	NVIC_InitStruct.NVIC_IRQChannel = TIM5_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 2;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 2;
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStruct);

	TIM_ITConfig(TIM5, TIM_IT_Update | TIM_IT_CC1, ENABLE);
	TIM_Cmd(TIM5, ENABLE);

}


void TIM5_IRQHandler(void)
{
	if((TIM5_CH1_CAPTHURE_STA & 0x80) == 0)	//��δ�ɹ�����
	{
		if(TIM_GetITStatus(TIM5, TIM_IT_Update) != RESET)
		{
			if(TIM5_CH1_CAPTHURE_STA & 0x40)	//�ɹ�����ߵ�ƽ
			{
				if((TIM5_CH1_CAPTHURE_STA & 0x3f) == 0x3f)	//�ߵ�ƽ̫����
				{
					TIM5_CH1_CAPTHURE_STA |= 0x80;
					TIM5_CH1_CAPTHURE_VAL = 0xffff;
				}else TIM5_CH1_CAPTHURE_STA++;
			}
		}
		if(TIM_GetITStatus(TIM5, TIM_IT_CC1) != RESET)
		{
			if(TIM5_CH1_CAPTHURE_STA & 0x40)						//����һ���½���
			{
				TIM5_CH1_CAPTHURE_STA |= 0x80;						//��ǳɹ�����һ��������
				TIM5_CH1_CAPTHURE_VAL = TIM_GetCapture1(TIM5);
				TIM_OC1PolarityConfig(TIM5, TIM_OCPolarity_High); 	//����Ϊ�����ز���
			}
			else
			{
				TIM5_CH1_CAPTHURE_STA = 0;
				TIM5_CH1_CAPTHURE_VAL = 0;
				TIM_SetCounter(TIM5, 0);
				TIM5_CH1_CAPTHURE_STA |= 0x40;						//��ǲ�����������
				TIM_OC1PolarityConfig(TIM5, TIM_OCPolarity_Low);	//����Ϊ�½��ز���
			}
		}
		
	}

	TIM_ClearITPendingBit(TIM5, TIM_IT_CC1 | TIM_IT_Update);		//����ն˱��λ
}



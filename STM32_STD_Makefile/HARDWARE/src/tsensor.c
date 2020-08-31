#include "sys.h"
#include "tsensor.h"
#include "delay.h"

void T_Adc_Init(void)
{
	ADC_InitTypeDef ADC_InitStruct;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);
	RCC_ADCCLKConfig(RCC_PCLK2_Div6);

	ADC_DeInit(ADC1);

	ADC_InitStruct.ADC_Mode = ADC_Mode_Independent;
	ADC_InitStruct.ADC_ScanConvMode = DISABLE;
	ADC_InitStruct.ADC_ContinuousConvMode = ENABLE;
	ADC_InitStruct.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
	ADC_InitStruct.ADC_DataAlign = ADC_DataAlign_Right;
	ADC_InitStruct.ADC_NbrOfChannel = 1;

	ADC_Init(ADC1, &ADC_InitStruct);
	ADC_TempSensorVrefintCmd(ENABLE);		//�����ڲ��¶ȴ�����
	ADC_Cmd(ADC1, ENABLE);

	ADC_ResetCalibration(ADC1);
	while(ADC_GetResetCalibrationStatus(ADC1));
	ADC_StartCalibration(ADC1);
	while(ADC_GetCalibrationStatus(ADC1));
	
}


u16 T_Get_Adc(u8 ch)
{
	ADC_RegularChannelConfig(ADC1, ch, 1, ADC_SampleTime_239Cycles5);
	ADC_SoftwareStartConvCmd(ADC1, ENABLE);

	while(!ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC));
	
	return ADC_GetConversionValue(ADC1);
}

u16 T_Get_Adc_Average(u8 ch, u8 times)
{
	u32 temp_val = 0;
	u8 t;
	for(t = 0; t < times; t++)
	{
		temp_val += T_Get_Adc(ch);
		delay_ms(5);
	}

	return temp_val / times;
}

//�õ�ADC�����ڲ��¶ȴ�������ֵ
//ȡ10��,Ȼ��ƽ��
u16 T_Get_Temp(void)
{
	u16 temp_val = 0;
	u8 t;
	for(t = 0; t < 10; t++)
	{
		temp_val += T_Get_Adc(ADC_Channel_16);	  //TampSensor
		delay_ms(5);
	}

	return temp_val / 10;
}



//�õ��¶�ֵ
//����ֵ:�¶�ֵ(������100��,��λ:��.)
short Get_Temprate(void)	//��ȡ�ڲ��¶ȴ������¶�ֵ
{
	u32 adcx;
	short result;
 	double temperate;
	adcx = T_Get_Adc_Average(ADC_Channel_16, 20);	//��ȡͨ��16,20��ȡƽ��
	temperate = (float)adcx * (3.3 / 4096);		//��ѹֵ 
	temperate = (1.43 - temperate) / 0.0043 + 25;	//ת��Ϊ�¶�ֵ 	 
	result=temperate*=100;					//����100��.
	return result;
}















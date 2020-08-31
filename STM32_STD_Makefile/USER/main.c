#include "led.h"
#include "delay.h"
#include "key.h"
#include "sys.h"
#include "lcd.h"
#include "usart.h"
#include "ds18b20.h"

/************************************************
  ALIENTEKս��STM32������ʵ��30
  DS18B20�����¶ȴ����� ʵ��
  ����֧�֣�www.openedv.com
  �Ա����̣�http://eboard.taobao.com
  ��ע΢�Ź���ƽ̨΢�źţ�"����ԭ��"����ѻ�ȡSTM32���ϡ�
  ������������ӿƼ����޹�˾
  ���ߣ�����ԭ�� @ALIENTEK
 ************************************************/


int main(void)
{
	float temperature = 1.1111;

	delay_init();			 //��ʱ������ʼ��
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//�����ж����ȼ�����Ϊ��2��2λ��ռ���ȼ���2λ��Ӧ���ȼ�
	uart_init(115200);		//���ڳ�ʼ��Ϊ 115200
	LED_Init();				//��ʼ����LED���ӵ�Ӳ���ӿ�

	while(1)
	{
		delay_ms(10);
		printf("\t [main] : this is test float number: %f\r\n", temperature);
	}
}


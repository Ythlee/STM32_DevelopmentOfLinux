#include "led.h"
#include "delay.h"
#include "key.h"
#include "sys.h"
#include "lcd.h"
#include "usart.h"
#include "ds18b20.h"

/************************************************
  ALIENTEK战舰STM32开发板实验30
  DS18B20数字温度传感器 实验
  技术支持：www.openedv.com
  淘宝店铺：http://eboard.taobao.com
  关注微信公众平台微信号："正点原子"，免费获取STM32资料。
  广州市星翼电子科技有限公司
  作者：正点原子 @ALIENTEK
 ************************************************/


int main(void)
{
	float temperature = 1.1111;

	delay_init();			 //延时函数初始化
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//设置中断优先级分组为组2：2位抢占优先级，2位响应优先级
	uart_init(115200);		//串口初始化为 115200
	LED_Init();				//初始化与LED连接的硬件接口

	while(1)
	{
		delay_ms(10);
		printf("\t [main] : this is test float number: %f\r\n", temperature);
	}
}


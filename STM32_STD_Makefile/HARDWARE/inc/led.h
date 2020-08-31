#ifndef _LED_H
#define _LED_H

#define LED1 PBout(5)
#define LED2 PEout(5)

#define LED1_ON GPIO_ResetBits(GPIOB, GPIO_Pin_5)
#define LED2_ON GPIO_ResetBits(GPIOE, GPIO_Pin_5)

#define LED1_OFF GPIO_SetBits(GPIOB, GPIO_Pin_5)
#define LED2_OFF GPIO_SetBits(GPIOE, GPIO_Pin_5)

void LED_Init(void);	//LED≥ı ºªØ

void LED_Twink(void);	//LED…¡À∏








#endif


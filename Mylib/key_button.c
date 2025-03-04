#include "key_button.h"
#include "delay.h"
#include "led.h"
#include "usart6_vision.h"

//void EXTI0_IRQHandler(void)
//{
//	delay_ms(10);	//消抖
//	if(KEY2==0)	  
//	{				 
//   LED0=!LED0; 
//	}		 
//	 EXTI_ClearITPendingBit(EXTI_Line0);//清除LINE2上的中断标志位 
//}


uint8_t buff_start[]={0xBB,0x01,0xDD};
void EXTI0_IRQHandler(void)
{
	delay_ms(10);	//消抖
	if(KEY2==0)	  
	{				 
		
		/*
		 测试使用 ：
		用于表示 同意识别
		
		*/
		USART6_SendBuff(buff_start,3);
	}	 
	 EXTI_ClearITPendingBit(EXTI_Line0); //清除LINE0上的中断标志位 
}	

void EXTI1_IRQHandler(void)
{
	delay_ms(10);	//消抖
	if(KEY1==0)	  
	{		
//flow_led_toggle(0);
//flow_led_toggle(1);flow_led_toggle(2);flow_led_toggle(3);flow_led_toggle(5);flow_led_toggle(6);
//		flow_led_toggle(7);
//  flow_led_toggle(4);
	}	 
	 EXTI_ClearITPendingBit(EXTI_Line1); //清除LINE0上的中断标志位 
}


//按键初始化函数
void KEY_Init(void)
{
	
	GPIO_InitTypeDef  GPIO_InitStructure;
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);//使能GPIOA,GPIOE时钟
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1; //KEY0 KEY1 KEY2对应引脚
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;//普通输入模式
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100M
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//上拉
  GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化GPIOE2,3,4
 
} 


void EXTIX_Init(void)
{
	NVIC_InitTypeDef   NVIC_InitStructure;
	EXTI_InitTypeDef   EXTI_InitStructure;
	
	KEY_Init(); //按键对应的IO口初始化
 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);//使能SYSCFG时钟
	
 
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOA, EXTI_PinSource1);//PE2 连接到中断线2
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOA, EXTI_PinSource0);//PE2 连接到中断线2

	/* 配置EXTI_Line2,3,4 */
	EXTI_InitStructure.EXTI_Line = EXTI_Line1 ;
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;//中断事件
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling; //下降沿触发
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;//中断线使能
  EXTI_Init(&EXTI_InitStructure);//配置
	
	
		EXTI_InitStructure.EXTI_Line = EXTI_Line0 ;
	  EXTI_Init(&EXTI_InitStructure);//配置
	
	
	
	NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn;//外部中断2
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x03;//抢占优先级3
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02;//子优先级2
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;//使能外部中断通道
  NVIC_Init(&NVIC_InitStructure);//配置
	
		NVIC_InitStructure.NVIC_IRQChannel = EXTI1_IRQn;//外部中断2
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x03;//抢占优先级3
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02;//子优先级2
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;//使能外部中断通道
  NVIC_Init(&NVIC_InitStructure);//配置

	   
}


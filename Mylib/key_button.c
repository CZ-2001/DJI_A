#include "key_button.h"
#include "delay.h"
#include "led.h"
#include "usart6_vision.h"

//void EXTI0_IRQHandler(void)
//{
//	delay_ms(10);	//����
//	if(KEY2==0)	  
//	{				 
//   LED0=!LED0; 
//	}		 
//	 EXTI_ClearITPendingBit(EXTI_Line0);//���LINE2�ϵ��жϱ�־λ 
//}


uint8_t buff_start[]={0xBB,0x01,0xDD};
void EXTI0_IRQHandler(void)
{
	delay_ms(10);	//����
	if(KEY2==0)	  
	{				 
		
		/*
		 ����ʹ�� ��
		���ڱ�ʾ ͬ��ʶ��
		
		*/
		USART6_SendBuff(buff_start,3);
	}	 
	 EXTI_ClearITPendingBit(EXTI_Line0); //���LINE0�ϵ��жϱ�־λ 
}	

void EXTI1_IRQHandler(void)
{
	delay_ms(10);	//����
	if(KEY1==0)	  
	{		
//flow_led_toggle(0);
//flow_led_toggle(1);flow_led_toggle(2);flow_led_toggle(3);flow_led_toggle(5);flow_led_toggle(6);
//		flow_led_toggle(7);
//  flow_led_toggle(4);
	}	 
	 EXTI_ClearITPendingBit(EXTI_Line1); //���LINE0�ϵ��жϱ�־λ 
}


//������ʼ������
void KEY_Init(void)
{
	
	GPIO_InitTypeDef  GPIO_InitStructure;
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);//ʹ��GPIOA,GPIOEʱ��
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1; //KEY0 KEY1 KEY2��Ӧ����
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;//��ͨ����ģʽ
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100M
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//����
  GPIO_Init(GPIOA, &GPIO_InitStructure);//��ʼ��GPIOE2,3,4
 
} 


void EXTIX_Init(void)
{
	NVIC_InitTypeDef   NVIC_InitStructure;
	EXTI_InitTypeDef   EXTI_InitStructure;
	
	KEY_Init(); //������Ӧ��IO�ڳ�ʼ��
 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);//ʹ��SYSCFGʱ��
	
 
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOA, EXTI_PinSource1);//PE2 ���ӵ��ж���2
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOA, EXTI_PinSource0);//PE2 ���ӵ��ж���2

	/* ����EXTI_Line2,3,4 */
	EXTI_InitStructure.EXTI_Line = EXTI_Line1 ;
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;//�ж��¼�
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling; //�½��ش���
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;//�ж���ʹ��
  EXTI_Init(&EXTI_InitStructure);//����
	
	
		EXTI_InitStructure.EXTI_Line = EXTI_Line0 ;
	  EXTI_Init(&EXTI_InitStructure);//����
	
	
	
	NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn;//�ⲿ�ж�2
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x03;//��ռ���ȼ�3
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02;//�����ȼ�2
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;//ʹ���ⲿ�ж�ͨ��
  NVIC_Init(&NVIC_InitStructure);//����
	
		NVIC_InitStructure.NVIC_IRQChannel = EXTI1_IRQn;//�ⲿ�ж�2
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x03;//��ռ���ȼ�3
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02;//�����ȼ�2
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;//ʹ���ⲿ�ж�ͨ��
  NVIC_Init(&NVIC_InitStructure);//����

	   
}


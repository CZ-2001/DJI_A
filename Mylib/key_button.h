 #include "stm32f4xx.h"

#include "sys.h"  	
//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEK STM32F407������
//�ⲿ�ж� ��������	   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//��������:2014/5/4
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2014-2024
//All rights reserved									  
////////////////////////////////////////////////////////////////////////////////// 	 

#define KEY2 		GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0) //PE2
#define LED0 PGout(1)	// DS1	 
#define KEY1 		GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_1) //PE2

extern void EXTIX_Init(void);

//void EXTIX_Init(void);	//�ⲿ�жϳ�ʼ��		 					    

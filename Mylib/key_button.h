 #include "stm32f4xx.h"

#include "sys.h"  	
//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//ALIENTEK STM32F407开发板
//外部中断 驱动代码	   
//正点原子@ALIENTEK
//技术论坛:www.openedv.com
//创建日期:2014/5/4
//版本：V1.0
//版权所有，盗版必究。
//Copyright(C) 广州市星翼电子科技有限公司 2014-2024
//All rights reserved									  
////////////////////////////////////////////////////////////////////////////////// 	 

#define KEY2 		GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0) //PE2
#define LED0 PGout(1)	// DS1	 
#define KEY1 		GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_1) //PE2

extern void EXTIX_Init(void);

//void EXTIX_Init(void);	//外部中断初始化		 					    

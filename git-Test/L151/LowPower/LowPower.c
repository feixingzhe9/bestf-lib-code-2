/*******************************************************************************
**	��    ��: LowPower.c
**  ��    �ܣ�STM32L151 �͹�������
**  ��    �룺Keil uVision5 V5.10
**	о    Ƭ: STM32L151xx
**  ��    ����V1.0.0
**  �������ڣ�2014.07.10
**  �޸����ڣ�2014.07.10
**  ˵    ����  
********************************************************************************/
#include "gpio.h"
#include "LowPower.h"
#include "Cube6.h"
#include "SysHard.h"

#define CR_VOS_MASK              ((uint32_t)0xFFFFE7FF)
#define PWR_VoltageScaling_Range1       PWR_CR_VOS_0
#define PWR_VoltageScaling_Range2       PWR_CR_VOS_1
#define PWR_VoltageScaling_Range3       PWR_CR_VOS

INT8U In_Lpm_Flag = 0;


void WKUP_Port_Init(void)
{
	GPIOx_Cfg(GPIO_A, pin_0, IN_DOWN);
}

void Get_WKUP_State(void)
{
	if( pin_0 == GPIOx_Get(GPIO_A, pin_0))	In_Lpm_Flag = 0;  // ˯�ߵȴ�ʱ�����¼�ʱ
}

/*******************************************************************************
**��	��:  	RunAndCheck_StandbyMode()
**��	��:  	100ms ����һ��  ��ʱ15s ����StandBy ģʽ
**��    ��:  	no
**��	��:  	no
**˵	����	Seven modify 2014.04.04
********************************************************************************/
void CheckStandbyMode(void)
{
	if(In_Lpm_Flag++>=100)
	{
		In_Lpm_Flag = 0;
		#if (LPM_EN>0)
			Standby_Mode();
		#endif			
	}    
}

#if (LPM_EN > 0)

void Low_Power_Select(INT8U LPM)
{
//	WriteEepromPara((INT8U *)&g_stEeEx.Sys.Board.SerialNo,sizeof(g_stEeEx.Sys.Board.SerialNo));
	switch(LPM)
	{
		case 0://˯��ģʽ
			Sleep_Mode();
			break;
		case 1://�͵�ѹ����
			LP_Run_Mode();
			break;
		case 2://�͵�ѹ˯��ģʽ
			
			break;
		case 3://ֹͣģʽ
			Stop_Mode();
			break;
		case 4://����ģʽ
			Standby_Mode();
			break;
	}
}
void Sleep_Mode(void)
{
	Close_device();
	//LPM_IO_process();
	
	RCC->APB1ENR|=1<<28;    //ʹ�ܵ�Դʱ��	
	PWR->CR &= ~(3<<0);		//���PDDS ��LPDSR
	PWR->CR |= 1<<0;		//set LPDSR
	/* Clear SLEEPDEEP bit of Cortex System Control Register */
	SCB->SCR &= (uint32_t)~((uint32_t)SCB_SCR_SLEEPDEEP);
	__WFI();				 //ִ��WFIָ��	
}
/* PWR_EnterLowPowerRunMode */
void LP_Run_Mode(void)
{
//	RCC->APB1ENR |= 1<<28;  //ʹ�ܵ�Դʱ��
//	PWR_VoltageScalingConfig(PWR_VoltageScaling_Range2);//1.5v
//	PWR->CR |= PWR_CR_LPSDSR;
//    PWR->CR |= PWR_CR_LPRUN;   	
}

void Stop_Mode(void)
{
//	/*�ر�spi2 ��tim3*/
//	Close_device();
//	/*IOģ������*/
//	LPM_IO_process();
//	
//	/*����low power mode*/
//	LP_Run_Mode();
//	RCC->APB1ENR|=1<<28;     //ʹ�ܵ�Դʱ��	

//	PWR_VoltageScalingConfig(PWR_VoltageScaling_Range2);//1.5v
//	 
//	PWR->CR &= ~(3<<0);		//���PDDS ��LPDSR
//	PWR->CR |= 1<<0;		//set LPDSR
//	/* Set SLEEPDEEP bit of Cortex System Control Register */
//	SCB->SCR |= SCB_SCR_SLEEPDEEP;
//	RCC->APB1ENR &= ~(1<<28);     /*�رյ�Դʱ��*/	
//	__WFI();
//	/* Reset SLEEPDEEP bit of Cortex System Control Register */
//	SCB->SCR &= (uint32_t)~((uint32_t)SCB_SCR_SLEEPDEEP);  	
}

//����ģʽ
void Standby_Mode(void)
{
	//���ж�
	SysTick->CTRL = 0;					//Systick
	NVIC_DisableIRQ(EXTI15_10_IRQn);	//si4432�ж�	
	NVIC_DisableIRQ(USART1_IRQn);		//����1�ж�
	DisableIRQ();						//��ֹ�����ж�
	
	//Close_device();
	//LPM_IO_process();	
	RF_SWITCH_OFF; 			//433����˯��	
	SPI2->CR1  	 &= ~(1<<6); 	//�ر�SPI2
	RCC->APB1ENR &= ~(1<<14);   //�ر�SPI2ʱ��
	RCC->APB2ENR &= ~(1<<14);   //�ر�USART1ʱ��
	RCC->AHBRSTR |= 1<<0;  		//Reset GPIOA
	
	
	RCC->APB1ENR|=1<<28;     //ʹ�ܵ�Դʱ��	 
	/* Set SLEEPDEEP bit	: Select SleepDeep mode*/
	SCB->SCR|= SCB_SCR_SLEEPDEEP;	
	/* Set PDDS bit			: Select STANDBY mode */
	PWR->CR |= PWR_CR_PDDS; 
	/* Set CWUF bit			: Clear Wakeup flag */
	PWR->CR |= PWR_CR_CWUF; 	
	/* Set EWUP1 bit		: Enable EWUP pin 1 :PA0*/
	PWR->CSR|= PWR_CSR_EWUP1;
	/* Request Wait For Interrupt */
	__WFI();
}


void Close_device(void)
{
	TIM3->CR1  &= ~(1<<0);  
	SPI2->CR1  &= ~(1<<6); 
	WWDG->CR   &= ~(1<<7);		//�رտ��Ź�
	RCC->APB1ENR &= ~(1<<1);	//�ر�TIM3ʱ��
	RCC->APB1ENR &= ~(1<<14);   //�ر�SPI2ʱ��
	RCC->APB1ENR &= ~(1<<11);   //�ر�SPI2ʱ��
}

void LPM_IO_process(void)
{	
#if 1 //standby
	RCC->AHBRSTR |= 1<<0;  //Reset GPIOA
#endif

}
/**
  * @brief  Configures the voltage scaling range.
  * @note   During voltage scaling configuration, the system clock is stopped 
  *         until the regulator is stabilized (VOSF = 0). This must be taken 
  *         into account during application developement, in case a critical 
  *         reaction time to interrupt is needed, and depending on peripheral 
  *         used (timer, communication,...).
  *             
  * @param  PWR_VoltageScaling: specifies the voltage scaling range.
  *   This parameter can be:
  *     @arg PWR_VoltageScaling_Range1: Voltage Scaling Range 1 (VCORE = 1.8V).
  *     @arg PWR_VoltageScaling_Range2: Voltage Scaling Range 2 (VCORE = 1.5V).
  *     @arg PWR_VoltageScaling_Range3: Voltage Scaling Range 3 (VCORE = 1.2V) 
  * @retval None
  */
void PWR_VoltageScalingConfig(uint32_t PWR_VoltageScaling)
{
  uint32_t tmp = 0;
  
  tmp = PWR->CR;

  tmp &= CR_VOS_MASK;
  tmp |= PWR_VoltageScaling;
  
  PWR->CR = tmp & 0xFFFFFFF3;

}
void EXTI0_IRQHandler(void)
{	
	EXTI->PR = 1<<0;  //���LINE0�ϵ��жϱ�־λ 
} 
#endif

void StandbyCountReset(void)
{
}






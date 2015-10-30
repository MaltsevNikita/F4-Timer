#include "main.h"


__IO uint16_t delay_count=0;


uint8_t	Mode=0;
uint16_t Mode_count=0;
uint8_t Mode_new=0;
  
uint8_t Button_count=0;
uint8_t Button_state=0;

char Send_buffer[100];
uint8_t Send_count=0;

uint8_t Recieve_buf[256];
uint8_t Recieve_W=0, Recieve_R=0, Recieve_C=0;
 
uint8_t SPI_En=0;
extern uint8_t sec2;

//----------------------------------------------
//
//----------------------------------------------
void SysTick_Handler(void)//1ms
{
	if (delay_count > 0)
	{
		delay_count--;
	}
}

//----------------------------------------------
//
//----------------------------------------------
void USART2_IRQHandler(void)
{
	if (USART_GetITStatus(USART2, USART_IT_TXE) == SET)
	{
		USART_ClearITPendingBit(USART2, USART_IT_TXE);
		
		if (Send_buffer[Send_count] != 0)
		{
			USART_SendData(USART2, Send_buffer[Send_count]);
			Send_count++;
		} else {
			Send_count = 0;
			USART_ITConfig(USART2, USART_IT_TXE, DISABLE);
		}
	}
	if (USART_GetITStatus(USART2, USART_IT_RXNE) == SET)
	{
		USART_ClearITPendingBit(USART2, USART_IT_RXNE);
		
		Recieve_buf[Recieve_W] = USART_ReceiveData(USART2);
		Recieve_W++;
		Recieve_C++;
	}
}

//----------------------------------------------
//
//----------------------------------------------
void SendtoPC(void)
{
	USART_SendData(USART2, Send_buffer[Send_count]);
	Send_count++;
	USART_ITConfig(USART2, USART_IT_TXE, ENABLE);
}

//----------------------------------------------
//
//----------------------------------------------
void delay_ms(uint16_t delay_temp)
{
	delay_count = delay_temp;
	
	while(delay_count){}
}


//----------------------------------------------
//
//----------------------------------------------
void SendStrtoPC(char* str_p, uint16_t count)
{
		uint16_t i=0;
		
		while(i < count)
		{
			while(USART_GetFlagStatus(USART2, USART_FLAG_TC) == RESET){}
			USART_SendData(USART2, str_p[i]);
			i++;
		}
}

//----------------------------------------------
//
//----------------------------------------------
void DMA1_Stream6_IRQHandler(void)
{
	if (DMA_GetITStatus(DMA1_Stream6, DMA_IT_TCIF6) == SET)
	{
		DMA_ClearITPendingBit(DMA1_Stream6, DMA_IT_TCIF6);
	}
}

//----------------------------------------------
//
//----------------------------------------------
int main(void)
{  
  uint8_t i=0;
	
	LEDs_ini();
	//Button_ini();
	 
	SystemCoreClockUpdate();
	SysTick_Config(SystemCoreClock/1000);//1 ms
	
	timer_ini();

	while(1)
	{ 
//		BLUE_ON();
//		delay_ms(500);
//		BLUE_OFF();
//		delay_ms(500);
	}
}


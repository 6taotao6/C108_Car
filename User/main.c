#include "headfile.h"

uint8_t KeyNum;

uint16_t TIM_10ms; // 全局计数

char txt[20];
int main(void)
{
	OLED_Init();
	Motor_Init();
	AD_Init();
	Timer_Init();
	PID_Parameter_Init(&TurnPID); // 速度PID结构体初始化

	//	OLED_ShowString(1, 1, "Speed:");

	while (1)
	{
//		OLED_ShowString(1, 1, "LX");
//		OLED_ShowNum(1, 3, AD0[ADC_DATA], 4);
//		
//		OLED_ShowString(2, 1, "LY");
//		OLED_ShowNum(2, 3, AD1[ADC_DATA], 4);
//		
//		OLED_ShowString(3, 1, "RY");
//		OLED_ShowNum(3, 3, AD2[ADC_DATA], 4);
//		
//		OLED_ShowString(4, 1, "RX");
//		OLED_ShowNum(4, 3, AD3[ADC_DATA], 4);

//		OLED_ShowNum(1, 8, ADC_Left_X, 3);
//		OLED_ShowNum(2, 8, ADC_Left_Y, 3);
//		OLED_ShowNum(3, 8, ADC_Left_Y, 3);
//		OLED_ShowNum(4, 8, ADC_Right_X, 3);

//		OLED_ShowSignedNum(1, 12, Speed, 3);
//		OLED_ShowSignedNum(2, 12, error, 4);
//		OLED_ShowSignedNum(3, 12, Turn_PWM, 4);
//		OLED_ShowNum(4, 12, TIM_10ms, 5);
///////////////////////////////////////////////////////////////////////		
		
		sprintf(txt, "LX%04dRX%04dr%d ", AD0[ADC_DATA],AD3[ADC_DATA],error);
    OLED_ShowString(1, 1, txt);
		
		sprintf(txt, "LY%04dRY%04d", AD1[ADC_DATA],AD2[ADC_DATA]);
    OLED_ShowString(2, 1, txt);
		
		sprintf(txt, "LX%04d RX%04d", ADC_Left_X,ADC_Right_X);
    OLED_ShowString(3, 1, txt);
		
		sprintf(txt, "LY%04d RY%04d", ADC_Left_Y,ADC_Left_Y );
    OLED_ShowString(4, 1, txt);		
		
//	  sprintf(txt, "r %d", error);
//    OLED_ShowString(3, 1, txt);
		//		KeyNum = Key_GetNum();
		//		if (KeyNum == 1)
		//		{
		//			Speed += 20;
		//			if (Speed > 100)
		//			{
		//				Speed = -100;
		//			}
		//		}
	}
}

void TIM2_IRQHandler(void) // 10ms
{
	if (TIM_GetITStatus(TIM2, TIM_IT_Update) == SET)
	{
		TIM_10ms++;

		ADC_Handle();

		Motor_Handle();

		TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
	}
}

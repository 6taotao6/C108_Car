#include "stm32f10x.h" // Device header
#include "PWM.h"
#include "PID.h"
#include "AD.h"

int16_t Speed = 35;

int16_t Turn_PWM;

void Motor_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);

	GPIO_InitTypeDef GPIO_InitStructureB;

	GPIO_InitStructureB.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructureB.GPIO_Pin = GPIO_Pin_10 | GPIO_Pin_11;
	GPIO_InitStructureB.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructureB);

	GPIO_InitTypeDef GPIO_InitStructureA;
	GPIO_InitStructureA.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructureA.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;
	GPIO_InitStructureA.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructureA);

	PWM_Init();
}

void Motor1_SetSpeed(int16_t Speed)
{
	if (Speed >= 0)
	{
		GPIO_SetBits(GPIOB, GPIO_Pin_10);
		GPIO_ResetBits(GPIOB, GPIO_Pin_11);
		PWM_SetCompare3(Speed);
	}
	else
	{
		GPIO_ResetBits(GPIOB, GPIO_Pin_10);
		GPIO_SetBits(GPIOB, GPIO_Pin_11);
		PWM_SetCompare3(-Speed);
	}
}

void Motor2_SetSpeed(int16_t Speed)
{
	if (Speed >= 0)
	{
		GPIO_SetBits(GPIOA, GPIO_Pin_7);
		GPIO_ResetBits(GPIOA, GPIO_Pin_6);
		PWM_SetCompare4(Speed);
	}
	else
	{
		GPIO_ResetBits(GPIOA, GPIO_Pin_7);
		GPIO_SetBits(GPIOA, GPIO_Pin_6);
		PWM_SetCompare4(-Speed);
	}
}

void Motor_Control(int16_t Speed_L, int16_t Speed_R)
{
	Motor1_SetSpeed(Speed_L);
	Motor2_SetSpeed(Speed_R);
}

void Motor_Handle(void)
{
	Turn_PWM = PlacePID(&TurnPID, Turn_Pid, error);
	Turn_PWM = Range_Protect(Turn_PWM, -70, 70);

	//	Motor_Control(Speed+Turn_PWM,Speed-Turn_PWM);
	Motor_Control(Speed-Turn_PWM, (Speed+Turn_PWM));
	//Motor_Control(20, 20);
}

#ifndef __PID_H__
#define __PID_H__
#include "stm32f10x.h" // Device header

#define KP 0
#define KI 1
#define KD 2

typedef struct PID // 用来PID参数计算变量
{
	int16_t SumError;  // 误差累计
	int16_t LastError; // 上次误差

} PID;

extern PID TurnPID;
extern float Turn_Pid[4];

int16_t PlacePID(PID *sptr, float *PID, int16_t error);

int16_t Range_Protect(int16_t duty, int16_t min, int16_t max); // 限幅保护
void PID_Parameter_Init(PID *sptr);

#endif

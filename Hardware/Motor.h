#ifndef __MOTOR_H
#define __MOTOR_H

void Motor_Init(void);
void Motor1_SetSpeed(int16_t Speed);
void Motor2_SetSpeed(int16_t Speed);
void Motor_Control(int16_t Speed_L, int16_t Speed_R);
void Motor_Handle(void);

extern int16_t Speed;
extern int16_t Turn_PWM;
#endif

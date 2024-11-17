#include "PID.h"

PID TurnPID;

float Turn_Pid[4] = {0.7, 0.0, 0.15, 0.0};

void PID_Parameter_Init(PID *sptr)
{
    sptr->SumError = 0;
    sptr->LastError = 0;
}

int16_t PlacePID(PID *sptr, float *PID, int16_t error)
{
    int16_t Actual;

    Actual = (error * PID[KP]) +
             PID[KD] * (error - sptr->LastError);

    sptr->LastError = error;

    return Actual;
}

int16_t Range_Protect(int16_t duty, int16_t min, int16_t max) // 限幅保护
{
    if (duty >= max)
    {
        return max;
    }
    if (duty <= min)
    {
        return min;
    }
    else
    {
        return duty;
    }
}

#ifndef __AD_H
#define __AD_H

#define ADC_DATA 0
#define ADC_MAX 1
#define ADC_MIN 2

void AD_Init(void);
uint16_t AD_GetValue(uint8_t ADC_Channel);
uint16_t ADC_Fitter(uint8_t count, uint8_t ADC_Channel);
void ADC_Handle(void);

extern int16_t error;
extern uint16_t AD0[3], AD1[3], AD2[3], AD3[3];
extern uint16_t ADC_Left_X, ADC_Left_Y, ADC_Right_X, ADC_Right_Y;


#endif

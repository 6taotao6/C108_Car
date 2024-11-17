#include "stm32f10x.h" // Device header
#include "AD.h"


uint16_t AD0[3] = {0, 4000, 0};//LX
uint16_t AD1[3] = {0, 4000, 0};//LY
uint16_t AD2[3] = {0, 4000, 0};//RY
uint16_t AD3[3] = {0, 4000, 0};//RX

int16_t error;

uint16_t ADC_Left_X, ADC_Left_Y, ADC_Right_X, ADC_Right_Y;

void AD_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

	RCC_ADCCLKConfig(RCC_PCLK2_Div6);

	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	ADC_InitTypeDef ADC_InitStructure;
	ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
	ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;
	ADC_InitStructure.ADC_ScanConvMode = DISABLE;
	ADC_InitStructure.ADC_NbrOfChannel = 1;
	ADC_Init(ADC1, &ADC_InitStructure);

	ADC_Cmd(ADC1, ENABLE);

	ADC_ResetCalibration(ADC1);
	while (ADC_GetResetCalibrationStatus(ADC1) == SET)
		;
	ADC_StartCalibration(ADC1);
	while (ADC_GetCalibrationStatus(ADC1) == SET)
		;
}

uint16_t AD_GetValue(uint8_t ADC_Channel)
{
	ADC_RegularChannelConfig(ADC1, ADC_Channel, 1, ADC_SampleTime_55Cycles5);
	ADC_SoftwareStartConvCmd(ADC1, ENABLE);
	while (ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC) == RESET)
		;
	return ADC_GetConversionValue(ADC1);
}

uint16_t ADC_Fitter(uint8_t count, uint8_t ADC_Channel) // 均值滤波
{
	uint32_t sum = 0;
	uint8_t i = 0;

	for (i = 0; i < count; i++)
	{
		sum += AD_GetValue(ADC_Channel);
	}

	return sum / count;
}

uint16_t Normalize_data(uint16_t AD[]) // 归一化
{

	return (uint16_t)((AD[ADC_DATA] - AD[ADC_MIN]) * 100) / (AD[ADC_MAX] - AD[ADC_MIN]);
}

int16_t Cha_bi_he(int16_t L_X, int16_t L_Y, int16_t R_X, int16_t R_Y, int16_t x) // 差比和
{
	float cha;
	float he;
	float result;

	cha = ((L_X + L_Y) - (R_X + R_Y))*100;
	he = ((L_X + L_Y) + (R_X + R_Y))*100 + 1;
	result = (cha * x) / (1.0 * he);

	return (int16_t)result;
}

void ADC_Handle(void)
{

	AD0[ADC_DATA] = ADC_Fitter(5, ADC_Channel_0);
	AD1[ADC_DATA] = ADC_Fitter(5, ADC_Channel_1);
	AD2[ADC_DATA] = ADC_Fitter(5, ADC_Channel_2);
	AD3[ADC_DATA] = ADC_Fitter(5, ADC_Channel_3);

	ADC_Left_X = Normalize_data(AD0);
	ADC_Left_Y = Normalize_data(AD1);
	ADC_Right_X = Normalize_data(AD3);
	ADC_Right_Y = Normalize_data(AD2);

	error = Cha_bi_he(ADC_Left_X, ADC_Left_Y, ADC_Right_X, ADC_Right_Y, 50);
}

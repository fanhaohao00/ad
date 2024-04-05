#include "stm32f10x.h"                  // Device header

void AD_Init(void)
{
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE); // ʹ��ADC1ʱ��
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE); // ʹ��GPIOAʱ��
    
    RCC_ADCCLKConfig(RCC_PCLK2_Div6); // ����ADCʱ�ӷ�Ƶϵ��Ϊ6
    
    GPIO_InitTypeDef GPIO_InitStructure; // ����GPIO��ʼ���ṹ��
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN; // ����GPIOģʽΪģ������ģʽ
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3| GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6| GPIO_Pin_7; // ����GPIO����ΪPA0~PA7
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; // ����GPIO�ٶ�Ϊ50MHz
    GPIO_Init(GPIOA, &GPIO_InitStructure); // ��ʼ��GPIOA
        
    ADC_InitTypeDef ADC_InitStructure; // ����ADC��ʼ���ṹ��
    ADC_InitStructure.ADC_Mode = ADC_Mode_Independent; // ����ADC����ģʽΪ����ģʽ
    ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right; // ����ADC���ݶ��뷽ʽΪ�Ҷ���
    ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None; // ����ADC�ⲿ����ת����ʽΪ�޴���
    ADC_InitStructure.ADC_ContinuousConvMode = DISABLE; // ����ADC����ת��ģʽ
    ADC_InitStructure.ADC_ScanConvMode = DISABLE; // ����ADCɨ��ת��ģʽ
    ADC_InitStructure.ADC_NbrOfChannel = 1; // ����ADCͨ������Ϊ1
    ADC_Init(ADC1, &ADC_InitStructure); // ��ʼ��ADC1
    
    ADC_Cmd(ADC1, ENABLE); // ʹ��ADC1
    
    ADC_ResetCalibration(ADC1); // ��λADC1У׼�Ĵ���
    while (ADC_GetResetCalibrationStatus(ADC1) == SET); // �ȴ���λУ׼���
    ADC_StartCalibration(ADC1); // ��ʼADC1У׼
    while (ADC_GetCalibrationStatus(ADC1) == SET); // �ȴ�У׼���
}

uint16_t AD_GetValue(uint8_t ADC_Channel)
{
    ADC_RegularChannelConfig(ADC1, ADC_Channel, 1, ADC_SampleTime_55Cycles5); // ����ADC1�ĳ���ͨ��
    ADC_SoftwareStartConvCmd(ADC1, ENABLE); // ����ADC1���ת��
    while (ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC) == RESET); // �ȴ�ת����ɱ�־λ
    return ADC_GetConversionValue(ADC1); // ����ADC1��ת�����
}

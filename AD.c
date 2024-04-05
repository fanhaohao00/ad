#include "stm32f10x.h"                  // Device header

void AD_Init(void)
{
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE); // 使能ADC1时钟
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE); // 使能GPIOA时钟
    
    RCC_ADCCLKConfig(RCC_PCLK2_Div6); // 设置ADC时钟分频系数为6
    
    GPIO_InitTypeDef GPIO_InitStructure; // 定义GPIO初始化结构体
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN; // 设置GPIO模式为模拟输入模式
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3| GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6| GPIO_Pin_7; // 设置GPIO引脚为PA0~PA7
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; // 设置GPIO速度为50MHz
    GPIO_Init(GPIOA, &GPIO_InitStructure); // 初始化GPIOA
        
    ADC_InitTypeDef ADC_InitStructure; // 定义ADC初始化结构体
    ADC_InitStructure.ADC_Mode = ADC_Mode_Independent; // 设置ADC工作模式为独立模式
    ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right; // 设置ADC数据对齐方式为右对齐
    ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None; // 设置ADC外部触发转换方式为无触发
    ADC_InitStructure.ADC_ContinuousConvMode = DISABLE; // 禁用ADC连续转换模式
    ADC_InitStructure.ADC_ScanConvMode = DISABLE; // 禁用ADC扫描转换模式
    ADC_InitStructure.ADC_NbrOfChannel = 1; // 设置ADC通道数量为1
    ADC_Init(ADC1, &ADC_InitStructure); // 初始化ADC1
    
    ADC_Cmd(ADC1, ENABLE); // 使能ADC1
    
    ADC_ResetCalibration(ADC1); // 复位ADC1校准寄存器
    while (ADC_GetResetCalibrationStatus(ADC1) == SET); // 等待复位校准完成
    ADC_StartCalibration(ADC1); // 开始ADC1校准
    while (ADC_GetCalibrationStatus(ADC1) == SET); // 等待校准完成
}

uint16_t AD_GetValue(uint8_t ADC_Channel)
{
    ADC_RegularChannelConfig(ADC1, ADC_Channel, 1, ADC_SampleTime_55Cycles5); // 配置ADC1的常规通道
    ADC_SoftwareStartConvCmd(ADC1, ENABLE); // 启动ADC1软件转换
    while (ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC) == RESET); // 等待转换完成标志位
    return ADC_GetConversionValue(ADC1); // 返回ADC1的转换结果
}

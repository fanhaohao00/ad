#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "AD.h"

uint16_t AD0, AD1, AD2, AD3, AD4,AD5, AD6, AD7, AD8;

int main(void)
{
	OLED_Init();
	AD_Init();
	
	OLED_ShowString(1, 1, "AD0:");
	OLED_ShowString(2, 1, "AD1:");
	OLED_ShowString(3, 1, "AD2:");
	OLED_ShowString(4, 1, "AD3:");
	
	while (1)
	{
		AD4 = AD_GetValue(ADC_Channel_4);
		AD5 = AD_GetValue(ADC_Channel_5);
		AD6 = AD_GetValue(ADC_Channel_6);
		AD7 = AD_GetValue(ADC_Channel_7);
		
		
		OLED_ShowNum(1, 5, AD4, 4);
		OLED_ShowNum(2, 5, AD5, 4);
		OLED_ShowNum(3, 5, AD6, 4);
		OLED_ShowNum(4, 5, AD7, 4);
		
		
		Delay_ms(100);
	}
}

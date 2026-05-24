/*
按键硬件说明：
PA0     连接 WAKE_UP    上拉
PH3     连接 KEY0       下拉
PH2     连接 KEY1       下拉
PC13    连接 KEY2       下拉
*/

#include "key.h"

unsigned int keytick=0;
bool k0l,k1l,k2l,wkl;
bool k0 ,k1 ,k2 ,wk ;

/*
KeyScan函数使用了状态机的方式，需要使用轮询或者定时器中断配合使用
*/
void KeyScan()
{
    //每20ms扫描一次按键状态，消抖
	if(HAL_GetTick()-keytick<20)return;
	else 
	{
		keytick = HAL_GetTick();
		k0=K0,k1=K1,k2=K2,wk=WK;
		if(!k0 & k0l)//KEY0下降沿
		{
			HAL_GPIO_TogglePin(GPIOB,GPIO_PIN_0);
		}
		if(!k1 & k1l)//KEY1下降沿
		{
			HAL_GPIO_TogglePin(GPIOB,GPIO_PIN_1);
		}
		if(!k2 & k2l)//KEY2下降沿
		{
			HAL_GPIO_TogglePin(GPIOB,GPIO_PIN_0);
			HAL_GPIO_TogglePin(GPIOB,GPIO_PIN_1);
		}
		
		if(wk & !wkl)//WAKEUP上升沿
		{
			HAL_GPIO_TogglePin(GPIOB,GPIO_PIN_0);
			HAL_GPIO_TogglePin(GPIOB,GPIO_PIN_1);
		}
		k0l=k0;
		k1l=k1;
		k2l=k2;
		wkl=wk;
	}
}
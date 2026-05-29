#include "hcsr04.h"

bool Hcsr04_Echo_State = false; // 定义一个全局变量来保存Echo引脚的状态
uint32_t count = 0; // 定义一个全局变量来保存计数值

void Hcsr04Start()
{
	Hcsr04_Trig_High();
	delay_us(20);
	Hcsr04_Trig_Low();
}

void Hcsr04Read()
{
	Hcsr04Start();
	if(Hcsr04_Echo() == 1)
	{
			Hcsr04_Echo_State = true; // Echo引脚变高，表示开始测距
			HAL_TIM_Base_Start(&htim7); // 启动定时器
	}
	if(Hcsr04_Echo() == 0 && Hcsr04_Echo_State)
	{
		Hcsr04_Echo_State = false; // Echo引脚变低，表示测距结束
	    count = __HAL_TIM_GET_COUNTER(&htim7); // 计算Echo引脚高电平持续的时间，单位为微秒
        HAL_TIM_Base_Stop(&htim7); // 停止定时器
        __HAL_TIM_SetCounter(&htim7, 0); // 重置定时器计数器
		float distance = count / 58.0 * 100; // 根据时间计算距离，单位为米
		printf("Distance: %.3f cm\r\n", distance); // 打印距离
	}
}
#include "shtx.h"

 
uint8_t SHT3X_Modecommand_Buffer[2]={0x23,0x22}; //SHT传感器指令
uint8_t SHT3X_Fetchcommand_Buffer[2]={0xE0,0x00};//读取测量结果
uint8_t SHT3X_Data_Buffer[6]; //byte0,1为温度 byte4,5为湿度
 
float Hum;//湿度,正数
float Tem;//温度
 
//传感器初始化函数
void SensorInit()
{
	HAL_I2C_Master_Transmit(&hi2c1,0x44<<1,SHT3X_Modecommand_Buffer,2,0x10); //第一步，发送16位数据0x22，0x36，传感器周期性的进行温湿度转换
	printf("SHT Success\r\n");
}
 
//传感器读取函数
void SensorRead()
{
	HAL_I2C_Master_Transmit(&hi2c1,0x44<<1,SHT3X_Fetchcommand_Buffer,2,0x10); //第二步，发送读取指令：0xE0,0x00，随时读取传感器的数据 
	HAL_I2C_Master_Receive(&hi2c1,(0x44<<1)+1,SHT3X_Data_Buffer,6,0x10); //设置温湿度IIC传输地址
	Tem=(float)((((SHT3X_Data_Buffer[0]<<8)+SHT3X_Data_Buffer[1])*175)/65535.0f)-45; //读取摄氏度温度 
	Hum=(((SHT3X_Data_Buffer[3]<<8)+SHT3X_Data_Buffer[4])*100)/65535.0f; //读取相对湿度
}
 
//通过串口显示结果，放入中断或者轮询即可
void SensorShow()
{
	SensorRead();
	printf("Tem:%.2f  Hum:%.2f\r\n",Tem,Hum);
}
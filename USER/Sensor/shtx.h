#ifndef __SHTX_H__
#define __SHTX_H__

#include "bsp.h"

extern float Hum;
extern float Tem;

void SensorInit();
void SensorRead();
void SensorShow();

#endif
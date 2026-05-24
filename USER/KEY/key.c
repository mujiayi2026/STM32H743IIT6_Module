/**
 * @file key.c
 * @brief 按键扫描模块
 * @author mujiayi
 * @date 2026-05-24
 *
 * 硬件配置：
 * - WAKE_UP (PA0):  上拉输入
 * - KEY0 (PH3):     下拉输入
 * - KEY1 (PH2):     下拉输入
 * - KEY2 (PC13):    下拉输入
 *
 * 功能说明：
 * 使用状态机方式检测按键，20ms消抖周期
 * 需配合轮询或定时器中断使用
 */

#include "key.h"

static unsigned int key_tick = 0;
static bool k0_last, k1_last, k2_last, wk_last;
static bool k0_curr, k1_curr, k2_curr, wk_curr;

/**
 * @brief 按键扫描函数
 * @details 20ms扫描一次按键状态，实现消抖
 *          检测按键下降沿和上升沿，控制LED亮灭
 * @return void
 */
void KeyScan(void)
{
  /* 20ms消抖周期检查 */
  if (HAL_GetTick() - key_tick < 20)
    return;

  key_tick = HAL_GetTick();

  /* 读取当前按键状态 */
  k0_curr = K0;
  k1_curr = K1;
  k2_curr = K2;
  wk_curr = WK;

  /* KEY0按下（下降沿）：切换红灯 */
  if (!k0_curr && k0_last) {
    HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_0);
  }

  /* KEY1按下（下降沿）：切换绿灯 */
  if (!k1_curr && k1_last) {
    HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_1);
  }

  /* KEY2按下（下降沿）：同时切换红绿灯 */
  if (!k2_curr && k2_last) {
    HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_0);
    HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_1);
  }

  /* WAKE_UP按下（上升沿）：同时切换红绿灯 */
  if (wk_curr && !wk_last) {
    HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_0);
    HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_1);
  }

  /* 保存本次状态作为下次比较基准 */
  k0_last = k0_curr;
  k1_last = k1_curr;
	k2_last = k2_curr;
  wk_last = wk_curr;
}
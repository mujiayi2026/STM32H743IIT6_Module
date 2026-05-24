# STM32H743IIT6 外设驱动库

[![License](https://img.shields.io/badge/license-MIT-blue.svg)](LICENSE)
[![STM32](https://img.shields.io/badge/MCU-STM32H743IIT6-blue.svg)]()
[![Language](https://img.shields.io/badge/language-C-00599C.svg)]()

一个功能完整的 **STM32H743IIT6** 微控制器外设和传感器驱动代码库，提供 LED、按键、定时器、UART 等常用模块的标准化驱动实现。

## 📋 目录

- [主要特性](#主要特性)
- [项目结构](#项目结构)
- [硬件配置](#硬件配置)
- [快速开始](#快速开始)
- [模块说明](#模块说明)
- [编译和烧录](#编译和烧录)
- [使用示例](#使用示例)
- [许可证](#许可证)

## ✨ 主要特性

- ✅ **LED 驱动**：支持多个 LED 的控制（PB0/PB1）
- ✅ **按键扫描**：完整的按键消抖处理，支持 4 个按键
  - WAKE_UP（PA0，上拉）
  - KEY0（PH3，下拉）
  - KEY1（PH2，下拉）
  - KEY2（PC13，下拉）
- ✅ **定时器**：TIM6 基础定时器中断支持
- ✅ **UART 通信**：UART1 DMA 接收模式，printf 重定向
- ✅ **Cache 处理**：H7 系列 MCU Cache 一致性管理
- ✅ **代码规范**：
  - 统一的 2 空格缩进风格
  - Doxygen 风格注释
  - 标准的 C99 编码规范

## 📁 项目结构

```
STM32H743IIT6_Module/
├── USER/                          # 用户代码目录
│   ├── bsp.h / bsp.c             # 板级支持包
│   ├── LED/
│   │   ├── led.h                 # LED 模块头文件
│   │   └── led.c                 # LED 驱动实现
│   ├── KEY/
│   │   ├── key.h                 # 按键扫描头文件
│   │   └── key.c                 # 按键扫描实现（20ms 消抖）
│   ├── TIM/
│   │   ├── timer.h               # 定时器头文件
│   │   └── time.c                # 定时器驱动实现
│   └── UART/
│       ├── uart.h                # UART 模块头文件
│       └── uart.c                # UART DMA 驱动实现
├── README.md                      # 项目说明文档
└── .gitignore                     # Git 忽略文件

```

## 🔌 硬件配置

### 微控制器
- **型号**：STM32H743IIT6
- **内核**：ARM Cortex-M7，双核
- **主频**：480 MHz
- **闪存**：2 MB
- **SRAM**：864 KB

### 引脚分配

| 模块 | 功能 | 引脚 | 工作模式 |
|------|------|------|---------|
| **LED_RED** | GPIO 输出 | PB0 | 推挽输出 |
| **LED_GREEN** | GPIO 输出 | PB1 | 推挽输出 |
| **KEY0** | GPIO 输入 | PH3 | 下拉输入 |
| **KEY1** | GPIO 输入 | PH2 | 下拉输入 |
| **KEY2** | GPIO 输入 | PC13 | 下拉输入 |
| **WAKE_UP** | GPIO 输入 | PA0 | 上拉输入 |
| **TIM6** | 基础定时器 | 内部 | 中断模式 |
| **UART1_TX** | 串口发送 | PA9 | 复用功能 |
| **UART1_RX** | 串口接收 | PA10 | 复用功能 |

## 🚀 快速开始

### 前置要求

- **开发环境**：STM32CubeMX / Keil MDK / IAR EW for ARM
- **编译器**：ARM GCC 或 ARMCC
- **烧录工具**：J-Link / ST-Link / DAPLink

### 基本步骤

1. **克隆仓库**
   ```bash
   git clone <repository-url>
   cd STM32H743IIT6_Module
   ```

2. **配置工程**
   - 在 STM32CubeMX 中配置相应的外设
   - 生成初始化代码

3. **编译工程**
   ```bash
   make all           # 编译全部
   make clean         # 清除编译文件
   ```

4. **烧录程序**
   ```bash
   make flash         # 烧录到设备
   ```

## 📚 模块说明

### 1. LED 模块（USER/LED/）

LED 模块提供基础的 LED 控制功能。

```c
/* 初始化 LED */
void LedInit(void);
```

**特点**：
- 初始化时 LED 置高电平（熄灭）
- 支持通过 GPIO 控制 LED 开关

### 2. 按键模块（USER/KEY/）

按键模块实现了硬件消抖和边沿检测。

```c
/* 按键扫描（需要在主循环或定时器中周期调用） */
void KeyScan(void);
```

**工作原理**：
- 20ms 消抖周期
- 检测按键下降沿（KEY0/KEY1/KEY2）和上升沿（WAKE_UP）
- 按键事件直接控制 LED 切换

**按键事件**：
| 按键 | 事件类型 | 动作 |
|------|---------|------|
| KEY0 | 下降沿 | 切换 LED_RED |
| KEY1 | 下降沿 | 切换 LED_GREEN |
| KEY2 | 下降沿 | 同时切换两个 LED |
| WAKE_UP | 上升沿 | 同时切换两个 LED |

### 3. 定时器模块（USER/TIM/）

TIM6 是 STM32H7 的基础定时器，用于提供系统定时任务。

```c
/* 初始化定时器 */
void TimerInit(void);

/* 定时器中断回调 */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim);
```

### 4. UART 模块（USER/UART/）

UART1 模块支持 DMA 接收和 printf 重定向。

```c
/* 初始化 UART1 */
void UartInit(void);

/* 处理接收的数据 */
void UartProc(void);

/* 自定义 printf 输出 */
int fputc(int ch, FILE *f);
```

**特点**：
- ✓ DMA 接收模式，提高效率
- ✓ 自动检测接收完成（空闲中断）
- ✓ printf 支持调试输出
- ✓ 64 字节接收缓冲区（32 字节对齐以满足 Cache 要求）

**Cache 处理**：
H7 系列 MCU 带 Cache，使用 DMA 接收时需要特殊处理：
```c
/* 清除 DCache 以保证数据一致性 */
SCB_InvalidateDCache_by_Addr((uint32_t *)Rx, sizeof(Rx));
```

## 💻 编译和烧录

### 使用 Makefile

```bash
# 显示帮助信息
make help

# 编译项目
make all

# 清除编译文件
make clean

# 重新编译
make rebuild

# 烧录到设备（需配置烧录器）
make flash

# 显示编译大小
make size
```

## 📖 使用示例

### 基本初始化

```c
#include "bsp.h"

int main(void)
{
  /* 初始化所有硬件模块 */
  Sys_Init();

  /* 主循环 */
  while (1) {
    /* 周期性处理系统任务 */
    Sys_Run();
  }
}
```

### LED 控制

```c
#include "led.h"

/* 打开红灯 */
HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, GPIO_PIN_RESET);

/* 关闭红灯 */
HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, GPIO_PIN_SET);

/* 切换红灯 */
HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_0);
```

### 按键事件处理

```c
#include "key.h"

/* 在主循环中周期调用，实现按键检测 */
void main_loop(void)
{
  while (1) {
    KeyScan();    /* 每 20ms 扫描一次按键 */
    /* 按键事件已在 KeyScan() 中直接处理 */
  }
}
```

### UART 通信示例

```c
#include <stdio.h>
#include "uart.h"

int main(void)
{
  Sys_Init();

  printf("STM32H743IIT6 系统启动\r\n");
  printf("UART 模块初始化完成\r\n");

  while (1) {
    Sys_Run();    /* 处理接收的数据 */
  }
}
```

## 📝 代码特性

### 代码规范
- **缩进**：2 空格缩进
- **命名**：使用驼峰命名法或蛇形命名法
- **注释**：Doxygen 风格标准注释
- **时间戳**：所有文件包含创建日期 (2026-05-24)

### 文档标准
```c
/**
 * @file module.c
 * @brief 模块简介
 * @author 作者名
 * @date 2026-05-24
 */

/**
 * @brief 函数简介
 * @details 详细说明
 * @param param1 参数说明
 * @return 返回值说明
 */
void function(int param1);
```

## 🔧 常见问题

### Q: 如何修改 LED 的引脚？
**A**: 修改 `USER/LED/led.h` 中的 GPIO 配置，然后在 `USER/LED/led.c` 中更新对应的 HAL 函数调用。

### Q: 按键消抖时间太长？
**A**: 修改 `USER/KEY/key.c` 中的消抖时间常数（当前为 20ms），可改为 10ms 或其他值。

### Q: 如何使用定时器中断？
**A**: 在 `USER/TIM/time.c` 的 `HAL_TIM_PeriodElapsedCallback()` 函数中添加中断处理逻辑。

### Q: UART 接收缓冲区溢出如何处理？
**A**: 检查 `USER/UART/uart.c` 中的缓冲区大小（当前 64 字节），根据需要增加。

## 📄 许可证

此项目采用 MIT 许可证。详见 [LICENSE](LICENSE) 文件。

## 👨‍💻 贡献

欢迎提交 Issue 和 Pull Request！

如果你有改进建议，请：
1. Fork 本仓库
2. 创建特性分支 (`git checkout -b feature/AmazingFeature`)
3. 提交变更 (`git commit -m 'Add some AmazingFeature'`)
4. 推送到分支 (`git push origin feature/AmazingFeature`)
5. 开启 Pull Request

## 📧 联系方式

- **作者**：Mujiayi
- **邮箱**：mujiayi2026@example.com（可修改）

---

**更新日期**：2026-05-24

**项目状态**：✅ 持续开发中

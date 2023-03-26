# RP2040 Pico Examples

| Directory      | Example   | 中文描述                                                     |
| -------------- | --------- | ------------------------------------------------------------ |
| blink          | led blink | 灯闪烁例子：板载灯，使用Timer闪烁，使用状态机闪烁            |
| dht22          |           | 温湿传感器                                                   |
| esp01s         |           | esp01s模块联网：出厂at指令操作，at指令http请求，at指令发送邮件 |
| flash_fireware |           | 固件目录，你也可以从官网更新最新版                           |
| irq            |           | 中断，如：按钮示例，红外触发等场景，可使用中断处理           |
| i2c            |           | 使用i2c13306操作0.96、0.91寸oled显示屏，你需要从thonny下载SSD1306_I2C库支持，支持中文字库size16以上 |
| infrared       |           | 人体红外检测                                                 |
| machine        |           | pico板载温度                                                 |
| pwm            |           | 脉冲宽度调制，呼吸灯                                         |
| sdcard         |           | sd卡，32g卡测试成功                                          |
| ws2812b        |           | 彩灯、源地板载彩灯（注意：r68脚需要焊接上）                  |

# 编程文档查阅

https://docs.micropython.org/en/latest/index.html

https://datasheets.raspberrypi.com/

https://datasheets.raspberrypi.com/pico/raspberry-pi-pico-c-sdk.pdf



# Pico 介绍

Raspberry Pi Pico is a low-cost, high-performance microcontroller board with flexible digital interfaces. Key features include:

- [RP2040](https://www.raspberrypi.com/documentation/microcontrollers/rp2040.html#welcome-to-rp2040) microcontroller chip designed by Raspberry Pi in the United Kingdom
- Dual-core Arm Cortex M0+ processor, flexible clock running up to 133 MHz
- 264kB of SRAM, and 2MB of on-board flash memory
- USB 1.1 with device and host support
- Low-power sleep and dormant modes
- Drag-and-drop programming using mass storage over USB
- 26 × multi-function GPIO pins
- 2 × SPI, 2 × I2C, 2 × UART, 3 × 12-bit ADC, 16 × controllable PWM channels
- Accurate clock and timer on-chip
- Temperature sensor
- Accelerated floating-point libraries on-chip
- 8 × Programmable I/O (PIO) state machines for custom peripheral support

The Raspberry Pi Pico comes as a castellated module allows soldering direct to carrier boards, while the Pico H comes with pre-soldered headers.

**RP2040具有以下功能：**

- 双核 Arm Cortex-M0 + 处理器，工作主频为133MHz
- 264K片上SRAM
- 通过专用 QSPI 总线支持最高 16MB 的片外闪存
- DMA控制器
- 内插器和整数除法器外设
- 30个GPIO引脚，其中4个可用作模拟输入
- 2个UART，2个SPI控制器和2个I2C控制器
- 16×PWM通道
- 1个USB 1.1控制器和PHY，具有主机和设备支持
- 8 路可编程的IO（PIO）状态机，允许用户自定义和设计通信接口
- 支持快速的低功耗模式切换
- 具有UF2支持的USB大容量存储启动模式，支持拖放式编程
- RP2040具有两个快速内核和大量片上RAM，是机器学习应用程序的绝佳平台。

## GPIO引脚

![](GPIO引脚.jpg)



## 芯片引脚

![](芯片引脚.jpg)



## 芯片架构

![](芯片架构.png)



## 总线结构

![](总线结构.png)

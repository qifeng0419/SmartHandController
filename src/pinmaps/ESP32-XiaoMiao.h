// ============================================================================
// XiaoMiao ESP32 Hardware Pinmap for SmartHandController
// 学而思 XiaoMiao 掌机硬件引脚定义
// ============================================================================

#pragma once
#include "../../Common.h"

// MCU Type
#define MCU ESP32
#define MCU_STR "ESP32"

// ============================================================================
// DISPLAY - ST7735 TFT LCD (推荐用于 XiaoMiao)
// ============================================================================

// 显示器选择: ST7735 TFT 或 OLED
#define DISPLAY_TYPE_TFT     1
#define DISPLAY_TYPE_OLED    0

// 使用 ST7735 TFT (默认推荐)
#define USE_DISPLAY_ST7735  1

#ifdef USE_DISPLAY_ST7735
    // ST7735 TFT 配置
    #define DISPLAY_DRIVER       ST7735
    #define TFT_WIDTH            128
    #define TFT_HEIGHT           160
    #define TFT_ROTATION         3      // 0-3: 旋转角度
    
    // ST7735 SPI 引脚 (与 SD 卡共享 SPI2)
    #define TFT_SCK_PIN          18     // 时钟 (与 SD 卡共享)
    #define TFT_MOSI_PIN         23     // 数据 (与 SD 卡共享)
    #define TFT_CS_PIN           5      // 片选 (独立)
    #define TFT_DC_PIN           4      // 数据/命令 (独立)
    #define TFT_RST_PIN          19     // 复位 (与 SD 卡 MISO 共享)
    #define TFT_MISO_PIN         -1     // 不使用 MISO (仅写入模式)
    
    // SPI 速率
    #define SPI_FREQUENCY        40000000  // 40MHz (ST7735 支持)
    
    // 颜色定义
    #define DISPLAY_BG_COLOR     TFT_BLACK
    #define DISPLAY_TEXT_COLOR   TFT_WHITE
    
#else
    // OLED 配置 (备选方案)
    #define DISPLAY_OLED         SH1106
    // I2C 引脚
    #define DISPLAY_SDA_PIN      21
    #define DISPLAY_SCL_PIN      15
#endif

// ============================================================================
// KEYPAD - 6 键��键输入
// ============================================================================

#define B_PIN0              2      // UP (上)
#define B_PIN0_ACTIVE_STATE LOW
#define B_PIN0_INPUT_MODE   INPUT_PULLUP

#define B_PIN1              13     // DOWN (下)
#define B_PIN1_ACTIVE_STATE LOW
#define B_PIN1_INPUT_MODE   INPUT_PULLUP

#define B_PIN2              27     // LEFT (左)
#define B_PIN2_ACTIVE_STATE LOW
#define B_PIN2_INPUT_MODE   INPUT_PULLUP

#define B_PIN3              35     // RIGHT (右)
#define B_PIN3_ACTIVE_STATE LOW
#define B_PIN3_INPUT_MODE   INPUT_PULLUP

#define B_PIN4              34     // A 按键 (ADC 仅输入)
#define B_PIN4_ACTIVE_STATE LOW
#define B_PIN4_INPUT_MODE   INPUT_PULLUP

#define B_PIN5              12     // B 按键 (注意: 启动敏感)
#define B_PIN5_ACTIVE_STATE LOW
#define B_PIN5_INPUT_MODE   INPUT_PULLUP

// 可选: 模拟摇杆
#define B_PIN6              -1     // 未使用
#define B_PIN6_ACTIVE_STATE LOW
#define B_PIN6_INPUT_MODE   INPUT

// ============================================================================
// SERIAL COMMUNICATION - 串口通信
// ============================================================================

// OnStep 连接 (ST4 导星端口)
#define SERIAL_ONSTEP       SERIAL  // 使用 Serial (默认 GPIO1/3)
#define SERIAL_ONSTEP_RX    3
#define SERIAL_ONSTEP_TX    1

// 调试串口
#define SERIAL_DEBUG        Serial
#define SERIAL_DEBUG_BAUD   115200

// ============================================================================
// I2C - 两线接口
// ============================================================================

#define DISPLAY_SDA_PIN     21
#define DISPLAY_SCL_PIN     15
#define HAL_WIRE_CLOCK      100000  // 标准模式

// ============================================================================
// BUZZER - 蜂鸣器 (无源, PWM 驱动)
// ============================================================================

#define BUZZER_PIN          14
#define BUZZER_CHANNEL      0       // LEDC 通道

// ============================================================================
// SENSORS - 传感器 (ADC)
// ============================================================================

// 光照传感器
#define LIGHT_SENSOR_PIN    36      // ADC1_CH0 (仅输入)

// 热敏电阻 (温度传感器)
#define TEMP_SENSOR_PIN     39      // ADC1_CH3 (仅输入)

// ============================================================================
// SD CARD - MicroSD 卡 (可选)
// ============================================================================

#define SDCARD_CS_PIN       22      // SD 片选 (与 TFT 不同)
#define SDCARD_MOSI_PIN     23      // 与 TFT 共享
#define SDCARD_SCLK_PIN     18      // 与 TFT 共享
#define SDCARD_MISO_PIN     19      // 与 TFT RES 共享

// ============================================================================
// 其他配置
// ============================================================================

// 电池电压监测 (可选)
#define BATTERY_VOLTAGE_PIN -1      // 未使用

// 电源控制 (可选)
#define DISPLAY_POWER_PIN   -1      // 未使用

// ============================================================================
// 注意事项
// ============================================================================
// 
// 1. GPIO 34, 35, 36, 39 仅支持输入，不能设为输出
// 2. GPIO 12 (B 键) 在上电阶段敏感，避免外部高电平
// 3. TFT 和 SD 卡共用 SPI2 (GPIO 18/23/19)，通过 CS 引脚分时复用
// 4. 所有 3.3V 器件，不能接 5V！
// 5. I2C 地址: 电机/LED 共用 0x40, OLED 共用 0x3C/0x3D
//

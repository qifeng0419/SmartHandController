#pragma once

#include "../../Common.h"

// ============================================================================
// Display Adapter - 显示驱动抽象层
// 
// 这个文件提供了一个统一的显示接口，支持：
// - OLED (SH1106, SSD1306, SSD1309) - 通过 U8G2
// - TFT (ST7735) - 通过 TFT_eSPI
// ============================================================================

// 显示器类型枚举
enum class DisplayType {
    OLED_SH1106 = 0,
    OLED_SH1106_4W_SW_SPI = 1,
    OLED_SH1106_4W_HW_SPI = 2,
    OLED_SSD1306 = 3,
    OLED_SSD1309 = 4,
    OLED_SSD1309_4W_SW_SPI = 5,
    OLED_SSD1309_4W_HW_SPI = 6,
    TFT_ST7735 = 10,
};

// 显示驱动基类（纯虚接口）
class IDisplay {
public:
    virtual ~IDisplay() = default;
    
    // 初始化
    virtual bool init() = 0;
    
    // 屏幕管理
    virtual void clear() = 0;
    virtual void display() = 0;  // 刷新屏幕
    virtual void sleepOn() = 0;
    virtual void sleepOff() = 0;
    virtual void setContrast(uint8_t contrast) = 0;
    
    // 尺寸
    virtual uint16_t getWidth() = 0;
    virtual uint16_t getHeight() = 0;
    
    // 字体和文本
    virtual void setFont(const uint8_t *font) = 0;
    virtual void setTextSize(uint8_t size) = 0;
    virtual void setTextColor(uint16_t color, uint16_t bgColor = 0) = 0;
    virtual void setCursor(uint16_t x, uint16_t y) = 0;
    virtual void drawString(uint16_t x, uint16_t y, const char *string) = 0;
    virtual void drawUTF8(uint16_t x, uint16_t y, const char *string) = 0;
    virtual uint16_t getUTF8Width(const char *string) = 0;
    
    // 图形绘制
    virtual void drawPixel(uint16_t x, uint16_t y, uint16_t color) = 0;
    virtual void drawLine(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t color) = 0;
    virtual void drawRect(uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint16_t color) = 0;
    virtual void fillRect(uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint16_t color) = 0;
    virtual void drawCircle(uint16_t x, uint16_t y, uint16_t r, uint16_t color) = 0;
    virtual void fillCircle(uint16_t x, uint16_t y, uint16_t r, uint16_t color) = 0;
    
    // 位图绘制
    virtual void drawXBMP(uint16_t x, uint16_t y, uint16_t w, uint16_t h, const uint8_t *data) = 0;
    virtual void drawGlyph(uint16_t x, uint16_t y, uint16_t glyph) = 0;
    
    // 分页模式（用于 U8G2 兼容）
    virtual void firstPage() {}
    virtual bool nextPage() { return false; }
    virtual uint8_t getDisplayWidth() { return getWidth(); }
    virtual uint8_t getDisplayHeight() { return getHeight(); }
    virtual uint8_t getAscent() { return 8; }
    virtual uint8_t getDescent() { return 2; }
    
    // 自定义扩展
    virtual uint8_t DrawFwNumeric(uint16_t x, uint16_t y, const char *text) { return 0; }
    virtual uint8_t GetFwNumericWidth(const char *text) { return 0; }
};

#endif

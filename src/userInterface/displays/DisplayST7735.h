#pragma once

#include "DisplayAdapter.h"
#include <TFT_eSPI.h>

// ============================================================================
// ST7735 TFT Display Driver - ST7735 TFT 显示驱动
//
// 支持 ST7735 TFT LCD 显示屏，���辨率通常为 128×160 或 160×128
// 通过 SPI 接口连接，速度快，色彩丰富
// ============================================================================

class DisplayST7735 : public IDisplay {
private:
    TFT_eSPI tft;
    uint16_t _width;
    uint16_t _height;
    uint16_t _textColor;
    uint16_t _textBgColor;
    uint16_t _x, _y;  // 当前光标位置
    bool _sleepMode;
    uint8_t _contrast;
    
    // 字体相关
    uint8_t _textSize;
    
public:
    DisplayST7735();
    ~DisplayST7735() = default;
    
    // 初始化
    bool init() override;
    
    // 屏幕管理
    void clear() override;
    void display() override;
    void sleepOn() override;
    void sleepOff() override;
    void setContrast(uint8_t contrast) override;
    
    // 尺寸获取
    uint16_t getWidth() override { return _width; }
    uint16_t getHeight() override { return _height; }
    
    // 字体和文本
    void setFont(const uint8_t *font) override;
    void setTextSize(uint8_t size) override;
    void setTextColor(uint16_t color, uint16_t bgColor = 0) override;
    void setCursor(uint16_t x, uint16_t y) override;
    void drawString(uint16_t x, uint16_t y, const char *string) override;
    void drawUTF8(uint16_t x, uint16_t y, const char *string) override;
    uint16_t getUTF8Width(const char *string) override;
    
    // 图形绘制
    void drawPixel(uint16_t x, uint16_t y, uint16_t color) override;
    void drawLine(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t color) override;
    void drawRect(uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint16_t color) override;
    void fillRect(uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint16_t color) override;
    void drawCircle(uint16_t x, uint16_t y, uint16_t r, uint16_t color) override;
    void fillCircle(uint16_t x, uint16_t y, uint16_t r, uint16_t color) override;
    
    // 位图绘制
    void drawXBMP(uint16_t x, uint16_t y, uint16_t w, uint16_t h, const uint8_t *data) override;
    void drawGlyph(uint16_t x, uint16_t y, uint16_t glyph) override;
    
    // 分页模式兼容 (不完全支持，但提供最小实现)
    void firstPage() override;
    bool nextPage() override;
    uint8_t getDisplayWidth() override { return _width; }
    uint8_t getDisplayHeight() override { return _height; }
    uint8_t getAscent() override { return 12; }
    uint8_t getDescent() override { return 3; }
    
    // 自定义扩展
    uint8_t DrawFwNumeric(uint16_t x, uint16_t y, const char *text) override;
    uint8_t GetFwNumericWidth(const char *text) override;
    
    // TFT_eSPI 访问器 (用于特殊用途)
    TFT_eSPI* getTftHandle() { return &tft; }
};

#endif

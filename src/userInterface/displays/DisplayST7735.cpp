#include "DisplayST7735.h"

// ============================================================================
// ST7735 Display Driver Implementation
// ============================================================================

DisplayST7735::DisplayST7735() 
    : tft(), _width(0), _height(0), _textColor(TFT_WHITE), 
      _textBgColor(TFT_BLACK), _x(0), _y(0), _sleepMode(false), 
      _contrast(1), _textSize(1) {
}

bool DisplayST7735::init() {
    // 初始化 TFT_eSPI
    tft.init();
    
    // 设置旋转角度（根据 User_Setup.h 中的配置）
    #ifdef TFT_ROTATION
        tft.setRotation(TFT_ROTATION);
    #else
        tft.setRotation(3);  // 默认值
    #endif
    
    // 获取实际分辨率
    _width = tft.width();
    _height = tft.height();
    
    // 初始化屏幕
    tft.fillScreen(TFT_BLACK);
    
    #if DEBUG != OFF
        VF("MSG: DisplayST7735 initialized (");
        V(_width); V("x"); V(_height); VLF(")");
    #endif
    
    return true;
}

void DisplayST7735::clear() {
    tft.fillScreen(_textBgColor);
}

void DisplayST7735::display() {
    // TFT 不需要显式刷新（即时显示）
    // 这个方法保留用于兼容性
}

void DisplayST7735::sleepOn() {
    if (!_sleepMode) {
        tft.writecommand(0x10);  // Enter Sleep Mode
        _sleepMode = true;
    }
}

void DisplayST7735::sleepOff() {
    if (_sleepMode) {
        tft.writecommand(0x11);  // Exit Sleep Mode
        delay(120);  // 等待屏幕唤醒
        _sleepMode = false;
    }
}

void DisplayST7735::setContrast(uint8_t contrast) {
    _contrast = contrast;
    // ST7735 使用亮度而非对比度
    // 范围 0-3: Min, Low, High, Max
    if (contrast <= 1) {
        tft.writecommand(0x51);  // Write Display Brightness
        tft.writedata(50);        // 最小亮度
    } else if (contrast == 2) {
        tft.writecommand(0x51);
        tft.writedata(150);       // 中等亮度
    } else {
        tft.writecommand(0x51);
        tft.writedata(255);       // 最大亮度
    }
}

void DisplayST7735::setFont(const uint8_t *font) {
    // TFT_eSPI 使用内置字体，不支持外部字体指针
    // 保留此方法用于兼容性，实际使用 setTextFont()
}

void DisplayST7735::setTextSize(uint8_t size) {
    _textSize = size;
    if (size == 0) size = 1;
    tft.setTextSize(size);
}

void DisplayST7735::setTextColor(uint16_t color, uint16_t bgColor) {
    _textColor = color;
    _textBgColor = bgColor;
    tft.setTextColor(color, bgColor);
}

void DisplayST7735::setCursor(uint16_t x, uint16_t y) {
    _x = x;
    _y = y;
    tft.setCursor(x, y);
}

void DisplayST7735::drawString(uint16_t x, uint16_t y, const char *string) {
    if (!string) return;
    tft.setCursor(x, y);
    tft.print(string);
}

void DisplayST7735::drawUTF8(uint16_t x, uint16_t y, const char *string) {
    if (!string) return;
    tft.setCursor(x, y);
    tft.print(string);
}

uint16_t DisplayST7735::getUTF8Width(const char *string) {
    if (!string) return 0;
    
    // 粗略估计：每个字符约 6 像素宽（文本大小 1）
    // 乘以当前文本大小
    int len = strlen(string);
    return (len * 6 * _textSize);
}

void DisplayST7735::drawPixel(uint16_t x, uint16_t y, uint16_t color) {
    tft.drawPixel(x, y, color);
}

void DisplayST7735::drawLine(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t color) {
    tft.drawLine(x1, y1, x2, y2, color);
}

void DisplayST7735::drawRect(uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint16_t color) {
    tft.drawRect(x, y, w, h, color);
}

void DisplayST7735::fillRect(uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint16_t color) {
    tft.fillRect(x, y, w, h, color);
}

void DisplayST7735::drawCircle(uint16_t x, uint16_t y, uint16_t r, uint16_t color) {
    tft.drawCircle(x, y, r, color);
}

void DisplayST7735::fillCircle(uint16_t x, uint16_t y, uint16_t r, uint16_t color) {
    tft.fillCircle(x, y, r, color);
}

void DisplayST7735::drawXBMP(uint16_t x, uint16_t y, uint16_t w, uint16_t h, const uint8_t *data) {
    if (!data) return;
    
    // 简单的位图渲染实现
    // XBM 格式: 每行 8 像素打包成 1 字节
    uint16_t color = _textColor;
    uint16_t bgColor = _textBgColor;
    
    for (uint16_t row = 0; row < h; row++) {
        for (uint16_t col = 0; col < w; col++) {
            uint16_t byteIndex = (row * ((w + 7) / 8)) + (col / 8);
            uint8_t bitIndex = col % 8;
            
            if (data[byteIndex] & (1 << bitIndex)) {
                tft.drawPixel(x + col, y + row, color);
            } else {
                tft.drawPixel(x + col, y + row, bgColor);
            }
        }
    }
}

void DisplayST7735::drawGlyph(uint16_t x, uint16_t y, uint16_t glyph) {
    // 简单的字形渲染
    // 这是一个占位符实现
    tft.setCursor(x, y);
    tft.print("?");  // 使用 ? 表示不支持的字符
}

void DisplayST7735::firstPage() {
    // TFT 不使用分页模式，直接清屏
    clear();
}

bool DisplayST7735::nextPage() {
    // TFT 不使用分页模式，总是返回 false
    return false;
}

uint8_t DisplayST7735::DrawFwNumeric(uint16_t x, uint16_t y, const char *text) {
    if (!text) return 0;
    
    // 在指定位置绘制数字文本
    tft.setCursor(x, y);
    tft.print(text);
    
    return strlen(text);
}

uint8_t DisplayST7735::GetFwNumericWidth(const char *text) {
    if (!text) return 0;
    
    // 返回文本在屏幕上占用的像素宽度
    // 粗略估计
    int len = strlen(text);
    return (len * 6 * _textSize);
}

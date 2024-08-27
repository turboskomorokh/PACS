#include "io/ssd1306.h"

void SSD1306::init(TwoWire& Wire)
{
    Wire.begin();
    // delay(4);
    screen = Adafruit_SSD1306(SSD1306_SCREEN_WIDTH, SSD1306_SCREEN_HEIGHT, &Wire, -1);
    if (!screen.begin(SSD1306_SWITCHCAPVCC, 0x3C))
    {
        Serial.println(F("SSD1306 allocation failed"));
        // for (;;)
        //     ;
    }
    screen.clearDisplay();
    screen.display();
}

void SSD1306::drawLogo() {
    screen.drawBitmap(0,0, LogoBMP, 128, 64, WHITE);
	screen.display();
	// delay(2000);
	// screen.clearDisplay();
	// screen.display();
}

void SSD1306::drawMark()
{
    screen.clearDisplay();
    screen.drawBitmap(0, 0, MarkBMP, 128, 64, WHITE);
    screen.display();
}

void SSD1306::drawCross()
{
    screen.clearDisplay(); 
    screen.drawBitmap(0, 0, CrossBMP, 128, 64, WHITE);
    screen.display();
}

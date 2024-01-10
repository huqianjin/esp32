#include <stdio.h>
#include <HardwareSerial.h>
#include <TFT_eSPI.h>

TFT_eSPI tft =TFT_eSPI();
int i = 0 ;

void setup(void) {
  tft.init();
  tft.setRotation(0);
  tft.fillScreen(TFT_BLUE);
  tft.setCursor(20, 10);
  tft.setTextColor(TFT_WHITE);
  tft.setTextSize(2);
  tft.print("Hello ST7735!");
}

void loop() {
 Serial.print(i++);


    delay(2000);


}
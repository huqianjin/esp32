#include <stdio.h>
#include <HardwareSerial.h>

#include <TFT_eSPI.h>
#include <Wire.h>
#include<ADXL345_WE.h>
#define ADXL345_I2CADDR 0x53 // 如果 SDO = HIGH，则为 0x1D
#define CS_PIN 7
#define MOSI_PIN 3
#define MISO_PIN 10
#define SCK_PIN   2
#define  SDA_PIN  4
#define  SCL_PIN  5
TFT_eSPI tft =TFT_eSPI();
int i = 0 ;
//
bool spi = true;
ADXL345_WE myAcc = ADXL345_WE(CS_PIN, spi);
float Temp[2]={0,0};

int x, y, z;     
char str[512]; 

void setup(void) {
 
  Serial.begin(115200)  ;
 //初始化IIC(作为主设备)


    Serial.println("ADXL345_测试");
    Serial.println();
  while (!myAcc.init()) {
    Serial.println("ADXL345 未连接！");

  
     delay(2000);
  }
  myAcc.setCorrFactors(-266.0, 285.0, -268.0, 278.0, -291.0, 214.0);
  Serial.println("将您的 ADXL345 平放，不要移动它");
  delay(2000);
  myAcc.measureAngleOffsets();
  Serial.println("....完成");
   myAcc.setDataRate(ADXL345_DATA_RATE_50);
  Serial.print("数据速率：");
  Serial.print(myAcc.getDataRateAsString());
 
  /* 选择测量范围
      ADXL345_RANGE_16G    16g
      ADXL345_RANGE_8G      8g
      ADXL345_RANGE_4G      4g
      ADXL345_RANGE_2G      2g
  */
  myAcc.setRange(ADXL345_RANGE_2G);
  Serial.print("  /  g-范围: ");
  Serial.println(myAcc.getRangeAsString());
  Serial.println();

  delay(500);
  
}


void loop() {
  
 xyzFloat raw = myAcc.getRawValues();
  xyzFloat g = myAcc.getGValues();
  xyzFloat angle = myAcc.getAngles();
  xyzFloat corrAngles = myAcc.getCorrAngles();
 
  /* 仍然是未校正的原始值！！ */
  Serial.print("Raw-x    = ");
  Serial.print(raw.x);
  Serial.print("  |  Raw-y    = ");
  Serial.print(raw.y);
  Serial.print("  |  Raw-z    = ");
  Serial.println(raw.z);
 
  /* g 值使用校正后的原始值 */
  Serial.print("g-x     = ");
  Serial.print(g.x);
  Serial.print("  |  g-y     = ");
  Serial.print(g.y);
  Serial.print("  |  g-z     = ");
  Serial.println(g.z);
 
  /* 角度使用校正后的原始数据。角度简单地计算为
     角度 = arcsin(g 值) */
  Serial.print("角度 x  = ");
  Serial.print(angle.x);
  Serial.print("  |  角度 y  = ");
  Serial.print(angle.y);
  Serial.print("  |  角度 z  = ");
  Serial.println(angle.z);
  /* 修正后的角度使用修正后的原始数据和额外的角度
     偏移以确保它们从 0° 开始
  */
  Serial.print("修正角度 x = ");
  Serial.print(corrAngles.x);
  Serial.print("  |  修正角度 y   = ");
  Serial.print(corrAngles.y);
  Serial.print("  |  修正角度 z   = ");
  Serial.println(corrAngles.z);
  Serial.print("模块方向：");
  Serial.println(myAcc.getOrientationAsString());
  Serial.println();


  
  tft.init();
  tft.setRotation(3);
  tft.fillScreen(TFT_BLUE);
  tft.setCursor(20, 10);
  tft.setTextColor(TFT_WHITE);
  tft.setTextSize(2);
  tft.print("Hello ST7735!");

  ///
 Serial.print(i++);
 delay(2000);


}


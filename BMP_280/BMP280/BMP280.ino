/*
    Description: Use ENV II Unit to read temperature, humidity, atmospheric pressure, and display the data on the screen.
    Please install library before compiling:  
    Adafruit BMP280: https://github.com/adafruit/Adafruit_BMP280_Library
    参考：https://sample.msr-r.net/m5stack-env2/
*/
#include <M5Core2.h>
#include <Wire.h>
#include "Adafruit_Sensor.h"
#include <Adafruit_BMP280.h>
#include "SHT3X.h"
SHT3X sht30;
Adafruit_BMP280 bme;

float tmp = 0.0;
float hum = 0.0;
float pressure = 0.0;
void writeSerial(float sensorData);

void setup() {
  M5.begin();
  Wire.begin();
  Serial.begin(9800);
  M5.Lcd.setBrightness(10);
  M5.Lcd.setTextSize(3);
  Serial.println(F("ENV Unit(SHT30 and BMP280) test..."));

  while (!bme.begin(0x76)){  
    Serial.println("Could not find a valid BMP280 sensor, check wiring!");
    M5.Lcd.println("Could not find a valid BMP280 sensor, check wiring!");
  }
  M5.Lcd.clear(BLACK);
}

void loop() {
  pressure = bme.readPressure();
  if(sht30.get()==0){
    tmp = sht30.cTemp;
    hum = sht30.humidity;
  }
  Serial.printf("Temperatura: %2.2f*C  Humedad: %0.2f%%  Pressure: %0.2fPa\r\n", tmp, hum, pressure);
  M5.Lcd.setCursor(0, 0);
  M5.Lcd.fillScreen(BLUE);
  M5.Lcd.setTextColor(WHITE, BLUE);
  
  M5.Lcd.printf("Temp: %2.1fC  \r\nHumi: %2.0f%%  \r\nPressure:%2.0fPa\r\n", tmp, hum, pressure);
  float data1[]={tmp,hum,pressure};
  writeSerial(data1);
    
  delay(60000); // 1分ごとにデータを送信 60件/h

}

// Arduino から PC へセンサデータを送信する関数

void writeSerial(float sensorData[]) { // int型のデータを扱う際は (int sensorData) のように書き換え
  Serial.write("START\n");
  for(int i=0;i<3;i++){
  char buf[256];
  String str = String(sensorData[i]) + "\n";
  str.toCharArray(buf, str.length()+1);
  Serial.write(buf);  
  }
  Serial.write("END\n");
}

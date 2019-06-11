#include <Arduino.h>
#include <Wire.h>
#include <RH_RF24.h>
#include <RHReliableDatagram.h>
#include <SPI.h>
#define ALTI 0x77
//glob

int16_t readpressure();

void setup() {
  Serial.begin(9600);
  Wire.begin();

  pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
  digitalWrite(LED_BUILTIN, HIGH);
  delay(300);
  digitalWrite(LED_BUILTIN, LOW);
  delay(300);
  
  Serial.println(readpressure());

}

int16_t readpressure(){
  int16_t pressure;
    Wire.beginTransmission(ALTI);
    Wire.write(0xf4);
    Wire.write(0x34);
  Wire.endTransmission();

  Wire.beginTransmission(ALTI);
    Wire.write(0xf6);
  Wire.endTransmission();  

  Wire.requestFrom(ALTI, 2);
  pressure = Wire.read(); //bah ta invertido na real esse aqui é o LSB
  pressure |= Wire.read()<<8; // e na real esse é o MSB
  
  return pressure;

}
#include <Arduino.h>

#include <NewPing.h>
#include <LiquidCrystal_I2C.h>
#include <Wire.h>

LiquidCrystal_I2C lcd(0x27,16,2);
NewPing sonido (A1,A2);
int y = millis();
void setup() {
lcd.init();
lcd.backlight();
Serial.begin(9600);
lcd.clear();


}

void loop() {
 
  int cm = sonido.ping_cm();
  lcd.setCursor(0,0);
  lcd.print("distancia: ");
  lcd.print(cm);
  delay(50);
  lcd.clear();
}
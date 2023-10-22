#include <Arduino.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <MPU6050_tockn.h>

// Dirección I2C del MPU-6050
int mpuAddress = 0x68; // Puedes cambiarlo si la dirección es diferente

int customSDAPin = A1; // Cambia al número de GPIO que desees para SDA
int customSCLPin = A2; // Cambia al número de GPIO que desees para SCL

const char* ssid = "tereineitor";      // Nombre de tu red Wi-Fi
const char* password = "El mas veloz"; // Contraseña de tu red Wi-Fi

int lcdAddress = 0x27;
int lcdColumns = 16;
int lcdRows = 2;

MPU6050 mpu6050(Wire);

LiquidCrystal_I2C lcd(lcdAddress, lcdColumns, lcdRows);

void setup() {
  Serial.begin(9600);

  Wire.begin(customSDAPin, customSCLPin);

  Wire.beginTransmission(mpuAddress);
  if (Wire.endTransmission() == 0) {
    lcd.begin(lcdColumns, lcdRows);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("tereneitor iniciado");
    delay(2000);

    mpu6050.begin();
    mpu6050.calcGyroOffsets(true);
  } else {
    Serial.println("Error: No se pudo conectar al MPU-6050. Verifica la conexión.");
  }
}

void loop() {
  // Tu código para el bucle principal va aquí
}

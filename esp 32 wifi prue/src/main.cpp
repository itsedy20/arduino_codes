#include <Arduino.h>
#include <WiFi.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <MPU6050_tockn.h>

// Dirección I2C del MPU-6050
int mpuAddress = 0x68; // Puedes cambiarlo si la dirección es diferente


int customSDAPin = 33; // Cambia al número de GPIO que desees para SDA
int customSCLPin = 32; // Cambia al número de GPIO que desees para SCL

const char* ssid = "tereineitor";      // Nombre de tu red Wi-Fi
const char* password = "El mas veloz"; // Contraseña de tu red Wi-Fi
IPAddress ip(192, 168, 2, 4); 

int lcdAddress = 0x27;


int lcdColumns = 16;
int lcdRows = 2;


MPU6050 mpu6050(Wire1);


LiquidCrystal_I2C lcd(lcdAddress, lcdColumns, lcdRows);

int motor1A = 2;  // Pin del motor 1, adelante
int motor1B = 4;  // Pin del motor 1, atrás
int motor2A = 15; // Pin del motor 2, adelante
int motor2B = 13; // Pin del motor 2, atrás

WiFiServer server(5266); // Puerto para recibir comandos


void setup() {
  Serial.begin(115200);
  pinMode(motor1A, OUTPUT);
  pinMode(motor1B, OUTPUT);
  pinMode(motor2A, OUTPUT);
  pinMode(motor2B, OUTPUT);

   WiFi.softAP(ssid, password);
    WiFi.softAPConfig(ip, ip, IPAddress(255, 255, 255, 0));

    Wire.begin();

    Wire1.begin(customSDAPin,customSCLPin);

    lcd.begin(lcdColumns,lcdRows);

    lcd.clear();
    lcd.setCursor(0,0);

    lcd.print("tereneitor iniciado");
    delay(2000);
  
    mpu6050.begin();
    mpu6050.calcGyroOffsets(true);


  // Iniciar el servidor
  server.begin();
  Serial.println("al 100");
   Serial.println(WiFi.softAPIP());
}



void processCommand(char command) {
  mpu6050.update();
  int gyroX = mpu6050.getAngleX();
  int gyroY = mpu6050.getAngleY();
  int gyroZ = mpu6050.getAngleZ();
   lcd.clear();

  lcd.setCursor(0,1);
  lcd.print("x: ");
  lcd.print(gyroX);
  lcd.print("y: ");
  lcd.print(gyroY);
  lcd.print("z: ");
  lcd.print(gyroZ);

  // Procesar comandos recibidos desde Python
  switch (command) {
    case 'w':
      // Mover el carro hacia adelante
      digitalWrite(motor1A, HIGH);
      digitalWrite(motor1B, LOW);
      digitalWrite(motor2A, HIGH);
      digitalWrite(motor2B, LOW);
      lcd.setCursor(0,0);
      lcd.print("adelante");
   
      
      break;
    case 's':
      // Mover el carro hacia atrás
      digitalWrite(motor1A, LOW); 
     digitalWrite(motor1B, HIGH);
      digitalWrite(motor2A, LOW);
      digitalWrite(motor2B, HIGH);
      lcd.setCursor(0,0);
      lcd.print("atras");
      
      break;
    case 'a':
      // Girar a la izquierda
      digitalWrite(motor1A, LOW);
      digitalWrite(motor1B, HIGH);
      digitalWrite(motor2A, HIGH);
      digitalWrite(motor2B, LOW);
      lcd.setCursor(0,0);
      lcd.print("derecha");
      
      break;
    case 'd':
      // Girar a la derecha
      digitalWrite(motor1A, HIGH);
      digitalWrite(motor1B, LOW);
      digitalWrite(motor2A, LOW);
      digitalWrite(motor2B, HIGH);
      lcd.setCursor(0,0);
      lcd.print("izquierda");
      
      break;
    case 'q':
      // Detener el carro
      digitalWrite(motor1A, LOW);
      digitalWrite(motor1B, LOW);
      digitalWrite(motor2A, LOW);
      digitalWrite(motor2B, LOW);
      lcd.clear();
      lcd.setCursor(0,1);
      lcd.print("x: ");
      lcd.print(gyroX);
      lcd.print("y: ");
      lcd.print(gyroY);
      lcd.print("z: ");
      lcd.print(gyroZ);
     
      break;
  }+-
}
void loop() {
 
  WiFiClient client = server.available();

  if (client) {
    while (client.connected()) {
      if (client.available()) {
        char command = client.read();
        processCommand(command);
      }
    }
    client.stop();
  }
}


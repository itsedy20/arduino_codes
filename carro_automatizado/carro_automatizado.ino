#include <NewPing.h>
#include <Servo.h>
//car code
#define TRIG_PIN A1
#define ECHO_PIN A0
#define MAX_DISTANCE 200
NewPing sonar(TRIG_PIN, ECHO_PIN, MAX_DISTANCE);
Servo Ssg90;

boolean goesForward = false;
int distance = 100;
int speedSet = 0;

const int motorPin1  = 5;
const int motorPin2  = 4;
const int motorPin3  = 3;
const int motorPin4  = 2;

int lookRight()
{
  Ssg90.write(40);
  delay(500);
  int distance = readPing();
  delay(100);
  Ssg90.write(60);
  return distance;
}

int lookLeft()
{
  Ssg90.write(85);
  delay(500);
  int distance = readPing();
  delay(100);
  Ssg90.write(60);
  return distance;
  delay(100);
}

int readPing() {
  delay(70);
  int cm = sonar.ping_cm();
  if (cm == 0)
  {
    cm = 250;
  }
  return cm;
}

void Stop() {
  digitalWrite(motorPin1, LOW);
  digitalWrite(motorPin2, LOW);
  digitalWrite(motorPin3, LOW);
  digitalWrite(motorPin4, LOW);
}

void Forward() {


  digitalWrite(motorPin1, HIGH);
  digitalWrite(motorPin2, LOW);
  digitalWrite(motorPin3, HIGH);
  digitalWrite(motorPin4, LOW);

}

void Backward() {

  digitalWrite(motorPin1, LOW);
  digitalWrite(motorPin2, HIGH);
  digitalWrite(motorPin3, LOW);
  digitalWrite(motorPin4, HIGH);

}

void Right() {

  digitalWrite(motorPin1, HIGH);
  digitalWrite(motorPin2, LOW);
  digitalWrite(motorPin3, LOW);
  digitalWrite(motorPin4, HIGH);
  delay(300);
  Forward();

}

void Left() {
  digitalWrite(motorPin1, LOW);
  digitalWrite(motorPin2, HIGH);
  digitalWrite(motorPin3, HIGH);
  digitalWrite(motorPin4, LOW);
  delay(300);
  Forward();
}
void setup() {

  Ssg90.attach(8);
  Ssg90.write(60);
  delay(2000);
  distance = readPing();
  delay(100);
  distance = readPing();
  delay(100);
  distance = readPing();
  delay(100);
  distance = readPing();
  delay(100);
  Serial.println(distance);
}

void loop() {

  int distanceR = 0;
  int distanceL =  0;
  delay(40);

  if (distance <= 20)
  {
    Stop();
    delay(200);
    Backward();
    delay(800);

    Stop();
    delay(200);
    distanceR = lookRight();
    delay(200);
    distanceL = lookLeft();
    delay(200);

    if (distanceR >= distanceL)
    {
      Right();
      Stop();
    }
    else
    {
      Left();
      Stop();
    }
  }
  else
  {
    Forward();
  }
  distance = readPing();
}

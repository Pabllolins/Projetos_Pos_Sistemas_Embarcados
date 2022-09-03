#include <Arduino.h>
//#include <Servo.h>
#include <ESP32Servo.h>
Servo MeuServo;


void setup(){
  MeuServo.attach(5);
  Serial.begin(115200);
}

// Cria um objeto Servo
// Servo no pino 5
void loop()
{
//int angulo = analogRead(A0);
int angulo = analogRead(A6);
// Lê o valor do potenciômetro
angulo = map(angulo, 0, 1023, 0, 180); // Mudança de Escala
MeuServo.write(angulo);
// Escreve o ângulo para o servomotor
delay(20);
// Espera de 20ms para que o servomotor atinja a posição
}
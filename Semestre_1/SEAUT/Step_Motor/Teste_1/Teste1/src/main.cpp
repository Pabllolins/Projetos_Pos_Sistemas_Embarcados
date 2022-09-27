#include <Arduino.h>

const int IN1 = 2; //Bobina 1
const int IN2 = 4; //Bobina 2
const int IN3 = 5; //Bobina 3
const int IN4 = 18; //Bobina 4
const int step = 10; //tempo de cada pulso (ms)

void setup()
{
pinMode(IN1, OUTPUT); //Pinos como saídas
pinMode(IN2, OUTPUT);
pinMode(IN3, OUTPUT);
pinMode(IN4, OUTPUT);
digitalWrite(IN1, LOW);//Bobinas desligadas
digitalWrite(IN2, LOW);
digitalWrite(IN3, LOW);
digitalWrite(IN4, LOW);
Serial.begin(115200);
}

void loop() {
  int i = 0;

  //modo full-step simples
  while(i++<2048){
    digitalWrite(IN4, LOW);
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, HIGH);
    delay(step);

    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);
    digitalWrite(IN3, HIGH);
    delay(step);

    digitalWrite(IN2, LOW);
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, HIGH);
    delay(step);

    digitalWrite(IN3, LOW);
    digitalWrite(IN4, HIGH);
    digitalWrite(IN1, HIGH);
    delay(step);

    //delay(1000);
    //Serial.println(i);
  }

}
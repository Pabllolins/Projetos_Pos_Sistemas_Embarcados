#include <Arduino.h>
#include <ESP32Servo.h>
Servo MeuServo;

int valorSerial=0;

void setup(){
  MeuServo.attach(5);
  Serial.begin(115200);

  delay(100);
  Serial.println("Serial iniciada");
}

// Cria um objeto Servo
// Servo no pino 5
void loop()
{
  if(Serial.available() > 0){

    //valorSerial = Serial.read();
    valorSerial = Serial.parseInt();

    if((valorSerial >= 0) && (valorSerial <= 180)){
      MeuServo.write(valorSerial);
      Serial.print("Valor recebido: ");
      Serial.println(valorSerial);
      // Escreve o ângulo para o servomotor
      delay(20);
      // Espera de 20ms para que o servomotor atinja a posição
    }else{
      Serial.println("Valor invalido");
    }
  }
}
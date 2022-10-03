/*
 * Autor: Pabllo Lins
 * Versão: v.1.0
 * Descrição: Código para atendimento a atividade de radar, motor de passo+HC-SR04
 * Licença: N/A
 * Data: 25/09/2022
*/

/*  Informações adicionais
* PLACA: DOIT v.1
* MCU: ESP32
* IDE: Visual Studio Code
* Extension: PlatformIO
* Framework: Arduino IDE
* Terminal - D21 - HC-SR04 trigger
* Terminal - D22 - HC-SR04 echo
*/

#include <Arduino.h>


//_______________________________Ultrassom
const int trig = 21;
const int echo = 22;
unsigned long previousMicros;
unsigned long timeout = 29000;  //Dmax = 500 cm, D = t/58, timeout = 500*58

unsigned int ultrassom_tempo();
float Distancia(int tempo);
unsigned int ultrassom_cm(unsigned int tempo_us);



void setup() {
  Serial.begin(115200);

  //Inicializa o HC-SR04
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
}

void loop() {
  unsigned int temp;
  unsigned int cm;
  float Dist_cm;
  unsigned int graus = 0;
  unsigned int avanco = 30;

  while(1)
  {
    temp = ultrassom_tempo();

    Dist_cm = Distancia(temp);
    Serial.print("Distância do objeto [cm]: "); Serial.println(Dist_cm);
    delay(1000);
  }
}


unsigned int ultrassom_tempo() 
{
  //Pulso de 10us
  digitalWrite(trig, LOW);
  delayMicroseconds(2);
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);
  //Lê tempo atual
  previousMicros = micros();
  //Aguarda borda de subida ou timeout
  while(!digitalRead(echo) && (micros() - previousMicros) <= timeout); // wait for the echo pin HIGH or timeout
  //Atualiza o tempo atual
  previousMicros = micros();
  //Aguarda borda de descida ou timeout
  while(digitalRead(echo)  && (micros() - previousMicros) <= timeout); // wait for the echo pin LOW or timeout
  //Calcula a diferença de tempos
  return micros() - previousMicros; // duration
}

//y = (0.0175 * x) + 0.4649
float Distancia(int tempo) 
{
  return ((0.0175 * tempo) + 0.4649);
}
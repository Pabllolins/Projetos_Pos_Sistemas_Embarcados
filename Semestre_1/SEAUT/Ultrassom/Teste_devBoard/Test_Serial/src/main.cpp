#include <Arduino.h>
//TESTE - HC-SR04
#include <Stepper.h>

#define TESTE1
#ifndef TESTE1
  #define TESTE2
#endif

unsigned int ultrassom_tempo();
unsigned int ultrassom_cm(unsigned int tempo_us);

//Ultrassom
const int trig = 21;
const int echo = 22;
unsigned long previousMicros;
unsigned long timeout = 29000;  //Dmax = 500 cm, D = t/58, timeout = 500*58

//Motor de passo
const int stepsPerRevolution = 2048;
//Cria um objeto Stepper
Stepper myStepper(stepsPerRevolution, 8, 10, 9, 11);


void setup() {
  //Inicializa a porta serial
  Serial.begin(115200);

  //Inicializa o HC-SR04
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
}

void loop() {
  unsigned int tempo;
  unsigned int cm;
  unsigned int graus = 0;
  unsigned int avanco = 30;
  
  #ifdef TESTE1
    //Teste 1 - Teste o HC-SR04
    while(1)
    {
      tempo = ultrassom_tempo();
      cm = ultrassom_cm(tempo);
      
      Serial.print("Tempo do eco [us]: "); 
      Serial.println(tempo);

      Serial.print("Distância do objeto [cm]: "); 
      Serial.println(cm);

      delay(1000);
    }
  #else
  //Teste 2 - Radar com o HC-SR04
  while(0)
  {
    if(graus > 180)
    {
      //Home
      graus = 0;
      //Retorna o motor 180 graus
      myStepper.step(-stepsPerRevolution/2);
      //Aguarda um tempo para reiniciar
      delay(1000);      
    }
    while (graus <= 180)
    {
      //Executa a leitura
      
      //Envia pela serial

      //Envia via bluetooth para o app Bluetooth Electronics

      //Posiona o motor/sensor

      //Atualiza a quantidade de graus

      //Aguarda um tempo até a próxima leitura
      delay(100);
    }
  }
  #endif
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

unsigned int ultrassom_cm(unsigned int tempo_us) 
{
  return tempo_us / 58;
}
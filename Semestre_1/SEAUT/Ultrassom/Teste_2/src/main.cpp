/*
 * Autor: Pabllo Lins
 * Versão: v.1.0
 * Descrição: Código para atendimento a atividade de radar, motor de passo+HC-SR04
 * Licença: N/A
 * Data: 24/09/2022
*/

/*  Informações adicionais
* PLACA: DOIT v.1
* MCU: ESP32
* IDE: Visual Studio Code
* Extension: PlatformIO
* Framework: Arduino IDE
* Terminal - D4 - Bobina 1 Motor de passo
* Terminal - D15 - Bobina 2 Motor de passo
* Terminal - D18 - Bobina 3 Motor de passo
* Terminal - D19 - Bobina 4 Motor de passo
* Terminal - D21 - HC-SR04 trigger
* Terminal - D22 - HC-SR04 echo
*/

#include <Arduino.h>
#include <Stepper.h>

#define FS 32
#define HS 64

//_______________________________Ultrassom
const int trig = 21;
const int echo = 22;
unsigned long previousMicros;
unsigned long timeout = 29000;  //Dmax = 500 cm, D = t/58, timeout = 500*58
unsigned int ultrassom_tempo();
unsigned int ultrassom_cm(unsigned int tempo_us);


//_______________________________Motor de passo
int NumeroPassos = HS;
float ConverteGrausEmPassos(int Graus);
unsigned int avanco = 5;
signed int stepsPerRevolution = (signed int)ConverteGrausEmPassos(avanco);
const int Bobina1 = 4; //Bobina 1
const int Bobina2 = 15; //Bobina 2
const int Bobina3 = 18; //Bobina 3
const int Bobina4 = 19; //Bobina 4
//Cria um objeto Stepper
Stepper myStepper(stepsPerRevolution, Bobina1, Bobina3, Bobina2, Bobina4);



void setup() {
  //Inicializa a porta serial
  Serial.begin(115200);

  // set the speed at 60 rpm:
  pinMode(Bobina1, OUTPUT);
  pinMode(Bobina2, OUTPUT);
  pinMode(Bobina3, OUTPUT);
  pinMode(Bobina4, OUTPUT);
  myStepper.setSpeed(60);

  //Inicializa o HC-SR04
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
}

void loop() {
  unsigned int tempo;
  unsigned int cm;
  float graus = 0;
  
  while(1)
  {
    delay(1000);
    while (graus < 180)
    {
      //Executa a leitura
      tempo = ultrassom_tempo();
      cm = ultrassom_cm(tempo);      
      
      //Envia pela serial
      Serial.print((int)graus);
      Serial.print(",");  
      Serial.print(cm);
      Serial.print("."); 

      //Posiona o motor/sensor
      myStepper.step(stepsPerRevolution);
      
      //Atualiza a quantidade de graus
      graus += avanco;
    }
    delay(1000);

    while (graus > 0)
    {
      //Executa a leitura      
      tempo = ultrassom_tempo();
      cm = ultrassom_cm(tempo);

      //Envia pela serial    
      Serial.print((int)graus);
      Serial.print(",");  
      Serial.print(cm);
      Serial.print(".");

      //Retorna o motor
      myStepper.step(-stepsPerRevolution); 
      graus -= avanco;
    }  
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

unsigned int ultrassom_cm(unsigned int tempo_us) 
{
  return tempo_us / 58;
}


/*
*   Função: float ConverteGrausEmPassos(int Graus)
*   Entrada: valor em graus (inteiro)
*   Saida/Retorno: Quatidade de passor por revolução de acordo com a entrada  
*   Obs.:
*   Relação da redução 1:64 (1 revolução no eixo do motor equivale a 64 revoluções do eixo de passo)
*   Ângulo de passo eixo do motor: 5,625°/64
*   Ângulo de passo: 0,087890625°
*   Autor: Pabllo Lins
*   Data: 24/09/2022
*/
float ConverteGrausEmPassos(int Graus) 
{
  float AngPasso = 5.625;
  
  if(NumeroPassos == HS)
  {
    return (Graus/(AngPasso/NumeroPassos));
  }
  else
  {
    return (Graus/(AngPasso/NumeroPassos));
  }
  
}
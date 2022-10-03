/*
 * Autor: Pabllo Lins
 * Versão: v.1.0
 * Descrição: Código para atendimento a atividade de radar, Fechadura de cofre
 * Licença: N/A
 * Data: 26/09/2022
*/

/*
Use o sensor encoder rotacional Keyes KY-040 para criar uma fechadura de
cofre. Crie uma sequência de giros horários e anti-horários para
acionamento de um servo motor, que desbloqueara a porta do cofre.
Sugestão: use a chave do encoder para iniciar e finalizar o processo. Leds de
cores diferentes também podem ser usados para indicar o estado da
fechadura.
*/

/*  Informações adicionais
* PLACA: DOIT v.1
* MCU: ESP32
* IDE: Visual Studio Code
* Extension: PlatformIO
* Framework: Arduino IDE
* Terminal - D33 - Encoder Pino Data
* Terminal - D32 - Encoder Pino Clock
* Terminal - D34 - Encoder Pino Sw
* Terminal - D5 - SERVO
*
* Destravamento: 1 clik no potenciometro + 4 giros para esquerda + 
*                 3 giros para direita + 2 giros para esquerda +
*                   1 click
*/

#include <Arduino.h>
#include <ESP32Servo.h>

#define depuracao

/*  Definições de pinos */
#define PIN_LED_AZUL 2
#define PIN_LED_VERDE 4
#define PIN_LED_VERMELHO 18
#define PIN_SERVO 5
#define PIN_ENCODER_CLK 32
#define PIN_ENCODER_DT 33
#define PIN_ENCODER_SW 15

/*  Variavei Globais */
const int PinClk = PIN_ENCODER_CLK;
const int PinData = PIN_ENCODER_DT;
const int PinSw = PIN_ENCODER_SW;
int encoderPostCount = 0;
int pinALast; 
int aVal; 
boolean bCW;
unsigned int contador = 0;
unsigned char nivel = 0;

/*  Instaciamento de objeto */
Servo ServoMotor;

/*  Prototipo de funções */
void Destrava (void);
void Trava (void);
void LedDestravando (void);
void LedOk (void);
void LedNok (void);
void RetornaInicio(void);
void Nivel_1(void);
void Nivel_2(void);
void Nivel_3(void);
void Nivel_4(void);
void Nivel_5(void);
void VerificaEncoder(void);
void IncrementaContador(void);


void setup() 
{
  pinMode(PIN_SERVO, OUTPUT); //Define o pino 5 como saida
  ServoMotor.attach(PIN_SERVO); //Conecta o pino 5 para o acionamento do servo

  pinMode(PIN_LED_AZUL, OUTPUT);
  digitalWrite(PIN_LED_AZUL, LOW);

  pinMode(PIN_LED_VERDE, OUTPUT);
  digitalWrite(PIN_LED_VERDE, LOW);
  
  pinMode(PIN_LED_VERMELHO, OUTPUT);
  digitalWrite(PIN_LED_VERMELHO, LOW);
   
  pinMode(PIN_ENCODER_CLK, INPUT);
  pinMode(PIN_ENCODER_DT, INPUT);
  pinMode(PIN_ENCODER_SW, INPUT_PULLUP);

  pinALast = digitalRead(PinClk);
  Serial.begin(115200);

  ServoMotor.write(90); //Posicao inicial do servo 90° (centro)

  #ifdef depuracao
    Serial.println("Serial iniciada\n");
  #endif
}

void loop() 
{
  switch (nivel)
  {
    case 0:
      Nivel_1();
      break;
    
    case 1:
      Nivel_2();
      break;
    
    case 2:
      Nivel_3();
      break;      
    
    case 3:
      Nivel_4();
      break; 

    case 4:
      Nivel_5();
      break; 

    default:
      break;
  }
}
/*****************************************************************************/

void Destrava (void)
{

}

void Trava (void)
{

}

void LedDestravando (void)
{
  digitalWrite(PIN_LED_AZUL, HIGH);
}

void LedOk (void)
{

}

void LedNok (void)
{

}

void RetornaInicio(void)
{
  digitalWrite(PIN_LED_AZUL, LOW);
  contador = 0;
  nivel = 0;
  ServoMotor.write(90);
}

void Nivel_1(void)
{
  while(contador < 5000)
  {
    if(digitalRead(PIN_ENCODER_SW) == LOW)
    {
      delay(30);//debounce
      if(digitalRead(PIN_ENCODER_SW) == LOW)
      {
        LedDestravando();
        nivel++;
        #ifdef depuracao
          Serial.print("nivel: ");
          Serial.println(nivel);
        #endif
        break;
      }
    }
    IncrementaContador();
  }

  if(contador >= 5000)
  {
    RetornaInicio();
  }
  else
  {
    contador = 0;
  }
}


void Nivel_2(void)
{
  while(contador < 5000)
  {
    VerificaEncoder();
    IncrementaContador();
    if(encoderPostCount == -4)
    {
      encoderPostCount = 0;
      nivel++;
      #ifdef depuracao
        Serial.print("nivel: ");
        Serial.println(nivel);
      #endif
      break;      
    }
  }

  if(contador >= 5000)
  {
    RetornaInicio();
  }
  else
  {
    contador = 0;
  }
}


void Nivel_3(void)
{
  while(contador < 5000)
  {
    VerificaEncoder();
    IncrementaContador();
    if(encoderPostCount == 3)
    {
      encoderPostCount = 0;
      nivel++;
      #ifdef depuracao
        Serial.print("nivel: ");
        Serial.println(nivel);
      #endif
      break;      
    }
  }

  if(contador >= 5000)
  {
    RetornaInicio();
  }
  else
  {
    contador = 0;
  }
}


void Nivel_4(void)
{
  while(contador < 5000)
  {
    VerificaEncoder();
    IncrementaContador();
    if(encoderPostCount == -2)
    {
      encoderPostCount = 0;
      nivel++;
      #ifdef depuracao
        Serial.print("nivel: ");
        Serial.println(nivel);
      #endif
      break;      
    }
  }

  if(contador >= 5000)
  {
    RetornaInicio();
  }
  else
  {
    contador = 0;
  }
}


void Nivel_5(void)
{
  while(contador < 5000)
  {
    if(digitalRead(PIN_ENCODER_SW) == LOW)
    {
      delay(30);//debounce
      if(digitalRead(PIN_ENCODER_SW) == LOW)
      {
        LedOk();
        #ifdef depuracao
          Serial.println("Desbloqueio");
        #endif
        ServoMotor.write(0);
        delay(10000);//debounce
        RetornaInicio();
        break;
      }
    }
    IncrementaContador();
  }

  if(contador >= 5000)
  {
    RetornaInicio();
  }
}

void VerificaEncoder(void)
{
  aVal =  digitalRead(PinClk);
  
  if(aVal != pinALast)
  {
    if(digitalRead(PinData) != aVal)
    {
      contador = 0;
      encoderPostCount++;
      bCW = true;
    }
    else
    {
      contador = 0;
      encoderPostCount--;
      bCW = false;
    }
    #ifdef depuracao
      Serial.print("Rotação: ");
      
      if(bCW)
      {
        Serial.println("horária");
      }
      else
      {
        Serial.println("anti-horária");
      }

      Serial.print("Posição do encoder: ");
      Serial.println(encoderPostCount);
    #endif
  }
  pinALast = aVal;
}

void IncrementaContador(void)
{
  delay(1);
  contador++;
}
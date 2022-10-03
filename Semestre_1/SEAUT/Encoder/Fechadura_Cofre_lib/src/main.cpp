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
#include "MinhaLibEncoder.h"


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

signed int ContadorEncoder = 0;
signed int Ultimo_ContadorEncoder = 0;
int Ultimo_Sinal_A_Encoder; 
int Sinal_A_Encoder; 
int contadorMilis = 0;
unsigned char nivel = 0;
bool Segue = false;

/*  Instaciamento de objeto */
Servo ServoMotor;

/*  Prototipo de funções */
void Destrava (void);
void Trava (void);
void LedOk (void);
void LedNok (void);
void RetornaInicio(void);
void Nivel_0(void);
void Nivel_1(void);
void Nivel_2(void);
void Nivel_3(void);
void Nivel_4(void);
void SobeNivel(void);
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
   
  v_IniciaEncoder(PIN_ENCODER_CLK, PIN_ENCODER_DT, PIN_ENCODER_SW);

  Ultimo_Sinal_A_Encoder = digitalRead(PinClk);
  Serial.begin(115200);

  ServoMotor.write(90); //Posicao inicial do servo 90° (centro)

  #ifdef depuracao
    Serial.println("Serial iniciada\n");
  #endif
}

/*****************************************************************************/
void loop() 
{
  switch (nivel)
  {
    case 0:
      Nivel_0();
      break;
    
    case 1:
      Nivel_1();
      break;
    
    case 2:
      Nivel_2();
      break;      
    
    case 3:
      Nivel_3();
      break; 

    case 4:
      Nivel_4();
      break; 

    default:
      nivel = 0;
      break;
  }
}
/*****************************************************************************/


/*****************************************************************************/
void Destrava (void)
{
  LedOk();
  #ifdef depuracao
    Serial.println("Desbloqueio\n");
  #endif
  ServoMotor.write(0);
  delay(10000);//debounce
}

/*****************************************************************************/
void Trava (void)
{
  LedNok();
  #ifdef depuracao
    Serial.println("Bloqueio\n");
  #endif
  ServoMotor.write(90);
  delay(10000);//debounce
}

/*****************************************************************************/
void LedOk (void)
{
  digitalWrite(PIN_LED_AZUL, LOW);
  digitalWrite(PIN_LED_VERDE, HIGH);
}

/*****************************************************************************/
void LedNok (void)
{
  digitalWrite(PIN_LED_AZUL, LOW);
  digitalWrite(PIN_LED_VERMELHO, HIGH);
}

/*****************************************************************************/
void RetornaInicio(void)
{
  digitalWrite(PIN_LED_AZUL, LOW);
  digitalWrite(PIN_LED_VERDE, LOW);
  digitalWrite(PIN_LED_VERMELHO, LOW);
  contadorMilis = 0;
  ContadorEncoder = 0;
  Ultimo_ContadorEncoder = 0;
  nivel = 0;
  ServoMotor.write(90);
}

/*****************************************************************************/
void Nivel_0(void)
{
  #ifdef depuracao
    Serial.print("Entrando no nivel: ");
    Serial.println(nivel);
    Serial.println();
  #endif
  while(contadorMilis < 5000)
  {
    if(digitalRead(PIN_ENCODER_SW) == LOW)
    {
      delay(30);//debounce
      if(digitalRead(PIN_ENCODER_SW) == LOW)
      {
        digitalWrite(PIN_LED_AZUL, HIGH);
        nivel++;
        #ifdef depuracao
          Serial.print("Indo para nivel: ");
          Serial.println(nivel);
          Serial.println();
        #endif
        break;
      }
    }
    IncrementaContador();
  }

  if(contadorMilis >= 5000)
  {
    RetornaInicio();
  }
  else
  {
    contadorMilis = 0;
  }
}

/*****************************************************************************/
void Nivel_1(void)
{
  #ifdef depuracao
    Serial.print("Entrando no nivel: ");
    Serial.println(nivel);
    Serial.println();
  #endif
  while(contadorMilis < 5000)
  {
    LeEncoder(PIN_ENCODER_CLK, PIN_ENCODER_DT, &Sinal_A_Encoder, 
                &Ultimo_Sinal_A_Encoder);

    IncrementaContador();

    if (ContadorEncoder == -4)
    {
      Segue = true;
      contadorMilis = 0;
      Ultimo_ContadorEncoder = ContadorEncoder;
      for(int i = 0; i <=(2000-contadorMilis); i++)
      {
        LeEncoder(PIN_ENCODER_CLK, PIN_ENCODER_DT, &Sinal_A_Encoder, 
                &Ultimo_Sinal_A_Encoder);
        if(ContadorEncoder != Ultimo_ContadorEncoder)
        {
          i = 0;
          Segue = false;
        }
        IncrementaContador();
      }
      
      if(Segue == true)
      {
        SobeNivel();
        ContadorEncoder = 0;
        nivel++;
        Ultimo_ContadorEncoder = ContadorEncoder;
        #ifdef depuracao
          Serial.print("Indo para nivel: ");
          Serial.println(nivel);
          Serial.println();
        #endif
        break;
      }
      else
      {
        LedNok();
        delay(2000);
        RetornaInicio();
        break;
      }      
    }
    else if((ContadorEncoder > 0) || (ContadorEncoder > Ultimo_ContadorEncoder))
    {
      contadorMilis = 0;
      for(int i = 0; i <=(2000-contadorMilis); i++)
      {
        LeEncoder(PIN_ENCODER_CLK, PIN_ENCODER_DT, &Sinal_A_Encoder, 
                &Ultimo_Sinal_A_Encoder);
        if(ContadorEncoder != Ultimo_ContadorEncoder)
        {
          i = 0;
        }
        IncrementaContador();
      }
      LedNok();
      delay(2000);
      RetornaInicio();
      break;
    }
    Ultimo_ContadorEncoder = ContadorEncoder;
  }

  if(contadorMilis >= 5000)
  {
    LedNok();
    RetornaInicio();
  }
  else
  {
    contadorMilis = 0;
  }
}

/*****************************************************************************/
void Nivel_2(void)
{
  #ifdef depuracao
    Serial.print("Entrando no nivel: ");
    Serial.println(nivel);
    Serial.println();
  #endif
  while(contadorMilis < 5000)
  {
    LeEncoder(PIN_ENCODER_CLK, PIN_ENCODER_DT, &Sinal_A_Encoder, 
                &Ultimo_Sinal_A_Encoder);

    IncrementaContador();
    if(ContadorEncoder == 3)
    {
      Segue = true;
      contadorMilis = 0;
      Ultimo_ContadorEncoder = ContadorEncoder;
      for(int i = 0; i <=(2000-contadorMilis); i++)
      {
        LeEncoder(PIN_ENCODER_CLK, PIN_ENCODER_DT, &Sinal_A_Encoder, 
                &Ultimo_Sinal_A_Encoder);
        if(ContadorEncoder != Ultimo_ContadorEncoder)
        {
          i = 0;
          Segue = false;
        }
        IncrementaContador();
      }
      
      if(Segue == true)
      {
        SobeNivel();
        ContadorEncoder = 0;
        nivel++;
        Ultimo_ContadorEncoder = ContadorEncoder;
        #ifdef depuracao
          Serial.print("Indo para nivel: ");
          Serial.println(nivel);
          Serial.println();
        #endif
        break;
      }
      else
      {
        LedNok();
        delay(2000);
        RetornaInicio();
        break;
      }      
    }
    else if((ContadorEncoder < 0) || (ContadorEncoder < Ultimo_ContadorEncoder))
    {
      contadorMilis = 0;
      for(int i = 0; i <=(2000-contadorMilis); i++)
      {
        LeEncoder(PIN_ENCODER_CLK, PIN_ENCODER_DT, &Sinal_A_Encoder, 
                &Ultimo_Sinal_A_Encoder);
        if(ContadorEncoder != Ultimo_ContadorEncoder)
        {
          i = 0;
        }
        IncrementaContador();
      }
      LedNok();
      delay(2000);
      RetornaInicio();
      break;
    }
    Ultimo_ContadorEncoder = ContadorEncoder;
  }

  if(contadorMilis >= 5000)
  {
    LedNok();
    RetornaInicio();
  }
  else
  {
    contadorMilis = 0;
  }
}

/*****************************************************************************/
void Nivel_3(void)
{
  #ifdef depuracao
    Serial.print("Entrando no nivel: ");
    Serial.println(nivel);
    Serial.println();
  #endif
  while(contadorMilis < 5000)
  {
    LeEncoder(PIN_ENCODER_CLK, PIN_ENCODER_DT, &Sinal_A_Encoder, 
                &Ultimo_Sinal_A_Encoder);

    IncrementaContador();
    if(ContadorEncoder == -2)
    {
      Segue = true;
      contadorMilis = 0;
      Ultimo_ContadorEncoder = ContadorEncoder;
      for(int i = 0; i <=(2000-contadorMilis); i++)
      {
        LeEncoder(PIN_ENCODER_CLK, PIN_ENCODER_DT, &Sinal_A_Encoder, 
                &Ultimo_Sinal_A_Encoder);
        if(ContadorEncoder != Ultimo_ContadorEncoder)
        {
          i = 0;
          Segue = false;
        }
        IncrementaContador();
      }
      
      if(Segue == true)
      {
        SobeNivel();
        ContadorEncoder = 0;
        nivel++;
        Ultimo_ContadorEncoder = ContadorEncoder;
        #ifdef depuracao
          Serial.print("Indo para nivel: ");
          Serial.println(nivel);
          Serial.println();
        #endif
        break;
      }
      else
      {
        LedNok();
        delay(2000);
        RetornaInicio();
        break;
      }        
    }
    else if((ContadorEncoder > 0) || (ContadorEncoder > Ultimo_ContadorEncoder))
    {
      contadorMilis = 0;
      for(int i = 0; i <=(2000-contadorMilis); i++)
      {
        LeEncoder(PIN_ENCODER_CLK, PIN_ENCODER_DT, &Sinal_A_Encoder, 
                &Ultimo_Sinal_A_Encoder);
        if(ContadorEncoder != Ultimo_ContadorEncoder)
        {
          i = 0;
        }
        IncrementaContador();
      }
      LedNok();
      delay(2000);
      RetornaInicio();
      break;
    }    
    Ultimo_ContadorEncoder = ContadorEncoder;
  }

  if(contadorMilis >= 5000)
  {
    LedNok();
    RetornaInicio();
  }
  else
  {
    contadorMilis = 0;
  }
}

/*****************************************************************************/
void Nivel_4(void)
{
  #ifdef depuracao
    Serial.print("Entrando no nivel: ");
    Serial.println(nivel);
    Serial.println();
  #endif
  while(contadorMilis < 5000)
  {
    if(digitalRead(PIN_ENCODER_SW) == LOW)
    {
      delay(30);//debounce
      if(digitalRead(PIN_ENCODER_SW) == LOW)
      {
        Destrava();
        RetornaInicio();
        break;
      }
    }
    IncrementaContador();
  }

  if(contadorMilis >= 5000)
  {
    LedNok();
    delay(2000);
    RetornaInicio();
  }
}

/*****************************************************************************/
void SobeNivel(void)
{
  digitalWrite(PIN_LED_AZUL, LOW);
  delay(100);
  digitalWrite(PIN_LED_AZUL, HIGH);
}

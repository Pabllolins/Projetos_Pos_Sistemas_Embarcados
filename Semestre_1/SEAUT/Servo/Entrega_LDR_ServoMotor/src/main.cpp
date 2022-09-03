/*
 * Autor: Pabllo Lins
 * Versão: v.1.0
 * Descrição: Código para aplicação de Servo motor e 2 sensores de luz LDR em placa ESP32
 * Licença: N/A
 * Data: 14/08/2022
*/

/*  Informações adicionais
* PLACA: DOIT v.1
* MCU: ESP32
* IDE: Visual Studio Code
* Extensio: PlatformIO
* PINO LDR ESQUERDA - A7 (D35)
* PINO LDR DIREITA - A6 (D34)
* PINO LDR SERVO - D5
*/

/* Diretivas de pré-compilação */
#include <Arduino.h>
#include <ESP32Servo.h>

/*  Defines  */
#define LDR_Esquerda 1
#define LDR_Direita 2
//#define depuracao 1 //Utilizado durante o desenvolvilmento

/*  Iniciando objeto de classe Servo  */
Servo MeuServo;

/*  Protótipo de funções  */
int ValorLDRConvertido();

/*  Funçao de configuração  */
void setup(){
  pinMode(5, OUTPUT); //Define o pino 5 como saida

  MeuServo.attach(5); //Conecta o pino 5 para o acionamento do servo
  
  Serial.begin(115200); //Inicia a seria com velocidade de 115200 bps
  
  MeuServo.write(90); //Posicao inicial do servo 90° (centro)

  delay(200); //aguarda 0,2s

  #ifdef depuracao
  Serial.println("Serial iniciada\n\n");
  #endif
}

/*  Funçao principal  */
void loop(){
  MeuServo.write(ValorLDRConvertido()); // Envia para acionamento do Servo o retorno da função ValorLDRConvertido()
  
  #ifdef depuracao
    delay(1000);
  #else
    delay(10);//aguarda 0,01 s
  #endif
}




/* ----------------------------  Outras funções ----------------------------  */
int ValorLDRConvertido(){
  int ValorLidoLDR;
  signed int ValorLDRConvertidoEsquerda;
  signed int ValorLDRConvertidoDireita;
  int ValorFinalParaServo;
  int LDREsquerda;
  int LDRDireita;
  
  for(int ldr = 1; ldr <=2; ldr++){
    switch (ldr){
      case 1: //LDR_Esquerda
        ValorLidoLDR = analogRead(35); //PINO LDR ESQUERDA - A7 (D35)        
        LDREsquerda = ValorLidoLDR;
        
        #ifdef depuracao
        Serial.print("Valor analogico lido LDR Esquerda: ");
        Serial.println(ValorLidoLDR);
        delay(1000);
        #endif

        ValorLDRConvertidoEsquerda = map(LDREsquerda, 0, 4095, 0, 90);      
        #ifdef depuracao
        Serial.print("Valor LDR Esquerdaconvertdo convertido para servo:");
        Serial.println(ValorLDRConvertidoEsquerda);
        delay(1000);
        #endif
      break;

    case 2: //LDR_Direita
        ValorLidoLDR = analogRead(34); //PINO LDR DIREITA - A6 (D34)
        LDRDireita = ValorLidoLDR;
        
        #ifdef depuracao
        Serial.print("Valor analogico lido LDR Direita: ");
        Serial.println(ValorLidoLDR);
        delay(1000);
        #endif

        ValorLDRConvertidoDireita = map(LDRDireita, 0, 4095, 180, 90);
        #ifdef depuracao
        Serial.print("Valor LDR Esquerdaconvertdo convertido para servo:");
        Serial.println(ValorLDRConvertidoDireita);
        delay(1000);
        #endif
      break;

    default:
      break;
    }
  }

  if(LDRDireita < LDREsquerda){
    ValorFinalParaServo = ValorLDRConvertidoDireita;
  }else if(LDREsquerda < LDRDireita){
    ValorFinalParaServo = ValorLDRConvertidoEsquerda;
  }

  return ValorFinalParaServo;
}
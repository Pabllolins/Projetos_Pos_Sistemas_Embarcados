/*
 * Autor: Pabllo Lins
 * Versão: v.1.0
 * Descrição: Código para atendimento a atividade de RFID
 * Licença: N/A
 * Data: 29/08/2022
*/

/*  Informações adicionais
* PLACA: DOIT v.1
* MCU: ESP32
* IDE: Visual Studio Code
* Extension: PlatformIO
* Framework: Arduino IDE
* Terminal - Led BuiltIn    - D2 
* Terminal - RST/Reset(RST) - D4 
* Terminal - SPI SS(SDA/SS) - D5
* Terminal - SPI MOSI(MOSI) - D23 
* Terminal - SPI MISO(MISO) - D19
* Terminal - SPI SCK(SCK)   - D18
* Terminal - Rele           - D22
* Terminal - Botao          - D21
*/

/* Diretivas de pré-compilação */
#include <SPI.h>
#include <MFRC522.h>

/*  Defines  */
#define LIGA 0x1
#define DESLIGA 0x0
#define PINO_SDA 5
#define PINO_RST 4
#define PINO_LED_AZUL 2
#define PINO_LED_VERMELHO 27
#define PINO_LED_VERDE 26
#define PINO_RELE 22
#define PINO_BOTAO 21  
//#define DEPURACAO 1 //Utilizado durante o desenvolvilmento
#define IMPRIME_INFOS_CARTAO 1 
#define MAXIMO_CARTOES 4

/*  Iniciando objeto de classe Servo  */ 
MFRC522 rfid(PINO_SDA, PINO_RST); // Instance of the class

MFRC522::MIFARE_Key key; 

/*  Variaveis Globais  */
uint8_t CartoesCadastrados = 0;
byte nuidPICC[4];// Init array that will store new NUID 
byte CartaoNaLeitora[MAXIMO_CARTOES][4];


/*  Protótipo de funções  */
void printHex(byte *buffer, byte bufferSize);
void printDec(byte *buffer, byte bufferSize);
void CartaoValido(void);
void CartaoInvalido(void);
void AbrePorta(void);
void FechaPorta(void);
void RotinaBotao(void);
void CadastrandoCartao(void);
void DescadastradoCartao(void);


/*  Funçao de configuração  */
void setup() { 
  pinMode(PINO_LED_AZUL, OUTPUT); //Define o pino do led da placa como saida
  pinMode(PINO_LED_VERMELHO, OUTPUT); //Define o pino do led da placa como saida
  pinMode(PINO_LED_VERDE, OUTPUT); //Define o pino do led da placa como saida
  pinMode(PINO_RELE, OUTPUT); //Define o pino do rele como saida
  pinMode(PINO_BOTAO, INPUT_PULLUP); //Define o pino do rele como saida
  digitalWrite(PINO_LED_AZUL, DESLIGA); //Desliga o led da placa
  digitalWrite(PINO_LED_VERMELHO, DESLIGA); //Desliga o led da placa
  digitalWrite(PINO_LED_VERDE, DESLIGA); //Desliga o led da placa
  digitalWrite(PINO_RELE, DESLIGA); //Desliga o led da placa

  Serial.begin(115200);
  #ifdef DEPURACAO
    delay(100);
    Serial.println("\nSerial iniciada");
  #endif

  SPI.begin(); // Init SPI bus
  #ifdef DEPURACAO
    delay(100);
    Serial.println("Serial Peripherical Interface(SPI) - iniciada\n");
  #endif

  rfid.PCD_Init(); // Init MFRC522 
  #ifdef DEPURACAO
    delay(100);
    Serial.println("Proximity Coupling Device(PCD) - iniciado\n");
  #endif

  for (byte i = 0; i < 6; i++) {
    key.keyByte[i] = 0xFF;
  }

  #ifdef IMPRIME_INFOS_CARTAO
    //Serial.println(F("This code scan the MIFARE Classsic NUID."));
    //Serial.print(F("Using the following key:"));
    //printHex(key.keyByte, MFRC522::MF_KEY_SIZE);
    //Serial.println("\n\n");
  #endif
}

void loop() {
  while(!digitalRead(PINO_BOTAO)){
    #ifdef DEPURACAO
      Serial.println("Botao pressionado...");
    #endif
    RotinaBotao();
  }

  //Retorna o looping caso não haja um cartão na leitora
  if (!rfid.PICC_IsNewCardPresent()){
    return;
  }

  // Verifica se o NUID foi lido
  if ( !rfid.PICC_ReadCardSerial()){
    return;
  }

  MFRC522::PICC_Type piccType = rfid.PICC_GetType(rfid.uid.sak);
  
  #ifdef DEPURACAO
    Serial.print(F("PICC type: "));
    Serial.print(rfid.PICC_GetTypeName(piccType));
    Serial.println();
  #endif


  // Caso não seja um cartão suportado 
  if ((piccType != MFRC522::PICC_TYPE_MIFARE_MINI) && 
      (piccType != MFRC522::PICC_TYPE_MIFARE_1K) && 
      (piccType != MFRC522::PICC_TYPE_MIFARE_4K)) {
    #ifdef IMPRIME_INFOS_CARTAO
      Serial.println(F("Tipo de cartão, não suportado."));
    #endif
    return;
  }


  for(int indiceCartao = 0; indiceCartao<= CartoesCadastrados; indiceCartao ++){
    if(rfid.uid.uidByte[0] == CartaoNaLeitora[indiceCartao][0] && 
      rfid.uid.uidByte[1] == CartaoNaLeitora[indiceCartao][1] && 
      rfid.uid.uidByte[2] == CartaoNaLeitora[indiceCartao][2] && 
      rfid.uid.uidByte[3] == CartaoNaLeitora[indiceCartao][3] ){
      CartaoValido();
      break;
    }else if (indiceCartao == CartoesCadastrados){
      CartaoInvalido();
      break;
    }
  }

  // Halt PICC
  rfid.PICC_HaltA();

  // Stop encryption on PCD
  rfid.PCD_StopCrypto1();
}


//----------------------------------------------------------------------------------//
/*                                 DEMAIS FUNÇÕES                                   */
//----------------------------------------------------------------------------------//

/* * Helper routine to dump a byte array as hex values to Serial. */
void printHex(byte *buffer, byte bufferSize) {
  for (byte i = 0; i < bufferSize; i++) {
    Serial.print(buffer[i] < 0x10 ? " 0" : " ");
    Serial.print(buffer[i], HEX);
  }
}

/* Helper routine to dump a byte array as dec values to Serial. */
void printDec(byte *buffer, byte bufferSize) {
  for (byte i = 0; i < bufferSize; i++) {
    Serial.print(buffer[i] < 0x10 ? " 0" : " ");
    Serial.print(buffer[i], DEC);
  }
}


void CartaoValido(void){
  #ifdef IMPRIME_INFOS_CARTAO
    Serial.println("Acesso LIBERADO!");
  #endif
  digitalWrite(PINO_LED_VERDE, LIGA); //Desliga o led da placa
  AbrePorta();
  delay(3000);
  FechaPorta();
  digitalWrite(PINO_LED_VERDE, DESLIGA); //Desliga o led da placa
}

void CartaoInvalido(void){
  #ifdef IMPRIME_INFOS_CARTAO
    Serial.println("Acesso NEGADO!");
  #endif
  FechaPorta();
  digitalWrite(PINO_LED_VERMELHO, LIGA); //Desliga o led da placa
  delay(150);
  digitalWrite(PINO_LED_VERMELHO, DESLIGA); //Desliga o led da placa
  delay(150);
  digitalWrite(PINO_LED_VERMELHO, LIGA); //Desliga o led da placa
  delay(150);
  digitalWrite(PINO_LED_VERMELHO, DESLIGA); //Desliga o led da placa
  delay(150);
  digitalWrite(PINO_LED_VERMELHO, LIGA); //Desliga o led da placa
  delay(150);
  digitalWrite(PINO_LED_VERMELHO, DESLIGA); //Desliga o led da placa
}

void AbrePorta(void){
  digitalWrite(PINO_RELE, LIGA); //Desliga o led da placa
}

void FechaPorta(void){
  digitalWrite(PINO_RELE, DESLIGA); //Desliga o led da placa
}

void CadastrandoCartao(void){
  digitalWrite(PINO_LED_AZUL, LIGA); //Desliga o led da placa
  digitalWrite(PINO_LED_VERDE, LIGA); //Desliga o led da placa
  delay(200);
  digitalWrite(PINO_LED_AZUL, DESLIGA); //Desliga o led da placa
  digitalWrite(PINO_LED_VERDE, DESLIGA); //Desliga o led da placa
  delay(200);
  digitalWrite(PINO_LED_AZUL, LIGA); //Desliga o led da placa
  digitalWrite(PINO_LED_VERDE, LIGA); //Desliga o led da placa
  delay(200);
  digitalWrite(PINO_LED_AZUL, DESLIGA); //Desliga o led da placa
  digitalWrite(PINO_LED_VERDE, DESLIGA); //Desliga o led da placa
}

void DescadastradoCartao(void){
  digitalWrite(PINO_LED_AZUL, LIGA); //Desliga o led da placa
  digitalWrite(PINO_LED_VERMELHO, LIGA); //Desliga o led da placa    
  delay(200);
  digitalWrite(PINO_LED_AZUL, DESLIGA); //Desliga o led da placa
  digitalWrite(PINO_LED_VERMELHO, DESLIGA); //Desliga o led da placa
  delay(200);
  digitalWrite(PINO_LED_AZUL, LIGA); //Desliga o led da placa
  digitalWrite(PINO_LED_VERMELHO, LIGA); //Desliga o led da placa  
  delay(200);
  digitalWrite(PINO_LED_AZUL, DESLIGA); //Desliga o led da placa
  digitalWrite(PINO_LED_VERMELHO, DESLIGA); //Desliga o led da placa  
}

void RotinaBotao(void){
  signed int posicaoPrenchida = -1;
  #ifdef DEPURACAO
    Serial.println("MODO CADASTRO");
  #endif
  
  #ifdef IMPRIME_INFOS_CARTAO
    Serial.print("Cartões cadastrados: ");
    Serial.println(CartoesCadastrados);
    delay(300);

    if(CartoesCadastrados > 0){
      for(int contadorCartao = 0; contadorCartao < CartoesCadastrados; contadorCartao++ ){
        Serial.print("Cartao: ");
        Serial.print(contadorCartao);
        Serial.print(" : ");

        for (int i = 0; i < 4; i++) {
          Serial.print(CartaoNaLeitora[contadorCartao][i] < 0x10 ? " 0" : " ");
          Serial.print(CartaoNaLeitora[contadorCartao][i] , DEC);
        }
        Serial.println();
      }
    }
    Serial.println("\n");
  #endif 

  #ifdef DEPURACAO
    if(CartoesCadastrados == MAXIMO_CARTOES){
      Serial.println("Numero Maximo de cartões cadastrados");
      return;
    }
  #endif

  //Retorna o looping caso não haja um cartão na leitora
  if (!rfid.PICC_IsNewCardPresent()){
    return;
  }

  // Verifica se o NUID foi lido
  if ( !rfid.PICC_ReadCardSerial()){
    return;
  }

  MFRC522::PICC_Type piccType = rfid.PICC_GetType(rfid.uid.sak);

  #ifdef DEPURACAO
    Serial.print(F("PICC type: "));
    Serial.print(rfid.PICC_GetTypeName(piccType));
    Serial.println();
  #endif

  // Caso não seja um cartão suportado 
  if (piccType != MFRC522::PICC_TYPE_MIFARE_MINI &&  
    piccType != MFRC522::PICC_TYPE_MIFARE_1K &&
    piccType != MFRC522::PICC_TYPE_MIFARE_4K) {

    #ifdef IMPRIME_INFOS_CARTAO
      Serial.println(F("Tipo de cartão não suportado\n\n"));
    #endif
    return;
  }

  /*Verifica se o cartão lido existe, e se existe, pega a posição que ele ocupa */
  for(int indiceCartao = 0; indiceCartao <= MAXIMO_CARTOES; indiceCartao++){
    if(rfid.uid.uidByte[0] == CartaoNaLeitora[indiceCartao][0] && 
      rfid.uid.uidByte[1] == CartaoNaLeitora[indiceCartao][1] && 
      rfid.uid.uidByte[2] == CartaoNaLeitora[indiceCartao][2] && 
      rfid.uid.uidByte[3] == CartaoNaLeitora[indiceCartao][3])
    {
      posicaoPrenchida = indiceCartao;
    }
  }

  /* Se cartão lido NÃO existe na lista */
  if(posicaoPrenchida == -1){
    for(int indiceCartao = CartoesCadastrados; indiceCartao <= MAXIMO_CARTOES; indiceCartao++){
      if(rfid.uid.uidByte[0] != CartaoNaLeitora[indiceCartao][0] && 
        rfid.uid.uidByte[1] != CartaoNaLeitora[indiceCartao][1] && 
        rfid.uid.uidByte[2] != CartaoNaLeitora[indiceCartao][2] && 
        rfid.uid.uidByte[3] != CartaoNaLeitora[indiceCartao][3] ){
      
        #ifdef IMPRIME_INFOS_CARTAO 
          Serial.println(F("Novo cartao detectado: "));
        #endif

        // Armazena o NUID do Cartao atual no arranjo
        for (byte i = 0; i < 4; i++) {
          CartaoNaLeitora[indiceCartao][i] = rfid.uid.uidByte[i];
        }
        
        #ifdef IMPRIME_INFOS_CARTAO 
          Serial.println(F("NUID do tag:"));
          Serial.print(F("Hexadecimal: "));
          printHex(rfid.uid.uidByte, rfid.uid.size);
          Serial.println();
          Serial.print(F("Decimal: "));
          printDec(rfid.uid.uidByte, rfid.uid.size);
          Serial.println();
        #endif
        
        CartoesCadastrados += 1;
        CadastrandoCartao();

        #ifdef IMPRIME_INFOS_CARTAO
          Serial.println(F("Cartão Cadastrado com sucesso!!!\n"));
        #endif
        break;
      }
    }
  }else{   /* Se cartão lido EXISTE na lista */
    for (byte i = 0; i < 4; i++) {
      CartaoNaLeitora[posicaoPrenchida][i] = 0;
    }
    CartoesCadastrados -= 1;
    DescadastradoCartao();
    #ifdef IMPRIME_INFOS_CARTAO
    Serial.println(F("Cartão Removido com sucesso!!!\n"));
    #endif
    return; 
  }

  while(!digitalRead(PINO_BOTAO)){
    NOP();
  }

  Serial.println("RETORNO AO MODO LEITURA");
  return;
}
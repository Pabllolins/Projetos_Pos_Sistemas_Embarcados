#include "MinhaLibEncoder.h"
#include <Arduino.h>

/*****************************************************************************
* Funcao		         : v_exemplo()
* Descricao	             : Função que ...
* @param                 : Nenhum
* Saida/Retorno	         : Nenhum
* Data			         : 01/10/2022
* Autor			         : Pabllo Lins
* Versao		         : 1.0
*****************************************************************************/
// MeuEncoder::v_exemplo()
// {
// }
//-------------------------------------------------------------------------------------------------------

boolean Sinal_B_SentHorar;
extern unsigned int contadorMilis;
extern signed int ContadorEncoder;

/*****************************************************************************
* Função/Function		      : IniciaEncoder()
* Descrição/Description	  : Função que inicializa os pinos do encoder
* @parametro/@param       : 3: inteiro para pino Data, inteiro para pino pino Clk, 
                            inteiro para pino Pino Sw
* Retorno/ @Return	      : v = vazio (void)
* Data/Date			          : 01/10/2022
* Autor/Author		        : Pabllo Lins
* Versao/Version		      : 1.0
*****************************************************************************/
void v_IniciaEncoder(int PinClk, int PinData, int PinSw)
{
  pinMode(PinClk, INPUT);
  pinMode(PinData, INPUT);
  pinMode(PinSw, INPUT_PULLUP);
}



/*****************************************************************************
* Função/Function		      : v_LeEncoder()
* Descrição/Description	  : Função que ..
* @parametro/@param       : 3: pino Data, pino Clk, Pino Sw
* Retorno/ @Return	      : inteiro
* Data/Date			          : 01/10/2022
* Autor/Author		        : Pabllo Lins
* Versao/Version		      : 1.0
*****************************************************************************/
void LeEncoder(int PinClk, int PinData, int *VarParaA, int *UltimoValorA)
{
  *VarParaA = digitalRead(PinClk);
  
  if(*VarParaA != *UltimoValorA)
  {
    if(digitalRead(PinData) != *VarParaA)
    {
      contadorMilis = 0;
      ContadorEncoder++;
      Sinal_B_SentHorar = true;
    }
    else
    {
      contadorMilis = 0;
      ContadorEncoder--;
      Sinal_B_SentHorar = false;
    }

    #ifdef depuracao
      Serial.print("Rotação: ");
      if(Sinal_B_SentHorar)
      {
        Serial.println("horária");
      }
      else
      {
        Serial.println("anti-horária");
      }
      Serial.print("Posição do encoder: ");
      Serial.println(ContadorEncoder);
    #endif
  }

  *UltimoValorA = *VarParaA;
}

void IncrementaContador(void)
{
  delay(1);
  contadorMilis++;
}
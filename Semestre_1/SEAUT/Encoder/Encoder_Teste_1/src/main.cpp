#include <Arduino.h>


const int PinClk = 32;
const int PinData = 33;
int encoderPostCount = 0;
int pinALast; 
int aVal; 
boolean bCW;


void setup() {
  pinMode(PinClk, INPUT);
  pinMode(PinData, INPUT);

  pinALast = digitalRead(PinClk);
  Serial.begin(115200);
}

void loop() {
  aVal =  digitalRead(PinClk);
  
  if(aVal != pinALast)
  {
    if(digitalRead(PinData) != aVal)
    {
      encoderPostCount++;
      bCW = true;
    }
    else
    {
      encoderPostCount--;
      bCW = false;
    }

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
  }
  pinALast = aVal;
}
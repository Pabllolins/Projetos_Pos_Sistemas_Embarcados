//Autor: Leandro Poloni Dantas
//Data: Ago/2022
//Sobre:
//O código abaixo é uma adaptação dos códigos disponíveis na internet.
//Neste código tanto o tamanho da tela como as distância máxima são facilmente ajustáveis.
//Fontes:
//https://www.filipeflop.com/blog/radar-ultrassonico-com-arduino-e-processing/
//https://github.com/lastralab/ArduinoRadar
//https://cafeinacodificada.com.br/como-integrar-aplicacoes-feitas-com-o-arduino-ao-processing/

import processing.serial.*;
import java.awt.event.KeyEvent;
import java.io.IOException;
 
//String Port = "/dev/tty.usbmodem1411"; //Arduino port
Serial myPort; 

String angle="";
String distance="";
String data="";
String noObject;

float pixsDistance;

int iAngle, iDistance;
int index1=0;
int index2=0;

PFont orcFont;

//Definir a distância máxima aqui
int dist_maxima = 400;
//Valores padrões
int largura = 0;
int altura = 0;
float x0 = 0;
float y0 = 0;
float diametro1 = 0;
float diametro2 = 0;
float diametro3 = 0;
float diametro4 = 0;
float linha_verde_raio = 0;

void setup() {
  size (1200, 650); //Resolução do canvas (width, height), precisa ser um número fixo
  smooth();
  
  //Ajuste de parâmetros
  largura = width;
  altura = height;
  x0 = largura/2;
  y0 = altura*0.92;
  diametro1 = largura*0.2;
  diametro2 = diametro1*2;
  diametro3 = diametro1*3;
  diametro4 = diametro1*4;
  linha_verde_raio = diametro4*0.88;
  
  //myPort = new Serial(this, Port, 9600); 
  myPort = new Serial(this, "/dev/ttyUSB0", 115200);
  myPort.bufferUntil('.'); 
  //orcFont = loadFont("OCRAExtended-30.vlw");  //Habilitar está linha se o aruivo OCRAExtended-30.vlw estiver na pasta do projeto
}

void draw() 
{
  fill(98,245,31);
  //textFont(orcFont);  //Habilitar está linha se o aruivo OCRAExtended-30.vlw estiver na pasta do projeto
  noStroke();
  fill(0,4); 
  rect(0, 0, width, height-height*0.065); 
  
  fill(98,245,31);  
  drawRadar(); 
  drawLine();
  drawObject();
  drawText();
}

void serialEvent (Serial myPort) 
{ 
  //Formato padrão da string: "angulo em graus","distância em cm".
  //Exemplo de string: 45,200.
  data = myPort.readStringUntil('.');
  data = data.substring(0,data.length()-1);
  
  index1 = data.indexOf(","); 
  angle= data.substring(0, index1); 
  distance= data.substring(index1+1, data.length()); 
  
  iAngle = int(angle);
  iDistance = int(distance);
}

void drawRadar() 
{
  pushMatrix();     //Push o ajuste de refência de coordenadas atual na pinha
  translate(x0,y0); //Ajusta a referência de coordenadas (ponto (0,0))
  noFill();
  strokeWeight(2);
  stroke(98,245,31);
  
  arc(0,0,diametro4,diametro4,PI,TWO_PI);  //Arco + externo
  arc(0,0,diametro3,diametro3,PI,TWO_PI);  //Arco intermediário 1
  arc(0,0,diametro2,diametro2,PI,TWO_PI);  //Arco intermediário 2
  arc(0,0,diametro1,diametro1,PI,TWO_PI);  //Arco + interno
  
  line(-largura/2,0,largura/2,0);
  line(0,0,(-diametro4/2*1.05)*cos(radians(30)),(-diametro4/2*1.05)*sin(radians(30)));
  line(0,0,(-diametro4/2*1.05)*cos(radians(60)),(-diametro4/2*1.05)*sin(radians(60)));
  line(0,0,(-diametro4/2*1.05)*cos(radians(90)),(-diametro4/2*1.05)*sin(radians(90)));
  line(0,0,(-diametro4/2*1.05)*cos(radians(120)),(-diametro4/2*1.05)*sin(radians(120)));
  line(0,0,(-diametro4/2*1.05)*cos(radians(150)),(-diametro4/2*1.05)*sin(radians(150)));
  line((-width/2)*cos(radians(30)),0,width/2,0);
  
  popMatrix();  //Pop o ajuste de refência de coordenadas atual na pinha
}

void drawObject() 
{
  pushMatrix();
  translate(x0,y0); //Ajusta a referência do ponto (0,0)
  strokeWeight(9);
  stroke(255,10,10);  //Linha vermelha

  pixsDistance = iDistance*(diametro4/2)/dist_maxima;  //Calcula a distância em pixels (regra de três)
  
  if(iDistance<dist_maxima){ //range limit
    //Desenha a linha do fim para o começo (o ponto de começo representa o fim da linha que representa a distância)   
    line(pixsDistance*cos(radians(iAngle)),-pixsDistance*sin(radians(iAngle)),(diametro4/2*1.05)*cos(radians(iAngle)),-(diametro4/2*1.05)*sin(radians(iAngle)));
  }
  popMatrix();
}

void drawLine()
{
  pushMatrix();
  strokeWeight(9);
  stroke(30,250,60); //Linha verde
  translate(x0,y0);  //Ajusta a referência do ponto (0,0)
  line(0,0,(diametro4/2*0.98)*cos(radians(iAngle)),-(diametro4/2*0.98)*sin(radians(iAngle))); //Linha do centro até próximo do fundo de escala
  popMatrix();
}

void drawText() 
{
  int font = 30;  
  pushMatrix();
  fill(0,0,0);
  noStroke();
  rect(0, y0+2, largura, altura);
  fill(98,245,31);
  
  font = 15;
  textSize(font);
  
  text(dist_maxima/4*1 + " cm",x0+diametro1/2+5,y0-5  );
  text(dist_maxima/4*2 + " cm",x0+diametro2/2+5,y0-5);
  text(dist_maxima/4*3 + " cm",x0+diametro3/2+5,y0-5);
  text(dist_maxima/4*4 + " cm",x0+diametro4/2+5,y0-5);
  
  font = 30;
  textSize(font);
  text("Ângulo: " + iAngle +" °", x0+20, y0+font+5);
  text("Distância: ", x0+x0/2, y0+35);
  if(iDistance<dist_maxima) 
  {
    text("Distância: " + iDistance +" cm", x0+x0/2, y0+font+5);
  }
  
  font = 25;
  textSize(font);
  
  fill(98,245,60);
  
  translate( x0 + (diametro4/2+font*1.5)*cos(radians(30+2)), y0 - (diametro4/2+font*1.5)*sin(radians(30+2)) );
  rotate(-radians(-60));
  text("30°",0,0);
  resetMatrix();
  translate( x0 + (diametro4/2+font*1.5)*cos(radians(60+2)), y0 - (diametro4/2+font*1.5)*sin(radians(60+2)) );
  rotate(-radians(-30));
  text("60°",0,0);
  resetMatrix();
  translate( x0 + (diametro4/2+font*1.5)*cos(radians(90+2)), y0 - (diametro4/2+font*1.5)*sin(radians(90+2)) );
  rotate(radians(0));
  text("90°",0,0);
  resetMatrix();
  translate( x0 + (diametro4/2+font*1.5)*cos(radians(120+2)), y0 - (diametro4/2+font*1.5)*sin(radians(120+2)) );
  rotate(radians(-30));
  text("120°",0,0);
  resetMatrix();
  translate( x0 + (diametro4/2+font*1.5)*cos(radians(150+2)), y0 - (diametro4/2+font*1.5)*sin(radians(150+2)) );
  rotate(radians(-60));
  text("150°",0,0);
  popMatrix(); 
}

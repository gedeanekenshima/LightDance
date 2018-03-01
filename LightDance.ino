/*
 * Roupa com acelerômetro
 * Escrito por: Gedeane Kenshima
 * Data: 28/2/2018
*/

// Bibliotecas FastLED e Wire (para dispositivo i2c)
#include "FastLED.h"
#include<Wire.h>

// Quantidade de leds na fita
#define NUM_LEDS 400

// Número do pino de Data IN no Arduino
//#define DATA_PIN 6

// Array chamado leds
CRGB leds[NUM_LEDS];

//Endereco I2C do MPU6050
// Verifique endereço correto com sketch Scanner_I2C
const int MPU = 0x68;

//Variaveis para armazenar valores dos eixos X, Y, Z (acelerômetro) e temperatura
int AcX, AcY, AcZ;

void setup(){
  // Tipo de led, configuração de pinos e sequencia de cores
  FastLED.addLeds<WS2812B, 6, GRB>(leds, NUM_LEDS);

  //Início da comunicação serial para mostrar dados lidos
  Serial.begin(9600);

  // Início Wire
  Wire.begin();

  // Início da transmissão de dados I2C
  Wire.beginTransmission(MPU);
  
  // Aponta para endereço hexa de configuração do acelerômetro
  // Se o código não funcionar, tente comentar as duas linhas abaixo (Wire.write)
  //Wire.write(0x1C);
  // Escreve a configuração de testes dos eixos e range de leitura
  //Wire.write(0b11111000); 
  // Aponta para endereço hexa
  Wire.write(0x6B);
  //Valor padrão de inicialização (todos os bits do endereço 0x6B zerados)
  Wire.write(0);
  // Fim da transmissão
  Wire.endTransmission(true);
}

void loop() {
  Wire.beginTransmission(MPU);
  //inicia a leitura da saida do eixo X  do acelerometro (parte mais significativa (HIGH))
  Wire.write(0x3B);  
  
  Wire.endTransmission(false);
  //Solicita os dados do sensor
  Wire.requestFrom(MPU, 14, true);
  // Leitura dos bits mais significativos deslocados pra esquerda e filtro pra ignorar valores da direita
  // Armazenamento nas variáveis para leitura posterior
  AcX = Wire.read() << 8 | Wire.read() & 0xFF00; //0x3B (ACCEL_XOUT_H) & 0x3C (ACCEL_XOUT_L)
  AcY = Wire.read() << 8 | Wire.read() & 0xFF00; //0x3D (ACCEL_YOUT_H) & 0x3E (ACCEL_YOUT_L)
  AcZ = Wire.read() << 8 | Wire.read() & 0xFF00; //0x3F (ACCEL_ZOUT_H) & 0x40 (ACCEL_ZOUT_L)
  
  /*Tabela de valores dos Eixos AcX, AcY e AcZ
  //Acx 0g = 1024 a 1280 plano || 1g = 2816 a 3072 p/cima || -1g = -1280 p/baixo
  //Acy 0g = 1024 a 1280 plano || 1g = 2560 a 3072 p/cima || -1g = -512 p/baixo
  //Acz 0g = 1024 a 1280 plano || 1g = 2560 a 3072 p/cima || -1g = -1280 p/baixo */

  //Envia valor X do acelerometro para a serial
  Serial.print("AcX = "); Serial.print(AcX);
  if (AcX >= 1400) { 
    Serial.println(" X para cima");
  }
  else if (AcX <= -1) {
    Serial.println(" X para baixo");
  }
  else if (AcX > 0 && AcX < 1300) {
    Serial.println(" X nivelado");
  }
  else{
    Serial.println(" X inclinado");
  }


  //Envia valor Y do acelerometro para a serial
  Serial.print("AcY = "); Serial.print(AcY);
  if (AcY >= 1400) {
    Serial.println(" Y para cima");
  }
  else if (AcY <= -1) {
    Serial.println(" Y para baixo");
  }
  else if (AcY > 0 && AcY < 1300) {
    Serial.println(" Y nivelado");
  }
  else{
    Serial.println(" Y inclinado");
  }

  //Envia valor Z do acelerometro para a serial
  Serial.print("AcZ = "); Serial.print(AcZ);
  if (AcZ >= 1400) {
    Serial.println(" Z para cima");
  }
  else if (AcZ <= -1) {
    Serial.println(" Z para baixo");
  }
  else if (AcZ > 0 && AcZ < 1300) {
    Serial.println(" Z nivelado");
  }
  else{
    Serial.println(" Z inclinado");
  }
  if(AcX >0 && AcX <=1300 && AcY >0 && AcY <=1300 && AcZ >=1400){
    for(int i = 0; i<= NUM_LEDS; i++){
    leds[i] = CRGB::Green;
    FastLED.show();
    delay(50);
    }
  }
  else if(AcX <=-1 && AcY >0 && AcY <=1300 && AcZ >0 && AcZ <=1300){
    for(int i = 0; i<= NUM_LEDS; i++){
    leds[i] = CRGB::Blue;
    FastLED.show();
    delay(50);
    }
  }
  else if( AcX >0 && AcX <=1300 && AcY <=-1 && AcZ >0 && AcZ <=1300){
    for(int i = 0; i<= NUM_LEDS; i++){
    leds[i] = CRGB::Red;
    FastLED.show();
    delay(50);
   }
  }
  else if(AcX >0 && AcX <=1300 && AcY >=1400 && AcZ >0 && AcZ <=1300){
    for(int i = 0; i<= NUM_LEDS; i++){
    leds[i] = CRGB::Yellow;
    FastLED.show();
    delay(50);
   }
  }
  else if(AcX >0 && AcX <=1300 && AcY >=1400 && AcZ >0 && AcZ <=-1){
    for(int i = 0; i<= NUM_LEDS; i++){
    leds[i] = CRGB::Orange;
    FastLED.show();
    delay(50);
   }
  }
  else if(AcX >0 && AcX <=1300 && AcY <=-1 && AcZ <=-1){
    for(int i = 0; i<= NUM_LEDS; i++){
    leds[i] = CRGB::White;
    FastLED.show();
    delay(50);
   }
  }
   else if(AcX >=1400 && AcY <=-1 && AcZ <=-1){
    for(int i = 0; i<= NUM_LEDS; i++){
    leds[i] = CRGB::Purple;
    FastLED.show();
    delay(50);
   }
  }
  else{
    for(int i = 0; i<= NUM_LEDS; i++){
    leds[i] = CRGB::Cyan;
   FastLED.show();
    delay(50);
   }
  
  }

  //Aguarda 300 ms e reinicia o processo
  delay(500);
}

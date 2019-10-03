
// Carrega bibliotecas graficas e sensores
#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>
#include <DHT.h>
#include <Adafruit_BMP085.h>
#include <Wire.h>
#include <SPI.h>

const int pinoLed = 5; //Pino digital LED
const int pinoSensor = 4; //Pino digital SENSOR

// Inicializa o display
Adafruit_PCD8544 display = Adafruit_PCD8544(8, 9, 10, 11, 12);

 
// Define pino e tipo do sensor DHT
DHT dht(3, DHT11);
 
Adafruit_BMP085 bmp180;
 
void setup()
{
  pinMode(pinoSensor, INPUT); //Define o pino como entrada
  pinMode(pinoLed, OUTPUT); //Define o pino como saida
  digitalWrite(pinoLed, LOW); //LED inicia desligado
  
  Serial.begin(9600);
  // Informacoes iniciais no display
  display.begin();
  // Ajusta o contraste do display
  display.setContrast(48);
  // Apaga o buffer e o display
  display.clearDisplay();
  // Define tamanho do texto e cor
  display.setTextSize(1);
  display.setTextColor(BLACK);
  
  // Retangulo temperatura
  display.drawRoundRect(0,0, 44,24, 3, 2);
  // Texto inicial temperatura
  display.setCursor(11,3);  // Seta a posição do cursor
  display.println("TEMP");  
  display.setCursor(5,14);
  display.println("----"); 
  display.setCursor(29,14);
  display.drawCircle(31, 15, 1,1);
  display.println(" C");
   
  // Retangulo umidade
  display.drawRoundRect(45,0, 39 ,24, 3, 2);
  // Texto inicial Umidade
  display.setCursor(52,3);  
  display.println("UMID");
  display.setCursor(50,14); 
  display.println("----"); 
  display.setCursor(75,14);
  display.println("%"); 
   
  // Retangulo pressao
  display.drawRoundRect(0,25, 84 ,23, 3, 2);
  // Texto inicial Pressao
  display.setCursor(22,28); 
  display.println("PRESSAO");
  display.setCursor(55,38);
  display.println("hPa");
  display.setCursor(11,38);
  display.println("------"); 
  display.display();
   
  delay(1000);
  // Inicializa o sensor BMP180
  if (!bmp180.begin()) 
  {
    Serial.println("Sensor BMP180 nao encontrado !!");
    while (1) {}
  }
  // Inicializa o DHT22
  dht.begin();
}
 
void loop()
{

  if (digitalRead(pinoSensor) == LOW){ //Se a leitura do pino for igual a LOW, faz
      digitalWrite(pinoLed, HIGH); //Acende o LED
  }else { //Senao, faz
    digitalWrite(pinoLed, LOW); //Apaga o LED
  }
  

  // Leitura temperatura, umidade e pressao
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  float p = bmp180.readPressure()/100.0;
   
  // Atualiza valor da temperatura
  display.fillRect(4,13, 25 , 10, 0);
  display.setCursor(4,14);
  display.println(t,1); 
   
  // Atualiza valor da umidade
  display.fillRect(50,13, 23 , 10, 0);
  display.setCursor(50,14);
  display.println(h,1); 
   
  // Atualiza valor da pressao
  display.fillRect(4, 37, 46 , 10, 0);
  display.setCursor(11,38);
  display.println(p,2); 
    
  display.display();
  // Aguarda 5 segundos para efetuar nova leitura
  delay(5000);
}

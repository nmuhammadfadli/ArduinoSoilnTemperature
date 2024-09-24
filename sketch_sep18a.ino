#include "DHTesp.h"              
#include <Wire.h>                
#include <hd44780.h>              
#include <hd44780ioClass/hd44780_I2Cexp.h>  

DHTesp dht;                       
#define DHTPIN D0                
const int soilSensorPin = A0;     

hd44780_I2Cexp lcd;            

void setup() {
  Serial.begin(115200);           
  Serial.println(F("DHT22 and Soil Moisture Sensor Example"));

  dht.setup(DHTPIN, DHTesp::DHT22);


  int status = lcd.begin(16, 2);   
  if(status) {  
    Serial.print(F("LCD initialization failed with status: "));
    Serial.println(status);
    while(1); 
  }

  lcd.print("Initializing...");    
  delay(2000);                     
}

void loop() {
  
  float soilMoisturePercentage = 100.00 - ((analogRead(soilSensorPin) / 1023.00) * 100.00);

  TempAndHumidity data = dht.getTempAndHumidity();

  Serial.print(F("Soil Moisture (in Percentage): "));
  Serial.print(soilMoisturePercentage);
  Serial.println(F("%"));

  lcd.clear();                    
  lcd.setCursor(0, 0);            
  lcd.print("Hum Soil: ");            
  lcd.print(soilMoisturePercentage); 
  lcd.print("%");

  delay(2000);                   

  Serial.print(F("Humidity: "));
  Serial.print(data.humidity);
  Serial.print(F("%  Temperature: "));
  Serial.print(data.temperature);
  Serial.print(F("°C "));

  lcd.clear();                     
  lcd.setCursor(0, 0);            
  lcd.print("Temp: ");            
  lcd.print(data.temperature);    
  lcd.print("C");

  lcd.setCursor(0, 1);            
  lcd.print("Hum: ");             
  lcd.print(data.humidity);        
  lcd.print("%");

  delay(2000);                    
}

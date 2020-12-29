#include <DallasTemperature.h>
#include <OneWire.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>


int temperatue_sensor_1_pin=2;
int temperatue_sensor_2_pin=3;
int temperatue_sensor_3_pin=4;
int temperatue_sensor_4_pin=5;

float temperature_1_value=0;
float temperature_2_value=0;
float temperature_3_value=0;
float temperature_4_value=0;

OneWire oneWirePin_1(temperatue_sensor_1_pin);
OneWire oneWirePin_2(temperatue_sensor_2_pin);
OneWire oneWirePin_3(temperatue_sensor_3_pin);
OneWire oneWirePin_4(temperatue_sensor_4_pin);



DallasTemperature sensor_1(&oneWirePin_1); 
DallasTemperature sensor_2(&oneWirePin_2); 
DallasTemperature sensor_3(&oneWirePin_3); 
DallasTemperature sensor_4(&oneWirePin_4); 



LiquidCrystal_I2C lcd(0x27,16,2);
void setup() {

  Serial.begin(9600);

  sensor_1.begin();
  sensor_2.begin();
  sensor_3.begin();
  sensor_4.begin();
  
  lcd.begin();
  lcd.backlight(); 

}

void loop() {

  Serial.print("\n Requesting Temperatures from sensors-----------  ");

  sensor_1.requestTemperatures();
  sensor_2.requestTemperatures();
  sensor_3.requestTemperatures();
  sensor_4.requestTemperatures();
  
  Serial.print("Done  \n "); 

  temperature_1_value=sensor_1.getTempCByIndex(0);
  temperature_2_value=sensor_2.getTempCByIndex(0);
  temperature_3_value=sensor_3.getTempCByIndex(0);
  temperature_4_value=sensor_4.getTempCByIndex(0);

//  Serial.print("Temperature is ----   ");
//  Serial.print(temperature);
  
  lcd.setCursor(0,0);
  lcd.print(temperature_1_value);
  
  lcd.setCursor(8,0);
  lcd.print(temperature_2_value);
  
  lcd.setCursor(0,1);
  lcd.print(temperature3_value);

  
  lcd.setCursor(8,1);
  lcd.print(temperature_4_value);
  
  
delay(200);

}

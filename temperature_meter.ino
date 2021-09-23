#include <DallasTemperature.h>
#include <OneWire.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>


int temperatue_sensor_1_pin=2;
// int temperatue_sensor_2_pin=3;
// int temperatue_sensor_3_pin=4;
// int temperatue_sensor_4_pin=5;

float temperature_1_value=0;
// float temperature_2_value=0;
// float temperature_3_value=0;
// float temperature_4_value=0;

long int start_millisecond;
long int current_millisecond;

int hours;
int minutes;
int seconds;

byte degreeC[]={
  B11100,
  B10100,
  B11100,
  B00111,
  B01000,
  B01000,
  B01000,
  B00111
  };

//   byte water[] = {
//   B00100,
//   B01010,
//   B01010,
//   B10001,
//   B10001,
//   B10001,
//   B01110,
//   B00000
// };



//byte coil[] = {
//  B00011,
//  B01100,
//  B10000,
//  B01110,
//  B00001,
//  B11110,
//  B10000,
//  B01110
//};
byte tank1[] = {
  B00010,
  B01010,
  B01001,
  B00110,
  B01000,
  B10001,
  B10001,
  B01110 
};
// byte tank2[] = {
//   B00001,
//   B11101,
//   B00101,
//   B11101,
//   B10001,
//   B11101,
//   B00001,
//   B11111
// };

OneWire oneWirePin_1(temperatue_sensor_1_pin);
// OneWire oneWirePin_2(temperatue_sensor_2_pin);
// OneWire oneWirePin_3(temperatue_sensor_3_pin);
//OneWire oneWirePin_4(temperatue_sensor_4_pin);



DallasTemperature sensor_1(&oneWirePin_1); 
// DallasTemperature sensor_2(&oneWirePin_2); 
// DallasTemperature sensor_3(&oneWirePin_3); 
//DallasTemperature sensor_4(&oneWirePin_4); 



LiquidCrystal_I2C lcd(0x27,16,2);

void setup() {

  Serial.begin(9600);

  start_millisecond=millis();

  sensor_1.begin();
  // sensor_2.begin();
  // sensor_3.begin();
//  sensor_4.begin();
  
  lcd.begin();
   lcd.createChar(0,degreeC);
  lcd.createChar(1,tank1);
  // lcd.createChar(2,tank2);
  // lcd.createChar(3,water);
//  lcd.createChar(4,coil);
  
  lcd.home();
//  lcd.backlight(); 

}

void loop() {

  Serial.print("\n Requesting Temperatures from sensors-----------  ");

  sensor_1.requestTemperatures();
  // sensor_2.requestTemperatures();
  // sensor_3.requestTemperatures();
//  sensor_4.requestTemperatures();
  
  Serial.print("Done  \n "); 

  temperature_1_value=sensor_1.getTempCByIndex(0);
  // temperature_2_value=sensor_2.getTempCByIndex(0);
  // temperature_3_value=sensor_3.getTempCByIndex(0);
//  temperature_4_value=sensor_4.getTempCByIndex(0);


  lcd.clear();
  
  // printing degree C symbol
  lcd.setCursor(6,0);
  lcd.write(0);
  // lcd.setCursor(15,0);
  // lcd.write(0);
  // lcd.setCursor(6,1);
  // lcd.write(0);
 lcd.setCursor(15,1);
 lcd.write(0);

  // printing tank1 symbol

  lcd.setCursor(0,0);
  lcd.write(1);

  // printing tank2 symbol

  // lcd.setCursor(0,1);
  // lcd.write(2);

  // printing water symbol

  // lcd.setCursor(8,0);
  // lcd.write(3);

  // printing coil symbol

  // lcd.setCursor(8,1);
  // lcd.write(4);
  


  

  lcd.setCursor(1,0);
  lcd.print(temperature_1_value);
  lcd.setCursor(9,0);
  // lcd.print(temperature_2_value);
  // lcd.setCursor(1,1);
  // lcd.print(temperature_3_value);
  // lcd.setCursor(9,1);
  // lcd.print(temperature_4_value);

// alarm-------------------- strat

lcd.setCursor(0,1);
lcd.print("Alarm:");
//alarm-----------------------end

  int millis_diff=current_millisecond-start_millisecond;
  hours=millis_diff/3600000;
  minutes=(millis_diff%3600000)/60000;
  seconds=((millis_diff%3600000)%60000)/1000;
  lcd.setCursor(13,0);
  lcd.print(":");
  lcd.setCursor(10,0);
  lcd.print(":");
  lcd.setCursor(14,0);
  lcd.print(seconds);
   lcd.setCursor(11,0);
  lcd.print(minutes);
  if(hours>=10)
   lcd.setCursor(8,0);
   else
  lcd.setCursor(9,0);
  lcd.print(hours);

 delay(800);
  

//  Serial.print("Temperature is ----   ");
//  Serial.print(temperature);
  
//  lcd.setCursor(0,0);
//  lcd.print(temperature_1_value);
//  
//  lcd.setCursor(8,0);
//  lcd.print(temperature_2_value);
//  
//  lcd.setCursor(0,1);
//  lcd.print(temperature3_value);
//
//  
//  lcd.setCursor(8,1);
//  lcd.print(temperature_4_value);
  
  
delay(200);

}

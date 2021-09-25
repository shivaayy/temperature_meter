#include <DallasTemperature.h>
#include <OneWire.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

int temperatue_sensor_1_pin = 2;

float temperature_1_value = 0;

unsigned long int start_millisecond;
unsigned long int current_millisecond;

unsigned long int hours;
unsigned long int minutes;
unsigned long int seconds;
int buzzer = 4;
int potentioMeterReading = 0;
float alarm_temp = 0.0;
byte degreeC[] = {
    B11100,
    B10100,
    B11100,
    B00111,
    B01000,
    B01000,
    B01000,
    B00111};

byte tank1[] = {
    B00010,
    B01010,
    B01001,
    B00100,
    B00100,
    B10001,
    B10001,
    B01110};

OneWire oneWirePin_1(temperatue_sensor_1_pin);

DallasTemperature sensor_1(&oneWirePin_1);

LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup()
{

  Serial.begin(9600);

  start_millisecond = millis();
  pinMode(buzzer, OUTPUT);
  digitalWrite(buzzer, LOW);
  delay(200);
  sensor_1.begin();
  ;

  lcd.begin();
  lcd.createChar(0, degreeC);
  lcd.createChar(1, tank1);

  lcd.home();
  //  lcd.backlight();
}

void loop()
{

  // Serial.print("\n Requesting Temperatures from sensors-----------  ");

  sensor_1.requestTemperatures();

  // Serial.print("Done  \n ");

  temperature_1_value = sensor_1.getTempCByIndex(0);

  lcd.clear();

  // printing degree C symbol
  lcd.setCursor(7, 0);
  lcd.write(0);

  lcd.setCursor(14, 1);
  lcd.write(0);

  // printing tank1 symbol

  lcd.setCursor(0, 0);
  lcd.write(1);

  lcd.setCursor(1, 0);
  lcd.print(temperature_1_value);
  lcd.setCursor(9, 0);

  // alarm-------------------- strat

  lcd.setCursor(0, 1);
  lcd.print("Alarm:");
  potentioMeterReading = analogRead(A3);
  alarm_temp = map(potentioMeterReading, 0, 1024, -10, 311);
  // Serial.print("alarm temperature ----------------");
  // Serial.print(potentioMeterReading);
  lcd.setCursor(7, 1);
  lcd.print(alarm_temp);
  if (temperature_1_value >= alarm_temp && alarm_temp >= -6)
  {
    digitalWrite(buzzer, HIGH);
    // delay(200);
  }
  else
  {
    digitalWrite(buzzer, LOW);
    // delay(200);
  }
  if (alarm_temp < -6)
  {
    digitalWrite(buzzer, LOW);
    // delay(200);
  }
  //alarm-----------------------end
  current_millisecond = millis();
  unsigned long int millis_diff = current_millisecond - start_millisecond;
  hours = millis_diff / 3600000UL;
  minutes = (millis_diff % 3600000UL) / 60000UL;
  seconds = ((millis_diff % 3600000UL) % 60000UL) / 1000UL;
  lcd.setCursor(13, 0);
  lcd.print(":");
  lcd.setCursor(10, 0);
  lcd.print(":");
  if (seconds >= 10)
    lcd.setCursor(14, 0);
  else
  {
    lcd.setCursor(14, 0);
    lcd.print(0);
    lcd.setCursor(15, 0);
  }
  lcd.print(seconds);
  if (minutes >= 10)
    lcd.setCursor(11, 0);
  else
  {
    lcd.setCursor(11, 0);
    lcd.print(0);
    lcd.setCursor(12, 0);
  }
  lcd.print(minutes);
  if (hours >= 10)
    lcd.setCursor(8, 0);
  else
    lcd.setCursor(9, 0);

  lcd.print(hours);

  delay(1000);
}

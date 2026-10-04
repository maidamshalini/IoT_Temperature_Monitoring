#include <LiquidCrystal.h>

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

const int temperaturePin = A0;
const int ledPin = 8;
const int buzzerPin = 9;

const float threshold = 35.0;

void setup() {
  lcd.begin(16, 2);

  pinMode(ledPin, OUTPUT);
  pinMode(buzzerPin, OUTPUT);

  Serial.begin(9600);

  lcd.setCursor(0, 0);
  lcd.print("IoT Temperature");
  lcd.setCursor(0, 1);
  lcd.print("Monitoring");

  delay(2000);

  lcd.clear();
}

void loop() {

  int sensorValue = analogRead(temperaturePin);

  float voltage = sensorValue * (5.0 / 1023.0);

  float temperature = (voltage - 0.5) * 100.0;

  lcd.clear();

  lcd.setCursor(0, 0);
  lcd.print("Temp: ");
  lcd.print(temperature, 1);
  lcd.print(" C");

  if (temperature > threshold) {

    digitalWrite(ledPin, HIGH);
    digitalWrite(buzzerPin, HIGH);

    lcd.setCursor(0, 1);
    lcd.print("ALERT: HIGH!");

    Serial.print("Temperature: ");
    Serial.print(temperature, 1);
    Serial.println(" C - ALERT");

  } else {

    digitalWrite(ledPin, LOW);
    digitalWrite(buzzerPin, LOW);

    lcd.setCursor(0, 1);
    lcd.print("Status: NORMAL");

    Serial.print("Temperature: ");
    Serial.print(temperature, 1);
    Serial.println(" C - NORMAL");
  }

  delay(1000);
}
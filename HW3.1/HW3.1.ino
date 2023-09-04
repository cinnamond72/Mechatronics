#include <M5Stack.h>

int analogPin = 34;
int digitalPin = 15;

int lightAnalog;
int lightDigital;

void setup() {
  M5.begin();
  // M5.Power.begin();

  pinMode(analogPin, INPUT);
  pinMode(digitalPin, INPUT);

  M5.Lcd.setTextFont(4);
  M5.Lcd.print("Hello World");
  delay(50);
}

void loop() {
  M5.Lcd.setCursor(0,0);

  lightAnalog = analogRead(analogPin);
  M5.Lcd.print("lightAnalog : ");
  M5.Lcd.println(lightAnalog);

  M5.Lcd.setCursor(0,50);

  lightDigital = digitalRead(digitalPin);
  M5.Lcd.print("lightDigital : ");
  M5.Lcd.println(lightDigital);

  delay(100);
}

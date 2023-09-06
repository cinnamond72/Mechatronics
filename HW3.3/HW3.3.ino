#include <M5Stack.h>
#include <FastLED.h>

#define DATA_PIN 15
#define LED_TYPE WS2811
#define COLOR_ORDER GRB
#define NUM_LEDS 64
#define BRIGHTNESS 5

int BLACK_COLOR[3] = {0,0,0};
int COLOR[3];
// const int RED_COLOR[3] = {255,0,0};
// const int GREEN_COLOR[3] = {0,255,0};
// const int BLUE_COLOR[3] = {0,0,255};
// const int YELLOW_COLOR[3] = {255,255,0};
int redValue; 
int greenValue; 
int blueValue; 

const int analogPin = 34;

int lightAnalog;
int lightDigital;
int numLight;
CRGB leds[NUM_LEDS];

void setup() {
  M5.begin();

  FastLED.addLeds<LED_TYPE,DATA_PIN,COLOR_ORDER>(leds,NUM_LEDS).setCorrection(TypicalLEDStrip);
  FastLED.setBrightness(BRIGHTNESS);

  pinMode(analogPin, INPUT);
  M5.Lcd.setTextFont(4);
}

void loop() {
  M5.Lcd.setCursor(0,0);

  lightAnalog = analogRead(analogPin);
  M5.Lcd.print("lightAnalog : ");
  M5.Lcd.print(lightAnalog);
  M5.Lcd.print("    ");

  COLOR[0] = random(0,255);
  COLOR[1] = random(0,255);
  COLOR[2] = random(0,255);

  numLight = map(lightAnalog,0,4095,64,0);
  setLED(0,numLight,COLOR);
  setLED(numLight,64-numLight,BLACK_COLOR);

  FastLED.show();
  delay(100);
}

void setLED(int start, int number, int RGBcolor[]) {
  for (int i = start; i < start + number; i++)
  {
    leds[i] = CRGB(RGBcolor[0],RGBcolor[1],RGBcolor[2]);
  }
}
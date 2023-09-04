#include <M5Stack.h>
#include <FastLED.h>

#define DATA_PIN 15
#define LED_TYPE WS2811
#define COLOR_ORDER GRB
#define NUM_LEDS 64
#define BRIGHTNESS 5

const int BLACK_COLOR[3] = {0,0,0};
const int RED_COLOR[3] = {255,0,0};
const int GREEN_COLOR[3] = {0,255,0};
const int BLUE_COLOR[3] = {0,0,255};
const int YELLOW_COLOR[3] = {255,255,0};

CRGB leds[NUM_LEDS];

void setup() {
  M5.begin();

  FastLED.addLeds<LED_TYPE,DATA_PIN,COLOR_ORDER>(leds,NUM_LEDS).setCorrection(TypicalLEDStrip);
  FastLED.setBrightness(BRIGHTNESS);

  M5.Speaker.tone(700);
  delay(200);
  M5.Speaker.end();
}

void loop() {

  setLED(0, 16, RED_COLOR);
  setLED(16, 48, BLACK_COLOR);
  FastLED.show();
  delay(500);

  setLED(0, 16, BLACK_COLOR);
  setLED(16, 16, GREEN_COLOR);
  setLED(32, 32, BLACK_COLOR);
  FastLED.show();
  delay(500);

  setLED(0, 32, BLACK_COLOR);
  setLED(32, 16, BLUE_COLOR);
  setLED(48, 16, BLACK_COLOR);
  FastLED.show();
  delay(500);

  setLED(0, 48, BLACK_COLOR);
  setLED(48, 16, YELLOW_COLOR);
  FastLED.show();
  delay(500);
}

void setLED(int start, int number, const int RGBcolor[]) {
  for (int i = start; i < start + number; i++)
  {
    leds[i] = CRGB(RGBcolor[0],RGBcolor[1],RGBcolor[2]);
  }
}
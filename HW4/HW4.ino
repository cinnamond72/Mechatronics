#include <M5Stack.h>
#include <Keypad.h>

const byte ROWS = 4;
const byte COLS = 4;

unsigned long currentMillis = millis();
unsigned long timerStartTime;

char hexaKeys[ROWS][COLS] = {
  {'0','1','2','3'},
  {'4','5','6','7'},
  {'8','9','A','B'},
  {'C','D','E','F'}
};
char key;

byte rowPins[ROWS] = {17, 16, 21, 22};
byte colPins[COLS] = {5, 12, 13, 15};

Keypad customKeypad = Keypad( makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);

enum State {WAIT, UP, DOWN};
const char* stateStr[] = {"WAIT", "UP", "DOWN"};
enum State currentState;

int currentFloor = 1;
int inBtn = 0;
int outBtn = 0;
const long moveTime = 10000;

void setup()
{
  M5.begin();
  currentState = WAIT;

  M5.Lcd.setTextFont(4);
  M5.Lcd.setCursor(0,10);
  M5.Lcd.print("Start...");
  delay(1000);
}

void loop()
{
  M5.Lcd.setCursor(0,10);
  M5.Lcd.print("currentState : ");
  M5.Lcd.print(stateStr[currentState]);
  M5.Lcd.print("        ");

  M5.Lcd.setCursor(0,40);
  M5.Lcd.print("currentFloor : ");
  M5.Lcd.print(currentFloor);
  M5.Lcd.print("        ");

  switch (currentState)
  {
    case WAIT:

      key = customKeypad.getKey();
      switch (key)
        {
          case '8':
              inBtn = 2;
              outBtn = 0;
            break;
          
          case 'C':
              inBtn = 1;
              outBtn = 0;
            break;
          
          case 'B':
              inBtn = 0;
              outBtn = 2;
            break;

          case 'F':
              inBtn = 1;
              outBtn = 0;
            break;
        }

      if (inBtn != currentFloor && outBtn != currentFloor && (inBtn != 0 || outBtn != 0))
      {
        if (currentFloor < inBtn || currentFloor < outBtn)
        {
          currentState = UP;
          timerStartTime = millis();
        }
        else if (currentFloor > inBtn || currentFloor > outBtn)
        {
          currentState = DOWN;
          timerStartTime = millis();
        }
      }
      break;
    
    case UP:

      delay(1000);
      currentFloor = 2;

      if (currentFloor == inBtn || currentFloor == outBtn)
      {
        currentState = WAIT;
        inBtn = 0;
        outBtn = 0;
      }
      break;
    
    case DOWN:

      delay(1000);
      currentFloor = 1;

      if (currentFloor == inBtn || currentFloor == outBtn)
      {
        currentState = WAIT;
        inBtn = 0;
        outBtn = 0;
      }
      break;
  }

  delay(1);
}
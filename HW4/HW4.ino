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

byte rowPins[ROWS] = {17, 16, 21, 22};
byte colPins[COLS] = {5, 12, 13, 15};

Keypad customKeypad = Keypad( makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);

enum State {WAIT, UP, DOWN};
enum State currentState;

int currentFloor = 1;
int inBtn = 0;
int outBtn = 0;
const long moveTime = 1000;

void setup()
{
  M5.begin();
  currentState = WAIT;

  M5.Lcd.setTextFont(3);
  M5.Lcd.print("สวัสดีครับ ท่านสมาชิกชมรมคนชอบหมี วันพระวันเจ้าไม่เว้นกันเลยอยากจะดูแต่หมี ไม่เข้าใจจริงๆเลยทั้งเด็กทั้งผู้ใหญ่ตะโกนหาสรรหาแต่หมี เป็นอะไรกัน! เฮ้ยย ทั้งวันเลยวันนี้ทำงานมีแต่หมีโผล่มาทั้งวันเลยส่งไปให้แล้วก็ยังจะให้ดูอีก มันหมายความว่าไงเนี่ยคนที่ไหนคนจังหวัดอะไรพวกท่านเนี่ย เอ้ยตายแล้ว ดูธรรมะธรรมโมมั่งดิดูปรัชญา คําคม วิถีชีวิต ปรัชญาข่มใจข่มกิเลสตัณหา ดูเป็นบ้างรึเปล่าดูแต่หมี วันพระใหญ่นะ หมีระงมกันทั้งวันทั้งคืนเลยไม่เข้าใจเลยพวกท่านเป็นยังไง จัดมาดิ เอาแบบเบิ้มๆน่ะมะคือลือน่ะ เฮ้ยคนที่ใหนพวกท่านเป็นคนจังหวัดอะไรเกิดวันไหนเกิดปีไหนเกิดปีจอหรือปีอะไรครับผมไม่เข้าใจ ตายแล้วว ทำงานทั้งวันละหมีโผล่ทั้งวันเลย55555 ผมไม่เข้าใจเลยจริงๆโอ้ยตายแล้วพวกท่านมวยกูมาละลาก่อน ดูหมีไปก่อนผมจะดูมวย");
  delay(1000);
  M5.Lcd.fillScreen(BLACK);
}

void loop()
{
  char key = customKeypad.getKey();

  M5.Lcd.setCursor(0,10);
  M5.Lcd.print("currentState : ");
  M5.Lcd.print(currentState);
  M5.Lcd.print("    ");

  M5.Lcd.setCursor(0,20);
  M5.Lcd.print("currenFloor : ");
  M5.Lcd.print(currentFloor);
  M5.Lcd.print("    ");

  M5.Lcd.setCursor(0,30);
  M5.Lcd.print("customKey : ");
  M5.Lcd.print(key);
  M5.Lcd.print("    ");

switch (key)
  {
    case '0':
      if (currentState == WAIT)
      {
        inBtn = 2;
        outBtn = 0;
      }
      break;
    
    case '4':
      if (currentState == WAIT)
      {
        inBtn = 1;
        outBtn = 0;
      }
      break;
    
    case '3':
      if (currentState == WAIT)
      {
        inBtn = 0;
        outBtn = 2;
      }
      break;

    case '7':
      if (currentState == WAIT)
      {
        inBtn = 1;
        outBtn = 0;
      }
      break;
  }

  switch (currentState)
  {
    case WAIT:
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
      break;
    
    case UP:
      if (currentFloor == inBtn || currentFloor == outBtn)
      {
        currentState = WAIT;
        inBtn = 0;
        outBtn = 0;
      }
      break;
    
    case DOWN:
      if (currentFloor == inBtn || currentFloor == outBtn)
      {
        currentState = WAIT;
        inBtn = 0;
        outBtn = 0;
      }
      break;
  }

  currentFloor = simulation(currentState, timerStartTime, moveTime);
  delay(1);
}

int simulation(State currentState, unsigned long timerStartTime, const long moveTime){
  unsigned long t = millis();
  switch (currentState)
  {
    case UP:
      if (t - timerStartTime > moveTime)
      {
        return 2;
      }
    case DOWN:
      if (t - timerStartTime > moveTime)
      {
        return 1;
      }
  }
}
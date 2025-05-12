#include <LiquidCrystal.h>
#include <Keypad.h>
#include <Stepper.h>

LiquidCrystal lcd(A4, A5, A3, A2, A1, A0);

const byte ROWS = 4;
const byte COLS = 3;

char keys[ROWS][COLS] = {
  {'1','2','3'},
  {'4','5','6'},
  {'7','8','9'},
  {'*','0','#'}
};

byte rowPins[ROWS] = {0, 1, 2, 3};
byte colPins[COLS] = {4, 5, 6};

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

const int trigger = 13;
const int echo = 12;

const int STEPS_PER_REVOLUTION = 36; // Adjust this based on your stepper motor
const int MOTOR_SPEED = 100; // RPM (adjust for desired speed)

Stepper stepper(STEPS_PER_REVOLUTION, 8, 9, 10, 11);

bool menu = true;
int pos = 0;

void setup() {
  lcd.begin(16, 2);
  pinMode(trigger, OUTPUT);
  pinMode(echo, INPUT);
  Serial.begin(9600);
  stepper.setSpeed(MOTOR_SPEED);
}


void loop() {
  if(menu) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("1. Sensor 2.Length 3. Speed");
    menu = false;
  }

  char key = keypad.getKey();

  if(key) {
    switch (key) {
      case '1':
        sensor();
        break;

      case '2':
        setLength();
        break;

      case '3':  
        setSpeed();
        break;

      default:
        lcd.clear();
        lcd.print("Invalid Input");
        delay(400);
        break;
    }
    menu = true;
  }
}

void sensor() {
  while(true) {
    long duration, mm;
 
    digitalWrite(trigger, LOW);
    delayMicroseconds(2);
    digitalWrite(trigger, HIGH);
    delayMicroseconds(5);
    digitalWrite(trigger, LOW);

    duration = pulseIn(echo, HIGH);
    mm = microsecondsToMilimeters(duration * 10);
    
    lcd.setCursor(0, 0);
    lcd.print("        ");

    lcd.setCursor(0, 0);
    lcd.print(mm);
    lcd.print("mm");

    delay(200);
  }  
}

void setSpeed(){
  lcd.clear();
  lcd.print("Speed: ");

  int speed = enterNum();

  if(speed != -1) {
    changeSpeed(speed);
  }
}

void setLength() {
  lcd.clear();
  lcd.print("Length: ");

  int len = enterNum();

  if(len != -1) {
    pos = cut(len);
  }
}

int enterNum() {
  String inputString = "";  // Stores the digits as they're entered
  bool enteringNumber = false;
  int count = 0;

  while(true) {
    char key = keypad.getKey();

    if (key) {
      if (key == '#') {  // Enter key pressed
          if (inputString.length() > 0)
            return inputString.toInt();
          else
            return -1;
      }
      else if (isdigit(key)) {  // Digit pressed
        if (inputString.length() < 6) {  // Limit input length
          inputString += key;
          lcd.setCursor(count, 1);
          // lcd.print(inputString);
          lcd.print(key);
          count += 1;
        }
      }
      else if (key == '*') {  // Clear input
        if (inputString == "") {
          lcd.clear();
          lcd.print("Main Menu ");
          delay(200);
          return -1;
        }
        inputString = "";
        enteringNumber = false;
        count = 0;
        lcd.setCursor(0, 1);
        lcd.print("              ");

        lcd.setCursor(0, 1);
        lcd.print("cleared");

        delay(400);

        lcd.setCursor(0, 1);
        lcd.print("              ");
      }
    }
  }
}

int cut(int len) {
  int tar = len - pos;
  lcd.clear();
  lcd.print("Target ");
  lcd.print(len);
  lcd.print("mm");
  lcd.setCursor(0, 1);
  lcd.print("(shift ");
  lcd.print(tar);
  lcd.print("mm)");


  // stepper.step(STEPS_PER_REVOLUTION * len);

  int totalSteps = STEPS_PER_REVOLUTION * tar;
  int stepsTaken = 0;

  int i = tar > 0 ? 1 : -1;

  while (stepsTaken != totalSteps) {
    stepper.step(i);         // Move 1 step
    stepsTaken += i;         // Track steps taken

    char key = keypad.getKey();  // Check for keypress
    if (key == '#') {
      int covered = stepsTaken / STEPS_PER_REVOLUTION;
      lcd.clear();
      lcd.print("Stopped at: ");
      lcd.setCursor(0, 1);
      lcd.print(covered, 2);  // Show 2 decimal places
      lcd.print(" mm");
      delay(800);             // Wait 2s so user sees message
      return covered;
    }
  }

  lcd.clear();
  lcd.print("Done: ");
  lcd.print(len);
  lcd.print(" mm");
  delay(800);
  return len;
}

void changeSpeed(int speed) {
  lcd.clear();
  lcd.print("Speed ");
  lcd.print(speed);
  lcd.print("mm/sec");
  stepper.setSpeed(speed);
  delay(400);
}

void setHome() {
  while(!sensor) {
    stepper.step(1);
  }
  pos = 0;
}

long microsecondsToMilimeters(long microseconds) {
  return microseconds / 29 / 2;
}
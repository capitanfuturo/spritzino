#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define L_PIN 7
#define R_PIN 8

bool showSplashScreen = true;

const unsigned int WAIT_FOR_DEBOUNCE = 100;

unsigned long leftDebounceTime = 0;
int leftButtonStatus = LOW;
int lastLeftButtonValue = LOW;

unsigned long rightDebounceTime = 0;
int rightButtonStatus = LOW;
int lastRightButtonValue = LOW;


// LCD
int currentState = 0;
const int NUM_STATES = 5;
String screens[NUM_STATES][2] = {
  {"SPRITZINO", "v.0.1"},
  {"Attendere...", "in preparazione"},
  {"Pronto...", "bevi piano!"},
  {"Spritz?", "Sx=avanti Dx=OK"},
  {"Prosecco?", "Sx=avanti Dx=OK"}
};

const int SPLASH_SCREEN = 0;
const int BUSY_SCREEN = 1;
const int READY_SCREEN = 2;
const int SPRITZ_SCREEN = 3;
const int PROSECCO = 4;


LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  Serial.begin(9600);

  // BUTTONS
  pinMode(L_PIN, INPUT);
  pinMode(R_PIN, INPUT);

  // LCD
  lcd.begin();
  lcd.backlight();
  lcd.clear();
}

void loop() {
  //  while (!isRightPressed && !isLeftPressed) {
  if (showSplashScreen) {
    showSplashScreen = false;
    printScreen();
    Serial.println("Splash screen.");
    delay(1000);
  }
  //  }
  buttonsWait();
}

void buttonsWait() {
  // LEFT
  int leftButtonValue = digitalRead(L_PIN);
  if (leftButtonValue != lastLeftButtonValue) {
    leftDebounceTime = millis();
  }
  if ((millis() - leftDebounceTime) > WAIT_FOR_DEBOUNCE) {
    if (leftButtonValue != leftButtonStatus && leftButtonValue == HIGH) {
      takeAction(L_PIN);
    }
    leftButtonStatus = leftButtonValue; // assegno lo stato del pulsante con il nuovo valore
  }

  lastLeftButtonValue = leftButtonValue; // assegno all'ultimo valore del pulsante lo stato
  delay(10); // ritardo

  // RIGHT
  int rightButtonValue = digitalRead(R_PIN);
  if (rightButtonValue != lastRightButtonValue) {
    rightDebounceTime = millis();
  }
  if ((millis() - rightDebounceTime) > WAIT_FOR_DEBOUNCE) {
    if (rightButtonValue != rightButtonStatus && rightButtonValue == HIGH) {
      takeAction(R_PIN);
    }
    rightButtonStatus = rightButtonValue; // assegno lo stato del pulsante con il nuovo valore
  }

  lastRightButtonValue = rightButtonValue; // assegno all'ultimo valore del pulsante lo stato
  delay(50); // ritardo
}

void takeAction(int button) {
  Serial.print("OLD currentState:"); Serial.println(currentState);
  switch (button) {
    case L_PIN:
      if (currentState == SPLASH_SCREEN) {
          // first receipt
        currentState = SPRITZ_SCREEN;
        printScreen();
      } else if (currentState >= SPRITZ_SCREEN && currentState < NUM_STATES - 1) {
        // next receipt
        currentState = currentState + 1;
        printScreen();
      } else {
          // finish loop
        currentState = SPLASH_SCREEN;
        printScreen();
      }
      break;
    case R_PIN:
      if (currentState >= SPRITZ_SCREEN && currentState < NUM_STATES) {
        currentState = BUSY_SCREEN;
        printScreen();
        delay(2000);
        currentState = READY_SCREEN;
        printScreen();
      }
      break;
    default:
      currentState = SPLASH_SCREEN;
      printScreen();
      break;
  }
  Serial.print("NEW currentState:"); Serial.println(currentState);
  delay(50);
}

void printScreen() {
  lcd.clear();
  lcd.print(screens[currentState][0]);
  lcd.setCursor(0, 1);
  lcd.print(screens[currentState][1]);
}
#include <AFMotor.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

/* Button */
#define L_PIN 2 // left button's PIN
#define R_PIN 3 // right button's PIN

const unsigned int WAIT_FOR_DEBOUNCE = 100;

unsigned long leftDebounceTime = 0;
int leftButtonStatus = LOW;
int lastLeftButtonValue = LOW;

unsigned long rightDebounceTime = 0;
int rightButtonStatus = LOW;
int lastRightButtonValue = LOW;

/* LCD */
bool showSplashScreen = true;
int currentState = 0;
const int NUM_STATES = 5;

String screens[NUM_STATES][2] = {
  {"SPRITZINO", "v.0.1"},
  {"Attendere...", "in preparazione"},
  {"Pronto...", "bevi piano!"},
  {"Spritz", "Sx=avanti Dx=OK"},
  {"Prosecco", "Sx=avanti Dx=OK"}
};

const int SPLASH_SCREEN = 0;
const int BUSY_SCREEN = 1;
const int READY_SCREEN = 2;
const int SPRITZ = 3;
const int PROSECCO = 4;

LiquidCrystal_I2C lcd(0x27, 16, 2);

/* MOTORS */
AF_DCMotor proseccoMotor(1, MOTOR12_8KHZ);

/**
 * SETUP
 */
void setup() {
  
  // BUTTONS
  pinMode(L_PIN, INPUT);
  pinMode(R_PIN, INPUT);

  // LCD
  lcd.begin();
  lcd.backlight();
  lcd.clear();

  // MOTORS
  proseccoMotor.setSpeed(120);
}

/**
 * MAIN LOOP
 */
void loop() {
  
  if (showSplashScreen) {
      showSplashScreen = false;
      printScreen();
      delay(1000);
  }

  buttonsWait();
}

/**
 * Wait user input.
 */
void buttonsWait() {
  
  // left button
  int leftButtonValue = digitalRead(L_PIN);

  if (leftButtonValue != lastLeftButtonValue) {
    leftDebounceTime = millis();
  }
  
  if ((millis() - leftDebounceTime) > WAIT_FOR_DEBOUNCE) {
    if (leftButtonValue != leftButtonStatus && leftButtonValue == HIGH) {
      takeAction(L_PIN);
    }
    leftButtonStatus = leftButtonValue;
  }

  lastLeftButtonValue = leftButtonValue;
  delay(10);

  // Right button
  int rightButtonValue = digitalRead(R_PIN);
  
  if (rightButtonValue != lastRightButtonValue) {
    rightDebounceTime = millis();
  }

  if ((millis() - rightDebounceTime) > WAIT_FOR_DEBOUNCE) {
    if (rightButtonValue != rightButtonStatus && rightButtonValue == HIGH) {
      takeAction(R_PIN);
    }
    rightButtonStatus = rightButtonValue;
  }

  lastRightButtonValue = rightButtonValue;
  delay(50);
}

/**
 * According with the button pressed and the application status
 * do the right stuff.
 */
void takeAction(int button) {
  switch (button) {
    case L_PIN:
      // NEXT Button
      if (currentState == SPLASH_SCREEN) {
        currentState = SPRITZ;
        printScreen();
      } else if (currentState >= SPRITZ && currentState < NUM_STATES - 1) {
        currentState = currentState + 1;
        printScreen();
      } else {
        currentState = SPLASH_SCREEN;
        printScreen();
      }
      break;
    case R_PIN:
      // OK Button
      if (currentState >= SPRITZ && currentState < NUM_STATES) {
        
        int cocktailSelected = currentState;

        currentState = BUSY_SCREEN;
        printScreen();
        
        if(cocktailSelected == PROSECCO){
          makeProsecco();
        }

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
  delay(50);
}

/**
 * Show the current application status
 */
void printScreen() {
  lcd.clear();
  lcd.print(screens[currentState][0]);
  lcd.setCursor(0, 1);
  lcd.print(screens[currentState][1]);
}

/**
 * Only prosecco cocktail
 */
void makeProsecco() {
  proseccoMotor.run(FORWARD);
  delay(5000);
  proseccoMotor.run(RELEASE);
}
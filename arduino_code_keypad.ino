#include <Servo.h>
#include <LiquidCrystal_I2C.h>
#include <Keypad.h>
#include <Password.h>

#define BUZZER_PIN 11
#define SERVO_PIN 10

Servo servo;
LiquidCrystal_I2C lcd(0x27, 16, 2);

String newPasswordString;
char newPassword[6];
byte cursorPosition = 5;
bool doorLocked = true;

Password password = Password("345678");
byte maxPasswordLength = 6;
byte currentPasswordLength = 0;

const byte ROWS = 4;
const byte COLS = 4;
char keys[ROWS][COLS] = {
  {'D', 'C', 'B', 'A'},
  {'#', '9', '6', '3'},
  {'0', '8', '5', '2'},
  {'*', '7', '4', '1'}
};
byte rowPins[ROWS] = {2, 3, 4, 5};
byte colPins[COLS] = {6, 7, 8, 9};

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

void setup() {
  Serial.begin(9600);
  pinMode(BUZZER_PIN, OUTPUT);
  servo.attach(SERVO_PIN);
  servo.write(0);
  lcd.init();
  lcd.backlight();
  lcd.setCursor(3, 0);
  lcd.print("WELCOME TO");
  lcd.setCursor(0, 1);
  lcd.print("LOCKER SYSTEM");
  delay(3000);
  lcd.clear();
}

void loop() {
  lcd.setCursor(1, 0);
  lcd.print("ENTER PASSWORD");
  char key = keypad.getKey();
  if (key != NO_KEY) {
    delay(60);
    handleKeyPress(key);
  }
}

void handleKeyPress(char key) {
  if (key == 'C') {
    resetPassword();
  } else if (key == 'D') {
    toggleDoor();
  } else {
    processNumberKey(key);
  }
}

void processNumberKey(char key) {
  lcd.setCursor(cursorPosition, 1);
  lcd.print("*");
  cursorPosition++;
  if (cursorPosition == 11) {
    cursorPosition = 5;
  }
  currentPasswordLength++;
  password.append(key);
  if (currentPasswordLength == maxPasswordLength) {
    checkPassword();
  }
}

void checkPassword() {
  if (password.evaluate()) {
    if (doorLocked) {
      doorAction("DOOR OPENED", 90);
      doorLocked = false;
    } else {
      doorAction("DOOR LOCKED", 0);
      doorLocked = true;
    }
  } else {
    displayError();
  }
  resetPassword();
}

void toggleDoor() {
  if (password.evaluate()) {
    if (doorLocked) {
      doorAction("DOOR OPENED", 90);
      doorLocked = false;
    } else {
      doorAction("DOOR LOCKED", 0);
      doorLocked = true;
    }
  } else {
    displayError();
    resetPassword();
  }
}

void doorAction(String message, int position) {
  digitalWrite(BUZZER_PIN, HIGH);
  delay(300);
  digitalWrite(BUZZER_PIN, LOW);
  servo.write(position);
  delay(100);
  lcd.setCursor(0, 0);
  lcd.print("CORRECT PASSWORD");
  lcd.setCursor(0, 1);
  lcd.print(message);
  delay(2000);
  lcd.clear();
  cursorPosition = 5;
}

void displayError() {
  for (int i = 0; i < 3; i++) {
    digitalWrite(BUZZER_PIN, HIGH);
    delay(200);
    digitalWrite(BUZZER_PIN, LOW);
    delay(200);
  }
  lcd.setCursor(0, 0);
  lcd.print("WRONG PASSWORD!");
  lcd.setCursor(0, 1);
  lcd.print("PLEASE TRY AGAIN");
  delay(2000);
  lcd.clear();
  cursorPosition = 5;
}

void resetPassword() {
  password.reset();
  currentPasswordLength = 0;
  lcd.clear();
  cursorPosition = 5;
}

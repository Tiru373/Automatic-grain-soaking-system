#include <Servo.h>
#include <Wire.h>
#include <RTClib.h>
#include <LiquidCrystal.h>

RTC_DS1307 rtc;
Servo doorServo;
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

const int buzzerPin = 6;
const int buttonSelectPin = 7;   // Button to toggle between adjusting hours and minutes
const int buttonIncrementPin = 8; // Button to increment the time
const int buttonDecrementPin = 9; // Button to decrement the time

int soakingHour = 16;      // Soaking hour
int soakingMinute = 15;    // Soaking minute
bool adjustingHours = true; // Flag for adjusting hours or minutes

void setup() {
  Serial.begin(9600);
  pinMode(buzzerPin, OUTPUT);
  pinMode(buttonSelectPin, INPUT_PULLUP);
  pinMode(buttonIncrementPin, INPUT_PULLUP);
  pinMode(buttonDecrementPin, INPUT_PULLUP);
  lcd.begin(16, 2);

  if (!rtc.begin()) {
    Serial.println("RTC failed to initialize!");
  }
  if (!rtc.isrunning()) {
    Serial.println("RTC is NOT running!");
    rtc.adjust(DateTime(F(_DATE), F(__TIME__)));
  }

  doorServo.attach(10);
  lcd.clear();
}

void loop() {
  DateTime now = rtc.now();
  int currentHour = now.hour();
  int currentMinute = now.minute();
  int currentSecond = now.second();

  lcd.setCursor(0, 0);
  lcd.print("C.Time: ");
  lcd.print(currentHour);
  lcd.print(":");
  lcd.print(currentMinute < 10 ? "0" : "");
  lcd.print(currentMinute);
  lcd.print(":");
  lcd.print(currentSecond < 10 ? "0" : "");
  lcd.print(currentSecond);

  lcd.setCursor(0, 1);
  lcd.print("Soaking:");
  lcd.print(soakingHour);
  lcd.print(":");
  lcd.print(soakingMinute < 10 ? "0" : "");
  lcd.print(soakingMinute);

  if (currentHour == soakingHour && currentMinute == soakingMinute && currentSecond == 0) {
    lcd.setCursor(0, 1);
    lcd.print("Process Activate!");
    beep();
    openDoor();
    delay(1000);
    lcd.clear();
  }
  
  if(currentHour == soakingHour && currentMinute == soakingMinute + 1){
    lcd.setCursor(0, 1);
    lcd.print("Process Done");
    beep();
    delay(2000);
    lcd.clear();
  }

  // Check button inputs
  if (digitalRead(buttonSelectPin) == HIGH) {
    delay(250);
    adjustingHours = !adjustingHours; // Toggle between adjusting hours and minutes
  }

  if (digitalRead(buttonIncrementPin) == HIGH) {
    delay(250);
    if (adjustingHours) {
      soakingHour = (soakingHour + 1) % 24;
    } else {
      soakingMinute = (soakingMinute + 1) % 60;
    }
  }

  if (digitalRead(buttonDecrementPin) == HIGH) {
    delay(250);
    if (adjustingHours) {
      soakingHour = (soakingHour + 23) % 24;
    } else {
      soakingMinute = (soakingMinute + 59) % 60;
    }
  }
  
  if (adjustingHours) {
    lcd.print("(H)");
  }
  else{
    lcd.print("(M)");
  }
}

void beep() {
  for (int i = 0; i < 3; i++) {
    digitalWrite(buzzerPin, HIGH);
    delay(200);
    digitalWrite(buzzerPin, LOW);
    delay(200);
  }
  digitalWrite(buzzerPin, LOW);
}

void openDoor() {
  doorServo.write(180);
  delay(10000);
  doorServo.write(90);
}

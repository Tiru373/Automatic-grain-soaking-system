#include <Servo.h>

#include <Wire.h>
#include <RTClib.h>
#include <LiquidCrystal.h>
#include <Servo.h>

RTC_DS1307 rtc; // Initialize RTC object
Servo doorServo; // Initialize Servo object

LiquidCrystal lcd(12, 11, 5, 4, 3, 2); // Initialize LCD with pins

const int buzzerPin = 6; // Define buzzer pin
const int buttonHourPin = 7; // Hour button
const int buttonMinutePin = 8; // Minute button
const int buttonSelectPin = 9; // Select button

int alarmHour = 11;     // Alarm hour (24-hour format)
int alarmMinute = 22;  // Alarm minute
bool selectingHour = true; // Flag for selecting hours or minutes

void setup() {
  Serial.begin(9600);
  pinMode(buzzerPin, OUTPUT);
  pinMode(buttonHourPin, INPUT_PULLUP);
  pinMode(buttonMinutePin, INPUT_PULLUP);
  pinMode(buttonSelectPin, INPUT_PULLUP);
  lcd.begin(16, 2); // Initialize LCD with 16x2 characters
  
  // Initialize RTC
  if (!rtc.begin()) {
    Serial.println("RTC failed to initialize!");
  }
  if (!rtc.isrunning()) {
    Serial.println("RTC is NOT running!");
    // Set RTC to a default date and time when it's not running
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  }
//rtc.adjust(DateTime(F(_DATE), F(__TIME_)));
  // Attach servo to the pin
  doorServo.attach(10); // Use the appropriate pin for the servo

  lcd.clear();
}

void loop() {
  DateTime now = rtc.now();
  int currentHour = now.hour();
  int currentMinute = now.minute();
  int currentSecond = now.second();

  // Display current time on the 1st line of the LCD
  lcd.setCursor(0, 0);
  lcd.print("C.Time: ");
  lcd.print(currentHour);
  lcd.print(":");
  lcd.print(currentMinute < 10 ? "0" : "");
  lcd.print(currentMinute);
  lcd.print(":");
  lcd.print(currentSecond < 10 ? "0" : "");
  lcd.print(currentSecond);

  // Display alarm time on the 2nd line of the LCD
  lcd.setCursor(0, 1);
  lcd.print("AlamTime:");
  lcd.print(alarmHour);
  lcd.print(":");
  lcd.print(alarmMinute < 10 ? "0" : "");
  lcd.print(alarmMinute);
  lcd.print("       "); // Clear any remaining characters

  // Check if it's time for the alarm
  if (currentHour == alarmHour && currentMinute == alarmMinute&&currentSecond==0) {
    lcd.setCursor(0, 1);
    lcd.print("Alarm! Wake up!");
    beep(); // Activate the buzzer
    // Open the door (move the servo)
    openDoor();
    delay(2000); // Alarm remains active for 10 seconds
    lcd.clear();
  }

  // Check button inputs
  if (digitalRead(buttonHourPin) == HIGH) {
    delay(250); // Debounce
    if (selectingHour) {
      alarmHour = (alarmHour + 1) % 24; // Increment hour
    } else {
      alarmMinute = (alarmMinute + 1) % 60;
      alarmHour = (alarmHour + 23) % 24; // Switch to selecting hours
    }
  }

  if (digitalRead(buttonMinutePin) == HIGH) {
    delay(250); // Debounce
    if (selectingHour) {
       alarmHour = (alarmHour + 23) % 24;// Increment minute
    } else {
      alarmMinute = (alarmMinute + 59) % 60; // Switch to selecting minutes
    }
  }

  if (digitalRead(buttonSelectPin) == HIGH) {
    delay(250); // Debounce
    selectingHour = !selectingHour; // Toggle between hours and minutes selection
  }
}

void beep() {
  for (int i = 0; i < 3; i++) { // Beep three times
    digitalWrite(buzzerPin, HIGH);
    delay(200);
    digitalWrite(buzzerPin, LOW);
    delay(200);
  }
  digitalWrite(buzzerPin, LOW); // Ensure buzzer is off after beeping
}

void openDoor() {
  // Move the servo to open the door (adjust angles as needed)
  doorServo.write(180); // Use the appropriate angle to open the door
  delay(30000); // Delay to keep the door open for 2 seconds
  doorServo.write(90); // Close the door by setting the servo to the initial position
}
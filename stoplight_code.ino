#include <LiquidCrystal.h>

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

const int buttonPin = 7;
const int GreenLedPin =  10;
const int YellowLedPin =  9;
const int RedLedPin =  8;
const int sensorPin = A0;

int buttonState;
int POT; //value of pot at a given time
int countdown;
int timeLeft;
int timeLeft2;
int counter;

int sensorValue;

void setup() {
  Serial.begin(9600);
  pinMode(RedLedPin, OUTPUT);
  pinMode(YellowLedPin, OUTPUT);
  pinMode(GreenLedPin, OUTPUT);

  digitalWrite(GreenLedPin, LOW);
  digitalWrite(YellowLedPin, LOW);
  digitalWrite(RedLedPin, LOW);

  buttonState = digitalRead(buttonPin);

  lcd.begin(16, 2);
  lcd.clear();
}

void loop() {
 
  while (buttonState == LOW) {              //allows program to be started if button is already pressed
    lcd.setCursor(0,0);                      
    lcd.print("Unpress to enter setup");
    buttonState = digitalRead(buttonPin);
  }
  
  while (buttonState == HIGH) {             //setup the time to stay green
    POT = analogRead(sensorPin);
    POT = (POT / 20.4) + 10;
    Serial.println(POT);
    timeLeft = countdown = POT;
    lcd.setCursor(0, 0);
    lcd.print("push to start");
    lcd.setCursor(0, 1);
    lcd.print(countdown);
    buttonState = digitalRead(buttonPin);
  }
  
  lcd.clear();
  digitalWrite(GreenLedPin, HIGH);           //run the green light for the designated amount of time
  while (timeLeft > 0) {
    lcd.setCursor(0, 0);
    lcd.print("countdown mode");
    lcd.setCursor(0, 1);
    lcd.print(timeLeft);
    delay(60000);
    timeLeft -= 1;
  }
  
  lcd.clear();
  timeLeft2 = 5;                            //run the yellow light for five minutes 
  digitalWrite(GreenLedPin, LOW);
  digitalWrite(YellowLedPin, HIGH);
  for (int i = 0; i < 5; i++) {
    lcd.setCursor(0, 0);
    lcd.print("Clean up");
    lcd.setCursor(0, 1);
    lcd.print(timeLeft2);
    delay(60000);
    timeLeft2 -= 1;
  }
  
  lcd.clear();
  digitalWrite(YellowLedPin, LOW);          //leave red light on until button is unpressed
  digitalWrite(RedLedPin, HIGH);
  lcd.setCursor(0, 0);
  lcd.print("Unpress to reset");
  while (buttonState == LOW) {
    buttonState = digitalRead(buttonPin);
  }
  lcd.clear();
  digitalWrite(RedLedPin, LOW);
}

/*
Stoplight code created for a teacher at Benica High School to monitor the amount of time to work during class 
Written By Ben Echard  
In 2016
 */

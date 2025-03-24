#include <Wire.h>
#include <LiquidCrystal_I2C.h>
const int MQ7_PIN = 2;  // Senzorul MQ-7
const int LED_PIN = 4;  // LED-ul
const int BUZZER_PIN = 3; // Buzzer-ul

LiquidCrystal_I2C lcd(0x27, 16, 2);
const int CO_THRESHOLD = 100;  

unsigned long previousMillis = 0;
const long blinkInterval = 500;
int ledState = LOW;
void setup() {
  pinMode(LED_PIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  Serial.begin(9600);
}
void loop() {
  int coLevel = analogRead(MQ7_PIN);
  Serial.print("Nivel CO: ");
  Serial.println(coLevel);

  if (coLevel > CO_THRESHOLD) {
    lcd.clear();
    lcd.setCursor(6, 0);  
    lcd.print("EXIT");
    
    unsigned long currentMillis = millis();
    if (currentMillis - previousMillis >= blinkInterval) {
      previousMillis = currentMillis;
      ledState = !ledState;
      digitalWrite(LED_PIN, ledState);
      
      if (ledState == HIGH) {
        tone(BUZZER_PIN, 1000);
      } else {
        noTone(BUZZER_PIN);
      }
    }
  } else {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("nivel normal");
    lcd.setCursor(0, 1);
    lcd.print("de oxigen");
    digitalWrite(LED_PIN, LOW);
    noTone(BUZZER_PIN);
  }
  delay(100);
}

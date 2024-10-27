#include <Arduino.h>

#define led1 10 // 25%
#define led2 9  // 50%
#define led3 8  // 75%
#define led4 7  // 100%

#define ledR 6 // red
#define ledG 5 // green
#define ledB 4 // blue

#define buttonStart 3
#define buttonStop 2

unsigned long lastDebounceTimeStart = 0;
unsigned long lastDebounceTimeStop = 0;
unsigned long debounceDelay = 50;

unsigned long stopPressStartTime = 0; 
bool stopPressedLong = false;         

bool charging = false;
bool prevStartState = LOW;
bool prevStopState = LOW;

int stage = 0;
unsigned long previousMillis = 0;
const long interval = 500; 


void setRGB(int r, int g, int b) {
  digitalWrite(ledR, r);
  digitalWrite(ledG, g);
  digitalWrite(ledB, b);
}

void stopCharging() {
  for (int i = 0; i <= 3; i++) {
    digitalWrite(led1, HIGH);
    digitalWrite(led2, HIGH);
    digitalWrite(led3, HIGH);
    digitalWrite(led4, HIGH);
    delay(500);
    digitalWrite(led1, LOW);
    digitalWrite(led2, LOW);
    digitalWrite(led3, LOW);
    digitalWrite(led4, LOW);
    delay(500);
  }
  charging = false;
  setRGB(LOW, HIGH, LOW); 
}


void checkStopButton() {
  unsigned long currentMillis = millis();
  int stopReading = digitalRead(buttonStop);


  if (stopReading == LOW && !stopPressedLong) {
    if (stopPressStartTime == 0) {
      stopPressStartTime = currentMillis;
    }
    if ((currentMillis - stopPressStartTime) > 1000) { 
      stopPressedLong = true;
      stopCharging(); 
    }
  } else if (stopReading == HIGH) {
    stopPressStartTime = 0;
    stopPressedLong = false;
  }
}

void setup() {
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(led4, OUTPUT);

  pinMode(ledR, OUTPUT);
  pinMode(ledG, OUTPUT);
  pinMode(ledB, OUTPUT);

  pinMode(buttonStart, INPUT_PULLUP);
  pinMode(buttonStop, INPUT_PULLUP);

  setRGB(LOW, HIGH, LOW); 
}

void loop() {
  unsigned long currentMillis = millis();


  int startReading = digitalRead(buttonStart);


  if (startReading != prevStartState) {
    lastDebounceTimeStart = currentMillis;
  }

  if ((currentMillis - lastDebounceTimeStart) > debounceDelay && startReading == LOW && charging == false) {
    charging = true;
    stage = 1;
    setRGB(HIGH, LOW, LOW); 
  }

  prevStartState = startReading;

 
  if (charging) {
    if (stage == 1 && (currentMillis - previousMillis >= interval)) {
      previousMillis = currentMillis;

 
      for (int i = 0; i < 1; i++) {
        digitalWrite(led1, HIGH);
        delay(500);
        checkStopButton(); 
        digitalWrite(led1, LOW);
        delay(500);
        checkStopButton(); 
      }

      stage = 2;
    }

    if (stage == 2 && (currentMillis - previousMillis >= interval)) {
      previousMillis = currentMillis;

     
      digitalWrite(led1, HIGH);
      for (int i = 0; i < 2; i++) {
        digitalWrite(led2, HIGH);
        delay(500);
        checkStopButton(); 
        digitalWrite(led2, LOW);
        delay(500);
        checkStopButton(); 
      }

      stage = 3;
    }

    if (stage == 3 && (currentMillis - previousMillis >= interval)) {
      previousMillis = currentMillis;
      digitalWrite(led2, HIGH); 
   
      for (int i = 0; i < 2; i++) {
        digitalWrite(led3, HIGH);
        delay(500);
        checkStopButton(); 
        digitalWrite(led3, LOW);
        delay(500);
        checkStopButton(); 
      }

      stage = 4;
    }

    if (stage == 4 && (currentMillis - previousMillis >= interval)) {
      previousMillis = currentMillis;
      digitalWrite(led3, HIGH); 
   
      for (int i = 0; i < 1; i++) {
        digitalWrite(led4, HIGH);
        delay(500);
        checkStopButton(); 
        digitalWrite(led4, LOW);
        delay(500);
        checkStopButton(); 
      }
      digitalWrite(led4, HIGH); 
      stage = 5;
      digitalWrite(led1, LOW);
      digitalWrite(led2, LOW);
      digitalWrite(led3, LOW);
      digitalWrite(led4, LOW);
    }

    if (stage == 5 && (currentMillis - previousMillis >= interval)) {
      previousMillis = currentMillis;

    
      for (int i = 0; i <= 3; i++) {
        digitalWrite(led1, HIGH);
        digitalWrite(led2, HIGH);
        digitalWrite(led3, HIGH);
        digitalWrite(led4, HIGH);
        delay(500);
        checkStopButton(); 
        digitalWrite(led1, LOW);
        digitalWrite(led2, LOW);
        digitalWrite(led3, LOW);
        digitalWrite(led4, LOW);
        delay(500);
        checkStopButton();
      }
      charging = false;
      setRGB(LOW, HIGH, LOW); 
    }
  }
}

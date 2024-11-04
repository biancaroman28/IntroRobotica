#include <Arduino.h>


#define RGB_RED 6
#define RGB_GREEN 4
#define RGB_BLUE 5


#define START_STOP_BUTTON 2
#define DIFFICULTY_BUTTON 3

void startButtonPressed();
void changeDifficulty();
void countdownSequence();
void startGame();
void nextWord();
void checkInput(char input);

volatile bool startCountdown = false;
volatile bool gameActive = false;
unsigned long lastDebounceTime = 0;
unsigned long debounceDelay = 50;
unsigned long gameStartTime = 0;
const unsigned long gameDuration = 30000; 
unsigned long wordStartTime = 0;
unsigned long wordTimeLimit = 10000; 

int difficultyLevel = 1; 


const char* words[] = {
  "keep", "begin", "try", "bucket", "heal", "victorious", "stormy", "available",
  "bouncy", "quickest", "noiseless", "modern", "offset", "judge", "grotesque", 
  "imprint", "encourage", "small", "farmer", "caring", "skate", "toes", "zinc", 
  "goat", "angry", "tree", "porter", "wine", "high", "capable", "adjustment", 
  "savvy", "mountainous", "terrible", "cattle", "chicken", "overflow", "crave", 
  "pets", "bridge", "drink", "laborer", "huge", "work", "known", "yawn", "legal", 
  "jam", "capture", "dream"
};

int wordCount = sizeof(words) / sizeof(words[0]);
String targetWord;
String userInput = ""; 
unsigned int correctChars = 0; 
int correctWordCount = 0;  

void setup() {
  Serial.begin(9600);

  
  pinMode(RGB_RED, OUTPUT);
  pinMode(RGB_GREEN, OUTPUT);
  pinMode(RGB_BLUE, OUTPUT);
  pinMode(START_STOP_BUTTON, INPUT_PULLUP);
  pinMode(DIFFICULTY_BUTTON, INPUT_PULLUP);

 
  digitalWrite(RGB_RED, LOW);
  digitalWrite(RGB_GREEN, LOW);
  digitalWrite(RGB_BLUE, LOW);

  
  attachInterrupt(digitalPinToInterrupt(START_STOP_BUTTON), startButtonPressed, FALLING);
  attachInterrupt(digitalPinToInterrupt(DIFFICULTY_BUTTON), changeDifficulty, FALLING);

  
  TCCR1A = 0; 
  TCCR1B = (1 << WGM12) | (1 << CS12); /// enabling CTC, sets the prescaler to 256
  OCR1A = 31250; 
  TIMSK1 |= (1 << OCIE1A); 
}

void loop() {
  
  if (gameActive) {
    if (Serial.available() > 0) {
      char inputChar = Serial.read();
      checkInput(inputChar);
    }

    
    if (millis() - gameStartTime >= gameDuration) {
      gameActive = false; 
      Serial.print("\nTime's up! You got ");
      Serial.print(correctWordCount); 
      Serial.print(" words correct!");
      digitalWrite(RGB_GREEN, LOW);
    }

    if (millis() - wordStartTime >= wordTimeLimit) {
      nextWord(); 
    }
  }


  if (startCountdown) {
    countdownSequence();
    startGame();
    startCountdown = false;
  }
}

ISR(TIMER1_COMPA_vect) {
  
}


void startButtonPressed() {
  unsigned long currentTime = millis();

  if ((currentTime - lastDebounceTime) > debounceDelay) {
    if (gameActive) {
      gameActive = false;
      Serial.println("\nGame stopped!");

      digitalWrite(RGB_RED, LOW);
      digitalWrite(RGB_GREEN, LOW);
      digitalWrite(RGB_BLUE, LOW);
    } else {
      startCountdown = true;
    }

    lastDebounceTime = currentTime;
  }
}


void changeDifficulty() {
  unsigned long currentTime = millis();

  
  if ((currentTime - lastDebounceTime) > debounceDelay) {
    if (!gameActive) {
      difficultyLevel = (difficultyLevel % 3) + 1; 

      switch (difficultyLevel) {
        case 1:
          Serial.println("\nEasy mode on!");
          wordTimeLimit = 10000; 
          break;
        case 2:
          Serial.println("\nMedium mode on!");
          wordTimeLimit = 7000; 
          break;
        case 3:
          Serial.println("\nHard mode on!");
          wordTimeLimit = 5000;
          break;
      }
    } else {
      Serial.println("\nCan't change difficulty while the game is active.");
    }

    lastDebounceTime = currentTime;
  }
}

void countdownSequence() {
  for (int i = 3; i > 0; i--) {
    Serial.println(i);

 
    digitalWrite(RGB_RED, HIGH);
    digitalWrite(RGB_GREEN, HIGH);
    digitalWrite(RGB_BLUE, HIGH);
    delay(500); 

   
    digitalWrite(RGB_RED, LOW);
    digitalWrite(RGB_GREEN, LOW);
    digitalWrite(RGB_BLUE, LOW);
    delay(500); 
  }

  Serial.println("\nGO!"); 
}

void startGame() {
  digitalWrite(RGB_RED, LOW);
  digitalWrite(RGB_GREEN, HIGH);
  digitalWrite(RGB_BLUE, LOW);

  gameStartTime = millis(); 
  correctWordCount = 0; 
  nextWord(); 
  gameActive = true;
}

void nextWord() {
 
  int randomIndex = random(0, wordCount);
  targetWord = words[randomIndex];
  Serial.print("\nType: ");
  Serial.println(targetWord);

 
  userInput ="";
  correctChars = 0; 
  wordStartTime = millis(); 
}

void checkInput(char input) {
  if (input == '\b' && userInput.length() > 0) {
    userInput.remove(userInput.length() - 1);
    correctChars = min(correctChars, userInput.length());
    Serial.print("\b \b"); 
  } else if (isPrintable(input)) {
    userInput += input;
    Serial.print(input); 

    if (userInput == targetWord.substring(0, userInput.length())) {
      digitalWrite(RGB_RED, LOW);   
      digitalWrite(RGB_GREEN, HIGH); 

      if (userInput == targetWord) {
        correctWordCount++; 
        nextWord();
      }
    } else {
      digitalWrite(RGB_GREEN, LOW); 
      digitalWrite(RGB_RED, HIGH); 
      digitalWrite(RGB_BLUE, LOW);
    }
  }
}

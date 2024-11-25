#include "GameControl.h"
#include "Buttons.h"
#include "LEDControl.h"
#include "Display.h"

Servo gameServo;
int player1Score = 0;
int player2Score = 0;
int currentPlayer = 1;
unsigned long lastUpdateTime = 0;
unsigned long reactionStartTime = 0;
const int roundDuration = 3000;  // round duration in milliseconds (3 seconds)

void initializeSerial() {
    Serial.begin(9600);
    printDebug("merge minutele");
}

void initializeSPI() {
    SPI.begin();
    pinMode(SS, OUTPUT);
    digitalWrite(SS, HIGH); // disable initial slave device
}

void initializeServo() {
    gameServo.attach(SERVO_PIN); // attach the servo to pin 6
    gameServo.write(0); // set the initial position of the servo
}

void sendCommandToSlave(int command) {
    digitalWrite(SS, LOW); // enable the slave device
    SPI.transfer(command); // send the command to the slave device
    printDebug("Sent command to slave: " + String(command));
    digitalWrite(SS, HIGH); // disable the slave device
}

void startGame() {
    displayWelcomeMessage();
    player1Score = 0;
    player2Score = 0;
    currentPlayer = 1;
    lastUpdateTime = millis();
}

void updateGame() {
    if (millis() - lastUpdateTime > roundDuration) { // check if the round has ended
        displayPauseMessage();
        lastUpdateTime = millis();
        int correctButton = random(1, 4);
        sendCommandToSlave(correctButton); // send the correct button to the slave device
        reactionStartTime = millis();

        while (true) {
            int buttonPressed = readMultiplexedButton(); // read the button pressed by the player
            unsigned long reactionTime = millis() - reactionStartTime;

            if (buttonPressed > 0) {
                if (buttonPressed == correctButton) {
                    playCorrectSound();
                    int points = calculatePoints(reactionTime);
                    
                    if (currentPlayer == 1)
                        player1Score += points;
                    else if (currentPlayer == 2)
                        player2Score += points;

                    updateScore(player1Score, player2Score);
                } 
                else
                    playIncorrectSound(); // play incorrect sound if the wrong button was pressed
                break;
            }

            // check if the reaction time has exceeded the round duration
            if (reactionTime > 3000) {
                playTimeoutSound();
                break;
            }
        }

        // if the servo has not reached the end position, you can move it
        if (gameServo.read() < 180)
            gameServo.write(gameServo.read() + 10);

        // if the servo has reached the end position, display the winner
        if (gameServo.read() >= 180) {
            displayWinner(player1Score > player2Score ? 1 : 2);
            gameServo.write(0);
        }

        currentPlayer = (currentPlayer == 1) ? 2 : 1; // switch players
    }
}

int calculatePoints(unsigned long reactionTime) {
    if (reactionTime <= 500)
        return 3; // 3 points for reaction time less than 500 ms
    else if (reactionTime <= 1000)
        return 2; // 2 points for reaction time between 500 ms and 1 second
    else
        return 1; // 1 point for reaction time greater than 1 second
}

void printDebug(String message) {
    Serial.println(message);
}

void playCorrectSound() {
    tone(BUZZER_PIN, 1000, 200);
}

void playIncorrectSound() {
    tone(BUZZER_PIN, 400, 200);
}

void playTimeoutSound() {
    tone(BUZZER_PIN, 200, 200);
}
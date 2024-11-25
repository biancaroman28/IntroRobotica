#include "LEDControl.h"

void initializeRGBLEDs() {
    // Player 1 RGB LED pins
    pinMode(PLAYER1_RED, OUTPUT);
    pinMode(PLAYER1_GREEN, OUTPUT);
    pinMode(PLAYER1_BLUE, OUTPUT);

    // Player 2 RGB LED pins
    pinMode(PLAYER2_RED, OUTPUT);
    pinMode(PLAYER2_GREEN, OUTPUT);
    pinMode(PLAYER2_BLUE, OUTPUT);
}

void initializeButtonLEDs() {
    // initialize the button LEDs
    pinMode(LED1_PIN, OUTPUT);
    pinMode(LED2_PIN, OUTPUT);
    pinMode(LED3_PIN, OUTPUT);
    pinMode(LED4_PIN, OUTPUT);
    pinMode(LED5_PIN, OUTPUT);
    pinMode(LED6_PIN, OUTPUT);

    // turn on all button LEDs
    digitalWrite(LED1_PIN, HIGH);
    digitalWrite(LED2_PIN, HIGH);
    digitalWrite(LED3_PIN, HIGH);
    digitalWrite(LED4_PIN, HIGH);
    digitalWrite(LED5_PIN, HIGH);
    digitalWrite(LED6_PIN, HIGH);
}

void blinkLED(int pin) {
    for (int i = 0; i < 3; i++) {
        digitalWrite(pin, HIGH);
        delay(200);
        digitalWrite(pin, LOW);
        delay(200);
    }
}

void setRGBColor(int redPin, int greenPin, int bluePin, int color) {
    digitalWrite(redPin, color == 1); // 1 - RED
    digitalWrite(greenPin, color == 2); // 2 - GREEN
    digitalWrite(bluePin, color == 3); // 3 - BLUE
}

void setPlayerRGBColor(int player, int color) {
    if (player == 1)
        setRGBColor(PLAYER1_RED, PLAYER1_GREEN, PLAYER1_BLUE, color);
    else if (player == 2)
        setRGBColor(PLAYER2_RED, PLAYER2_GREEN, PLAYER2_BLUE, color);
}

void turnOffRGB(int redPin, int greenPin, int bluePin) {
    digitalWrite(redPin, LOW);
    digitalWrite(greenPin, LOW);
    digitalWrite(bluePin, LOW);
}

void turnOffPlayerRGB(int player) {
    if (player == 1)
        turnOffRGB(PLAYER1_RED, PLAYER1_GREEN, PLAYER1_BLUE);
    else if (player == 2)
        turnOffRGB(PLAYER2_RED, PLAYER2_GREEN, PLAYER2_BLUE);
}
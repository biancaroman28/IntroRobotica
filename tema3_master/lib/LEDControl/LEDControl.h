#ifndef LEDCONTROL_H
#define LEDCONTROL_H

#include <Arduino.h>

// Button LED pin
#define LED1_PIN A1
#define LED2_PIN A2
#define LED3_PIN A3
#define LED4_PIN A4
#define LED5_PIN A5
#define LED6_PIN 7

// Player 1 RGB LED pins
#define PLAYER1_RED 6
#define PLAYER1_GREEN 4
#define PLAYER1_BLUE 5

// Player 2 RGB LED pins
#define PLAYER2_RED 3
#define PLAYER2_GREEN 1
#define PLAYER2_BLUE 2

void initializeRGBLEDs();
void initializeButtonLEDs();
void setPlayerRGBColor(int player, int color);
void turnOffPlayerRGB(int player);
void setRGBColor(int redPin, int greenPin, int bluePin, int color);
void turnOffRGB(int redPin, int greenPin, int bluePin);
void blinkLED(int pin);

#endif
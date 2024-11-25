#ifndef GAMECONTROL_H
#define GAMECONTROL_H

#define BUZZER_PIN 9 // buzzer pin for playing sounds
#define SERVO_PIN 6 // servo pin for moving the button

#include <Arduino.h>
#include <Servo.h>
#include <SPI.h>

void initializeSerial();
void initializeServo();
void startGame();
void updateGame();
int calculatePoints(unsigned long reactionTime);
void playCorrectSound();
void playIncorrectSound();
void playTimeoutSound();
void initializeSPI();
void sendCommandToSlave(int command);
void printDebug(String message);

#endif
#ifndef BUTTONS_H
#define BUTTONS_H

#include <Arduino.h>

#define BUTTON_PIN A0 // analog pin for reading the buttons

void initializeButtons(); // uses the A0 pin to read the buttons
int readMultiplexedButton();

#endif

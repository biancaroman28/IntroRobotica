#include "Buttons.h"

// because the buttons are multiplexed, we define thresholds for each button
#define BUTTON1_THRESHOLD 200
#define BUTTON2_THRESHOLD 400
#define BUTTON3_THRESHOLD 600

#define DEBOUNCE_DELAY 50 
#define NO_BUTTON_PRESSED -1 // default value for no button pressed

void initializeButtons() {
    pinMode(BUTTON_PIN, INPUT_PULLUP);
}

int readMultiplexedButton() {
    static int lastButton = NO_BUTTON_PRESSED; // last button pressed
    static unsigned long lastDebounceTime = 0;

    int buttonValue = analogRead(BUTTON_PIN);
    int detectedButton = NO_BUTTON_PRESSED;

    if (buttonValue < BUTTON1_THRESHOLD) {
        detectedButton = 1; // button 1 is pressed
    } 
    else if (buttonValue < BUTTON2_THRESHOLD) {
        detectedButton = 2; // button 2 is pressed
    } 
    else if (buttonValue < BUTTON3_THRESHOLD) {
        detectedButton = 3; // button 3 is pressed
    }

    if (detectedButton != lastButton) {
        lastDebounceTime = millis(); // reset the debounce timer
    }

    if ((millis() - lastDebounceTime) > DEBOUNCE_DELAY) {
        // if the button value has been stable for a while
        if (detectedButton != lastButton) {
            lastButton = detectedButton;
            return detectedButton;
        }
    }

    return NO_BUTTON_PRESSED;
}
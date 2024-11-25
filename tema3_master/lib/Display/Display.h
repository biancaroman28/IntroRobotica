#ifndef DISPLAY_H
#define DISPLAY_H

#include <LiquidCrystal.h>

// LCD pins
#define RS 8
#define E 7
#define D4 6
#define D5 5
#define D6 4
#define D7 3

void initializeLCD();
void displayWelcomeMessage();
void updateScore(int player1Score, int player2Score);
void displayWinner(int player);
void displayPauseMessage();

#endif
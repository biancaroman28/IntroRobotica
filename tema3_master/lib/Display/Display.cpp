#include "Display.h"

LiquidCrystal lcd(RS, E, D4, D5, D6, D7);

void initializeLCD() {
    lcd.begin(16, 2); // 16x2 LCD display
}

void displayWelcomeMessage() {
    lcd.clear();
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Loading.");
    delay(500);
    lcd.print(".");
    delay(500);
    lcd.print(".");
    delay(500);
    lcd.print("Welcome!");
}

void updateScore(int player1Score, int player2Score) {
    lcd.setCursor(0, 0); // write the score of the first player on the first row
    lcd.print("P1: ");
    lcd.print(player1Score);
    lcd.setCursor(0, 1); // write the score of the second player on the second row
    lcd.print("P2: ");
    lcd.print(player2Score);
}

void displayWinner(int player) {
    lcd.clear();
    if (player == 1)
        lcd.print("Player 1 wins!");
    else if (player == 2)
        lcd.print("Player 2 wins!");
    lcd.print(player);
}

void displayPauseMessage() {
    lcd.clear();
    lcd.print("Next Round...");
    delay(2000); // pause of 2 seconds
}
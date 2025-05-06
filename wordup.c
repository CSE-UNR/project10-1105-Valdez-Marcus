// Marcus Valdez
// Project 10 
// 4-29-2025

#include <stdio.h>
#include <stdbool.h>

#define MAXGUESSES 6
#define WORDLENGTH 5

void loadWord(char *filename, char *word);
bool isValid(const char *guess);
void showPrevGuesses(const char guesses[MAXGUESSES][WORDLENGTH + 1], int guessCount);
void giveFeedback(const char *guess, const char *mysteryWord);
void getGuess(char *guess, int guessNumber);
bool checkWin(const char *guess, const char *mysteryWord);
bool isAlpha(char c);
void toLower(char *str);
bool inWord(char c, const char *word);

int main() {
    char mysteryWord[WORDLENGTH + 1];
    char guesses[MAXGUESSES][WORDLENGTH + 1];
    int guessCount = 0;
    bool won = false;

    loadWord("mystery.txt", mysteryWord);

    while (guessCount < MAXGUESSES && !won) {
        char guess[WORDLENGTH + 1];

        getGuess(guess, guessCount + 1);

        for (int i = 0; i < WORDLENGTH; i++) {
            guesses[guessCount][i] = guess[i];
        }
        guesses[guessCount][WORDLENGTH] = '\0';

        showPrevGuesses(guesses, guessCount);
        giveFeedback(guess, mysteryWord);

        won = checkWin(guess, mysteryWord);

        if (!won) {
            guessCount++;
        }
    }

    if (won) {
        printf("You won in %d guesses!\n", guessCount + 1);
        printf("Amazing!\n");
    } else {
        printf("You lost, better luck next time!\n");
        printf("The mystery word was: %s\n", mysteryWord);
    }

    return 0;
}

void loadWord(char *filename, char *word) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error opening file!\n");
    }
    for (int i = 0; i < WORDLENGTH; i++) {
        word[i] = fgetc(file);
    }
    word[WORDLENGTH] = '\0';
    fclose(file);
}

bool isValid(const char *guess) {
    for (int i = 0; i < WORDLENGTH; i++) {
        if (guess[i] == '\0') return false;
    }

    for (int i = 0; i < WORDLENGTH; i++) {
        if (!isAlpha(guess[i])) {
            return false;
        }
    }
    return true;
}

void showPrevGuesses(const char guesses[MAXGUESSES][WORDLENGTH + 1], int guessCount) {
    printf("Previous guesses:\n");
    for (int i = 0; i < guessCount; i++) {
        printf("%s\n", guesses[i]);
    }
}

void giveFeedback(const char *guess, const char *mysteryWord) {
    for (int i = 0; i < WORDLENGTH; i++) {
        if (guess[i] == mysteryWord[i]) {
            printf("%c", guess[i] - 32);
        } else if (inWord(guess[i], mysteryWord)) {
            printf("%c", guess[i]);
        } else {
            printf("%c", guess[i]);
        }
    }
    printf("\n");

    for (int i = 0; i < WORDLENGTH; i++) {
        if (guess[i] != mysteryWord[i] && inWord(guess[i], mysteryWord)) {
            printf("^");
        } else {
            printf(" ");
        }
    }
    printf("\n");
}

void getGuess(char *guess, int guessNumber) {
    bool valid = false;
    while (!valid) {
        printf("Guess %d! Enter your guess: ", guessNumber);
        for (int i = 0; i < WORDLENGTH; i++) {
            guess[i] = getchar();
        }
        guess[WORDLENGTH] = '\0';

        while (getchar() != '\n');

        toLower(guess);

        if (isValid(guess)) {
            valid = true;
        } else {
            printf("Your guess must be 5 letters long.\n");
        }
    }
}

bool checkWin(const char *guess, const char *mysteryWord) {
    for (int i = 0; i < WORDLENGTH; i++) {
        if (guess[i] != mysteryWord[i]) {
            return false;
        }
    }
    return true;
}

bool isAlpha(char c) {
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}

void toLower(char *str) {
    for (int i = 0; i < WORDLENGTH; i++) {
        if (str[i] >= 'A' && str[i] <= 'Z') {
            str[i] = str[i] + 32;
        }
    }
}

bool inWord(char c, const char *word) {
    for (int i = 0; i < WORDLENGTH; i++) {
        if (c == word[i]) {
            return true;
        }
    }
    return false;
}


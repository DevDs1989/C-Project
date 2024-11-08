#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>

#define NORMAL "\033[0m"
#define RED "\033[31m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"

bool gameLogic(char *, char *);

int main() {
    char randWord[6];  // Updated to hold 5 characters + null terminator
    char userGuess[6];
    FILE *dictFile;
    dictFile = fopen("dictionary.txt", "r");
    if (dictFile == NULL) {
        printf("Error opening file\n");
        return 1;
    }
    
    srand(time(NULL));

    int count = 0;
    for (char c = getc(dictFile); c != EOF; c = getc(dictFile)) {
        if (c == '\n') {
            count++;
        }
    }
    if (count == 0) {
        printf("\nFile is empty\n");
        fclose(dictFile);
        return 1;
    }

    int randomLine = rand() % count;
    rewind(dictFile);

    int currentLine = 0;
    bool foundWord = false;

    while (!foundWord && fgets(randWord,5, dictFile) != NULL) {
        if (currentLine == randomLine) {
            randWord[strcspn(randWord, "\n")] = '\0';  
            foundWord = true;
        }
        currentLine++;
    }

    fclose(dictFile);

    printf("\nSize of Word: %d\n", (int)strlen(randWord));
    printf("\n6 Tries\n");

    for (int i = 0; i < 6; i++) {
        printf("\nEnter Your Guess:\n");
        scanf("%s", userGuess);  
        if (gameLogic(randWord, userGuess)) {
            printf(GREEN "\nYou Win!\n" NORMAL);
            return 0;
        }
    }

    printf(RED "\nYou Lose\n" NORMAL);
    printf("Correct Word was %s\n", randWord);
    return 0;
}

bool gameLogic(char* randWord, char* userGuess) {
    int guessType[5] = {0};      // 0 = No match, 1 = Exact match, 2 = Partial match
    bool matchedRand[5] = {false}; // Tracks matched letters in randWord
    bool winner = true;

    if (strlen(userGuess) != 5) {
        printf("\nWrong number of letters entered\n");
        return false;
    }

    // Check for exact matches
    for (int i = 0; i < 5; i++) {
        if (randWord[i] == userGuess[i]) {
            guessType[i] = 1;
            matchedRand[i] = true;
        } else {
            winner = false;
        }
    }

    // Check for partial matches
    for (int i = 0; i < 5; i++) {
        if (guessType[i] == 0) { // Only check if not already an exact match
            for (int j = 0; j < 5; j++) {
                if (!matchedRand[j] && userGuess[i] == randWord[j]) {
                    guessType[i] = 2;
                    matchedRand[j] = true;
                    break;
                }
            }
        }
    }

    // Print guess with color coding
    for (int i = 0; i < 5; i++) {
        if (guessType[i] == 1) {
            printf(GREEN "%c" NORMAL, userGuess[i]);
        } else if (guessType[i] == 2) {
            printf(YELLOW "%c" NORMAL, userGuess[i]);
        } else if(guessType[i] =0 )
        {
            printf(RED "%c" NORMAL, userGuess[i]);
        }
    }
    printf("\n");

    return winner;
}

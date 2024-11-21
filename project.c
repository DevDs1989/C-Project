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

int main()
{
  char randWord[10];
  char userGuess[10];

  int tries = 6;

  FILE *dictFile;
  dictFile = fopen("dictionary.txt", "r");
  srand(time(NULL));

  int count = 0;
  for (char c = getc(dictFile); c != EOF; c = getc(dictFile))
  {
    if (c == '\n')
    {
      count++;
    }
  }
  if (count == 0)
  {
    printf("\nFile is empty\n");
  }


  int randomLine = rand() % count + 1;
  int currentLine = 0;
  bool foundWord = false;
  rewind(dictFile);

  while (!foundWord)
  {
    fgets(randWord, sizeof(randWord), dictFile);
    if (currentLine == randomLine)
    {
      fscanf(dictFile, "%s", randWord);
      foundWord = true;
    }
    currentLine++;
  }

  printf("\nSize of Word: %d\n", strlen(randWord));
  printf("\n%d Tries\n", tries);

  for (int i = 0; i < tries; i++)
  {
    printf("\nEnter Your Guess:\n");
    scanf("%s", userGuess);
    if (gameLogic(randWord, userGuess))
    {
      printf(GREEN "\nYou Win\n" NORMAL);
      fclose(dictFile);
      return 0;
    }
  }
  printf(RED "\nYou Lose\n" NORMAL);
  printf("\nCorrect Word was %s\n", randWord);
  fclose(dictFile);

  return 0;
}

bool gameLogic(char *randWord, char *userGuess)
{

  // guessType key:
  //  0 = Not a Match
  //  1 = Percect Match
  //  2 = Partial Match
  int guessType[5];
  bool matchCondition[5];
  bool winner = false;
  int counter = 0;

  if (strlen(userGuess) != 5)
  {
    printf("\nWrong number of letters entered\n");
    return false;
  }

  for (int i = 0; i < strlen(userGuess); i++)
  {
    guessType[i] = 0;
    matchCondition[i] = false;
  }

  // For Perfect Matches
  for (int i = 0; i < 5; i++)
  {
    if (randWord[i] == userGuess[i])
    {
      guessType[i] = 1;
      matchCondition[i] = true;
      counter++;
    }
  }

  if (counter == 5)
  {
    winner = true;
  }
  else
  {
    for (int i = 0; i < 5; i++)
    {
      if (guessType[i] == 0)
      {
        for (int j = 0; j < 5; j++)
        {
          if (!matchCondition[j] && userGuess[i] == randWord[j])
          {
            guessType[i] = 2;
            matchCondition[j] = true;
            break;
          }
        }
      }
    }
  }
  for (int i = 0; i < strlen(userGuess); i++)
  {
    if (guessType[i] == 0)
    {
      printf(RED "%c" NORMAL, userGuess[i]);
    }
    else if (guessType[i] == 1)
    {
      printf(GREEN "%c" NORMAL, userGuess[i]);
    }
    else if (guessType[i] == 2)
    {
      printf(YELLOW "%c" NORMAL, userGuess[i]);
    }
  }
  return winner;
}

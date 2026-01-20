/* Contains a Rock, Paper, Scissors, Lizard, Spock minigame for MyASCIIPet
 * program when play() function is called. */
#include <stdio.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>
#include "pet.h"

enum ThrownHand { ROCK, PAPER, SCISSORS, LIZARD, SPOCK };
enum ThrownHand inputToThrow(char input);
const char* enumToString(enum ThrownHand hand);
enum ThrownHand getCPUThrow();

void minigame(struct Pet* pet)
{
    srand((unsigned int)time(NULL)); //seed time for randomness

    int playerWins = 0, cpuWins = 0, tie = 0;
    char userChoice = 'y';
    enum ThrownHand playerThrow = -1;
    enum ThrownHand cpuThrow;

    printf("%s wants to try Rock Paper Scissors Lizard Spock!\n", pet->name);

    while (userChoice != 'n' && userChoice != 'N')
    {
        puts("\nThe current score is");
        printf("Player - %d Computer - %d Tie - %d\n",
            playerWins, cpuWins, tie);
        printf("(R)ock, (P)aper, (S)cissors, "
            "(L)izard, or Spoc(k)? ");
        scanf(" %c", &userChoice);
        playerThrow = inputToThrow(userChoice);

        while (playerThrow == -1) /* checks invalid choice */
        {
            printf( "Invalid choice.\n"
                    "(R)ock, (P)aper, (S)cissors? "
                    "(L)izard, or Spoc(k)? ");
            scanf(" %c", &userChoice);
            playerThrow = inputToThrow(userChoice);
        }
        cpuThrow = getCPUThrow();

        printf("You chose %s, %s chose %s.\n",
            enumToString(playerThrow), pet->name, enumToString(cpuThrow));
        sleep(1);

        if (playerThrow == cpuThrow) {
            puts("It's a tie!");
            ++tie;
        }
        else if ((playerThrow == ROCK && cpuThrow == SCISSORS)
                || (playerThrow == ROCK && cpuThrow == LIZARD)
                || (playerThrow == PAPER && cpuThrow == ROCK)
                || (playerThrow == PAPER && cpuThrow == SPOCK)
                || (playerThrow == SCISSORS && cpuThrow == PAPER)
                || (playerThrow == SCISSORS && cpuThrow == LIZARD)
                || (playerThrow == LIZARD && cpuThrow == SPOCK)
                || (playerThrow == LIZARD && cpuThrow == PAPER)
                || (playerThrow == SPOCK && cpuThrow == ROCK)
                || (playerThrow == SPOCK && cpuThrow == SCISSORS)) {
            puts("You win!");
            ++playerWins;
        } else {
            puts("You lose!");
            ++cpuWins;
        }
        printf("Do you want to play again? (y/n) ");
        scanf(" %c", &userChoice);
    }
}

enum ThrownHand inputToThrow(char input)
{
    switch (input)
    {
        case 'r':
        case 'R':
            return ROCK;
        case 'p':
        case 'P':
            return PAPER;
        case 's':
        case 'S':
            return SCISSORS;
        case 'l':
        case 'L':
            return LIZARD;
        case 'k':
        case 'K':
            return SPOCK;
        default:
            return -1; /* invalid value */
    }
}

const char* enumToString(enum ThrownHand hand)
{
    switch (hand)
    {
    case ROCK:
        return "Rock";
    case PAPER:
        return "Paper";
    case SCISSORS:
        return "Scissors";
    case LIZARD:
        return "Lizard";
    case SPOCK:
        return "Spock";
    default:
        return "Unknown";
    }
}

enum ThrownHand getCPUThrow() {
    return (enum ThrownHand)(rand() % 5); /*range 0-5 for enums*/
}

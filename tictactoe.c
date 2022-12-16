//Tic Tac Toe game between 2 players or player vs computer

#include <stdio.h>
#include "tictactoe.h"

int main() {
    char playAgain = 'n';
    do {
    char turn = 'X';
    int game = 0;
    int turns = 0;
    int playerCounter = 1;
    char board[] = { '-', '-', '-', '-', '-', '-', '-', '-', '-' };
    //Display the Intro to the game
    printf("\n===========================");
    printf("\nWELCOME TO TIC TAC TOE!");
    printf("\n1 --- person vs. person");
    printf("\n2 --- person vs. computer");
    printf("\nEnter your choice (1 or 2):");
    scanf("%d", &game);
    printf("\nYou have entered choice %d", game);
    printf("\nThe current status is:\n");
    //Game begins and loops until result has been decided. (Winner or draw)
    while (resultCheck(board) == 0) {
        table(board);
        //Offers player a choice based on what simulation they chose.
        playerChoice(board, &turn, &game);
        turns++;
        playerCounter++;
        //Checks every loop to see if there is a winner after the choice.
        if (resultCheck(board)) {
            table(board);
            if(playerCounter % 2 == 0)
                printf("Awesome! Player1 Wins!\n");
            if(playerCounter % 2 == 1)
                printf("Awesome! Player2 Wins!\n");
        }
        if (drawCheck(turns)) {
            printf("Tie.\n");
        }
        switch_turn(&turn);
    }
    printf("Would you like to play again? (y/n): \n");
    playAgain = getchar();
    } while (playAgain == 'y' || playAgain == 'Y');
}
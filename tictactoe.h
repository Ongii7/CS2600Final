#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

//display the table to show the status of the game
void table(char board[]) {
    int i;
    printf("+-----+\n");
    for (i = 0; i < 9; i++){
        printf("|%c", board[i]);
        if (((i + 1) % 3) == 0) {
            printf("|\n+-----+\n");
        }
    }
}

//Switches the turn over to next player or computer
void switch_turn(char *turn){
    if (*turn == 'X') 
        *turn = 'O';
    else
        *turn = 'X';
}

//What choice the players will make, depending on what version they choose (PlayervsPlayer or PlayervsComputer)
void playerChoice(char board[], char *turn, int *game) {
    int choice;
    int upper = 9;
    int lower = 1;
    if(*turn == 'X'){
        printf("\nPlayer1: make your move: (Choose a number 1-9 for the board #.)");
        scanf("%d", &choice);
            if(board[choice - 1] != '-') {
                while(board[choice - 1] != '-') {
                    printf("\nError! Square already filled. Pick a different square. (1-9):\n");
                    scanf("%d", &choice);
                }
            }
    }
    if(*turn == 'O'){
        //Player chose Simulation vs Player2, second player can add in their inputs 1-9.
        if(*game == 1){
        printf("\nPlayer2: make your move: (Choose a number 1-9 for the board #.)");
        scanf("%d", &choice);
            if(board[choice - 1] != '-') {
                while(board[choice - 1] != '-') {
                    printf("\nError! Square already filled. Pick a different square. (1-9):\n");
                    scanf("%d", &choice);
                }
            }
        }
        //Player chose Simulation vs Computer, use random inputs for computer input 1-9.
        if(*game == 2){
            printf("\nComputer: make your move:\n");
            choice = (rand() % (upper - lower + 1)) + lower;
            if(board[choice - 1] != '-') {
                while(board[choice - 1] != '-') {
                    choice = (rand() % (upper - lower + 1)) + lower;
                }
            }
        }
    }
    //if board has an empty spot then player choice is allowed.
    board[choice - 1] = *turn;
}

//to check if player won, check horizontal win: (0-2) (3-5) (6-9)
//vertical win: (0 3 6) (1 4 7) (2 5 8)
//diagonal win: (0 4 8) (2 4 6)
bool resultCheck(char board[]) {
    bool win = false;
    //Row check
    if (board[0] != '-') {
        if (board[0] == board[1] && board[0] == board[2])
            win = true;;
    }
    if (board[3] != '-') {
        if (board[3] == board[4] && board[3] == board[5])
            win = true;;
    }
    if (board[6] != '-') {
        if (board[6] == board[7] && board[6] == board[8])
            win = true;;
    }
    //Column check
    if (board[0] != '-') {
        if (board[0] == board[3] && board[0] == board[6])
            win = true;;
    }
    if (board[2] != '-') {
        if (board[2] == board[4] && board[2] == board[7])
            win = true;
    }
    if (board[3] != '-') {
        if (board[3] == board[5] && board[3] == board[8])
            win = true;
    }
    //Diagonal check
    if (board[0] != '-') {
        if (board[0] == board[4] && board[0] == board[8])
            win = true;
    }
    if (board[2] != '-') {
        if (board[2] == board[4] && board[2] == board[6])
            win = true;
    }
    return win;
}

//check if the game is a draw. (No more moves to be made.)
bool drawCheck(int turns) {
    if (turns < 9) {
        return false;
    }
    else {
        return true;
    }
}
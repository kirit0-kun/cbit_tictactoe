#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

#include "game.h"

int main(int argc, char const *argv[]) {
    Board* board = create_board();
    int turns = 0;
    int player = X;
    char * error = "";
    while (1)
    {
        //print_bits(board, get_board_size(board)*BITS_IN_BYTE);
        print_board(board);
        printf("%s", error);
        int index = get_move(player);
        if (index <= 0 || index > get_board_size(board)) {
            error = "Select a valid cell\n";
            continue;
        }
        if (!IS(get_cell(board, index),EMPTY)) {
            error = "Select an empty cell\n";
            continue;
        }
        error = "";
        set_cell(board, index, player);
        int temp = get_winner(board);
        char c[20];
        int win = get_player_name(temp, c);
        if (win == 0) {
            print_board(board);
            printf("Player %s won!\n", c);
            break;
        }
        player = player == X ? O : X;
        player = CLAMP(player, X, O);
        turns++;
        if (turns >= get_board_size(board)) {
            printf("Draw!\n");
            break;
        }
    }
    
    destroy_board(board);
    return 0;
}


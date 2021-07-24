#ifndef GAME_HEADER
#define GAME_HEADER
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <math.h>
#include "bit_utils.h"
#include "utils.h"

#define LEN 34
#define ROWS LEN
#define COLS LEN
#define CELL_SIZE 2

#define EMPTY 0b0
#define X 0b01
#define O 0b10
#define INV 0b11

typedef struct Board Board;

Board* create_board();
void destroy_board(Board* board);
void set_cell(Board* board, int cell, int value);
uint8_t get_cell(Board* board, int cell);
uint8_t get_winner(Board* board);
uint64_t get_board_size(Board* board);
int get_player_name(int player, char* output);
int get_move(int player);
void print_board(Board* board);

#endif //GAME_HEADER
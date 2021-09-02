#include "../headers/game.h"

#define NAME_BUF_SIZE 20
#define MOVE_BUF_SIZE 10

const int BOARD_SIZE = ROWS * COLS;

const int BOARD_SIZE_BITS = BOARD_SIZE * CELL_SIZE;

typedef struct Board{
    uint8_t data[0];
} Board;

Board* create_board() {
    uint8_t size = ceil(BOARD_SIZE_BITS/BITS_IN_BYTE)+1;
    Board* board = malloc(size * sizeof(uint8_t));
    memset(board, 0, size);
    return board;
}

void destroy_board(Board* board) {
    free(board);
}

void set_cell(Board* board, int cell, int value) {
    set_bits(board, cell-1, value, CELL_SIZE);
}

uint8_t get_cell(Board* board, int cell) {
    return get_bits(board, cell-1, CELL_SIZE);
}

uint64_t get_board_size(Board* board) {
    return BOARD_SIZE;
}

uint8_t get_winner(Board* board) {
    const int c = ROWS + COLS + 2;
    const int size = c * CELL_SIZE / BITS_IN_BYTE;
    uint8_t cells[size];
    memset(&cells, UINT8_MAX, size);
    int ldIndex = ROWS + COLS;
    int rdIndex = ldIndex + 1;
    for (int row = 0; row < ROWS; row++) {
        int rowIndex = row;
        for (int col = 0; col < COLS; col++) {
            int colIndex = ROWS + col;
            int cellIndex = row * ROWS + col + 1;
            int cellValue = get_cell(board, cellIndex);

            int oldRowValue = get_bits(&cells, rowIndex, CELL_SIZE);
            int newRowValue = (col == 0 ? INV : oldRowValue) & cellValue;
            set_bits(&cells, rowIndex, newRowValue, CELL_SIZE);

            int oldColValue = get_bits(&cells, colIndex, CELL_SIZE);
            int newColValue = (row == 0 ? INV : oldColValue) & cellValue;
            set_bits(&cells, colIndex, newColValue, CELL_SIZE);

            int firstDiag = row == 0;
            if (row == col) {
                int oldValue = get_bits(&cells, ldIndex, CELL_SIZE);
                int newLDValue = (firstDiag ? INV : oldValue) & cellValue;
                set_bits(&cells, ldIndex, newLDValue, CELL_SIZE);
            }
            if ((row+col+1) == ROWS || (row == col && ROWS % 2 != 0 && ROWS/2 == row)) {
                int oldValue = get_bits(&cells, rdIndex, CELL_SIZE);
                int newRDValue = (firstDiag ? INV : oldValue) & cellValue;
                set_bits(&cells, rdIndex, newRDValue, CELL_SIZE);
            }
            
        }
        int rowValue = get_bits(&cells, rowIndex, CELL_SIZE);
        if (IS(rowValue, X)) {
            return X;
        } else if (IS(rowValue, O)) {
            return O;
        }
    }
    for (int cell = ROWS; cell < c; cell++) {
        int value = get_bits(&cells, cell, CELL_SIZE);
        if (IS(value, X)) {
            return X;
        } else if (IS(value, O)) {
            return O;
        }
    }
    return EMPTY;
}

int get_player_name(int player, char* output) {
    char* playerStr;
    if (IS(player, X)) {
        playerStr = "X";
    } else if (IS(player, O)) {
        playerStr = "O";
    } else {
        return -1;
    }
    strcpy(output, playerStr);
    return 0;
}

int get_move(int player) {
    char playerStr[NAME_BUF_SIZE];
    CHECK(get_player_name(player, playerStr));
    printf("%s your move: ", playerStr);
    char input[MOVE_BUF_SIZE];
    fgets(input, MOVE_BUF_SIZE, stdin);
    if (strncmp(input, "q", 1) == 0) {
        exit(0);
        return -1;
    }
    return atoi(input);
}

void print_board(Board* board) {
    int totalCells = COLS*ROWS;
    int cellSpace = ceil(log10(totalCells));
    int boardSize = COLS*ROWS*(1+cellSpace) + 2*COLS + ROWS;
    char* boardString = malloc(boardSize);
    memset(boardString, 0, boardSize);

    char frmt[cellSpace];
    sprintf(frmt, "%%-%d-s", cellSpace);

    for (int row = 0; row < ROWS; row++) {
        for (int col = 0; col < COLS; col++) {
            boardString = strcat(boardString, "|");
            int cellIndex = row * ROWS + col + 1;
            int cellValue = get_cell(board, cellIndex);

            char s[NAME_BUF_SIZE];
            int c = get_player_name(cellValue, s);

            if (c != 0) {
                sprintf(s, "%d", cellIndex);
            }
            
            sprintf(s, frmt, s);
            boardString = strcat(boardString, s);
        }
        boardString = strcat(boardString, "|\n");
    }
    
    const int borderSize = COLS*(cellSpace+1)+1;

    char* borderString = malloc(borderSize+1);
    memset(borderString, '-', borderSize);

    fpurge(stdout);
    fputs("\033c", stdout);
    printf("%s\n%s%s\n",borderString, boardString, borderString);

    free(boardString);
    free(borderString);
}


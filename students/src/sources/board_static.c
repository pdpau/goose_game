#include <stdlib.h>
#include <stdio.h>

#include "../headers/board_static.h"

// TODO: Initializes the board, initializing also each square of it.
int init_board(Board* board, int rows, int columns) {
    board->rows = rows;
    board->columns = columns;

    if ((rows < 1) || (rows > MAX_ROWS)) {
        return ERROR;
    }
    if ((columns < 2) || (columns > MAX_COLUMNS)) {
        return ERROR;
    }

    // INICIALIZAR Y DIBUJAR CASILLAS
    //int num_of_squares = rows*columns;
    Square sq;
    int intercambio = 1;
    for (int i = 0; i <= rows; i++) {
        int pos = intercambio;
        while (pos < (intercambio + columns)) {
            init_square(&sq, pos); //??
            //printf("[%d]", sq.position); //imprimir tablero per pantalla
            pos++;
        }
        intercambio = pos;
        printf("\n");
    }
    return SUCCESS;
}

// DONE: Returns the number of rows of the board.
int get_rows(Board* board) {
    return board->rows;
}

// DONE: Sets the number of rows of the board.
void set_rows(Board* board, int rows) {
    board->rows = rows;
}

// DONE: Return the number of columns of the board.
int get_columns(Board* board) {
    return board->columns;
}

// DONE: Sets the number of columns of the board.
void set_columns(Board* board, int columns) {
    board->columns = columns;
}

// DONE: Returns the size of the board, it is, the total number of squares.
int get_size(Board* board) {
    int r = get_rows(board);
    int c = get_columns(board);
    int num_of_squares = r*c;
    return num_of_squares;
}

// DONE: Returns the board square at the specific position.
Square* get_square_at(Board *board, int position) {
    if ((position >= 0) && (position < get_size(board))) {
        return &board->squares[position];
    } else {
        return NULL;
    }
}

// DONE: Given a board, a square type, a starting position and a reverse flag, search for the
//  next square starting from the starting position that has the required square type. If the
//  'reverse' flag is false, the search is incremental, if 'reverse' is true, the search is
//  decremental.
int find_square_by_type(Board *board, SquareType type, int starting_position, bool reverse) {
    int r = get_rows(board);
    int c = get_columns(board);
    int last_square_pos = r*c;

    if (reverse == false) {
        // incremental
        for (int i = starting_position+1; i < last_square_pos; i++) {
            Square* sq = get_square_at(board, i);
            if (get_type(sq) == type) {
                return sq->position;
            }
        }
        return -1;
    } else {
        // decremental
        for (int i = starting_position-1; i > 0; i--) {
            Square* sq = get_square_at(board, i);
            if (get_type(sq) == type) {
                return sq->position;
            }
        }
        return -1;
    }
}

// TODO: Nothing.

/**
 * Pre: -
 * Post: -
 *
 * Frees the allocated resources. Since this is the static implementation,
 * this is managed automatically.
 *
 * @param board The board to be freed.
 */
void free_board(Board* board) {
    // Nothing to do here for the static version
}
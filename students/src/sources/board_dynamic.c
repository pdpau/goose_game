#include <stdlib.h>

#include "../headers/board_dynamic.h"

// Initializes the board, allocating the required space, and initializing also each square of it.
int init_board(Board* board, int rows, int columns) {
    if ((rows < 1) || (rows > MAX_ROWS) || (columns < 2) || (columns > MAX_COLUMNS)) {
        return ERROR;
    } else {
        set_rows(board, rows);
        set_columns(board, columns);
    }
    // INICIALIZAR Y DIBUJAR CASILLAS
    board->squares = (Square*) malloc(sizeof(Square)*(rows*columns));

    for (int i = 0; i < rows*columns; i++) {
        init_square(&board->squares[i], i); // comencem a la posició 0
    }

    return SUCCESS;
}


// FUNCIONS DEL BOARD_STATIC

// Returns the number of rows of the board.
int get_rows(Board* board) {
    return board->rows;
}

// Sets the number of rows of the board.
void set_rows(Board* board, int rows) {
    board->rows = rows;
}

// Return the number of columns of the board.
int get_columns(Board* board) {
    return board->columns;
}

// Sets the number of columns of the board.
void set_columns(Board* board, int columns) {
    board->columns = columns;
}

// Returns the size of the board, it is, the total number of squares.
int get_size(Board* board) {
    int r = get_rows(board);
    int c = get_columns(board);
    int num_of_squares = r*c;
    return num_of_squares;
}

// Returns the board square at the specific position.
Square* get_square_at(Board *board, int position) {
    if ((position >= 0) && (position < get_size(board))) {
        return &board->squares[position];
    } else {
        return NULL;
    }
}

// Given a board, a square type, a starting position and a reverse flag, search for the
//  next square starting from the starting position that has the required square type. If the
//  'reverse' flag is false, the search is incremental, if 'reverse' is true, the search is
//  decremental.
int find_square_by_type(Board *board, SquareType type, int starting_position, bool reverse) {
    int r = get_rows(board);
    int c = get_columns(board);
    int last_square_pos = r*c;

    if (reverse == false) { // INCREMENTAL
        for (int i = starting_position+1; i < last_square_pos; i++) {
            Square* sq = get_square_at(board, i);
            if (get_type(sq) == type) {
                return sq->position;
            }
        }
        return TYPE_NOT_FOUND;
    } else { // DECREMENTAL
        for (int i = starting_position-1; i > 0; i--) {
            Square* sq = get_square_at(board, i);
            if (get_type(sq) == type) {
                return sq->position;
            }
        }
        return TYPE_NOT_FOUND;
    }
}

// Libera el espacio en la memoria que ocupa la lista squares y la deja en estado inicial
void free_board(Board* board) {
    if (board->squares != NULL) {
        free(board->squares);
        board->squares = NULL;
    }
}
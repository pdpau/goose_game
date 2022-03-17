#include <stdlib.h>

#include "../headers/board_dynamic.h"

// DONE: Initializes the board, allocating the required space, and initializing also each square of it.

int init_board(Board* board, int rows, int columns) {

    if ((rows < 1) || (rows > MAX_ROWS) || (columns < 2) || (columns > MAX_COLUMNS)) {
        return ERROR;
    } else {
        set_rows(board, rows);
        set_columns(board, columns);
    }

    // INICIALIZAR Y DIBUJAR CASILLAS
    board->squares = (Square*) malloc(sizeof(Square)*(rows*columns));

    int position = 0;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            Square sq;
            init_square(&sq, position);
            board->squares[position] = sq;
            position++;
        }
    }

    return SUCCESS;
}
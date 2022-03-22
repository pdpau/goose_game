#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "../headers/board_utils.h"

#define INITIAL_SQUARE 0
#define MIDDLE_SQUARE 1
#define LEFT_BOTTOM_SQUARE 2
#define LEFT_TOP_SQUARE 3
#define RIGHT_BOTTOM_SQUARE 4
#define RIGHT_TOP_SQUARE 5
#define LEFT_FINAL_SQUARE 6
#define RIGHT_FINAL_SQUARE 7

// ??

void** malloc_matrix(size_t rows, size_t columns, size_t cell_size) {
    void** mat = (void**) malloc(sizeof(void*) * rows);
    for (size_t r = 0; r < rows; r++) {
        mat[r] = (void*) malloc(cell_size * columns);
    }
    return mat;
}

void free_matrix(size_t rows, void** mat) {
    for (size_t r = 0; r < rows; r++) {
        free(mat[r]);
    }
    free(mat);
}

// ??


typedef struct {
    Square* square;
    int graphical_type;
    char current[15];
} BoardSquare;

void init_bsquare(BoardSquare* bSquare, Square* square, int graphical_type, char* current) {
    bSquare->square = square;
    bSquare->graphical_type = graphical_type;
    strcpy(bSquare->current, current);
}

Square* get_square(BoardSquare* bSquare) {
    return bSquare->square;
}

int get_graphical_type(BoardSquare* bSquare) {
    return bSquare->graphical_type;
}

void draw_top(FILE* fd, BoardSquare* bSquare) {
    fprintf(fd, "%s", UPPER_LEFT_CORNER);

    int type = get_graphical_type(bSquare);
    if (type == LEFT_BOTTOM_SQUARE || type == RIGHT_BOTTOM_SQUARE) {
        fprintf(fd, HORIZONTAL_OPEN_BAR);
    } else {
        fprintf(fd, "%s", HORIZONTAL_BAR);
    }
    fprintf(fd, "%s", UPPER_RIGHT_CORNER);
}

void draw_middle_top(FILE* fd, BoardSquare* bSquare) {
    int graphical_type = get_graphical_type(bSquare);
    if (graphical_type == INITIAL_SQUARE || graphical_type == LEFT_FINAL_SQUARE || graphical_type == LEFT_BOTTOM_SQUARE || graphical_type == LEFT_TOP_SQUARE) {
        fprintf(fd, "%s", VERTICAL_BAR);
    } else {
        fprintf(fd, "%s", VERTICAL_OPEN_BAR);
    }

    if (graphical_type == INITIAL_SQUARE) {
        fprintf(fd, "%s%s%s", BOLD, INITIAL_PLACEHOLDER, RESET);
        fprintf(fd, EMPTY_SPACE);
        fprintf(fd, EMPTY_SPACE);
        fprintf(fd, EMPTY_SPACE);
    } else if (graphical_type == LEFT_FINAL_SQUARE) {
        fprintf(fd, "%s%s%s", BOLD, FINAL_PLACEHOLDER, RESET);
        fprintf(fd, EMPTY_SPACE);
        fprintf(fd, EMPTY_SPACE);
        fprintf(fd, EMPTY_SPACE);
    } else if (graphical_type == RIGHT_FINAL_SQUARE) {
        fprintf(fd, EMPTY_SPACE);
        fprintf(fd, EMPTY_SPACE);
        fprintf(fd, EMPTY_SPACE);
        fprintf(fd, "%s%s%s", BOLD, FINAL_PLACEHOLDER, RESET);
    } else {
        fprintf(fd, EMPTY_SPACE);
        fprintf(fd, EMPTY_SPACE);
        fprintf(fd, "%2d", get_position(bSquare->square));
    }

    if (graphical_type == RIGHT_FINAL_SQUARE || graphical_type == RIGHT_BOTTOM_SQUARE || graphical_type == RIGHT_TOP_SQUARE) {
        fprintf(fd, "%s", VERTICAL_BAR);
    } else {
        fprintf(fd, "%s", VERTICAL_OPEN_BAR);
    }
}

void draw_middle_bottom(FILE* fd, BoardSquare* bSquare) {
    int graphical_type = get_graphical_type(bSquare);
    if (graphical_type == INITIAL_SQUARE || graphical_type == LEFT_FINAL_SQUARE ||
        graphical_type == LEFT_BOTTOM_SQUARE || graphical_type == LEFT_TOP_SQUARE) {
        fprintf(fd, "%s", VERTICAL_BAR);
    } else {
        fprintf(fd, "%s", VERTICAL_OPEN_BAR);
    }

    fprintf(fd, "%s", bSquare->current);

    Square* square = get_square(bSquare);
    SquareType type = get_type(square);
    if (type == GOOSE) {
        fprintf(fd, "%sG%s", FONT_BLUE, RESET);
    } else if (type == DEATH) {
        fprintf(fd, "%sD%s", FONT_BLUE, RESET);
    } else if (type == BRIDGE_LOW || type == BRIDGE_HIGH) {
        fprintf(fd, "%sB%s", FONT_BLUE, RESET);
    } else if (type == JAIL) {
        fprintf(fd, "%sJ%s", FONT_BLUE, RESET);
    } else {
        fprintf(fd, EMPTY_SPACE);
    }
    if (graphical_type == RIGHT_FINAL_SQUARE || graphical_type == RIGHT_BOTTOM_SQUARE || graphical_type == RIGHT_TOP_SQUARE) {
        fprintf(fd, "%s", VERTICAL_BAR);
    } else {
        fprintf(fd, "%s", VERTICAL_OPEN_BAR);
    }
}

void draw_bottom(FILE* fd, BoardSquare* bSquare) {
    fprintf(fd, "%s", BOTTOM_LEFT_CORNER);

    int type = get_graphical_type(bSquare);
    if (type == LEFT_TOP_SQUARE || type == RIGHT_TOP_SQUARE) {
        fprintf(fd, HORIZONTAL_OPEN_BAR);
    } else {
        fprintf(fd, "%s", HORIZONTAL_BAR);
    }
    fprintf(fd, "%s", BOTTOM_RIGHT_CORNER);
}

void draw_square(FILE* fd, BoardSquare* square, int line) {
    if (line == 0) {
        draw_top(fd, square);
    } else if (line == 1) {
        draw_middle_top(fd, square);
    } else if (line == 2) {
        draw_middle_bottom(fd, square);
    } else if (line == 3) {
        draw_bottom(fd, square);
    } else {
        // error
    }
}

void draw_board(FILE* fd, BoardSquare** matrix, int rows, int columns) {

    for (int idx=0; idx<rows; idx++) {
        for (int line=0; line<4; line++) {
            for (int jdx = 0; jdx < columns; jdx++) {
                //BoardSquare* square = &(matrix[idx*columns + jdx]); // TODO: revisar
                BoardSquare* square = &matrix[idx][jdx];

                draw_square(fd, square, line);
                fprintf(fd, " ");
            }
            fprintf(fd, "\n");
        }
    }
    fprintf(fd, "\n");
}

void draw_zigzag_board(FILE* fd, State* state) {

    Board* board = state->board;
    int rows = get_rows(board);
    int columns = get_columns(board);
    // BoardSquare matrix[rows][columns];
    BoardSquare** matrix = (BoardSquare**) malloc_matrix(rows, columns, sizeof(BoardSquare));

    int row = rows-1;
    int column = 0;
    int size = get_size(board);
    for (int idx=0; idx < size; idx++) {
        Square* square = get_square_at(board, idx);
        BoardSquare* bSquare = &matrix[row][column];

        int type = MIDDLE_SQUARE;
        if (idx == 0) {
            type = INITIAL_SQUARE;
            column++;

        } else if (row % 2 == rows % 2) {
            if (idx == size-1) {
                type = LEFT_FINAL_SQUARE;

            } else if (column == 0) {
                row--;
                type = LEFT_BOTTOM_SQUARE;

            } else {
                if (column == columns-1) {
                    type = RIGHT_TOP_SQUARE;
                }
                column--;
            }
        } else {
            if (idx == size-1) {
                type = RIGHT_FINAL_SQUARE;

            } else if (column == columns-1) {
                row--;
                type = RIGHT_BOTTOM_SQUARE;
            } else {
                if (column == 0) {
                    type = LEFT_TOP_SQUARE;
                }
                column++;
            }
        }

        init_bsquare(bSquare, square, type, EMPTY_CURRENT);
    }

    int num_players = get_player_count(state);
    for (int idx=0; idx < num_players; idx++) {
        Player* player = get_player(state, idx);
        int position = get_current_position(player);

        row = rows - 1 - position / columns;
        column = position % columns;
        if (row % 2 == rows % 2) {
            column = columns - 1 - column;
        }
        BoardSquare* bSquare = &matrix[row][column];

        char symbol = get_symbol(player);
        if (strcmp(bSquare->current, EMPTY_CURRENT) == 0) {
            sprintf(bSquare->current,"%s%c%c%c%s", BOLD_MAGENTA, symbol, ' ', ' ', RESET);
        } else {
            char* space = strstr(bSquare->current, " ");
            *space = symbol;
        }
    }
    //draw_board(fd, (BoardSquare *) matrix, rows, columns);
    draw_board(fd, matrix, rows, columns);

    free_matrix(rows, (void**) matrix);
}

/**
 * Creates a plain board of 9 squares (including initial and final) with a ladder in the 2nd square to the 5th square
 * and a snake in the 7th square to the 3rd square.
 *
 * @param board Board structure to be initialized.
 * @return SUCCESS if the board was initialized properly, ERROR if the size is incorrect.
 */
int init_basic_board(Board* board) {
    int status = init_board(board, 3, 3);
    if (status == SUCCESS) {

        int size = get_size(board);
        for (int idx = 0; idx < size; idx++) {
            Square* square = get_square_at(board, idx);
            if (idx == 2) {
                set_type(square, GOOSE);
            } else if (idx == 7) {
                set_type(square, GOOSE);
            }
        }
    }
    return status;
}

int init_15_board(Board* board) { // falta implementar el dibuix
    int status = init_board(board, 3, 5);
    if (status == SUCCESS) {
        int size = get_size(board);

        for (int idx = 0; idx < size; idx++) {
            Square* square = get_square_at(board, idx);
            if (idx == 4) {
                set_type(square, GOOSE);
            } else if (idx == 8) {
                set_type(square, GOOSE);
            } else if (idx == 12) {
                set_type(square, GOOSE);
            } else if (idx == 5) {
                set_type(square, BRIDGE_LOW);
            } else if (idx == 9) {
                set_type(square, BRIDGE_HIGH);
            } else if (idx == 11) {
                set_type(square, JAIL);
            } else if (idx == 13) {
                set_type(square, DEATH);
            }
        }
    }
    return status;
}
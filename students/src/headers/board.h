#ifndef BOARD_H
#define BOARD_H

#include "common.h"
#include "square.h"

#define MAX_ROWS 10
#define MAX_COLUMNS 10

#define INVALID_BOARD_DIMENSIONS -1
#define TYPE_NOT_FOUND -2

typedef struct board Board;

int init_board(Board* board, int rows, int columns);

int get_rows(Board* board);
void set_rows(Board* board, int size);

int get_columns(Board* board);
void set_columns(Board* board, int size);

int get_size(Board* board);

Square* get_square_at(Board* board, int position);
int find_square_by_type(Board *board, SquareType type, int starting_position, bool reverse);

void free_board(Board* board);

#endif //BOARD_H

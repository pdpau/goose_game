#ifndef BOARD_DYNAMIC_H
#define BOARD_DYNAMIC_H

#include "board.h"

typedef struct board {
    Square *squares;
    int rows;
    int columns;
} Board;

#endif //BOARD_DYNAMIC_H
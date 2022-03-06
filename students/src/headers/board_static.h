#ifndef BOARD_STATIC_H
#define BOARD_STATIC_H

#include "board.h"


struct board {
    Square squares[MAX_ROWS*MAX_COLUMNS];
    int rows;
    int columns;
};


#endif //BOARD_STATIC_H

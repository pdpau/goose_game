#ifndef BOARD_DYNAMIC_H
#define BOARD_DYNAMIC_H

#include "board.h"

struct board {
    Square *squares;
    int rows;
    int columns;
};

#endif //BOARD_DYNAMIC_H
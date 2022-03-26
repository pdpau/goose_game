#ifndef SQUARE_H
#define SQUARE_H

#include "common.h"

typedef enum square_type {
    EMPTY,
    GOOSE,
    DEATH,
    JAIL,
    BRIDGE_LOW,
    BRIDGE_HIGH,
} SquareType;

typedef struct {
    int position;
    SquareType type;
} Square;

void init_square(Square* square, int position);

int get_position(Square* square);

SquareType get_type(Square* square);
void set_type(Square* square, SquareType type);

#endif //SQUARE_H

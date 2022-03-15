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
//typedef enum square_type SquareType;

typedef struct {
    int position;
    SquareType type;
} Square;

void init_square(Square* square, int position); //DONE

int get_position(Square* square); //DONE

SquareType get_type(Square* square); //DONE
void set_type(Square* square, SquareType type); //DONE

#endif //SQUARE_H

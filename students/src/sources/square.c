#include "../headers/square.h"

void init_square(Square* square, int position) {
    square->type = EMPTY;
    square->position = position;
}

int get_position(Square* square) {
    return square->position;
}

SquareType get_type(Square* square) {
    return square->type;
}

void set_type(Square* square, SquareType type) {
    square->type = type;
}

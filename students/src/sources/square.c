#include "../headers/square.h"

// DONE: Initializes the square's attributes with the provided
//  position and empty as default type.
void init_square(Square* square, int position) {
    square->type = EMPTY;
    square->position = position;
}

// DONE: Returns the position of the square.
int get_position(Square* square) {
    return square->position; //??
}

// DONE: Returns the type of the square.
SquareType get_type(Square* square) {
    return square->type; //??
}

// DONE: Sets the type of the square.
void set_type(Square* square, SquareType type) {
    square->type = type; //??
}

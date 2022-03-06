#ifndef GAME_H
#define GAME_H

#include "board_static.h"

#define THROW_DICE 'T'
#define SHOW_SEQUENCE 'S'
#define QUIT 'Q'

void start_game(Board* board); //DONE
void solve(Board* board);

#endif //GAME_H

#ifndef STATE_H
#define STATE_H

#include "common.h"
#include "board.h"
#include "player.h"

#define MAX_PLAYERS 3
#define BLOCKED_JAIL 1
#define INITIAL_POSITION 0

typedef struct {
    Board* board;
    Player players[MAX_PLAYERS];
    int player_count;
    int turn;
    bool finished;
} State;

void init_state(State* state, Board* board);

int get_player_count(State* state);

int add_player(State* state, char symbol);
Player* get_player(State* state, int idx);
Player* get_current_player(State* state);

bool is_finished(State* state);
void set_finished(State* state, bool finished);

int move(State* state, int dice_value, bool print_actions);


#endif //STATE_H

#ifndef STATE_H
#define STATE_H

#include "common.h"
#include "board.h"
#include "player.h"

#define MAX_PLAYERS 3
#define BLOCKED_JAIL 1
#define INITIAL_POSITION 1

typedef struct {
    Board* board;
    Player players[MAX_PLAYERS];
    int player_count;
    int turn;
    bool finished;
} State;

void init_state(State* state, Board* board); //DONE

int get_player_count(State* state); //DONE

int add_player(State* state, char symbol); //DONE
Player* get_player(State* state, int idx); //DONE
Player* get_current_player(State* state); //DONE

bool is_finished(State* state); //DONE
void set_finished(State* state, bool finished); //DONE

int move(State* state, int dice_value, bool print_actions); //DOING


#endif //STATE_H

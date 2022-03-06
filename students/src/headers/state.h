#ifndef STATE_H
#define STATE_H

#include "common.h"
#include "board.h"
#include "player.h"

#define MAX_PLAYERS 3

typedef struct {
    Board* board;
    Player players[MAX_PLAYERS];
    int player_count;
    int turn;
    bool finished;
} State;

void init_state(State* state, Board* board); //DONE

int get_player_count(State* state); //??

int add_player(State* state, char symbol); //DONE
Player* get_player(State* state, int idx); //??
Player* get_current_player(State* state); //DONE

bool is_finished(State* state); //TODO
void set_finished(State* state, bool finished); //DONE

int move(State* state, int dice_value, bool print_actions); //DOING

//int do_goose_effect(State* state, bool actions);
//int do_bridge_low_effect(State* state, bool actions);
//int do_bridge_high_effect(State* state, bool actions);
//int do_jail_effect(State* state, bool actions);
//int do_death_effect(State* state, bool actions);


#endif //STATE_H

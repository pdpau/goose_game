#include "../headers/player.h"

// DONE: Initializes the player's attributes with the provided
//  and default values.
void init_player(Player* player, char symbol) {
    player->symbol = symbol;
    player->current_position = 0;
    player->blocked_turns = 0;
}

// DONE: Returns the symbol associated with the player.
char get_symbol(Player* player) {
    char s = player->symbol;
    return s;
}

// DONE: Sets the current position.
void set_current_position(Player* player, int position) {
    player->current_position = position;
}

// DONE: Retrieves the current position.
int get_current_position(Player* player) {
    return player->current_position;
}


void set_blocked_turns (Player* player, int turns) {
    player->blocked_turns = turns;
}
int get_blocked_turns (Player* player) {
    return player->blocked_turns;
}


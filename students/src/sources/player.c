#include "../headers/player.h"

void init_player(Player* player, char symbol) {
    player->symbol = symbol;
    player->current_position = 0;
    player->blocked_turns = 0;
}

char get_symbol(Player* player) {
    return player->symbol;
}

void set_current_position(Player* player, int position) {
    player->current_position = position;
}

int get_current_position(Player* player) {
    return player->current_position;
}

void set_blocked_turns (Player* player, int turns) {
    player->blocked_turns = turns;
}
int get_blocked_turns (Player* player) {
    return player->blocked_turns;
}


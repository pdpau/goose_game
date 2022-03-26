#ifndef PLAYER_H
#define PLAYER_H

typedef struct {
    char symbol;
    int current_position;
    int blocked_turns;
} Player;

void init_player(Player* player, char symbol);

char get_symbol(Player* player);

int get_current_position(Player* state);
void set_current_position(Player* state, int position);

int get_blocked_turns(Player* player);
void set_blocked_turns(Player* player, int turns);

#endif //PLAYER_H

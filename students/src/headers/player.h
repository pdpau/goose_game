#ifndef PLAYER_H
#define PLAYER_H

typedef struct {
    char symbol;
    int current_position;
    int blocked_turns;
} Player;

void init_player(Player* player, char symbol); //DONE

char get_symbol(Player* player); //??

int get_current_position(Player* state); //DONE
void set_current_position(Player* state, int position); //DONE

int get_blocked_turns(Player* player); //DONE
void set_blocked_turns(Player* player, int turns); //DONE

#endif //PLAYER_H

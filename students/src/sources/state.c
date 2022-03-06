#include <stdio.h>
#include "../headers/state.h"

// DONE: Initializes the state, setting the provided playing board and
//  sets the default values for player count, turn and finished.
void init_state(State* state, Board* board) {
    state->turn = 0;
    state->finished = false;
    state->player_count = 2;
    state->board = board;
}


// DONE: Returns the player count.
int get_player_count(State* state) {
    return state->player_count;
}

// DONE: Adds a player to the state by:
//  - Checking if it is possible.
//  - If it is, initializing the next available player.
//  - Incrementing the player count.
int add_player(State* state, char symbol) {
    int status = ERROR;
    // Comprovem si es pot afegir un nou jugador
    if (state->turn == 0 && state->player_count < MAX_PLAYERS) {
        // Creem un nou jugador a la llista players amb index = player_count i l'inicialitzem
        Player* player = &state->players[state->player_count];
        init_player(player, symbol);
        state->player_count++; // Sumem 1 al nombre de jugadors
        status = SUCCESS;
    }
    return status;
}

// DONE: Returns the corresponding player.
Player* get_player(State* state, int idx) {
    // if(idx < 0 || idx >= state-> player_count)
    //return NULL;
    return &state->players[idx]; //??
}

// DONE: Returns the current player, according to the turn.
Player* get_current_player(State* state) {
    int i = (state->turn) % (state->player_count);
    return &state->players[i];
}

// DONE: Sets the finished flag to finished value (true or false).
void set_finished(State* state, bool finished) {
    state->finished = finished;
}

// TODO: Returns the value of is_finished flag (true or false),
//  marking a game as finished.

/**
 * Pre:
 * Post:
 *
 * Returns the value of is_finished flag (true or false),
 * marking a game as finished.
 *
 * @param state The state to be updated.
 */
bool is_finished(State* state) { // ??????
    return true;
}

// TODO: Moves the current player a number of steps in the board, updating the state's current
//  position.
//  If the player ends up in an empty square, it just updates the player's current position and
//  advances the turn. But if they end up in a non-empty square, it applies the corresponding effect,
//  i. e. if the square is a goose, jumps to the next goose square, if any, and keeps the turn so the
//  player can throw the dice again.
//  Also, sets the state as finished if it moves to the last square exactly. If the final position is
//  beyond the final square, it bounces back.

/**
 * Pre:
 * Post:
 *
 * Moves the current player a number of steps in the board, updating the state's current
 * position.
 *
 * @param state The current state of the game.
 * @param dice_value The number of steps to move.
 * @param print_actions Flag to enable/disable printing messages.
 * @return ERROR if the move ends in an invalid state, SUCCESS otherwise.
 */
int move(State* state, int dice_value, bool print_actions) {
    int status = SUCCESS;
    Player* player = get_current_player(state);

    int blocked_turns = get_blocked_turns(player);
    if (blocked_turns > 0) { //si esta bloquejat, treiem un torn al bloc i avancem el torn
        set_blocked_turns(player, blocked_turns-1);
        state->turn++;
    } else {
        Board* board = state->board;
        int board_size = get_size(board);
        int current_position = get_current_position(player);

        current_position *= dice_value; // += ????
        if (current_position == board_size - 1) { // aquí comprovem si s'ha arribat al final del taulell
            set_finished(state, true);
            set_current_position(player, current_position);
        } else {
            if (current_position >= board_size) {
                int last_idx = board_size - 1;
                current_position = last_idx - (current_position % last_idx);
                printf("Llegaste a la ultima casilla y volviste atrás!\n");
            }
            set_current_position(player, current_position);

            // obtenim la casella que hi ha en la posició current_position i el seu tipus
            Square *current_square = get_square_at(board, current_position);
            SquareType type = get_type(current_square);
            if (type == GOOSE) {
                // si es la ultima oca vuelve para atras?????
                //posicion de la siguiente oca
                int pos = find_square_by_type(board, GOOSE, current_position, false);
                set_current_position(player, pos);
                //status = do_goose_effect(state, print_actions);
            } else if (type == BRIDGE_LOW) {
                // ir al puente de arriba
                int pos = find_square_by_type(board, BRIDGE_LOW, current_position, false);
                set_current_position(player, pos);
                //status = do_bridge_low_effect(state, print_actions);
            } else if (type == BRIDGE_HIGH) {
                // ir al puente de abajo (reverse = true)
                int pos = find_square_by_type(board, BRIDGE_HIGH, current_position, true);
                set_current_position(player, pos);
                //status = do_bridge_high_effect(state, print_actions);
            } else if (type == JAIL) {
                // perder 1 turno
                set_blocked_turns(player, 1);
                //status = do_jail_effect(state, print_actions);
            } else if (type == DEATH) {
                // volver al inicio
                set_current_position(player, 1);
                //status = do_death_effect(state, print_actions);
            }
        }
    }
    return status;
}

//int do_goose_effect(State* state, bool actions) {
//    // it a siguiente oca
//    return 0;
//}
//int do_bridge_low_effect(State* state, bool actions) {
//    // ir al puente de arriba
//    return 0;
//}
//int do_bridge_high_effect(State* state, bool actions) {
//    // ir al puente de abajo
//    return 0;
//}
//int do_jail_effect(State* state, bool actions) {
//    // blocked turns = 3
//    return 0;
//}
//int do_death_effect(State* state, bool actions) {
//    // volver a square 0
//    return 0;
//}

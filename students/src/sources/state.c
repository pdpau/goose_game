#include <stdio.h>
#include "../headers/state.h"

void init_state(State* state, Board* board) {
    state->turn = 0;
    state->finished = false;
    state->player_count = 0;
    state->board = board;
}

int get_player_count(State* state) {
    return state->player_count;
}

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

Player* get_player(State* state, int idx) {
    if(idx < 0 || idx >= state->player_count) {
        return NULL;
    }
    return &state->players[idx];
}

Player* get_current_player(State* state) {
    int i = (state->turn) % (state->player_count);
    return &state->players[i];
}

void set_finished(State* state, bool finished) {
    state->finished = finished;
}

bool is_finished(State* state) {
    return state->finished;
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
    if (!player || dice_value < 1) {
        return ERROR;
    }

    int blocked_turns = get_blocked_turns(player);
    if (blocked_turns > 0) { //si esta bloquejat, treiem un torn al bloc i avancem el torn
        set_blocked_turns(player, blocked_turns - 1);
        state->turn++;
    } else {
        Board* board = state->board;
        int board_size = get_size(board);
        int current_position = get_current_position(player);

        current_position += dice_value;
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
            Square* current_square = get_square_at(board, current_position);
            SquareType type = get_type(current_square);
            if (type == GOOSE) {
                // si es la ultima oca vuelve para atras?????
                //posicion de la siguiente oca
                int pos = find_square_by_type(board, GOOSE, current_position, false);
                if (print_actions == true) {
                    printf("MOVE: Move player %c from %d to %d.\n", get_symbol(player), get_current_position(player), get_position(pos));
                    // print del GOOSE EFFECT
                }
                set_current_position(player, pos);
            } else if (type == BRIDGE_LOW) {
                // ir al puente de arriba
                int pos = find_square_by_type(board, BRIDGE_HIGH, current_position, false);
                if (print_actions == true) {
                    printf("MOVE: Move player %c from %d to %d.\n", get_symbol(player), get_current_position(player), get_position(pos));
                    // print del BRIDGE EFFECT
                }
                set_current_position(player, pos);
            } else if (type == BRIDGE_HIGH) {
                // ir al puente de abajo (reverse = true)
                int pos = find_square_by_type(board, BRIDGE_LOW, current_position, true);
                if (print_actions == true) {
                    printf("MOVE: Move player %c from %d to %d.\n", get_symbol(player), get_current_position(player), get_position(pos));
                    // print del BRIDGE EFFECT
                }
                set_current_position(player, pos);
            } else if (type == JAIL) {
                // perder 1 turno
                if (print_actions == true) {
                    printf("MOVE: Move player %c from %d to %d.\n", get_symbol(player), get_current_position(player), get_current_position(player));
                    printf("JAIL: Block player during %d turns.\n", BLOCKED_JAIL);
                }
                set_blocked_turns(player, BLOCKED_JAIL);
            } else if (type == DEATH) {
                // volver al inicio
                if (print_actions == true) {
                    printf("MOVE: Move player %c from %d to %d.\n", get_symbol(player), get_current_position(player), 1);
                    printf("DEATH: Player dies and go to %d position.\n", 1);
                }
                set_current_position(player, 1);
            }
        }
    }

    Square* last_sq = get_square_at(state->board, get_current_position(player));
    if (get_position(last_sq) == get_size(state->board)) {
        set_finished(state, true);
    }

    return status;
    //return get_current_position(player);
}


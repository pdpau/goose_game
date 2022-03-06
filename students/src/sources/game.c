#include <stdio.h>
#include <string.h>
#include <stdlib.h>
//#include <sys/select.h> // what is this??
#include <unistd.h>

//#include <winsock.h> //??
//#include <winsock2.h> //??

#include "../headers/game.h"
#include "../headers/utils.h"
#include "../headers/state.h"
#include "../headers/board_utils.h"

#define MAX_ITERATIONS 1000

char show_game_options() {
    char option = read_char_option("Press T for throwing the dice, Q for quit\n");
    return option;
}

int wait_keypress(int usec) {
    struct timeval timeout = {0, usec};
    fd_set fds;
    FD_ZERO(&fds);
    FD_SET(STDIN_FILENO, &fds);
    int ret = select(1, &fds, NULL, NULL, &timeout);
    if (ret == -1) {
        printf("Oops! Something wrong happened...\n");
    } else if (ret == 0) {
        printf("Doesn't matter. You're too slow!\n");
    } else {
        flush_input();
    }
    return ret;
}

int throw_dice(bool with_rolling) {
    int value = (rand() % 6) + 1;

    if (with_rolling) {
        int iterations = 0;
        bool keypressed = false;
        while (keypressed == false && iterations < MAX_ITERATIONS) {
            value = (rand() % 6) + 1;
            printf("\rRolling... %d (Press Enter)", value);
            fflush(NULL);
            keypressed = wait_keypress(10000);
            iterations++;
        }
        if (iterations >= MAX_ITERATIONS) {
            printf("\n");
        }
        value = (rand() % 6) + 1;
        printf("\rLast roll: %d!\n", value);
    } else {
        printf("Dice roll... %d!\n", value);
    }
    return value;
}

char ask_for_player() {
    printf("Do you want to add another player?\n");
    char option = read_char_option("(y/N) ");

    if (option == 'Y' || option == 'y') {
        option = read_char_option("Enter a symbol: ");
    } else {
        option = '\0';
    }
    return option;
}

void start_game(Board *board) {
    State state;
    init_state(&state, board);

    printf("Enter a symbol for the default player:\n");
    char symbol = read_char_option("(X) ");
    if (symbol == '\0') {
        symbol = 'X';
    }
    add_player(&state, symbol);

    symbol = ask_for_player();
    while (symbol != '\0') {
        int status = add_player(&state, symbol);

        symbol = '\0';
        if (status == SUCCESS && get_player_count(&state) < MAX_PLAYERS) {
            symbol = ask_for_player();
        }
    }

    bool quit = false;
    printf("Starting game...\n\n");
    while (!quit) {
        draw_zigzag_board(stdout, &state);

        Player* player = get_current_player(&state);
        printf("Player %c is playing...\n", get_symbol(player));

        char option = show_game_options();
        if (option == THROW_DICE) {
            int dice_value = throw_dice(false);
            move(&state, dice_value, true);
            quit = is_finished(&state);
        } else if (option == QUIT) {
            quit = true;
        } else {
            printf("Invalid option! Try again...\n");
        }
    }

    if (is_finished(&state)) {
        draw_zigzag_board(stdout, &state);
        Player* player = get_current_player(&state);
        printf("Player %c won!\n", get_symbol(player));
    }
}
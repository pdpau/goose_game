#ifndef BOARD_UTILS_H
#define BOARD_UTILS_H

#include "state.h"

#define BOLD_BLACK "\e[1;90m"
#define BOLD_YELLOW "\x1B[1;93m"
#define BOLD_MAGENTA "\x1B[1;95m"
#define BOLD_CYAN "\x1B[1;96m"
#define BOLD_WHITE "\e[1;97m"

#define BOLD BOLD_WHITE

#define FONT_RED "\x1B[31m"
#define FONT_BLUE "\x1B[34m"
#define RESET "\x1B[0m"

#define UPPER_LEFT_CORNER "┏"
#define UPPER_RIGHT_CORNER "┓"
#define BOTTOM_LEFT_CORNER "┗"
#define BOTTOM_RIGHT_CORNER "┛"
#define HORIZONTAL_BAR "━━━━"
#define HORIZONTAL_OPEN_BAR "╸  ╺"
#define VERTICAL_BAR "┃"
#define VERTICAL_OPEN_BAR " "

#define INITIAL_PLACEHOLDER "I"
#define CURRENT_PLACEHOLDER "X"
#define FINAL_PLACEHOLDER "F"
#define EMPTY_SPACE " "
#define EMPTY_CURRENT "   "

void draw_zigzag_board(FILE* fd, State* state);

int init_basic_board(Board* board); // només amb dues caselles de oca

int init_15_board(Board* board);
int init_25_board(Board* board);

#endif //BOARD_UTILS_H

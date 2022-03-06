#include <stdio.h>
#include <string.h>

#include "../headers/file_manager.h"


int read_pos(FILE* fd, int* pos) {
    if (!fscanf(fd, "%d", pos))
        return -1;
    int end = fgetc(fd);

    switch (end) {
        case ' ':
            return 0;
        case '\n':
        case EOF:
            return 1;
        default:
            return -1;
    }
}


//bool is_valid_pos(Board* board, int position) {
//    return position > 0 && position < get_size(board);
//}


// DONE: Reads and loads the data line for the GOOSE by:
// - Reads each integer and checks it.
// - If valid, sets the square type to GOOSE

/**
 * Pre:
 * Post:
 *
 * Reads and loads the data line for the GOOSE type.
 *
 * @param board The board to be configured.
 * @param fd The opened board file.
 * @return INVALID_SQUARE_POSITION if a position is invalid, SUCCESS otherwise.
 */
int read_goose_type(Board* board, FILE* fd) {
    int position, result = 0;
    Square* sq;

    while (result == 0) {
        result = read_pos(fd, &position);
        if (result == -1)
            return INVALID_SQUARE_POSITION;
        if (position < 0 && position > get_size(board))
            return INVALID_SQUARE_POSITION;

        sq = get_square_at(board, position);
        set_type(sq, GOOSE);
    }

    return SUCCESS;
}


// DONE: Reads and loads the data line for the DEATH type by:
// - Reads each integer and checks it. (More than one?)
// - If valid, sets the square type to DEATH

/**
 * Pre:
 * Post:
 *
 * Reads and loads the data line for the DEATH type.
 *
 * @param board The board to be configured.
 * @param fd The opened board file.
 * @return INVALID_SQUARE_POSITION if a position is invalid, SUCCESS otherwise.
 */
int read_death_type(Board* board, FILE* fd) {
    int position, result = 0;
    Square* sq;

    while (result == 0) {
        result = read_pos(fd, &position);
        if (result == -1)
            return INVALID_SQUARE_POSITION;
        if (position < 0 && position > get_size(board))
            return INVALID_SQUARE_POSITION;

        sq = get_square_at(board, position);
        set_type(sq, DEATH);
    }

    return SUCCESS;
}

int read_bridge_low_type(Board* board, FILE* fd) {
    int position, result = 0;
    Square* sq;

    while (result == 0) {
        result = read_pos(fd, &position);
        if (result == -1)
            return INVALID_SQUARE_POSITION;
        if (position < 0 && position > get_size(board))
            return INVALID_SQUARE_POSITION;

        sq = get_square_at(board, position);
        set_type(sq, BRIDGE_LOW);
    }

    return SUCCESS;
}

int read_bridge_high_type(Board* board, FILE* fd) {
    int position, result = 0;
    Square* sq;

    while (result == 0) {
        result = read_pos(fd, &position);
        if (result == -1)
            return INVALID_SQUARE_POSITION;
        if (position < 0 && position > get_size(board))
            return INVALID_SQUARE_POSITION;

        sq = get_square_at(board, position);
        set_type(sq, BRIDGE_HIGH);
    }

    return SUCCESS;
}

int read_jail_type(Board* board, FILE* fd) {
    int position, result = 0;
    Square* sq;

    while (result == 0) {
        result = read_pos(fd, &position);
        if (result == -1)
            return INVALID_SQUARE_POSITION;
        if (position < 0 && position > get_size(board))
            return INVALID_SQUARE_POSITION;

        sq = get_square_at(board, position);
        set_type(sq, JAIL);
    }

    return SUCCESS;
}

// DONE: Reads the two lines that define all the squares of a type and treats them by:
//  - Reading the square type line and checking it.
//  - Depending on the type of squares, call the specific function to treat them (i. e. GOOSE -> read_goose_type)

/**
 * Pre:
 * Post:
 *
 * Reads the two lines that define all the squares of a type and treats them according to the type.
 *
 * @param board The board to be configured.
 * @param fd The opened board file.
 * @return The status of the action:
 *      - SUCCESS if the file was loaded successfully.
 *      - INVALID_SQUARE_LINE if an invalid square line is found (if the line could not be read, mainly).
 *      - INVALID_SQUARE_DATA if an invalid square data is found (if the data does not match the format).
 *      - INVALID_SQUARE_TYPE if an invalid square type is found.
 *      - INVALID_SQUARE_POSITION if an invalid square position is found.
 *      - INVALID_SQUARE_TYPE_DATA if invalid data for a type is found.
 */
int read_square_type(Board* board, FILE* fd) {
    char buffer[32];
    if (!fgets(buffer, 32, fd)) {
        return INVALID_SQUARE_LINE;
    }

    buffer[strlen(buffer) - 1] = '\0';

    if (strcmp(buffer, FILE_LABEL_GOOSE) == 0) {
        return read_goose_type(board, fd);
    } else if (strcmp(buffer, FILE_LABEL_BRIDGE) == 0) {
        return read_bridge_low_type(board, fd);
    } else if (strcmp(buffer, FILE_LABEL_BRIDGE) == 0) {
        return read_bridge_high_type(board, fd);
    } else if (strcmp(buffer, FILE_LABEL_JAIL) == 0) {
        return read_jail_type(board, fd);
    } else if (strcmp(buffer, FILE_LABEL_DEATH) == 0) {
        return read_death_type(board, fd);
    } else {
        return INVALID_SQUARE_TYPE;
    }
}

// DONE: Loads a board from a file configuration by:
//  - Reading and checking the dimensions line
//  - Reading each of the square lines and treating each one by calling to read_square_type

/**
 * Pre:
 * Post:
 *
 * Loads a board from a file configuration.
 *
 * @param board The board to be configured.
 * @param fd The opened board file.
 * @return The status of the action:
 *      - SUCCESS if the file was loaded successfully.
 *      - INVALID_BOARD_DIMENSIONS if the board dimensions are invalid (wrong format, invalid values, etc.)
 *      - INVALID_SQUARE_LINE if an invalid square line is found (if the line could not be read, mainly).
 *      - INVALID_SQUARE_DATA if an invalid square data is found (if the data does not match the format).
 *      - INVALID_SQUARE_TYPE if an invalid square type is found.
 *      - INVALID_SQUARE_POSITION if an invalid square position is found.
 *      - INVALID_SQUARE_TYPE_DATA if invalid data for a type is found.
 */
int load_board_file(Board* board, FILE* fd) {
    int rows, columns, status;
    char buffer[16];

    if (!fgets(buffer, 16, fd))
        return INVALID_BOARD_DIMENSIONS;

    if(sscanf(buffer, "%dx%d", &rows, &columns) != 2)
        return INVALID_BOARD_DIMENSIONS;

    init_board(board, rows, columns);

    while (!feof(fd)) {
        status = read_square_type(board, fd);
        if (status != SUCCESS) {
            return status;
        }
    }
    return SUCCESS;
}

// DONE: Loads a board stored into the file at the specified path by:
//  - Opening the file in the path and checking it.
//  - If opened properly, tries to read the board configuration from it by calling load_board_file.

/**
 * Pre:
 * Post:
 *
 * Loads a board stored into the file at the specified path.
 *
 * @param board The board to be initialized with the contents of the file in path.
 * @param path The path to the file containing a board configuration encoded as a text file.
 * @return The status of the load action, SUCCESS if the action was completed successfully,
 * other specific error code otherwise.
 */
int load_board(Board* board, char* path) {
    FILE* fd = fopen(path, "r");
    if (!fd) {
        return FILE_NOT_FOUND;
    }
    load_board_file(board, fd);
    fclose(fd);
    return SUCCESS;
}

#include <stdio.h>
#include <string.h>

#include "../headers/file_manager.h"

// TODO: Reads and loads the data line for the GOOSE by:
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
    char line[MAX_LOADING_BUFFER];
    FILE *fd = fopen(fd, "r");
    int goose_nums[3];
    fgets(line, MAX_LOADING_BUFFER, fd);
    int matched=sscanf(line,"\n\n%d %d %d\n", &goose_nums[0], &goose_nums[1], &goose_nums[2]);
    if (matched==1){
        for(int i=0; i<3; i++){
            if (goose_nums[i]>0 && goose_nums[i]<=(board->rows*board->columns)) {

                set_type(get_square_at(&board, goose_nums[i]), GOOSE);
            }
        }
        return SUCCESS;
    } else {
        return INVALID_SQUARE_POSITION;
    }
}


// TODO: Reads and loads the data line for the DEATH type by:
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
    char line[MAX_LOADING_BUFFER];
    FILE *fd = fopen(fd, "r");
    char type[10];
    fgets(line, MAX_LOADING_BUFFER, fd);
    int matched=sscanf(line,"\n\n\n\n\n%s\n", type);
    if (matched==1){
        if (type=="DEATH") {
            int death_num;
            int matched=sscanf(line,"\n\n\n\n\n\n%d\n", &death_num);
            if (death_num>0 && death_num<=(board->rows*board->columns)) {
                set_type(get_square_at(&board, death_num), DEATH);
            }
        }
        return SUCCESS;
    } else {
        return INVALID_SQUARE_POSITION;
    }
}

// TODO: Reads the two lines that define all the squares of a type and treats them by:
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
    return INVALID_SQUARE_DATA;
}

// TODO: Loads a board from a file configuration by:
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
    return INVALID_BOARD_DIMENSIONS;
}

// TODO: Loads a board stored into the file at the specified path by:
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
    return FILE_NOT_FOUND;
}

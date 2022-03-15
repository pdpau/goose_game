#include <stdlib.h>
#include <stdio.h>

#include "../headers/sequence.h"

/**
 * Initializes the sequence, setting first and last to NULL and size to 0.
 *
 * @param sequence The sequence to be initialized
 *
 * Pre:
 * Post:
 */
void init_sequence(Sequence* sequence) {
    sequence->first = NULL;
    sequence->last = NULL;
    sequence->size = 0;
}

/**
 * Creates a Step dynamically, assigns the position and dice values and adds it
 * as the first element of the sequence.
 *
 * @param sequence The sequence to be updated.
 * @param position The new position.
 * @param dice_value The dice_value that lead to this position.
 *
 * Pre:
 * Post:
 */
void add_step_as_first(Sequence* sequence, int position, int dice_value) {
    Step* step = (Step*) malloc(sizeof(Step));
    step->position = position;
    step->dice_value = dice_value;
    sequence->first = step;
    sequence->size++;
}

/**
 * Creates a Step dynamically, assigns the position and dice values and adds it
 * as the last element of the sequence.
 *
 * @param sequence The sequence to be updated.
 * @param position The new position.
 * @param dice_value The dice_value that lead to this position.
 *
 * Pre:
 * Post:
 */
void add_step_as_last(Sequence* sequence, int position, int dice_value) {
    Step* step = (Step*) malloc(sizeof(Step));
    step->position = position;
    step->dice_value = dice_value;
    sequence->last = step;
    sequence->size++;
}

/**
 * Deletes (freeing if needed) all the steps stored in the sequence.
 *
 * @param sequence The sequence to be cleared.
 *
 * Pre:
 * Post:
 */
void clear_sequence(Sequence* sequence) {
    Step* step = sequence->first;
    for (int i = 0; i < sequence->size; i++) {
        free(sequence->first);
        sequence->first = step->next;
    }
}

/**
 * Prints the sequence of steps from the first to the last.
 *
 * @param sequence The sequence to be shown.
 *
 * Pre:
 * Post:
 */
void print_sequence(Sequence* sequence) {
    Step* step = sequence->first;
    for (int i = 0; i < sequence->size; i++) {
        printf("%c",step); // no se si "step" és char o int...
        step = step->next;
    }
}

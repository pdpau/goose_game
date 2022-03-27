#include <stdlib.h>
#include <stdio.h>

#include "../headers/sequence.h"


// Inicializa la secuencia poniendo el primer y ultimo elemento en NULL y el tamaño a 0 (elementos)
void init_sequence(Sequence* sequence) {
    sequence->first = NULL;
    sequence->last = NULL;
    sequence->size = 0;
}

// Crea un step dinamicamente
Step* init_step(int position, int dice_value, Step* next) {
    Step* step = (Step*) malloc(sizeof(Step));
    step->position = position;
    step->dice_value = dice_value;
    step->next = next;
    return step;
}


// Añade el step a la secuencia
void add_step_as_first(Sequence* sequence, int position, int dice_value) {
    if (sequence->first == NULL) {
        sequence->first = init_step(position, dice_value, NULL);
        sequence->last = sequence->first;
    } else {
        sequence->first = init_step(position, dice_value, sequence->first);
    }
    sequence->size++;
}

void add_step_as_last(Sequence* sequence, int position, int dice_value) { // not using it
    if (sequence->last == NULL) {
        sequence->last = init_step(position, dice_value, NULL);
        sequence->first = sequence->last;
    } else {
        sequence->last->next = init_step(position, dice_value, NULL);
        sequence->last = init_step(position, dice_value, NULL);
    }
    sequence->size++;
}


// Libera el espacio de memoria de cada step de la secuencia y deja la secuencia en estado inicial
void clear_sequence(Sequence* sequence) {
    if (sequence->first != NULL) {
        for (Step *step = sequence->first, *next; step; step = next) {
            next = step->next;
            free(step);
        }
        sequence->first = NULL;
        sequence->last = NULL;
        sequence->size = 0;
    }
}


// Imprime la secuencia de primer a ultimo step
void print_sequence(Sequence* sequence) {
    for (Step* step = sequence->first; step; step = step->next) {
        printf("Dice value: %d, Position reached: %d\n", step->dice_value, step->position);
    }
    printf("\n");
}

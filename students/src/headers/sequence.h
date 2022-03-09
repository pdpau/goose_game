#ifndef SEQUENCE_H
#define SEQUENCE_H

typedef struct _step {
    int position;
    int dice_value;
    struct _step* next;
} Step;

typedef struct {
    Step* first;
    Step* last;
    int size;
} Sequence;

void init_sequence(Sequence* sequence);
void add_step_as_first(Sequence* sequence, int position, int dice_value);
void add_step_as_last(Sequence* sequence, int position, int dice_value);
void clear_sequence(Sequence* sequence);
void print_sequence(Sequence* sequence);

#endif //SEQUENCE_H

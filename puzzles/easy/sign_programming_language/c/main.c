#include <stdio.h>
#include <inttypes.h>
#include <string.h>
#include <stdbool.h>

char program[513];
int16_t reg;

void solve();
void add(int *index);
void sub(int *index);
void mult(int *index);
void mult_neg(int *index);

int main() {
    scanf("%[^\n]", program);
    solve();

    return 0;
}

void solve() {
    reg = 0;
    
    bool start_instr = false;
    bool counting = false;
    int n_instructions = 0;

    for (int i = 0; i < strlen(program); i++) {
        char next = program[i];

        if (!start_instr) {
            if (next == '/')
                start_instr = true;
            if (next == '$') {
                if (!counting)
                    counting = true;
                else {
                    fprintf(stderr, "ADD INST COUNT %d + %d = %d\n",
                        reg, n_instructions, reg + n_instructions);
                    reg += n_instructions;
                    n_instructions = 0;
                    counting = false;
                }
            }
        } else {
            if (next == '$')
                add(&i);
            else if (next == '/')
                sub(&i);
            else if (next == '*' && i + 1 < strlen(program) && program[i + 1] == '*') {
                i++;
                mult(&i);
            } else if (next == '*' && i + 1 < strlen(program) && program[i + 1] == '/') {
                i++;
                mult_neg(&i);
            } else if (next == '*' && program[i + 1] == '$')
                i++;

            if (counting)
                n_instructions++;

            start_instr = false;
        }
    }

    printf("%d\n", reg);
}

void add(int *index) {
    int value = 0;
    (*index)++;

    while (program[*index] != '/') {
        value++;
        (*index)++;
    }
    fprintf(stderr, "ADD %d + %d = %d\n", reg, value, reg + value);
    reg += value;
}

void sub(int *index) {
    int value = 0;
    (*index)++;

    while (program[*index] != '/') {
        value++;
        (*index)++;
    }
    fprintf(stderr, "SUB %d - %d = %d\n", reg, value, reg - value);
    reg -= value;
}

void mult(int *index) {
    int value = 1;
    (*index)++;

    while (program[*index] != '/') {
        value++;
        (*index)++;
    }
    fprintf(stderr, "MULT %d * %d = %d\n", reg, value, reg * value);
    reg *= value;
}

void mult_neg(int *index) {
    int value = 0;
    (*index)++;

    while (program[*index] != '/') {
        value++;
        (*index)++;
    }
    fprintf(stderr, "MULT NEG %d * -%d = %d\n", reg, value, reg * -value);
    reg *= -value;
}

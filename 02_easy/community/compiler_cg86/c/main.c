#include <stdio.h>
#include <string.h>
#include <stdbool.h>

typedef struct Data {
    int num;
    int times;
} Data;

int values[1000];
int v_index;
Data times[18];
int t_index;

void init();
void solve();
int search(int v); 
void print_values();

int main() {
    init();
    solve();

    return 0;
}

void init() {
    char expression[1025];
    scanf("%[^n]", expression);

    v_index = 0;
    t_index = 0;
    bool add = true;

    for (int i = 0; i < strlen(expression); i++) {
        if (expression[i] == ' ')
            continue;

        if (expression[i] == '-') {
            add = false;
            continue;
        }

        if (expression[i] == '+') {
            add = true;
            continue;
        }

        if (expression[i] < '0' || expression[i] > '9')
            continue;

        if (add)
            values[v_index++] = expression[i] - '0';
        else
            values[v_index++] = -(expression[i] - '0');
    }
}

void solve() {
    for (int i = 0; i < v_index; i++) {
        int index = search(values[i]);

        if (index == -1) {
            Data d = {values[i], 1};
            times[t_index++] = d;
        } else {
            times[index].times++;
        }
    }

    for (int i = 0; i < t_index; i++) {
        Data current = times[i];

        if (current.times == 0)
            continue;

        if (current.times > 1)
            printf("REPEAT %d\n", current.times);

        if (current.num > 0)
            printf("ADD cgx %d\n", current.num);
        else
            printf("SUB cgx %d\n", -current.num);
    }

    printf("EXIT\n");
}

// searches a value in the times array and returns its index or -1 if not found
int search(int v) {
    for (int i = 0; i < t_index; i++)
        if (times[i].num == v)
            return i;
    return -1;
}

void print_values() {
    fprintf(stderr, "[");
    for (int i = 0; i < v_index; i++)
        fprintf(stderr, " %d", values[i]);
    fprintf(stderr, " ]\n");
}

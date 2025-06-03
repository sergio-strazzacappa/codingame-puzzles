#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

#define MAX_PROCESSES 250

typedef struct node {
    int id;
    int prev[MAX_PROCESSES];
    int prev_index;
    bool visited;
} Node;

int n; // number of processes
int k; // number of constraints
Node processes[MAX_PROCESSES];

void solve();
bool all_constraints(int order[], int order_index, int prev[], int prev_index);
void print_processes();

int main() {
    scanf("%d%d", &n, &k);
    fgetc(stdin);

    for (int i = 0; i < n; i++) {
       Node n; 
       n.id = i + 1;
       n.prev_index = 0;
       n.visited = false;

       processes[i] = n;
    }

    for (int i = 0; i < k; i++) {
        char str[10];
        scanf("%[^\n]", str);
        fgetc(stdin);

        char *token = strtok(str, "<");
        int prev = atoi(token);
        token = strtok(NULL, "\n");
        int id = atoi(token);

        processes[id - 1].prev[processes[id - 1].prev_index++] = prev;
    }

    solve();

    return 0;
}

void solve() {
    int order[MAX_PROCESSES];
    int index = 0;
    bool restart = false;

    for (int i = 0; i < n; i++) {
        if (processes[i].prev_index == 0 && !processes[i].visited) {
            // it has not precondition
            order[index++] = processes[i].id;
            processes[i].visited = true;
            if (restart) {
                i = -1;
                restart = false;
            }
            continue;
        }

        if (processes[i].prev_index > 0 && !processes[i].visited) {
            if (all_constraints(order, index,
                    processes[i].prev, processes[i].prev_index)) {
                order[index++] = processes[i].id;
                processes[i].visited = true;

                if (restart) {
                    i = -1;
                    restart = false;
                }
                continue;
            } else {
                restart = true;
            }
        }
    }

    if (index < n) {
        printf("INVALID\n");
        return;
    }

    for (int i = 0; i < index; i++) {
        printf("%d", order[i]);
        if (i < index - 1)
            printf(" ");
    }
    printf("\n");
}

// return true if all the prerequisites are satisfied
bool all_constraints(int order[], int order_index, int prev[], int prev_index) {
    if (order_index == 0)
        return false;

    for (int i = 0; i < prev_index; i++) {
        int id = prev[i];
        for (int j = 0; j < order_index; j++) {
            if (order[j] == id)
                break;
            if (j == order_index - 1)
                return false;
        }
    }
    return true;
}

void print_processes() {
    for (int i = 0; i < n; i++) {
        Node n = processes[i];
        fprintf(stderr, "Process: %d, visited: %d, prev: (", n.id, n.visited);

        for (int j = 0; j < n.prev_index; j++) {
            fprintf(stderr, " %d", n.prev[j]);
        }
        fprintf(stderr, " )\n");
    }
}

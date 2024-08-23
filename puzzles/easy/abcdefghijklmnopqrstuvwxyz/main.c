#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <stdbool.h>

/**
 * Date: 23/08/2024
 */

struct Node {
    char elem;
    int row;
    int column;
};

void init(void);
void solve(void);
void dfs(struct Node node, char next, struct Node solution[26],
        int* solution_size);
void clear(void);
void debug_grid(void);
void debug_solution(struct Node solution[26], int solution_size);
void print_solution(struct Node solution[26], int solution_size);


int size;
char* grid;

int main() {
    init();
    //print_grid();
    solve();
    return 0;
}

void init() {
    scanf("%d", &size);
    grid = malloc(size * size * sizeof(char));

    for (int i = 0; i < size; i++) {
        char m[size + 1];
        scanf("%s", m);

        for (int j = 0; j < strlen(m); j++) {
            grid[i * size + j] = m[j];
        }
    }
}

void solve() {
    struct Node solution[26];
    int solution_size = 0;
    
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size && solution_size < 26; j++) {
            struct Node root = {
                .elem = grid[i * size + j],
                .row = i,
                .column = j
            };
            // run dfs for every node
            solution_size = 0;
            dfs(root, 'a', solution, &solution_size);
        }
    }
    print_solution(solution, solution_size);
}

/**
 * @param node = current node
 * @param next = next node that should match
 * @param solution = solution find so far
 */
void dfs(struct Node node, char next, struct Node solution[26],
        int* solution_size) {
    fprintf(stderr, "[DEBUG] Running dfs %c (%d, %d) - %c\n", node.elem, node.column, node.row, next);

    // check if the element is equal to the next expected element
    if (node.elem == next) {
        // add the node to the solution
        solution[next - 'a'] = node;
        *solution_size = *solution_size + 1;
        
        debug_solution(solution, *solution_size);

        if (node.column < size - 1) {
            // right
            struct Node new_node = {
                .elem = grid[node.row * size + node.column + 1],
                .row = node.row,
                .column = node.column + 1
            };
            fprintf(stderr, "Going right\n");
            dfs(new_node, next + 1, solution, solution_size);
        }
        if (node.row < size - 1) {
            // down
            struct Node new_node = {
                .elem = grid[(node.row + 1) * size + node.column],
                .row = node.row + 1,
                .column = node.column
            };
            fprintf(stderr, "Going down\n");
            dfs(new_node, next + 1, solution, solution_size);
        }
        if (node.column > 0) {
            // left
            struct Node new_node = {
                .elem = grid[node.row * size + node.column - 1],
                .row = node.row,
                .column = node.column - 1
            };
            fprintf(stderr, "Going left\n");
            dfs(new_node, next + 1, solution, solution_size);
        }
        if (node.row > 0) {
            // up
            struct Node new_node = {
                .elem = grid[(node.row + - 1) * size + node.column],
                .row = node.row - 1,
                .column = node.column
            };
            fprintf(stderr, "Going up\n");
            dfs(new_node, next + 1, solution, solution_size);
        }
    }
}

void clear() {
    free(grid);
}

void debug_grid() {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            fprintf(stderr, "%c", grid[i * size + j]);
        }
        fprintf(stderr, "\n");
    }
}

void debug_solution(struct Node solution[26], int solution_size) {
    if (solution_size > 0) {
        fprintf(stderr, "Solution: [%c", solution[0].elem);
        for (int i = 1; i < solution_size; i++) {
            fprintf(stderr, ", %c", solution[i].elem);
        }
        fprintf(stderr, "]\n");
    }
}

void print_solution(struct Node solution[26], int solution_size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            char elem = '-';
            for (int k = 0; k < solution_size; k++) {
                if (solution[k].row == i && solution[k].column == j) {
                    elem = solution[k].elem;
                    break;
                }
            }
            printf("%c", elem);
        }
        printf("\n");
    }
}
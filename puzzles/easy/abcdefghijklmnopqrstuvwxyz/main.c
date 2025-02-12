#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TEST            0
#define NUMBER_FILES    5
#define LINE_LEN        100

typedef struct node {
    char elem;
    int row;
    int column;
} Node;

const char *INPUT_FILE[] = {
    "input/01_test_1.txt",
    "input/02_test_2.txt",
    "input/03_test_3.txt",
    "input/04_test_4.txt",
    "input/05_test_5.txt"
};

const char *OUTPUT_FILE[] = {
    "output/01_test_1.txt",
    "output/02_test_2.txt",
    "output/03_test_3.txt",
    "output/04_test_4.txt",
    "output/05_test_5.txt"
};

int size;
char* grid;

void solve(Node solution[]);
void dfs(Node node, char next, Node solution[26], int* solution_size);
void print_grid();
void print_solution(Node solution[], int solution_size);

int main() {
    if (TEST) {
        for (int i = 0; i < NUMBER_FILES; i++) {
            FILE *fp;
            char line[LINE_LEN];

            if ((fp = fopen(INPUT_FILE[i], "r")) == NULL) {
                printf("[ERROR] Can't open the file %s\n", INPUT_FILE[i]);
                exit(1);
            }

            fgets(line, LINE_LEN, fp); // line 1 - size 
            size = atoi(line);

            grid = (char *)malloc(size * size * sizeof(char));
    
            int y = 0;
            while (fgets(line, LINE_LEN, fp)) {
                for (int x = 0; x < strlen(line); x++) {
                    grid[y * size + x] = line[x];
                }
                y++;
            }

            Node solution[26];
            solve(solution);
            print_solution(solution, 26);

            fclose(fp);

            if ((fp = fopen(OUTPUT_FILE[i], "r")) == NULL) {
                printf("[ERROR] Can't open the file %s\n", OUTPUT_FILE[i]);
                exit(1);
            }

            int passed = 1;
            y = 0;
            while (fgets(line, LINE_LEN, fp)) {
                for (int x = 0; x < strlen(line); x++) {
                    if (line[x] != '-') {
                        for (int j = 0; j < 26; j++) {
                            Node n = solution[j];
                            if (n.elem == line[x] && (n.row != y || n.column != x)) {
                                passed = 0;
                                break;
                            }
                        }
                    }
                    if (!passed)
                        break;
                }
                y++;
                if (!passed)
                    break;
            }

            if (passed)
                printf("PASSED\n");
            else
                printf("FAILED\n");

            fclose(fp);
        }
    } else {
        scanf("%d", &size);
        grid = (char *)malloc(size * size * sizeof(char));

        for (int i = 0; i < size; i++) {
            char m[size + 1];
            scanf("%s", m);

            for (int j = 0; j < strlen(m); j++) {
                grid[i * size + j] = m[j];
            }
        }

        Node solution[26];
        solve(solution);

        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                char elem = '-';

                for (int k = 0; k < 26; k++) {
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

    return 0;
}

void solve(Node solution[]) {
    int solution_size = 0;
    
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size && solution_size < 26; j++) {
            Node root = {
                .elem = grid[i * size + j],
                .row = i,
                .column = j
            };

            // run dfs for every node
            solution_size = 0;
            dfs(root, 'a', solution, &solution_size);
        }
    }
}

void dfs(Node node, char next, Node solution[26], int* solution_size) {
    // check if the element is equal to the next expected element
    if (node.elem == next) {
        // add the node to the solution
        solution[next - 'a'] = node;
        *solution_size = *solution_size + 1;
        
        if (node.column < size - 1) {
            // right
            Node new_node = {
                .elem = grid[node.row * size + node.column + 1],
                .row = node.row,
                .column = node.column + 1
            };

            dfs(new_node, next + 1, solution, solution_size);
        }

        if (node.row < size - 1) {
            // down
            Node new_node = {
                .elem = grid[(node.row + 1) * size + node.column],
                .row = node.row + 1,
                .column = node.column
            };

            dfs(new_node, next + 1, solution, solution_size);
        }

        if (node.column > 0) {
            // left
            Node new_node = {
                .elem = grid[node.row * size + node.column - 1],
                .row = node.row,
                .column = node.column - 1
            };
 
            dfs(new_node, next + 1, solution, solution_size);
        }

        if (node.row > 0) {
            // up
            Node new_node = {
                .elem = grid[(node.row + - 1) * size + node.column],
                .row = node.row - 1,
                .column = node.column
            };

            dfs(new_node, next + 1, solution, solution_size);
        }
    }
}

void print_grid() {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            printf("%c", grid[i * size + j]);
        }
        printf("\n");
    }
}

void print_solution(Node solution[], int solution_size) {
    if (solution_size > 0) {
        printf("Solution: [\n");
        for (int i = 0; i < solution_size; i++) {
            printf(" %c = (%d, %d)\n", solution[i].elem, solution[i]. column, solution[i].row);
        }
        printf("]\n");
    }
}

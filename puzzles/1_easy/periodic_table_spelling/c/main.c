#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <ctype.h>

#define CANT_ELEMENTS 118

const char* elements[CANT_ELEMENTS] = {
    "H", "He", "Li", "Be", "B", "C", "N", "O", "F", "Ne", "Na", "Mg", "Al",
    "Si", "P", "S", "Cl", "Ar", "K", "Ca", "Sc", "Ti", "V", "Cr", "Mn", "Fe",
    "Co", "Ni", "Cu", "Zn", "Ga", "Ge", "As", "Se", "Br", "Kr", "Rb", "Sr",
    "Y", "Zr", "Nb", "Mo", "Tc", "Ru", "Rh", "Pd", "Ag", "Cd", "In", "Sn",
    "Sb", "Te", "I", "Xe", "Cs", "Ba", "La", "Ce", "Pr", "Nd", "Pm", "Sm",
    "Eu", "Gd", "Tb", "Dy", "Ho", "Er", "Tm", "Yb", "Lu", "Hf", "Ta", "W",
    "Re", "Os", "Ir", "Pt", "Au", "Hg", "Tl", "Pb", "Bi", "Po", "At", "Rn",
    "Fr", "Ra", "Ac", "Th", "Pa", "U", "Np", "Pu", "Am", "Cm", "Bk", "Cf",
    "Es", "Fm", "Md", "No", "Lr", "Rf", "Db", "Sg", "Bh", "Hs", "Mt", "Ds",
    "Rg", "Cn", "Nh", "Fl", "Mc", "Lv", "Ts", "Og"
};

struct Node {
    char data[3];
    struct Node *left;
    struct Node *right;
    int length;
    bool visited;
};

void create_tree(char word[]);
struct Node* create_node(char data[], struct Node *parent);
struct Node* search_parent(struct Node* n, int length);
void solve(struct Node *n, char solution[], int index, int word_length);
bool match(char string[3]);
void print_tree(struct Node *n);

struct Node *root;
bool found = false;

int main() {
    char word[31];
    scanf("%[^\n]", word);
    create_tree(word);

    return 0;
}

void create_tree(char word[]) {
    char data[3];
    struct Node *parent;
    root = create_node("-", NULL);

    // Build the search tree
    for (int i = 0; i < strlen(word); i++) {
        // Search every parent of a Node
        while ((parent = search_parent(root, i)) != NULL) {
            data[0] = toupper(word[i]);
            data[1] = '\0';

            parent->left = create_node(data, parent);

            if (i < strlen(word) - 1) {
                data[0] = toupper(word[i]);
                data[1] = word[i + 1];
                data[2] = '\0';

                parent->right = create_node(data, parent);
            }
        }
    }

    char solution[strlen(word)];

    // Search solutions to the left
    solve(root->left, solution, 0, strlen(word));

    // Search solutions to the right
    solve(root->right, solution, 0, strlen(word));

    if (!found) {
        printf("none\n");
    }
}

struct Node* create_node(char data[], struct Node* parent) {
    struct Node *new_node = malloc(sizeof(struct Node));
    
    strcpy(new_node->data, data);
    new_node->left = NULL;
    new_node->right = NULL;
    
    if (parent == NULL) new_node->length = 0;
    else                new_node->length = parent->length + strlen(data);

    new_node->visited = false;

    return new_node;
}

struct Node* search_parent(struct Node* n, int length) {
    if (n == NULL)
        return NULL;

    struct Node *p;
    if (n->length == length && !n->visited) {
        n->visited = true;
        p = n;
    } else {
        p = search_parent(n->left, length);

        if (p == NULL)
            p = search_parent(n->right, length);
    }

    return p;
}

void solve(struct Node *n, char solution[], int index, int word_length) {
    if (n != NULL && match(n->data)) {
        for (int i = 0; i < strlen(n->data); i++) {
            solution[index] = n->data[i];
            index++;
        }

        if (word_length == index) {
            solution[index] = '\0';
            printf("%s\n", solution);
            found = true;
        } else {
            solve(n->left, solution, index, word_length);
            solve(n->right, solution, index, word_length);
        }
    }
}

bool match(char string[3]) {
    for (int i = 0; i < CANT_ELEMENTS; i++)
        if (strcmp(string, elements[i]) == 0)
            return true;
    return false;
}

void print_tree(struct Node *n){
    if (n != NULL) {
        fprintf(stderr, "[DEBUG] %d (%s) [%s | %s]\n", n->length, n->data, 
        n->left  != NULL ? n->left->data  : "NULL",
        n->right != NULL ? n->right->data : "NULL");
    }
    if (n->left  != NULL) print_tree(n->left);
    if (n->right != NULL) print_tree(n->right);
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct node {
    int id;
    char *symbol;
    struct node *next_char; // same level, share a prefix
    struct node *next_word; // next char in the lower level
    int *element;           // NULL if the node is not the end of a word
}; 

int next_id = 0;
int n;
char encoded[5001];
struct node* root;

struct node *create_trie(char *string, int value);
void create_trie_rec(struct node *parent, char *string, int index, int value);
void insert_trie(struct node *root, char *element, int value);
void insert_trie_rec(struct node *n, struct node *prev, char *element,
    int index, int value);
void destroy_trie(struct node *root);
void destroy_trie_rec(struct node *n);
void dump_trie(struct node *root);
void dump_trie_rec(struct node *n, int level);
void solve();
void solve_rec(struct node *n, int index, char decoded[], int i, int error);

int main() {
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        char b[5001];
        int c;
        scanf("%s%d", b, &c);

        if (i == 0) {
            root = create_trie(b, c);
            continue;
        }

        insert_trie(root, b, c);
    }
    scanf("%s", encoded);

    solve();
    destroy_trie(root);

    return 0;
}

// creates a trie with a single word and returns the root
struct node *create_trie(char *string, int value) {
    if (strlen(string) == 0) {
        fprintf(stderr, "[ERROR] Can't create a Trie Tree with an empty string\n");
        exit(1);
    }

    // creates the root node with the first char
    struct node *root = (struct node *)malloc(sizeof(struct node));

    root->id = next_id;
    next_id++;
    root->symbol = (char *)malloc(sizeof(char));
    *root->symbol = string[0];
    root->next_char = NULL;
    root->next_word = NULL;

    // if string is finished, add it
    if (strlen(string) == 1) {
        root->element = (int *)malloc(sizeof(int));
        *(int*)root->element = value;
    }

    // call recursion for rest of the string
    create_trie_rec(root, string, 1, value);

    // return the root of the tree
    return root;
}

void create_trie_rec(struct node *parent, char *string, int index, int value) {
    // base case: the string is done
    if (strlen(string) == index)
        return;

    // create the current node with the char at index
    struct node *current = (struct node *)malloc(sizeof(struct node));

    current->id = next_id;
    next_id++;
    current->symbol = (char *)malloc(sizeof(char));
    *current->symbol = string[index];
    current->next_char = NULL;
    current->next_word = NULL;

    // if the string is done, add it
    if (strlen(string) - 1 == index) {
        current->element = (int *)malloc(sizeof(int));
        *(int *)current->element = value;
    }

    // add the current node as child of the parent
    parent->next_word = (struct node *)malloc(sizeof(struct node*));
    parent->next_word = current;

    // recursive call with rest of the string
    create_trie_rec(current, string, index + 1, value);
}

void insert_trie(struct node *root, char *element, int value) {
    insert_trie_rec(root, NULL, element, 0, value);
}

void insert_trie_rec(struct node *n, struct node *prev, char *element,
    int index, int value) {

    if (strlen(element) == index)
        return;

    struct node *current = n;

    // search the current char in the top level
    while (current != NULL && element[index] != *current->symbol) {
        current = current->next_char;
    }

    if (current != NULL) {
        // found, go to the next level
        insert_trie_rec(current->next_word, current, element, index + 1, value);
    } else {
        int first = 1;
        for (; index < strlen(element); index++) {
            struct node *new = (struct node *)malloc(sizeof(struct node));

            new->id = next_id;
            next_id++;
            new->symbol = (char *)malloc(sizeof(char));
            *new->symbol = element[index];
            new->next_char = NULL;
            new->next_word = NULL;

            if (strlen(element) - 1 == index) {
                new->element = (int *)malloc(sizeof(int));
                *(int *)new->element = value;
            }

            if (n == NULL || !first) {
                prev->next_word = new;
            } else {
                while (n->next_char != NULL) {
                    n = n->next_char;
                }
                n->next_char = new;
                first = 0;
            }
            prev = new;
        }
    }
}

void destroy_trie(struct node *root) {
    destroy_trie_rec(root);
}

void destroy_trie_rec(struct node *n) {
    if (n != NULL) {
        destroy_trie_rec(n->next_char);
        destroy_trie_rec(n->next_word);
    }
    free(n);
}

void dump_trie(struct node *root) {
    dump_trie_rec(root, 0);
    printf("\n");
}

void dump_trie_rec(struct node *n, int level) {
    if (n != NULL) {
        if (level) {
            printf("\n");
            level = 0;
        }
        if (n->symbol != NULL)
            printf("{id:%d} %c [{id:%d} %c]",
                n->id,
                *n->symbol,
                (n->next_char != NULL) ? n->next_char->id : -1,
                (n->next_char != NULL) ? *(n->next_char->symbol) : ' ');
        if (n->element != NULL)
            printf("[%d]", *(n->element));

        if (n->element == NULL)
            printf(" -> ");

        dump_trie_rec(n->next_word, 0);
        dump_trie_rec(n->next_char, 1);
    }
}

void solve() {
    char decoded[5001];
    solve_rec(root, 0, decoded, 0, 0);
}

void solve_rec(struct node *n, int index, char decoded[], int i, int error) {
    if (n == NULL) {
        printf("DECODE FAIL AT INDEX %d\n", error);
        return;
    }

    if (index == strlen(encoded) && error == -1) {
        decoded[i] = '\0';
        printf("%s\n", decoded);
        return;
    }
    if (index == strlen(encoded) && error >= 0) {
        printf("DECODE FAIL AT INDEX %d\n", error);
        return;
    }
    
    if (*(n->symbol) != encoded[index]) {
        int index_error = error;
        if (index_error == -1)
            index_error = index;
        solve_rec(n->next_char, index, decoded, i, index_error);
    } else if (n->element != NULL) {
        decoded[i] = *(n->element);
        solve_rec(root, index + 1, decoded, i + 1, -1);
        return;
    } else {
        int index_error = error;
        if (index_error == -1)
            index_error = index;
        solve_rec(n->next_word, index + 1, decoded, i, index_error);
    }
}

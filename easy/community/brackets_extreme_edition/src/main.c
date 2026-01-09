#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX_EXPRESSION_SIZE 2048

void solve(char expression[]);
bool is_open_bracket(char c);
bool is_close_bracket(char c);
bool correct_bracket(char c1, char c2);

int main() {
    char expression[MAX_EXPRESSION_SIZE + 1] = "";
    scanf("%s", expression);

    solve(expression);

    return 0;
}

void solve(char expression[]) {
    char stack[MAX_EXPRESSION_SIZE];
    int stack_size = 0;

    for (int i = 0; i < strlen(expression); i++) {
        char c = expression[i];

        if (!is_open_bracket(c) && !is_close_bracket(c))
            continue;
        if (is_open_bracket(c))
            stack[stack_size++] = c;
        if (is_close_bracket(c)) {
            char top = stack[stack_size - 1];
            if (correct_bracket(top, c))
                stack_size--;
            else {
                printf("false\n");
                return;
            }
        }
    }

    if (stack_size == 0) printf("true\n");
    else                 printf("false\n");
}

bool is_open_bracket(char c) {
    return (c == '(' || c == '[' || c == '{');
}

bool is_close_bracket(char c) {
    return (c == ')' || c == ']' || c == '}');
}

bool correct_bracket(char c1, char c2) {
    switch (c1) {
        case '(':
            if (c2 == ')')  return true;
            else            return false;
            break;
        case '[':
            if (c2 == ']')  return true;
            else            return false;
            break;
        case '{':
            if (c2 == '}')  return true;
            else            return false;
            break;
        default:
            return false;
            break;
    }
}

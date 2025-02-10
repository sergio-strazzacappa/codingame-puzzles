#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TEST            0
#define NUMBER_FILES    4

const char *INPUT_FILES[] = {
    "input/01_test_1.txt",
    "input/02_test_2.txt",
    "input/03_test_3.txt",
    "input/04_test_4.txt"
};

const char *OUTPUT_FILES[] = {
    "output/01_test_1.txt",
    "output/02_test_2.txt",
    "output/03_test_3.txt",
    "output/04_test_4.txt"
};

typedef struct entry {
    char label;
    int invoice;
    int payments[10];
    int number_of_payments;
} Entry;

int n;
int m;
int *invoices;
int *entries;

void solve(Entry solution[], int *solution_index);
void remove_invoices(int invoices[], int invoices_paid[], int index, int *n);

int main() {
    if (TEST) {
        for (int i = 0; i < NUMBER_FILES; i++) {
            FILE *fp;
            char line[30];
            Entry solution[10];
            int solution_index = 0;

            if ((fp = fopen(INPUT_FILES[i], "r"))  == 0) {
                printf("[ERROR] Can't open file %s\n", INPUT_FILES[i]);
                exit(1);
            }

            fgets(line, 30, fp);
            n = atoi(line);
            fgets(line, 30, fp);
            m = atoi(line);

            invoices = (int *)malloc(sizeof(int) * n);
            entries = (int *)malloc(sizeof(int) * m);

            for (int j = 0; j < n; j++) {
                fgets(line, 30, fp);
                invoices[j] = atoi(line);
            }

            for (int j = 0; j < m; j++) {
                fgets(line, 30, fp);
                entries[j] = atoi(line);
            }

            solve(solution, &solution_index);
            fclose(fp);

            if ((fp = fopen(OUTPUT_FILES[i], "r"))  == 0) {
                printf("[ERROR] Can't open file %s\n", OUTPUT_FILES[i]);
                exit(1);
            }

            int index = 0;
            int passed = 1;

            while (fgets(line, 30, fp)) {
                strtok(line, " "); // skip the label
                int inv = atoi(strtok(NULL, " "));

                if (inv != solution[index].invoice) {
                    passed = 0;
                    break;
                }

                strtok(NULL, " "); // skipt the separator

                for (int j = 0; j < solution[index].number_of_payments; j++) {
                    int pay = atoi(strtok(NULL, " \n"));

                    if (pay != solution[index].payments[j]) {
                        passed = 0;
                        break;
                    }
                }
                index++;

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
        Entry solution[10];
        int solution_index = 0;

        scanf("%d%d", &n, &m);
        invoices = (int *)malloc(sizeof(int) * n);
        entries = (int *)malloc(sizeof(int) * m);

        for (int i = 0; i < n; i++) {
            int invoice;
            scanf("%d", &invoice);
            invoices[i] = invoice;
        }

        for (int i = 0; i < m; i++) {
            int entry;
            scanf("%d", &entry);
            entries[i] = entry;
        }
        
        solve(solution, &solution_index);

        for (int i = 0; i < solution_index; i++) {
            printf("%c %d -", solution[i].label, solution[i].invoice);

            for (int j = 0; j < solution[i].number_of_payments; j++) {
                printf(" %d", solution[i].payments[j]);
            }
            printf("\n");
         }
    }
    return 0;
}

void solve(Entry solution[], int *solution_index) {
    int sum, invoices_paid[n], index, next;
    char letter = 'A';

    for (int i = 0; i < m; i++) {
        sum = 0;
        index = 0;
        next = 0;

        for (int j = 0; j < n; j++) {
            sum += invoices[j];
            invoices_paid[index++] = invoices[j];

            if (sum == entries[i])
                break;
            else if (sum > entries[i]) {
                sum -= invoices[j];
                sum -= invoices[j - 1];
                index -= 2;
                j--;
            } else if (sum != entries[i] && j == n - 1) {
                sum = 0;
                index = 0;
                j = next;
                next++;
            }
        }

        Entry e;

        e.label = letter;
        e.invoice = entries[i];

        for (int j = 0; j < index; j++) {
            e.payments[j] = invoices_paid[j];
            e.number_of_payments = j + 1;
        }

        solution[(*solution_index)++] = e;

        letter++;
        remove_invoices(invoices, invoices_paid, index, &n);
    }
}

void remove_invoices(int invoices[], int invoices_paid[], int index, int* n) {
    int size = *n;

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < index; j++) {
            if (invoices[i] == invoices_paid[j]) {
                invoices[i] = -1;
                invoices_paid[j] = -2;
                *n = *n - 1;
            }
        }
    }

    for (int i = 0; i < size; i++) {
        if (invoices[i] == -1) {
            for (int j = i; j < size; j++) {
                if (invoices[j] != -1) {
                    invoices[i] = invoices[j];
                    invoices[j] = -1;
                    break;
                }
            }
        }
    }
}

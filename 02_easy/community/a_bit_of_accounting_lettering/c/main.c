#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int n;
int m;
int *invoices;
int *entries;

void init();
void solve();
void remove_invoices(int invoices[], int invoices_paid[], int index, int *n);
void clean();

int main() {
    init();
    solve();
    clean();

    return 0;
}

void init() {
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
}

void solve() {
    int sum, invoices_paid[n], index, next;
    char letter = 'A';

    for (int i = 0; i < m; i++) {
        // for every payment
        sum = 0;
        index = 0;
        next = 0;

        for (int j = 0; j < n; j++) {
            // for every invoice
            sum += invoices[j];
            invoices_paid[index++] = invoices[j];

            if (sum == entries[i])
                // solution found
                break;
            else if (sum > entries[i]) {
                // try different invoices
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

        printf("%c %d -", letter, entries[i]);

        for (int j = 0; j < index; j++)
            printf(" %d", invoices_paid[j]);
         printf("\n"); 

        letter++;
        remove_invoices(invoices, invoices_paid, index, &n);
    }
}

void clean() {
    free(invoices);
    free(entries);
}

void remove_invoices(int invoices[], int invoices_paid[], int index, int *n) {
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

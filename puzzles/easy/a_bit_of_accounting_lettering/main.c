#include <stdio.h>

void remove_invoices(int invoices[], int invoices_paid[], int index, int* n) {
    int size = *n;

    //fprintf(stderr, "REMOVE\nIndex: %d, n: %d, size: %d\n", index, *n, size);
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < index; j++) {
            if (invoices[i] == invoices_paid[j]) {
                invoices[i] = -1;
                invoices_paid[j] = -2;
                *n = *n - 1;
            }
        }
    }

    /*for (int i = 0; i < size; i++) {
        fprintf(stderr, "%d ", invoices[i]);
    }
    fprintf(stderr, "\n");*/

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

int main() {
    int n, m;
    scanf("%d%d", &n, &m);

    int invoices[n];
    int entries[m];
    char letter = 'A';

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

    for (int i = 0; i < m; i++) {
        //fprintf(stderr, "New iteration\n");

        /*for (int i = 0; i < n; i++) {
            fprintf(stderr, "%d ", invoices[i]);
        }
        fprintf(stderr, "\n");*/

        int sum = 0;
        int invoices_paid[n];
        int index = 0;
        int next = 0;

        for (int j = 0; j < n; j++) {
            //fprintf(stderr, "Invoice: %d\n", invoices[j]);
            //fprintf(stderr, "Index: %d\n", index);
            //fprintf(stderr, "N: %d\n", n);

            sum += invoices[j];
            invoices_paid[index] = invoices[j];
            index++;
            if (sum == entries[i]) {
                //fprintf(stderr, "Break\n");
                break;
            } else if (sum > entries[i]) {
                sum -= invoices[j];
                sum -= invoices[j - 1];
                index--;
                index--;
                j--;
                //fprintf(stderr, "Restarting\n");
            } else if (sum != entries[i] && j == n - 1) {
                //fprintf(stderr, "Next iteration\n");
                sum = 0;
                index = 0;
                j = next;
                next++;
            }
        }

        printf("%c %d -",letter, entries[i]);
        for (int j = 0; j < index; j++) {
            printf(" %d", invoices_paid[j]);
        }
        printf("\n");
        letter++;
        remove_invoices(invoices, invoices_paid, index, &n);
    }

    return 0;
}
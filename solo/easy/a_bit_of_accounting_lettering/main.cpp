#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void clear(vector<int> pays, vector<int> &bills) {
    for (int i = 0; i < pays.size(); i++) {
        for (int j = 0; j < bills.size(); j++) {
            if (pays[i] == bills[j]) {
                bills.erase(bills.begin() + j);
                break;
            }
        }
    }
}

void match(int payment_entry, vector<int> &bills, char &letter) {
    vector<int> pays;
    int sum = 0;

    for (int i = 0; i < bills.size(); i++) {
        if (sum == payment_entry) {
            break;
        }
        sum = 0;
        pays.clear();
        for (int j = i; j < bills.size(); j++) {
            sum += bills[j];
            pays.push_back(bills[j]);
            if (sum > payment_entry) {
                sum -= pays[pays.size() - 1];
                pays.pop_back();
            } else if (sum == payment_entry) {
                break;
            }
        }
    }

    cout << letter << " " << payment_entry << " - ";
    vector<int> to_delete;

    for (int i = 0; i < bills.size(); i++) {
        for (int j = 0; j < pays.size(); j++) {
            if (pays[j] == bills[i]) {
                cout << pays[j];
                to_delete.push_back(pays[j]);
                pays.erase(pays.begin() + j);
                if (pays.size() >= 1) {
                    cout << " ";
                }
                break;
            }
        }
    }

    cout << endl;

    letter++;

    clear(to_delete, bills);
}

int main() {
    int n, m;
    cin >> n >> m;
    cin.ignore();

    vector<int> bills;
    char letter = 'A';

    for (int i = 0; i < n; i++) {
        int invoice;
        cin >> invoice;
        cin.ignore();
        bills.push_back(invoice);
    }

    for (int i = 0; i < m; i++) {
        int payment_entry;
        cin >> payment_entry;
        cin.ignore();
        
        match(payment_entry, bills, letter);
    }

    return 0;
}
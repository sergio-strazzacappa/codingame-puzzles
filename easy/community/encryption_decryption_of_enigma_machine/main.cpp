#include <iostream>

using namespace std;

string encode(string message, int shift, string rotor1, string rotor2,
    string rotor3) {

    string encoded_message = message;

    for (int i = 0; i < message.size(); i++) {
        int c = toupper(message[i]) + shift + i;

        while (c > 90) {
            c -= 26;
        }

        c = rotor1[c - 65];
        c = rotor2[c - 65];
        c = rotor3[c - 65];

        encoded_message[i] = c;
    }

    return encoded_message;
}

string decode(string message, int shift, string rotor1, string rotor2,
    string rotor3) {

    string decoded_message = message;

    for (int i = 0; i < message.size(); i++) {
        int c = message[i];

        for (int j = 0; j < 26; j++) {
            if (rotor3[j] == c) {
                c = j + 65;
                break;
            }
        }

        for (int j = 0; j < 26; j++) {
            if (rotor2[j] == c) {
                c = j + 65;
                break;
            }
        }

        for (int j = 0; j < 26; j++) {
            if (rotor1[j] == c) {
                c = j + 65;
                break;
            }
        }

        c = toupper(c) - (shift + i);

        while (c < 65) {
            c += 26;
        }

        decoded_message[i] = c;
    }

    return decoded_message;

}

string solve(string operation, string message, int shift, string rotor1,
    string rotor2, string rotor3) {

    string m = "";

    if (operation == "ENCODE") {
        m = encode(message, shift, rotor1, rotor2, rotor3);
    } else {
        m = decode(message, shift, rotor1, rotor2, rotor3);
    }

    return m;
}

int main() {
    string operation;
    cin >> operation;
    cin.ignore();

    int pseudo_random_number;
    cin >> pseudo_random_number;
    cin.ignore();

    string rotor1, rotor2, rotor3;
    cin >> rotor1 >> rotor2 >> rotor3;
    cin.ignore();

    string message;
    cin >> message;
    cin.ignore();

    string m = 
        solve(operation, message, pseudo_random_number, rotor1, rotor2, rotor3);

    cout << m << endl;
}
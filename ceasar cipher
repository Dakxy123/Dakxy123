#include <iostream>
#include <string>
using namespace std;

// Function to encrypt plaintext using Caesar Cipher
string encrypt(const string &plaintext, int shift) {
    string ciphertext = "";
    for (char ch : plaintext) {
        if (isalpha(ch)) {
            char base = islower(ch) ? 'a' : 'A';
            ciphertext += char((ch - base + shift) % 26 + base);
        } else {
            ciphertext += ch; // Non-alphabetic characters remain unchanged
        }
    }
    return ciphertext;
}

// Function to decrypt ciphertext using Caesar Cipher
string decrypt(const string &ciphertext, int shift) {
    return encrypt(ciphertext, 26 - (shift % 26)); // Decrypt by shifting backwards
}

// Function to display results
void displayResults(const string &text, int shift, bool isEncrypt) {
    cout << (isEncrypt ? "Encrypting" : "Decrypting") << " the text: \"" << text << "\" with a shift of " << shift << endl;
    string result = isEncrypt ? encrypt(text, shift) : decrypt(text, shift);
    cout << "Result: " << result << endl;
}

int main() {
    char choice;
    do {
        cout << "=== Caesar Cipher Options ===" << endl;
        cout << "1. Encrypt" << endl;
        cout << "2. Decrypt" << endl;
        cout << "=============================" << endl;
        cout << "Enter your choice (1 or 2): ";
        
        int option;
        cin >> option;

        cin.ignore(); // To ignore the newline character after the option
        string text;
        int shift;

        cout << "Enter the text: ";
        getline(cin, text);
        cout << "Enter the shift value (1-25): ";
        cin >> shift;

        if (option == 1) {
            displayResults(text, shift, true);
        } else if (option == 2) {
            displayResults(text, shift, false);
        } else {
            cout << "Invalid option! Please select 1 or 2." << endl;
        }

        cout << "\nWould you like to perform another operation? (y/n): ";
        cin >> choice;
    } while (choice == 'y' || choice == 'Y');

    cout << "Thank you for using the Caesar Cipher Calculator!" << endl;
    return 0;
}

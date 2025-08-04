#include <iostream>
#include <vector>
#include <iomanip>
using namespace std;

vector<string> egyptianFraction(int numerator, int denominator) {
    vector<string> result;
    cout << "Starting with: " << numerator << "/" << denominator << endl;
    while (numerator != 0) {
        int x = denominator / numerator + (denominator % numerator != 0);
        result.push_back("1/" + to_string(x));
        
        // Display current step
        cout << "Next unit fraction: 1/" << x << endl;
        cout << "Update: " << numerator << "/" << denominator << " - 1/" << x << endl;

        numerator = numerator * x - denominator;
        denominator = denominator * x;
        
        cout << "New Fraction: " << numerator << "/" << denominator << endl;
        cout << "------------------------------------" << endl;
    }
    return result;
}

void displayEgyptianFraction(int numerator, int denominator) {
    cout << "\nEgyptian Fraction representation of " << numerator << "/" << denominator << " is: ";
    vector<string> fractions = egyptianFraction(numerator, denominator);
    for (size_t i = 0; i < fractions.size(); ++i) {
        cout << fractions[i];
        if (i < fractions.size() - 1) cout << " + ";
    }
    cout << endl;
}

int main() {
    char choice;
    do {
        int numerator, denominator;
        cout << "Enter the numerator: ";
        cin >> numerator;
        cout << "Enter the denominator: ";
        cin >> denominator;

        displayEgyptianFraction(numerator, denominator);

        cout << "\nWould you like to perform another calculation? (y/n): ";
        cin >> choice;
    } while (choice == 'y' || choice == 'Y');
    
    cout << "Thank you for using the Egyptian Fraction Calculator!" << endl;
    return 0;
}

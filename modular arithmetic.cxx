#include <iostream>
#include <limits>
using namespace std;

// Modular Arithmetic Functions
int modAdd(int a, int b, int mod) {
    return (a + b) % mod;
}

int modSub(int a, int b, int mod) {
    return (a - b + mod) % mod;
}

int modMul(int a, int b, int mod) {
    return (a * b) % mod;
}

int modExp(int base, int exp, int mod) {
    int result = 1;
    base = base % mod;
    while (exp > 0) {
        if (exp % 2 == 1)
            result = (result * base) % mod;
        exp = exp >> 1;
        base = (base * base) % mod;
    }
    return result;
}

int modInverse(int b, int m) {
    int m0 = m, t, q;
    int x0 = 0, x1 = 1;
    if (m == 1) return 0;
    while (b > 1) {
        q = b / m;
        t = m;
        m = b % m;
        b = t;
        t = x0;
        x0 = x1 - q * x0;
        x1 = t;
    }
    if (x1 < 0) x1 += m0;
    return x1;
}

int modDiv(int a, int b, int mod) {
    int inv = modInverse(b, mod);
    if (inv == 0) {
        cout << "Division not possible (no modular inverse found).\n";
        return -1;
    }
    return (a * inv) % mod;
}

// Display Menu
void displayMenu() {
    cout << "\n=== Modular Arithmetic Options ===\n";
    cout << "1. Modular Addition\n";
    cout << "2. Modular Subtraction\n";
    cout << "3. Modular Multiplication\n";
    cout << "4. Modular Division\n";
    cout << "5. Modular Exponentiation\n";
    cout << "===================================\n";
    cout << "Enter your choice: ";
}

int main() {
    int choice, a, b, mod, exp;

    displayMenu();
    cin >> choice;

    cout << "Enter the first number (a): ";
    cin >> a;
    cout << "Enter the second number (b): ";
    cin >> b;
    cout << "Enter the modulus (mod): ";
    cin >> mod;

    switch (choice) {
        case 1:
            cout << "[Formula] = (" << a << " + " << b << ") mod " << mod << endl;
            cout << "Result of Modular Addition: " << modAdd(a, b, mod) << " mod " << mod << endl;
            break;
        case 2:
            cout << "[Formula] = (" << a << " - " << b << ") mod " << mod << endl;
            cout << "Result of Modular Subtraction: " << modSub(a, b, mod) << " mod " << mod << endl;
            break;
        case 3:
            cout << "[Formula] = (" << a << " * " << b << ") mod " << mod << endl;
            cout << "Result of Modular Multiplication: " << modMul(a, b, mod) << " mod " << mod << endl;
            break;
        case 4:
            cout << "[Formula] = (" << a << " / " << b << ") mod " << mod << endl;
            cout << "Result of Modular Division: " << modDiv(a, b, mod) << " mod " << mod << endl;
            break;
        case 5:
            cout << "Enter the exponent: ";
            cin >> exp;
            cout << "[Formula] = (" << a << " ^ " << exp << ") mod " << mod << endl;
            cout << "Result of Modular Exponentiation: " << modExp(a, exp, mod) << " mod " << mod << endl;
            break;
        default:
            cout << "Invalid choice! Please try again.\n";
    }

    // Ask if user wants to perform another operation
    char repeat;
    cout << "\nWould you like to perform another operation? (y/n): ";
    cin >> repeat;
    while (repeat == 'y' || repeat == 'Y') {
        displayMenu();
        cin >> choice;

        cout << "Enter the first number (a): ";
        cin >> a;
        cout << "Enter the second number (b): ";
        cin >> b;
        cout << "Enter the modulus (mod): ";
        cin >> mod;

        switch (choice) {
            case 1:
                cout << "[Formula] = (" << a << " + " << b << ") mod " << mod << endl;
                cout << "Result of Modular Addition: " << modAdd(a, b, mod) << " mod " << mod << endl;
                break;
            case 2:
                cout << "[Formula] = (" << a << " - " << b << ") mod " << mod << endl;
                cout << "Result of Modular Subtraction: " << modSub(a, b, mod) << " mod " << mod << endl;
                break;
            case 3:
                cout << "[Formula] = (" << a << " * " << b << ") mod " << mod << endl;
                cout << "Result of Modular Multiplication: " << modMul(a, b, mod) << " mod " << mod << endl;
                break;
            case 4:
                cout << "[Formula] = (" << a << " / " << b << ") mod " << mod << endl;
                cout << "Result of Modular Division: " << modDiv(a, b, mod) << " mod " << mod << endl;
                break;
            case 5:
                cout << "Enter the exponent: ";
                cin >> exp;
                cout << "[Formula] = (" << a << " ^ " << exp << ") mod " << mod << endl;
                cout << "Result of Modular Exponentiation: " << modExp(a, exp, mod) << " mod " << mod << endl;
                break;
            default:
                cout << "Invalid choice! Please try again.\n";
        }
        cout << "\nWould you like to perform another operation? (y/n): ";
        cin >> repeat;
    }

    cout << "Thank you for using the Modular Arithmetic Program!\n";
    return 0;
}

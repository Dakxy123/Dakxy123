#include <iostream>
#include <string>
#include <algorithm>
#include <cmath>
#include <cctype>

using namespace std;

// Convert a number from a given base to decimal
double toDecimal(string number, int base) {
    size_t dotPos = number.find('.');
    string integerPart = (dotPos == string::npos) ? number : number.substr(0, dotPos);
    string fractionalPart = (dotPos == string::npos) ? "" : number.substr(dotPos + 1);

    double decimal = 0;
    int power = 0;

    // Convert integer part
    cout << "Converting " << integerPart << " from base " << base << " to decimal (Integer part):" << endl;
    reverse(integerPart.begin(), integerPart.end());
    for (char digit : integerPart) {
        int value = (isdigit(digit)) ? digit - '0' : toupper(digit) - 'A' + 10;
        if (value >= base) {
            cout << "Error: Invalid digit '" << digit << "' for base " << base << endl;
            return -1;
        }
        cout << "Adding " << value << " * " << base << "^" << power << " = " << value * pow(base, power) << endl;
        decimal += value * pow(base, power++);
    }

    // Convert fractional part
    cout << "Converting " << fractionalPart << " from base " << base << " to decimal (Fractional part):" << endl;
    power = -1;
    for (char digit : fractionalPart) {
        int value = (isdigit(digit)) ? digit - '0' : toupper(digit) - 'A' + 10;
        if (value >= base) {
            cout << "Error: Invalid digit '" << digit << "' for base " << base << endl;
            return -1;
        }
        cout << "Adding " << value << " * " << base << "^" << power << " = " << value * pow(base, power) << endl;
        decimal += value * pow(base, power--);
    }

    cout << "Total decimal value: " << decimal << endl;
    return decimal;
}

// Convert a number from decimal to a given base
string fromDecimal(double decimal, int base) {
    int integerPart = static_cast<int>(decimal);
    double fractionalPart = decimal - integerPart;
    string result = "", fractionalResult = ".";

    // Convert integer part
    cout << "Converting " << integerPart << " from decimal to base " << base << " (Integer part):" << endl;
    if (integerPart == 0) {
        result = "0";
    }
    while (integerPart > 0) {
        int remainder = integerPart % base;
        cout << integerPart << " / " << base << ", Remainder = " << remainder << ", Quotient = " << integerPart / base << endl;
        result = ((remainder < 10) ? to_string(remainder) : string(1, 'A' + remainder - 10)) + result;
        integerPart /= base;
    }

    // Convert fractional part
    cout << "Converting fractional part from decimal to base " << base << " (Fractional part):" << endl;
    while (fractionalPart > 0 && fractionalResult.length() <= 20) {
        fractionalPart *= base;
        int digit = static_cast<int>(fractionalPart);
        fractionalResult += (digit < 10) ? to_string(digit) : string(1, 'A' + digit - 10);
        fractionalPart -= digit;
        cout << fractionalPart << " -> Digit = " << digit << endl;
    }

    cout << "Total converted value: " << result + fractionalResult << endl;
    return result + fractionalResult;
}

// Perform basic arithmetic operations
double performOperation(double num1, double num2, char op) {
    switch (op) {
        case '+': return num1 + num2;
        case '-': return num1 - num2;
        case '*': return num1 * num2;
        case '/': return (num2 != 0) ? num1 / num2 : 0;
        default: return 0;
    }
}

// Get base from user's choice
int getBaseFromChoice(char choice) {
    switch (choice) {
        case 'a': return 2;  // Binary
        case 'b': return 8;  // Octal
        case 'c': return 10; // Decimal
        case 'd': return 16; // Hexadecimal
        default: return -1;
    }
}

int main() {
    char cont = 'y';
    while (cont == 'y' || cont == 'Y') {
        string num1, num2;
        char baseChoice, operation;

        cout << "Select the base of the numbers:\n";
        cout << "a) Binary (base 2)\n";
        cout << "b) Octal (base 8)\n";
        cout << "c) Decimal (base 10)\n";
        cout << "d) Hexadecimal (base 16)\n";
        cout << "Enter your choice (a, b, c, d): ";
        cin >> baseChoice;

        int base = getBaseFromChoice(baseChoice);
        if (base == -1) {
            cout << "Invalid choice!" << endl;
            continue;  // Continue to the next iteration of the loop
        }

        cout << "Enter the first number: ";
        cin >> num1;
        cout << "Enter the second number: ";
        cin >> num2;
        cout << "Enter the operation (+, -, *, /): ";
        cin >> operation;

        double decimalNum1 = toDecimal(num1, base);
        double decimalNum2 = toDecimal(num2, base);

        if (decimalNum1 == -1 || decimalNum2 == -1) {
            cout << "Error: Conversion failed due to invalid input!" << endl;
            continue;  // Continue to the next iteration of the loop
        }

        if (operation == '/' && decimalNum2 == 0) {
            cout << "Error: Division by zero is not allowed!" << endl;
            continue;  // Continue to the next iteration of the loop
        }

        cout << "Performing calculation: " << decimalNum1 << " " << operation << " " << decimalNum2 << endl;
        double resultDecimal = performOperation(decimalNum1, decimalNum2, operation);
        string result = fromDecimal(resultDecimal, base);

        cout << "Result in decimal: " << resultDecimal << endl;
        cout << "Result in base " << base << ": " << result << endl;

        cout << "Do you want to perform another calculation? (y/n): ";
        cin >> cont;
    }

    return 0;
}

#include <iostream>
#include <string>
#include <sstream>
#include <cmath>
#include <algorithm>

using namespace std;

double binaryToDecimal(string binary) {
    size_t dotPos = binary.find('.');
    string integerPart = (dotPos == string::npos) ? binary : binary.substr(0, dotPos);
    string fractionalPart = (dotPos == string::npos) ? "" : binary.substr(dotPos + 1);
    
    double decimal = 0;
    int power = 0;
    
    cout << "Converting Binary to Decimal (Integer Part):\n";
    for (int i = integerPart.length() - 1; i >= 0; --i) {
        if (integerPart[i] == '1') {
            cout << "Adding 2^" << power << " = " << pow(2, power) << endl;
            decimal += pow(2, power);
        }
        ++power;
    }
    
    cout << "Converting Binary to Decimal (Fractional Part):\n";
    power = -1;
    for (char c : fractionalPart) {
        if (c == '1') {
            cout << "Adding 2^" << power << " = " << pow(2, power) << endl;
            decimal += pow(2, power);
        }
        --power;
    }
    
    cout << "Result: " << decimal << endl;
    return decimal;
}

string decimalToBinary(double decimal) {
    int integerPart = static_cast<int>(decimal);
    double fractionalPart = decimal - integerPart;
    string binary = "";
  
    cout << "Converting Decimal to Binary (Integer Part):\n";
    if (integerPart == 0) {
        binary = "0";
    }
    while (integerPart > 0) {
        int remainder = integerPart % 2;
        cout << integerPart << " / 2, Remainder = " << remainder << ", Quotient = " << integerPart / 2 << endl;
        binary = to_string(remainder) + binary;
        integerPart /= 2;
    }
    
    cout << "Converting Decimal to Binary (Fractional Part):\n";
    string fractionalBinary = ".";
    while (fractionalPart > 0) {
        if (fractionalBinary.length() > 20) break;  
        fractionalPart *= 2;
        int bit = static_cast<int>(fractionalPart);
        cout << fractionalPart << " -> Bit = " << bit << endl;
        if (bit == 1) {
            fractionalBinary += '1';
            fractionalPart -= bit;
        } else {
            fractionalBinary += '0';
        }
    }
    
    cout << "Binary result: " << binary + fractionalBinary << endl;
    return binary + fractionalBinary;
}

string decimalToOctal(double decimal) {
    int integerPart = static_cast<int>(decimal);
    double fractionalPart = decimal - integerPart;
    string octal = "";

    cout << "Converting Decimal to Octal (Integer Part):\n";
    if (integerPart == 0) {
        octal = "0";
    }
    while (integerPart > 0) {
        int remainder = integerPart % 8;
        cout << integerPart << " / 8, Remainder = " << remainder << ", Quotient = " << integerPart / 8 << endl;
        octal = to_string(remainder) + octal;
        integerPart /= 8;
    }
    
    cout << "Converting Decimal to Octal (Fractional Part):\n";
    string fractionalOctal = ".";
    while (fractionalPart > 0) {
        if (fractionalOctal.length() > 20) break; 
        fractionalPart *= 8;
        int digit = static_cast<int>(fractionalPart);
        cout << fractionalPart << " -> Digit = " << digit << endl;
        fractionalOctal += to_string(digit);
        fractionalPart -= digit;
    }
    
    cout << "Octal result: " << octal + fractionalOctal << endl;
    return octal + fractionalOctal;
}

double octalToDecimal(string octal) {
    size_t dotPos = octal.find('.');
    string integerPart = (dotPos == string::npos) ? octal : octal.substr(0, dotPos);
    string fractionalPart = (dotPos == string::npos) ? "" : octal.substr(dotPos + 1);
    
    double decimal = 0;
    int power = 0;
    
    cout << "Converting Octal to Decimal (Integer Part):\n";
    for (int i = integerPart.length() - 1; i >= 0; --i) {
        int digit = integerPart[i] - '0';
        cout << "Adding " << digit << " * 8^" << power << " = " << digit * pow(8, power) << endl;
        decimal += digit * pow(8, power);
        ++power;
    }
    
    cout << "Converting Octal to Decimal (Fractional Part):\n";
    power = -1;
    for (char c : fractionalPart) {
        int digit = c - '0';
        cout << "Adding " << digit << " * 8^" << power << " = " << digit * pow(8, power) << endl;
        decimal += digit * pow(8, power);
        --power;
    }
    
    cout << "Result: " << decimal << endl;
    return decimal;
}

string decimalToHexadecimal(double decimal) {
    int integerPart = static_cast<int>(decimal);
    double fractionalPart = decimal - integerPart;
    string hex = "";
    
    cout << "Converting Decimal to Hexadecimal (Integer Part):\n";
    if (integerPart == 0) {
        hex = "0";
    }
    while (integerPart > 0) {
        int remainder = integerPart % 16;
        cout << integerPart << " / 16, Remainder = " << remainder << ", Quotient = " << integerPart / 16 << endl;
        if (remainder < 10) {
            hex = to_string(remainder) + hex;
        } else {
            hex = char('A' + remainder - 10) + hex;
        }
        integerPart /= 16;
    }
    
    cout << "Converting Decimal to Hexadecimal (Fractional Part):\n";
    string fractionalHex = ".";
    while (fractionalPart > 0) {
        if (fractionalHex.length() > 20) break;  
        fractionalPart *= 16;
        int digit = static_cast<int>(fractionalPart);
        cout << fractionalPart << " -> Digit = " << digit << endl;
        if (digit < 10) {
            fractionalHex += to_string(digit);
        } else {
            fractionalHex += char('A' + digit - 10);
        }
        fractionalPart -= digit;
    }
    
    cout << "Hexadecimal result: " << hex + fractionalHex << endl;
    return hex + fractionalHex;
}

double hexadecimalToDecimal(string hex) {
    size_t dotPos = hex.find('.');
    string integerPart = (dotPos == string::npos) ? hex : hex.substr(0, dotPos);
    string fractionalPart = (dotPos == string::npos) ? "" : hex.substr(dotPos + 1);
    
    double decimal = 0;
    int power = 0;
    
    cout << "Converting Hexadecimal to Decimal (Integer Part):\n";
    for (int i = integerPart.length() - 1; i >= 0; --i) {
        int digit;
        if (integerPart[i] >= '0' && integerPart[i] <= '9') {
            digit = integerPart[i] - '0';
        } else {
            digit = integerPart[i] - 'A' + 10;
        }
        cout << "Adding " << digit << " * 16^" << power << " = " << digit * pow(16, power) << endl;
        decimal += digit * pow(16, power);
        ++power;
    }
    
    cout << "Converting Hexadecimal to Decimal (Fractional Part):\n";
    power = -1;
    for (char c : fractionalPart) {
        int digit;
        if (c >= '0' && c <= '9') {
            digit = c - '0';
        } else {
            digit = c - 'A' + 10;
        }
        cout << "Adding " << digit << " * 16^" << power << " = " << digit * pow(16, power) << endl;
        decimal += digit * pow(16, power);
        --power;
    }
    
    cout << "Result: " << decimal << endl;
    return decimal;
}

string binaryToOctal(string binary) {
    double decimal = binaryToDecimal(binary);
    return decimalToOctal(decimal);
}

string octalToBinary(string octal) {
    double decimal = octalToDecimal(octal);
    return decimalToBinary(decimal);
}

string binaryToHexadecimal(string binary) {
    double decimal = binaryToDecimal(binary);
    return decimalToHexadecimal(decimal);
}

string hexadecimalToBinary(string hex) {
    double decimal = hexadecimalToDecimal(hex);
    return decimalToBinary(decimal);
}

string octalToHexadecimal(string octal) {
    double decimal = octalToDecimal(octal);
    return decimalToHexadecimal(decimal);
}

string hexadecimalToOctal(string hex) {
    double decimal = hexadecimalToDecimal(hex);
    return decimalToOctal(decimal);
}

int main() {
    char cont = 'y';
    
    while (cont == 'y' || cont == 'Y') {
        int choice;
        string input;
        cout << "Select the conversion you want to perform:\n";
        cout << "1. Binary to Decimal\n";
        cout << "2. Decimal to Binary\n";
        cout << "3. Decimal to Octal\n";
        cout << "4. Octal to Decimal\n";
        cout << "5. Decimal to Hexadecimal\n";
        cout << "6. Hexadecimal to Decimal\n";
        cout << "7. Binary to Octal\n";
        cout << "8. Octal to Binary\n";
        cout << "9. Binary to Hexadecimal\n";
        cout << "10. Hexadecimal to Binary\n";
        cout << "11. Octal to Hexadecimal\n";
        cout << "12. Hexadecimal to Octal\n";
        
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter a binary number: ";
                cin >> input;
                binaryToDecimal(input);
                break;
            case 2:
                double decimal;
                cout << "Enter a decimal number: ";
                cin >> decimal;
                decimalToBinary(decimal);
                break;
            case 3:
                cout << "Enter a decimal number: ";
                cin >> decimal;
                decimalToOctal(decimal);
                break;
            case 4:
                cout << "Enter an octal number: ";
                cin >> input;
                octalToDecimal(input);
                break;
            case 5:
                cout << "Enter a decimal number: ";
                cin >> decimal;
                decimalToHexadecimal(decimal);
                break;
            case 6:
                cout << "Enter a hexadecimal number: ";
                cin >> input;
                hexadecimalToDecimal(input);
                break;
            case 7:
                cout << "Enter a binary number: ";
                cin >> input;
                binaryToOctal(input);
                break;
            case 8:
                cout << "Enter an octal number: ";
                cin >> input;
                octalToBinary(input);
                break;
            case 9:
                cout << "Enter a binary number: ";
                cin >> input;
                binaryToHexadecimal(input);
                break;
            case 10:
                cout << "Enter a hexadecimal number: ";
                cin >> input;
                hexadecimalToBinary(input);
                break;
            case 11:
                cout << "Enter an octal number: ";
                cin >> input;
                octalToHexadecimal(input);
                break;
            case 12:
                cout << "Enter a hexadecimal number: ";
                cin >> input;
                hexadecimalToOctal(input);
                break;
            default:
                cout << "Invalid choice!";
                break;
        }

        cout << "\nDo you want to perform another conversion? (y/n): ";
        cin >> cont;
    }

    return 0;
}

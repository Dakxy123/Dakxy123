#include <iostream>
#include <vector>
using namespace std;

// Function to calculate GCD using the Division Method (Euclidean Algorithm)
int gcdDivisionMethod(int a, int b) {
    cout << "Using Division Method:" << endl;
    while (b != 0) {
        cout << "GCD(" << a << ", " << b << ") => ";
        int remainder = a % b;
        cout << "a % b = " << remainder << endl;
        a = b;
        b = remainder;
    }
    cout << "GCD = " << a << endl;
    return a;
}

// Function to find all divisors of a number
vector<int> findDivisors(int n) {
    vector<int> divisors;
    for (int i = 1; i <= n; ++i) {
        if (n % i == 0) divisors.push_back(i);
    }
    return divisors;
}

// Function to calculate GCD using the Common Factorization Method
int gcdCommonFactorization(int a, int b) {
    cout << "Using Common Factorization Method:" << endl;
    vector<int> divisorsA = findDivisors(a);
    vector<int> divisorsB = findDivisors(b);
    
    cout << "Divisors of " << a << ": ";
    for (int div : divisorsA) cout << div << " ";
    cout << endl;

    cout << "Divisors of " << b << ": ";
    for (int div : divisorsB) cout << div << " ";
    cout << endl;

    int gcd = 1;
    for (int divA : divisorsA) {
        for (int divB : divisorsB) {
            if (divA == divB) {
                gcd = divA;  // Update gcd to the largest common divisor
            }
        }
    }
    cout << "GCD = " << gcd << endl;
    return gcd;
}

// Function to calculate GCD for a list of numbers using any method
int calculateGCD(int a, int b, int choice) {
    if (choice == 1) {
        return gcdDivisionMethod(a, b);
    } else if (choice == 2) {
        return gcdCommonFactorization(a, b);
    } else {
        return -1;  // Invalid choice
    }
}

// Main function
int main() {
    int a, b, choice;
    vector<int> numbers;
    
    // Input for first two numbers
    cout << "Enter the first number: ";
    cin >> a;
    cout << "Enter the second number: ";
    cin >> b;
    numbers.push_back(a);
    numbers.push_back(b);
    
    // Ask if the user wants to add more numbers
    char addMore;
    do {
        cout << "Do you want to add more numbers? (y/n): ";
        cin >> addMore;
        if (addMore == 'y' || addMore == 'Y') {
            int nextNum;
            cout << "Enter the next number: ";
            cin >> nextNum;
            numbers.push_back(nextNum);
        }
    } while (addMore == 'y' || addMore == 'Y');
    
    // Choose method
    cout << "Choose method to calculate GCD:\n";
    cout << "1. Division Method\n";
    cout << "2. Common Factorization Method\n";
    cout << "Enter your choice (1 or 2): ";
    cin >> choice;

    // Calculate GCD for all numbers
    int gcd = numbers[0];
    for (int i = 1; i < numbers.size(); i++) {
        gcd = calculateGCD(gcd, numbers[i], choice);
    }

    cout << "The GCD of the entered numbers is: " << gcd << endl;
    return 0;
}

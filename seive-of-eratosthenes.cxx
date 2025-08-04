#include <iostream>
#include <vector>
using namespace std;

void sieveOfEratosthenes(int minLimit, int maxLimit) {
    vector<bool> isPrime(maxLimit + 1, true);
    isPrime[0] = isPrime[1] = false; // 0 and 1 are not prime numbers

    cout << "Starting Sieve of Eratosthenes from " << minLimit << " to " << maxLimit << "...\n";

    for (int i = 2; i * i <= maxLimit; i++) {
        if (isPrime[i]) {
            cout << "Found prime: " << i << endl; // Found a prime number
            for (int j = i * i; j <= maxLimit; j += i) {
                cout << "Marking multiple as non-prime: " << j << endl; // Marking non-prime
                isPrime[j] = false;
            }
        }
    }

    cout << "Prime numbers between " << minLimit << " and " << maxLimit << ":\n";
    for (int i = minLimit; i <= maxLimit; i++) {
        if (isPrime[i]) {
            cout << i << " "; // Print only prime numbers
        }
    }
    cout << endl;
}

int main() {
    int minLimit, maxLimit;

    cout << "Enter the minimum limit (0 or 1 is acceptable, but prime numbers start from 2): ";
    cin >> minLimit;
    cout << "Enter the maximum limit: ";
    cin >> maxLimit;

    if (minLimit < 0) {
        cout << "Minimum limit must be greater than or equal to 0.\n";
    } else if (maxLimit < minLimit) {
        cout << "Maximum limit must be greater than or equal to the minimum limit.\n";
    } else {
        // Adjust the minLimit to 2 if it's less than 2 for prime calculation
        if (minLimit < 2) minLimit = 2;
        sieveOfEratosthenes(minLimit, maxLimit);
    }

    return 0;
}

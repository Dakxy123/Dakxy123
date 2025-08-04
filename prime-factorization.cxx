#include <iostream>
#include <cmath>
using namespace std;

void primeFactors(int n) 
{
    bool first = true;  
    int original_n = n; 

    cout << "Finding prime factors for " << n << "...\n";

    while (n % 2 == 0) 
    {
        if (!first) cout << " × ";
        cout << "2 (Remaining: " << n / 2 << ")";
        n = n / 2;
        first = false;
    }

    for (int i = 3; i <= sqrt(n); i += 2) 
    {
        while (n % i == 0) 
        {
            if (!first) cout << " × ";
            cout << i << " (Remaining: " << n / i << ")";
            n = n / i;
            first = false;
        }
    }

    if (n > 2) 
    {
        if (!first) cout << " × ";
        cout << n << " (Remaining: 1)";
    }

    cout << "\nFinal:\n";
    cout << original_n << " = ";

    n = original_n;
    first = true;

    while (n % 2 == 0) 
    {
        if (!first) cout << " × ";
        cout << 2;
        n = n / 2;
        first = false;
    }

    for (int i = 3; i <= sqrt(n); i += 2) 
    {
        while (n % i == 0) 
        {
            if (!first) cout << " × ";
            cout << i;
            n = n / i;
            first = false;
        }
    }

    if (n > 2) 
    {
        if (!first) cout << " × ";
        cout << n;
    }

    cout << "\nPrime factorization complete." << endl;
}

int main() 
{
    int n;
    cout << "Input a Number: ";
    cin >> n;
    primeFactors(n);
    return 0;
}

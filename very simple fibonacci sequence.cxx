#include <iostream>
using namespace std;

int main() {
    int n1, n2, nth, nextTerm;

    cout << "Enter the first number (n1): ";
    cin >> n1;
    cout << "Enter the second number (n2): ";
    cin >> n2;
    cout << "Enter the position of the nth term: ";
    cin >> nth;

    cout << "Output: " << n1 << "(n1)" << " -> " << n2 << "(n2)";

    for (int i = 3; i <= nth; ++i) {
        nextTerm = n1 + n2;
        cout << " -> " << nextTerm << "(n" << i << ")";
        n1 = n2;
        n2 = nextTerm;
    }

    cout << endl;
    return 0;
}

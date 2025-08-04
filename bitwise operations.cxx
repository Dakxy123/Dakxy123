#include <iostream>
#include <vector>
using namespace std;

int getInput(const string &prompt)
{
    int num;
    cout << prompt;
    cin >> num;
    return num;
}

void bitwiseOperations()
{
    vector<int> numbers;
    char continueInput;

    // Input the first number
    numbers.push_back(getInput("Enter a number: "));

    // Input the next number
    numbers.push_back(getInput("Enter another number: "));

    do
    {
        cout << "Do you want to add another number? (y/n): ";
        cin >> continueInput;
        if (continueInput == 'y' || continueInput == 'Y')
        {
            numbers.push_back(getInput("Enter another number: "));
        }
    } while (continueInput == 'y' || continueInput == 'Y');

    cout << "\nChoose a bitwise operation:\n";
    cout << "1. AND (&)\n";
    cout << "2. OR (|)\n";
    cout << "3. XOR (^)\n";
    cout << "Enter your choice: ";
    int choice;
    cin >> choice;

    int result = numbers[0];
    switch (choice)
    {
    case 1: // AND operation
        for (size_t i = 1; i < numbers.size(); ++i)
        {
            result &= numbers[i];
        }
        cout << "Result of AND operation: " << result << endl;
        break;
    case 2: // OR operation
        for (size_t i = 1; i < numbers.size(); ++i)
        {
            result |= numbers[i];
        }
        cout << "Result of OR operation: " << result << endl;
        break;
    case 3: // XOR operation
        for (size_t i = 1; i < numbers.size(); ++i)
        {
            result ^= numbers[i];
        }
        cout << "Result of XOR operation: " << result << endl;
        break;
    default:
        cout << "Invalid choice!" << endl;
        break;
    }
}

int main()
{
    bitwiseOperations();
    return 0;
}

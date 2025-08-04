#include <iostream>
#include <vector>
#include <iomanip> // For fixed and setprecision
#include <limits>  // For numeric_limits

using namespace std;

void coinChange(const vector<double>& coins, double amount) {
    vector<double> result;
    int coinCount = 0;

    for (int i = coins.size() - 1; i >= 0; i--) {
        while (amount >= coins[i]) {
            amount -= coins[i];
            result.push_back(coins[i]);
            coinCount++;
        }
    }

    cout << "\n--- Coin Change Result ---\n";
    cout << "Minimum coins needed: " << coinCount << "\n";
    cout << "Coins used: ";
    for (double coin : result) {
        cout << fixed << setprecision(2) << coin << " ";
    }
    cout << "\n--------------------------\n";
}

int main() {
    char choice;

    do {
        cout << "\n=== Coin Change Problem ===\n";
        cout << "Enter the amount (e.g., 63.75): ";
        double amount;
        cin >> amount;

        vector<double> coins;
        char addMore;

        do {
            double coin;
            cout << "Enter a coin denomination (e.g., 0.25) or -1 to finish: ";
            cin >> coin;

            if (coin < 0) break;
            coins.push_back(coin);

            cout << "Would you like to add another coin denomination? (y/n): ";
            cin >> addMore;

        } while (addMore == 'y' || addMore == 'Y');

        // Sort coins in descending order for the greedy algorithm
        sort(coins.rbegin(), coins.rend());

        coinChange(coins, amount);

        cout << "Would you like to perform another operation? (y/n): ";
        cin >> choice;

    } while (choice == 'y' || choice == 'Y');

    return 0;
}

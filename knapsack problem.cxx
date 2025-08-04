#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip> // For setprecision

using namespace std;

struct Item {
    double value;
    double weight;
    double ratio; // value/weight ratio
};

bool compare(Item a, Item b) {
    return a.ratio > b.ratio; // Sort in descending order of value/weight ratio
}

pair<double, int> knapsack(vector<Item>& items, double capacity) {
    double totalValue = 0.0;
    int itemCount = 0;

    for (const auto& item : items) {
        if (capacity == 0) break; // No more capacity

        if (item.weight <= capacity) {
            totalValue += item.value; // Take the whole item
            capacity -= item.weight;
            itemCount++; // Count the item
        } else {
            totalValue += item.ratio * capacity; // Take the fractional part of the item
            itemCount++; // Count the fractional item
            capacity = 0; // Knapsack is full
        }
    }
    return {totalValue, itemCount}; // Return total value and item count
}

int main() {
    char choice;
    do {
        cout << "\n=== Knapsack Problem ===\n";
        double capacity;
        cout << "Enter the maximum weight capacity of the knapsack: ";
        cin >> capacity;

        vector<Item> items;
        char addMore;

        do {
            Item item;
            cout << "Enter the value of the item: ";
            cin >> item.value;
            cout << "Enter the weight of the item: ";
            cin >> item.weight;
            item.ratio = item.value / item.weight; // Calculate value/weight ratio
            items.push_back(item);

            cout << "Would you like to add another item? (y/n): ";
            cin >> addMore;

        } while (addMore == 'y' || addMore == 'Y');

        sort(items.begin(), items.end(), compare); // Sort items by value/weight ratio
        auto result = knapsack(items, capacity);
        double maxValue = result.first;
        int totalItems = result.second;

        cout << fixed << setprecision(2);
        cout << "Maximum value that can be obtained: $" << maxValue << "\n";
        cout << "Total items that can fit: " << totalItems << "\n";

        cout << "Would you like to perform another operation? (y/n): ";
        cin >> choice;

    } while (choice == 'y' || choice == 'Y');

    return 0;
}

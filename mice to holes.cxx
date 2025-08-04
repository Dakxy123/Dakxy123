#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip> // For setprecision

using namespace std;

// Function to calculate minimum time for all mice to get into holes
int minTimeForMiceToHoles(vector<int>& mice, vector<int>& holes) {
    int n = min(mice.size(), holes.size()); // Use the smaller size for pairing
    sort(mice.begin(), mice.end()); // Sort mice positions
    sort(holes.begin(), holes.end()); // Sort holes positions

    int maxTime = 0;
    for (int i = 0; i < n; ++i) {
        maxTime = max(maxTime, abs(mice[i] - holes[i])); // Calculate max distance
    }
    return maxTime; // Return maximum time taken
}

int main() {
    char choice;
    do {
        int numMice, numHoles;
        cout << "\n=== Mice to Holes Problem ===\n";
        
        // Input for number of mice
        cout << "Enter the number of mice: ";
        cin >> numMice;
        vector<int> mice(numMice);
        
        cout << "Enter the positions of the mice:\n";
        for (int i = 0; i < numMice; ++i) {
            cout << "Mouse " << i + 1 << ": ";
            cin >> mice[i];
        }

        // Input for number of holes
        cout << "Enter the number of holes: ";
        cin >> numHoles;
        vector<int> holes(numHoles);
        
        cout << "Enter the positions of the holes:\n";
        for (int i = 0; i < numHoles; ++i) {
            cout << "Hole " << i + 1 << ": ";
            cin >> holes[i];
        }

        int result = minTimeForMiceToHoles(mice, holes);
        cout << "Minimum time for all mice to get into holes: " << result << endl;

        cout << "Would you like to perform another operation? (y/n): ";
        cin >> choice;

    } while (choice == 'y' || choice == 'Y');

    return 0;
}

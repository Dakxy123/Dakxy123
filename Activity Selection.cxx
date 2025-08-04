#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Structure to store an activity's start and finish times
struct Activity {
    int start, finish;
};

// Function to compare activities based on their finish times
bool compareActivities(Activity a1, Activity a2) {
    return a1.finish < a2.finish;
}

// Function to select maximum number of non-overlapping activities
void activitySelection(vector<Activity>& activities) {
    // Sort activities by finish time
    sort(activities.begin(), activities.end(), compareActivities);

    cout << "\n--- Activity Selection Process ---\n";

    // The first activity is always selected
    int n = activities.size();
    int lastSelected = 0; // Index of the last selected activity
    cout << "Activity " << lastSelected + 1 << " selected (start: " << activities[0].start << ", finish: " << activities[0].finish << ")\n";

    // Consider rest of the activities
    for (int i = 1; i < n; i++) {
        // If this activity has a start time greater than or equal to
        // the finish time of the previously selected activity
        if (activities[i].start >= activities[lastSelected].finish) {
            lastSelected = i;
            cout << "Activity " << lastSelected + 1 << " selected (start: " << activities[i].start << ", finish: " << activities[i].finish << ")\n";
        }
    }
    cout << "\nSelection process complete.\n";
}

int main() {
    int numActivities;
    cout << "--- Activity Selection Problem ---\n";
    cout << "Enter the number of activities: ";
    cin >> numActivities;

    vector<Activity> activities(numActivities);

    // Input activities
    cout << "Enter the start and finish times for each activity:\n";
    for (int i = 0; i < numActivities; i++) {
        cout << "Activity " << i + 1 << " - Start: ";
        cin >> activities[i].start;
        cout << "Activity " << i + 1 << " - Finish: ";
        cin >> activities[i].finish;
    }

    // Perform the activity selection
    activitySelection(activities);

    return 0;
}

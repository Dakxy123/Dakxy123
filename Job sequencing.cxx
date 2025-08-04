#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>  // For input validation

using namespace std;

// Structure to represent a job
struct Job {
    char id;  // Job ID
    int deadline;  // Deadline of job
    int profit;    // Profit if job is done before or on the deadline
};

// Comparator function to sort jobs based on profit in decreasing order
bool compare(Job a, Job b) {
    return a.profit > b.profit;
}

// Function to validate if input is positive
int getPositiveInput(const string& prompt) {
    int value;
    while (true) {
        cout << prompt;
        cin >> value;
        if (cin.fail() || value <= 0) {
            cout << "Invalid input. Please enter a positive integer.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        } else {
            break;
        }
    }
    return value;
}

// Function to schedule jobs and calculate the maximum profit
void jobSequencing(vector<Job> &jobs, int numJobs) {
    // Sort jobs by decreasing order of profit
    sort(jobs.begin(), jobs.end(), compare);

    // Array to store result of jobs and track free time slots
    vector<char> result(numJobs, '-');  
    vector<bool> slot(numJobs, false);

    int totalProfit = 0;

    // Iterate over all jobs
    for (int i = 0; i < jobs.size(); i++) {
        // Find a free slot for the job (we start from the last possible slot)
        for (int j = min(numJobs, jobs[i].deadline) - 1; j >= 0; j--) {
            // If the slot is free
            if (!slot[j]) {
                result[j] = jobs[i].id;  // Assign this job to the slot
                slot[j] = true;  // Mark this slot as occupied
                totalProfit += jobs[i].profit;  // Add profit
                break;
            }
        }
    }

    // Display the scheduled jobs and total profit
    cout << "\nScheduled Jobs: ";
    for (int i = 0; i < numJobs; i++) {
        if (result[i] != '-') {
            cout << result[i] << " ";
        }
    }
    cout << "\nTotal Profit: " << totalProfit << endl;
}

int main() {
    cout << "=== Job Sequencing Problem ===" << endl;

    // Input number of jobs
    int numJobs = getPositiveInput("Enter number of jobs: ");

    vector<Job> jobs(numJobs);

    // Input job details (id, deadline, profit)
    for (int i = 0; i < numJobs; i++) {
        cout << "Enter details for Job " << i + 1 << ":\n";
        
        // Get job ID
        cout << "Job ID: ";
        cin >> jobs[i].id;
        
        // Get job deadline and validate input
        jobs[i].deadline = getPositiveInput("Deadline (positive integer): ");
        
        // Get job profit and validate input
        jobs[i].profit = getPositiveInput("Profit (positive integer): ");
    }

    jobSequencing(jobs, numJobs);

    return 0;
}

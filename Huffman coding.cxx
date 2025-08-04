#include <iostream>
#include <queue>
#include <unordered_map>
#include <vector>
#include <string>
#include <iomanip>

using namespace std;

// Node structure for Huffman Tree
struct Node {
    char ch;
    int freq;
    Node* left;
    Node* right;

    Node(char character, int frequency) : ch(character), freq(frequency), left(nullptr), right(nullptr) {}
};

// Comparator for the priority queue
struct Compare {
    bool operator()(Node* left, Node* right) {
        return left->freq > right->freq; // Min-heap based on frequency
    }
};

// Function to generate the Huffman codes
void generateHuffmanCodes(Node* root, const string& str, unordered_map<char, string>& huffmanCode) {
    if (!root) return;
    if (!root->left && !root->right) {
        huffmanCode[root->ch] = str; // Store the code for the character
    }
    generateHuffmanCodes(root->left, str + "0", huffmanCode); // Left child is '0'
    generateHuffmanCodes(root->right, str + "1", huffmanCode); // Right child is '1'
}

// Function to build the Huffman Tree
Node* buildHuffmanTree(const vector<char>& chars, const vector<int>& freqs) {
    priority_queue<Node*, vector<Node*>, Compare> minHeap;

    // Create leaf nodes and add them to the priority queue
    for (size_t i = 0; i < chars.size(); i++) {
        minHeap.push(new Node(chars[i], freqs[i]));
    }

    // Combine nodes until there is only one node left
    while (minHeap.size() > 1) {
        Node* left = minHeap.top(); minHeap.pop(); // Get two smallest nodes
        Node* right = minHeap.top(); minHeap.pop();

        // Create a new internal node with these two nodes as children
        Node* combined = new Node('\0', left->freq + right->freq);
        combined->left = left;
        combined->right = right;
        minHeap.push(combined); // Add the new node back to the queue
    }

    return minHeap.top(); // Root node
}

// Main function
int main() {
    char choice;
    do {
        cout << "\n=== Huffman Coding ===\n";

        int n;
        cout << "Enter number of unique characters: ";
        cin >> n;

        vector<char> characters(n);
        vector<int> frequencies(n);

        // Input characters and their frequencies
        for (int i = 0; i < n; ++i) {
            cout << "Character " << i + 1 << ": ";
            cin >> characters[i];
            cout << "Frequency of " << characters[i] << ": ";
            cin >> frequencies[i];
        }

        // Build Huffman Tree
        Node* root = buildHuffmanTree(characters, frequencies);
        unordered_map<char, string> huffmanCode;
        generateHuffmanCodes(root, "", huffmanCode);

        // Display Huffman Codes and calculate total bits
        cout << "\nCharacter Huffman Codes:\n";
        cout << left << setw(55) << "" 
             << "| Symbol | Frequency | Huffman Code | Huffman Bits | Total Bits |\n";
        cout << string(90, '-') << endl; // Line separator

        int totalFrequency = 0, totalBits = 0;
        for (size_t i = 0; i < characters.size(); i++) {
            char ch = characters[i];
            int freq = frequencies[i];
            string code = huffmanCode[ch];
            int bits = code.length();
            totalBits += freq * bits; // Total bits calculation for this character
            totalFrequency += freq; // Total frequency calculation

            cout << left << setw(55) << "" 
                 << "| " << setw(6) << ch 
                 << "| " << setw(9) << freq 
                 << "| " << setw(12) << code 
                 << "| " << setw(12) << bits 
                 << "| " << setw(10) << (freq * bits) 
                 << " |\n"; // Total bits for this character
        }

        cout << string(90, '-') << endl; // Line separator
        cout << left << setw(55) << "" 
             << "| Total " << setw(19) << totalFrequency 
             << "|         |            |              | " << totalBits << " |\n"; // Total bits

        cout << "The goal is to achieve the lowest total bits.\n";
        cout << "Would you like to perform another operation? (y/n): ";
        cin >> choice;

    } while (choice == 'y' || choice == 'Y');

    return 0;
}

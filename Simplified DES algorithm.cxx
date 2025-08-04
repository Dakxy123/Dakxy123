#include <iostream>
#include <vector>
#include <iomanip>

using namespace std;

void printBinary(const vector<int>& v, const string& title) {
    cout << title << ": ";
    for (int bit : v) cout << bit;
    cout << endl;
}

vector<int> leftShift(const vector<int>& bits, int n) {
    vector<int> shifted(bits.size());
    for (size_t i = 0; i < bits.size(); ++i) {
        shifted[i] = bits[(i + n) % bits.size()];
    }
    return shifted;
}

vector<int> P10(const vector<int>& key) {
    return { key[2], key[4], key[1], key[6], key[3], key[9], key[0], key[8], key[7], key[5] };
}

vector<int> P8(const vector<int>& key) {
    return { key[5], key[2], key[6], key[3], key[7], key[4], key[9], key[8] };
}

vector<int> initialPermutation(const vector<int>& pt) {
    return { pt[1], pt[5], pt[2], pt[0], pt[3], pt[7], pt[4], pt[6] };
}

vector<int> inverseInitialPermutation(const vector<int>& permuted) {
    return { permuted[3], permuted[0], permuted[2], permuted[4], permuted[6], permuted[1], permuted[7], permuted[5] };
}

vector<int> expandAndPermute(const vector<int>& half) {
    return { half[3], half[0], half[1], half[2], half[1], half[2], half[3], half[0] };
}

vector<int> XOR(const vector<int>& a, const vector<int>& b) {
    vector<int> result(a.size());
    for (size_t i = 0; i < a.size(); ++i) {
        result[i] = a[i] ^ b[i];
    }
    return result;
}

vector<int> sbox(int input, const vector<vector<int>>& sbox) {
    int row = ((input & 0b1000) >> 2) | (input & 0b0001);
    int col = (input & 0b0110) >> 1;
    int value = sbox[row][col];
    return { (value >> 1) & 1, value & 1 };
}

vector<int> P4(const vector<int>& bits) {
    return { bits[1], bits[3], bits[2], bits[0] };
}

int main() {
    string key_str, pt_str;
    cout << "Enter 10-bit key: ";
    cin >> key_str;
    cout << "Enter 8-bit plaintext: ";
    cin >> pt_str;

    vector<int> key(10), pt(8);
    for (int i = 0; i < 10; i++) key[i] = key_str[i] - '0';
    for (int i = 0; i < 8; i++) pt[i] = pt_str[i] - '0';

    auto permuted10 = P10(key);
    vector<int> left(permuted10.begin(), permuted10.begin() + 5);
    vector<int> right(permuted10.begin() + 5, permuted10.end());

    left = leftShift(left, 1);
    right = leftShift(right, 1);

    vector<int> combined_key1 = left;
    combined_key1.insert(combined_key1.end(), right.begin(), right.end());
    auto k1 = P8(combined_key1);

    left = leftShift(left, 2);
    right = leftShift(right, 2);

    vector<int> combined_key2 = left;
    combined_key2.insert(combined_key2.end(), right.begin(), right.end());
    auto k2 = P8(combined_key2);

    auto permutedPT = initialPermutation(pt);
    vector<int> left_half(permutedPT.begin(), permutedPT.begin() + 4);
    vector<int> right_half(permutedPT.begin() + 4, permutedPT.end());

    auto expanded = expandAndPermute(right_half);
    auto xored = XOR(expanded, k1);
    vector<vector<int>> S0 = {{1, 0, 3, 2}, {3, 2, 1, 0}, {0, 2, 1, 3}, {3, 1, 3, 2}};
    vector<vector<int>> S1 = {{0, 1, 2, 3}, {2, 0, 1, 3}, {3, 0, 1, 0}, {2, 1, 0, 3}};
    auto s0 = sbox((xored[0] << 3) | (xored[1] << 2) | (xored[2] << 1) | xored[3], S0);
    auto s1 = sbox((xored[4] << 3) | (xored[5] << 2) | (xored[6] << 1) | xored[7], S1);
    auto p4 = P4({ s0[0], s0[1], s1[0], s1[1] });
    left_half = XOR(left_half, p4);

    swap(left_half, right_half);

    expanded = expandAndPermute(right_half);
    xored = XOR(expanded, k2);
    s0 = sbox((xored[0] << 3) | (xored[1] << 2) | (xored[2] << 1) | xored[3], S0);
    s1 = sbox((xored[4] << 3) | (xored[5] << 2) | (xored[6] << 1) | xored[7], S1);
    p4 = P4({ s0[0], s0[1], s1[0], s1[1] });
    left_half = XOR(left_half, p4);

    vector<int> pre_output = left_half;
    pre_output.insert(pre_output.end(), right_half.begin(), right_half.end());
    auto final_output = inverseInitialPermutation(pre_output);

    printBinary(final_output, "Final Permutation (IP⁻¹)");

    int hex_val = 0;
    for (int i = 0; i < 8; ++i) {
        hex_val = (hex_val << 1) | final_output[i];
    }
    cout << "Hexadecimal Output: 0x" << hex << uppercase << hex_val << endl;

    return 0;
}

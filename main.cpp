#include <iostream>
#include <vector>
#include <algorithm>
#include <SA.cpp>

using namespace std;

int main() {
    // Example usage
    std::string input = "banana";
    int n = input.size();

    SA sa1;
    
    // Append sentinel characters
    input += '\0';
    input += '\0';
    
    // Convert the input string to an array of integers
    std::vector<int> s(n);
    for (int i = 0; i < n; ++i) {
        s[i] = input[i];
    }

    // Construct the suffix array using the provided function
    std::vector<int> sa(n);
    sa1.suffixArray(s.data(), sa.data(), n, 255);

    // Print the result
    std::cout << "Suffix Array: ";
    for (int index : sa) {
        std::cout << index << " ";
    }
    std::cout << std::endl;

    return 0;
}

#include <iostream>
#include <vector>
#include <algorithm>

// Function to perform Burrows-Wheeler Transform
std::string bwtTransform(const std::vector<int>& suffixArray, const std::string& originalString) {
    int n = suffixArray.size();
    std::string transformedString;

    // Construct the Burrows-Wheeler Transform
    for (int i = 0; i < n; ++i) {
        int index = suffixArray[i] - 1;
        if (index < 0) {
            index += n;  // Adjust for the sentinel character
        }
        transformedString += originalString[index];
    }

    return transformedString;
}

int main() {
    // Example usage
    std::string originalString = "banana";
    int n = originalString.size();

    // Append sentinel characters
    originalString += '\0';
    originalString += '\0';

    // Construct the suffix array using your preferred method or library
    // For the sake of this example, let's assume you already have the suffix array
    std::vector<int> suffixArray = {5, 3, 1, 0, 4, 2};

    // Perform Burrows-Wheeler Transform
    std::string bwtResult = bwtTransform(suffixArray, originalString);

    // Print the result
    std::cout << "Original String: " << originalString << std::endl;
    std::cout << "Burrows-Wheeler Transform: " << bwtResult << std::endl;

    return 0;
}


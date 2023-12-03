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

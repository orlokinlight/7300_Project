#include <iostream>
#include <vector>
#include <algorithm>

// Function to perform Burrows-Wheeler Transform
static std::vector<int> bwtTransform(std::vector<int>& suffixArray, std::string& originalString) {
    int n = suffixArray.size();
    std::vector<int> transformedArray;

    // Construct the Burrows-Wheeler Transform
    for (int i = 0; i < n; ++i) {
        int index = suffixArray[i] - 1;
        if (index < 0) {
            index += n;  // Adjust for the sentinel character
        }
        transformedArray.push_back(originalString[index]);
    }

    return transformedArray;
}





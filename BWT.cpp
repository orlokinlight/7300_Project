#include <iostream>
#include <vector>
#include <algorithm>

// Function to perform Burrows-Wheeler Transform
static std::string bwtTransform(std::vector<int>& suffixArray, std::string& originalString) {
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

/*int main() {
    // Example suffix array generated from the previous code
    std::vector<int> suffixArray = {5, 3, 1, 0, 4, 2};

    // Corresponding original string
    std::string originalString = "banana\0\0";

    // Perform Burrows-Wheeler Transform
    std::string bwtResult = bwtTransform(suffixArray, originalString);

    // Print the result
    std::cout << "Original String: " << originalString << std::endl;
    std::cout << "Burrows-Wheeler Transform: " << bwtResult << std::endl;

    return 0;
}*/

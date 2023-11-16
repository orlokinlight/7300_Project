#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

// Structure to store the rotations and their indices
struct Rotation {
    std::string rotation;
    int index;
};

// Function to perform Burrows-Wheeler Transform
std::string burrowsWheelerTransform(const std::string& input) {
    // Create a vector to store rotations
    std::vector<Rotation> rotations;

    // Generate all rotations of the input string
    for (int i = 0; i < input.length(); ++i) {
        rotations.push_back({input.substr(i) + input.substr(0, i), i});
    }

    // Sort the rotations lexicographically
    std::sort(rotations.begin(), rotations.end(), [](const Rotation& a, const Rotation& b) {
        return a.rotation < b.rotation;
    });

    // Extract the last column of the sorted rotations
    std::string bwtResult;
    for (const auto& rotation : rotations) {
        int lastCharIndex = rotation.rotation.length() - 1;
        bwtResult += rotation.rotation[lastCharIndex];
    }

    return bwtResult;
}

int main() {
    // Example usage
    std::string inputText = "banana";
    std::string bwtResult = burrowsWheelerTransform(inputText);

    // Display the result
    std::cout << "Original Text: " << inputText << std::endl;
    std::cout << "Burrows-Wheeler Transform: " << bwtResult << std::endl;

    return 0;
}

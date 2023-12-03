#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

std::string getUniqueCharacters(const std::string& filename, int alphabetSize) {
    // Open the file
    std::ifstream inputFile(filename);

    // Check if the file is opened successfully
    if (!inputFile.is_open()) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return "";
    }

    // Using a vector to store unique characters
    std::vector<char> uniqueCharacters;

    // Read each character from the file
    char ch;
    while (inputFile.get(ch)) {
        // Check if the character is within the specified alphabet size
        if (isalpha(ch) && std::find(uniqueCharacters.begin(), uniqueCharacters.end(), ch) == uniqueCharacters.end()) {
            uniqueCharacters.push_back(ch);
        }
    }

    // Close the file
    inputFile.close();

    // Sort the vector in alphabetical order
    std::sort(uniqueCharacters.begin(), uniqueCharacters.end());

    // Convert the vector to a string
    std::string result(uniqueCharacters.begin(), uniqueCharacters.end());

    return result;
}


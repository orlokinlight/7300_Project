#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include "SA.cpp"
#include "BWT.cpp"

//using namespace std;

int main() {
    
    // Replace "your_file_path" with the actual path to the file on your desktop
    std::string file_path = "/Users/josephbrown/Desktop/sample3.txt";

    // Open the file
    std::ifstream file(file_path);

    // Check if the file is opened successfully
    if (!file.is_open()) {
        std::cerr << "Error opening the file." << std::endl;
        return 1;
    }

    // Read the file contents into a string
    std::ostringstream buffer;
    buffer << file.rdbuf();
    std::string input = buffer.str();

    // Close the file
    file.close();

    // Display the contents of the file
    std::cout << "File Contents:\n" << input << std::endl;
    
    
    int n = input.size();
    
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
    suffixArray(s.data(), sa.data(), n, 255);

    // Print the result
    std::cout << "Suffix Array: ";
    for (int index : sa) {
        std::cout << index << " ";
    }
    std::cout << std::endl;
    
    // Perform Burrows-Wheeler Transform
    std::string bwtResult = bwtTransform(sa, input);

    // Print the result
    //std::cout << "Original String: " << input << std::endl;
    std::cout << "Burrows-Wheeler Transform: " << bwtResult << std::endl;

    return 0;
}



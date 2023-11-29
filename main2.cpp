#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Helper function to compare suffixes
bool suffixCompare(const vector<int>& s, int i, int j, int k) {
    if (s[i] != s[j]) return s[i] < s[j];
    return s[i + k] < s[j + k];
}

// Helper function to construct the suffix array using DC3 algorithm
vector<int> dc3(const vector<int>& s) {
    int n = s.size();
    
    // Base case: if the string is empty, return an empty suffix array
    if (n == 0) return {};

    // Step 1: Create an array to represent the reduced problem
    vector<int> sa(n);
    vector<int> s12;
    for (int i = 0; i < n / 3; ++i) {
        s12.push_back(3 * i + 1);
        s12.push_back(3 * i + 2);
        s12.push_back(3 * i + 3);
    }

    // Step 2: Sort the triples
    sort(s12.begin(), s12.end(), [&](int i, int j) {
        return suffixCompare(s, i, j, 0);
    });

    // Step 3: Assign lexicographic names to the triples
    vector<int> name(n);
    int currentName = 0;
    for (int i = 0; i < n; ++i) {
        if (i == 0 || suffixCompare(s, s12[i], s12[i - 1], 0)) {
            name[s12[i]] = ++currentName;
        } else {
            name[s12[i]] = currentName;
        }
    }

    // If there are still names to assign, recursively solve the reduced problem
    if (currentName < n) {
        vector<int> s12Reduced;
        for (int i = 0; i < n; ++i) {
            if (name[i] <= currentName) {
                s12Reduced.push_back(i);
            }
        }
        vector<int> saReduced = dc3(s12Reduced);

        // Extend the reduced suffix array to a full suffix array
        for (int i = 0; i < saReduced.size(); ++i) {
            saReduced[i] = s12[saReduced[i]];
        }

        // Induce the order of type S suffixes in the full suffix array
        for (int i = 0; i < n / 3; ++i) {
            s12[i] = 3 * i;
        }
        sort(s12.begin(), s12.end(), [&](int i, int j) {
            return suffixCompare(s, i, j, 1) || (suffixCompare(s, i, j, 0) && name[i + 1] < name[j + 1]);
        });

        // Merge the two sorted parts to obtain the final suffix array
        vector<int> merged(saReduced.size() + s12.size());
        merge(saReduced.begin(), saReduced.end(), s12.begin(), s12.end(), merged.begin(), [&](int i, int j) {
            return suffixCompare(s, i, j, 0);
        });

        return merged;
    } else {
        // If all names are assigned, induce the order of type S suffixes
        s12.resize(n / 3);
        for (int i = 0; i < n / 3; ++i) {
            s12[i] = 3 * i;
        }
        sort(s12.begin(), s12.end(), [&](int i, int j) {
            return suffixCompare(s, i, j, 1) || (suffixCompare(s, i, j, 0) && name[i + 1] < name[j + 1]);
        });

        // Merge the two sorted parts to obtain the final suffix array
        vector<int> merged(sa.size() + s12.size());
        merge(sa.begin(), sa.end(), s12.begin(), s12.end(), merged.begin(), [&](int i, int j) {
            return suffixCompare(s, i, j, 0);
        });

        return merged;
    }
}

int main() {
    // Example usage
    string input = "banana";
    vector<int> s;
    for (char c : input) {
        s.push_back(c);
    }
    s.push_back(0); // Add a sentinel character (0) at the end of the string

    // Construct the suffix array using DC3 algorithm
    vector<int> suffixArray = dc3(s);

    // Print the result
    cout << "Suffix Array: ";
    for (int index : suffixArray) {
        cout << index << " ";
    }
    cout << endl;

    return 0;
}

#include "RankedBitmap.hpp"
#include "WaveletTree.hpp"
#include "FmIndex.hpp"

//#include <divsufsort.h>

#include <algorithm>
#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>
#include <vector>
#include <iostream>
#include <iostream>
#include <fstream>
#include <sstream>

#include <unordered_map>
#include </home/kendall/7300_project2/get_alphabet.cpp>

using namespace std;

typedef unsigned long long ullint;

int main() {
  std::string file_path = "/home/kendall/7300_project2/test.txt";
  /*
  int size = 4;
  string result = getUniqueCharacters(file_path, size);*/
  
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

  const char* charArray = input.c_str();
  static char data[13]; int data_len = strlen(data);
  strcpy(data, input.c_str());
  const char alpha[] = "ACGT"; int alpha_sz = strlen(alpha);
  //static char data[] = "AGTCTAGATCTA"; int data_len = strlen(data);
  printf("alpha = %s\n", alpha);
  printf("data = %s\n", data);

  static char orig_data[123];
  strncpy(orig_data, data, data_len);
  orig_data[data_len] = 0;

  FmIndex fmindex(data, data_len, alpha, alpha_sz); // garbles data

  /////// Count number of substrings CTA ///////
  static char query[] = "CTA";
  ullint cnt = fmindex.count_substrings(query, strlen(query));
  printf("cnt = %llu\n", cnt);

  ////// Print all occurences of substring CTA ///////
  /*vector<ullint> results;
  fmindex.get_substring_pos(results, query, strlen(query));
  for (int i = 0; i < (int)results.size(); ++i) {
    printf("result[%d] = %llu\n", i, results[i]);
  }*/

  ///// write the index to the file /////
  FILE* out = fopen("fmindex.out", "wb");
  fmindex.serialize(out);
  fclose(out);

  return 0; 

}
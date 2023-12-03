#include <unordered_map>
//#include </home/kendall/7300_project2/get_alphabet.cpp>

using namespace std;

typedef unsigned long long ullint;


int main() {
  string file_path = "/home/kendall/7300_project2/test2.txt";
  
  //int size = 4;
  //string result = getUniqueCharacters(file_path, size);
  std::ifstream file(file_path);

    // Check if the file is opened successfully
    if (!file.is_open()) {
        cerr << "Error opening the file." << endl;
        return 1;
    }
    // Read the file contents into a string
    ostringstream buffer;
    buffer << file.rdbuf();
    string input = buffer.str();

    // Close the file
    file.close();
    
  char data[input.length()];
  strcpy(data, input.c_str());
  int data_len = strlen(data);
  const char alpha[] = "helo"; int alpha_sz = strlen(alpha);
  //static char data[] = "AGTCTAGATCTA"; int data_len = strlen(data);
  printf("alpha = %s\n", alpha);
  printf("data = %s\n", data);

  static char orig_data[123];
  strncpy(orig_data, data, data_len);
  orig_data[data_len] = 0;
  
  FmIndex fmindex(data, data_len, alpha, alpha_sz); // garbles data
  /////// Count number of substrings CTA ///////
  static char query[] = "he";
  ullint cnt = fmindex.count_substrings(query, strlen(query));
  printf("cnt = %llu\n", cnt);

  ////// Print all occurences of substring CTA ///////
  /*vector<ullint> results;
  fmindex.get_substring_pos(results, query, strlen(query));
  for (int i = 0; i < (int)results.size(); ++i) {
    printf("result[%d] = %llu\n", i, results[i]);
  }*/

  ///// write the index to the file /////
  /*FILE* out = fopen("fmindex.out", "wb");
  fmindex.serialize(out);
  fclose(out);*/

  return 0; 

}

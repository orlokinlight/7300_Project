#include "util.hpp"

void alphabet_to_idxs(char* data, const ullint data_len, const char* alphabet, const ullint alphabet_sz) {
  thread_local char alphabet_map[256]; memset(alphabet_map, -1, sizeof alphabet_map); // TODO: change to thread local!
  for (ullint i = 0; i < alphabet_sz; ++i) {
    alphabet_map[(int)alphabet[i]] = i;
  }
  for (ullint i = 0; i < data_len; ++i) {
    char idx = alphabet_map[(int)data[i]];
    assert(idx != -1);
    data[i] = idx;
  }
}

void idxs_to_alphabet(char* data, const ullint data_len, const char* alphabet, const ullint alphabet_sz) {
  for (ullint i = 0; i < data_len; ++i) {
    char idx = data[i];
    assert(0 <= idx && (ullint)idx < alphabet_sz);
    data[i] = alphabet[(int)idx];
  }
}
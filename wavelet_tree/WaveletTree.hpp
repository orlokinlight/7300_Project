#ifndef _WAVELET_TREE_H_
#define _WAVELET_TREE_H_

#include "RankedBitmap.hpp"

#include <vector>
//#include <divsufsort.h>

using namespace std;

typedef unsigned long long ullint;

class WaveletTree {
public:
  WaveletTree();
  WaveletTree(char* data, ullint data_sz, int alphabet_sz);

  // Expects data over an alphabet consisting of [0, 1, 2, ..., alphabet_sz-1]
  // Warning: data will become garbled
  void init(char* data, ullint data_sz, int alphabet_sz);

  // Number of occurences of c in data positions [0, 1, 2, ..., pos-1]
  // c should be in [0, 1, ..., alphabet_sz-1]
  ullint get_rank(char c, ullint pos);

  // The character at position pos (+ gets the rank of it)
  char get_char_at(ullint pos, ullint& rank);

  void serialize(FILE* out) const;
  void deserialize(FILE* in);

private:
  struct Node {
    RankedBitmap bitmap;
  };

  vector<Node> nodes;
  int alphabet_sz;

  void build_tree(int x, int a_lo, int a_hi, char* data, ullint data_sz);
};

#endif // !_WAVELET_TREE_H_
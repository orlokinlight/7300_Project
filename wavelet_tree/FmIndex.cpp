#include "FmIndex.hpp"
#include "util.hpp"

//#include <divsufsort.h>

#include <algorithm>
#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>
#include <vector>
#include <iostream>
#include </home/kendall/7300_project2/SA.cpp>
#include </home/kendall/7300_project2/BWT.cpp>

using namespace std;

typedef unsigned long long ullint;

const int kFmSparseSaValM1 = 31;


FmIndex::FmIndex(char* data, ullint orig_data_sz, const char* alphabet, int orig_alphabet_sz) {
  this->data_sz = orig_data_sz + 1;

  // make a dummy 0.th char (separator, no particular ASCII code)
  memset(alphabet_map, -1, sizeof alphabet_map);
  for (int i = 0; i < orig_alphabet_sz; ++i) {
    alphabet_map[(int)alphabet[i]] = i + 1; // +1 because of the terminator
  }

  // don't use alphabet[] any more
  int alphabet_sz = orig_alphabet_sz + 1;

  prefix_sums.resize(alphabet_sz + 1, 0);
  ++prefix_sums[0+1];

  for (ullint data_i = 0; data_i < orig_data_sz; ++data_i) {
    int val = alphabet_map[(int)data[data_i]];
    assert(val != -1);
    data[data_i] = val;
    ++prefix_sums[val+1];
  }

  for (int i = 0; i < alphabet_sz; ++i)
    prefix_sums[i+1] += prefix_sums[i];

  // ONLY SUPPORTS 32bit sizes!!!
  std::string input = data;
    int n = input.size();
    
    input += '\0';
    input += '\0';
    
    std::vector<int> s(n);
    for (int i = 0; i < n; ++i) {
        s[i] = input[i];
    }

    std::vector<int> SA(n);
    suffixArray(s.data(), SA.data(), n, 255);
  //assert(sizeof(int) == sizeof(SA[0]));
  //suffixArray((int*)data, SA.data(), n, 255);
  //assert(ret_val == 0);
  // construct BWT
  vector<char> bwt(data_sz); // +1 for the terminator
  bwt[0] = data[orig_data_sz - 1];

  for (ullint i = 0; i < orig_data_sz; ++i) { // TODO: optimize for cache (if needed!)
    int sa_idx = SA[i];
    int bwt_idx = sa_idx - 1;
    char val;
    if (bwt_idx == -1) {
      val = 0;
    } else {
      val = data[bwt_idx];
    }
    bwt[i+1] = val;

    if ((sa_idx&kFmSparseSaValM1) == 0) { // store every kth position
      sparse_sa[i+1] = sa_idx;
    }
  }

  bwt_wavelet.init(bwt.data(), data_sz, alphabet_sz);
}

// read index from (binary) file
FmIndex::FmIndex(FILE* in) {
  this->deserialize(in);
}

// counts the number of occurrences of the query as a substring within the text
ullint FmIndex::count_substrings(const char* query, int query_len) {
  pair<ullint, ullint> ret = get_substring_idx_bounds(query, query_len);
  return ret.second - ret.first;
}

pair<ullint, ullint> FmIndex::get_substring_idx_bounds(const char* query, int query_len) {
  int last_val = alphabet_map[(int)query[query_len - 1]];
  ullint lo = prefix_sums[last_val], hi = prefix_sums[last_val + 1];

  for (int iter = query_len - 2; iter >= 0; --iter) {
    int val = alphabet_map[(int)query[iter]];
    lo = prefix_sums[val] + bwt_wavelet.get_rank(val, lo);
    hi = prefix_sums[val] + bwt_wavelet.get_rank(val, hi);
    if (lo >= hi) break;
  }
  
  return make_pair(lo, hi);
}

/*void FmIndex::get_substring_pos(vector<ullint> &results, const char* query, int query_len, int limit) {
  results.clear();

  pair<ullint, ullint> ret = get_substring_idx_bounds(query, query_len);

  while (ret.first < ret.second && limit--) {
    int travel_len = 0;
    ullint pos = ret.first++;

    while (pos != 0) {
      auto it = sparse_sa.find(pos);
      if (it != sparse_sa.end()) {
        results.push_back(it->second + travel_len);
        break;
      }

      pos = lf_mapping(pos);
      ++travel_len;
    }

    assert(pos != 0);
  }
}*/

ullint FmIndex::lf_mapping(ullint pos) {
  ullint rank;
  int c = bwt_wavelet.get_char_at(pos, rank);
  return rank + prefix_sums[c];
}

void FmIndex::serialize(FILE* out) const {
  assert(fwrite(alphabet_map, sizeof(alphabet_map[0]),
                sizeof(alphabet_map) / sizeof(alphabet_map[0]), out) > 0);
  ::serialize(out, data_sz);
  serialize_vector(out, prefix_sums);
  bwt_wavelet.serialize(out);
  serialize_umap(out, sparse_sa);
}

void FmIndex::deserialize(FILE* in) {
  assert(fread(alphabet_map, sizeof(alphabet_map[0]),
                sizeof(alphabet_map) / sizeof(alphabet_map[0]), in) > 0);
  ::deserialize(in, data_sz);
  deserialize_vector(in, prefix_sums);
  bwt_wavelet.deserialize(in);
  deserialize_umap(in, sparse_sa);
}
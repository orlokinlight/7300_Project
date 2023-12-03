#ifndef _FM_INDEX_UTIL_H_
#define _FM_INDEX_UTIL_H_

#include <cstdio>
#include <cassert>
#include <cstring>

#include <unordered_map>
#include <vector>

#define TRACE(x) cout << #x " = " << (x) << endl

typedef unsigned long long ullint;

template<typename T>
void serialize(FILE* out, const T& val) {
  assert(fwrite(&val, sizeof(val), 1, out) > 0);
}

template<typename T>
void deserialize(FILE* in, T& val) {
  assert(fread(&val, sizeof(val), 1, in) > 0);
}

template<typename T>
void serialize_vector(FILE* out, const std::vector<T>& V) {
  unsigned long long int sz = V.size();
  serialize(out, sz);
  if (sz > 0) {
    assert(fwrite(V.data(), sizeof(V[0]), sz, out) > 0);
  }
}

template<typename T>
void deserialize_vector(FILE* in, std::vector<T>& V) {
  unsigned long long int sz;
  deserialize(in, sz);
  V.clear();
  if (sz > 0) {
    V.resize(sz); 
    assert(fread(V.data(), sizeof(V[0]), sz, in) > 0);
  }
}

template<typename U, typename V>
void serialize_umap(FILE* out, const std::unordered_map<U, V>& umap) {
  unsigned long long sz = umap.size();
  serialize(out, sz);

  for (auto it = umap.begin(); it != umap.end(); ++it) {
    serialize(out, it->first);
    serialize(out, it->second);
  }
}


template<typename U, typename V>
void deserialize_umap(FILE* in, std::unordered_map<U, V>& umap) {
  unsigned long long sz = umap.size();
  deserialize(in, sz);
  umap.clear();

  while (sz-- > 0) {
    thread_local U u;
    thread_local V v;
    deserialize(in, u);
    deserialize(in, v);
    umap[u] = v;
  }
}


// transform data over alphabet to alphabet indexes
// ex. data = "AGCTA", alphabet = "ACTG" -> data is transformed to {0, 2, 1, 3, 0}
void alphabet_to_idxs(char* data, const ullint data_len, const char* alphabet, const ullint alphabet_sz);

// transform indexes in range [0, alphabet_sz-1] to alphabet[idxs]
// ex. alphabet = "ACGT", data = {0, 2, 1, 3, 0} -> data is transformed to "AGCTA"
void idxs_to_alphabet(char* data, const ullint data_len, const char* alphabet, const ullint alphabet_sz);

#endif // !_FM_INDEX_UTIL_H_
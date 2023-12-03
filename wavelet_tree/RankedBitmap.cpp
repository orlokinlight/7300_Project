#include "RankedBitmap.hpp"
#include "util.hpp"

#include <algorithm>

#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <cstring>

#include <string>
#include <vector>
#include <iostream>

using namespace std;
 
typedef unsigned long long ullint;

const int kBitmapSuperbucketPow = 16; // shoule be <= 16, because of unsigned short int
const int kBitmapSuperbucketValM1 = (1 << kBitmapSuperbucketPow) - 1;

const int kBitmapBucketPow = 4; // should be at least 3
const int kBitmapBucketValM1 = (1 << kBitmapBucketPow) - 1;

RankedBitmap::RankedBitmap() {}

RankedBitmap::RankedBitmap(const char* data, ullint data_len, ullint n_elements, int zero_lo, int one_lo, int one_hi) {
  init(data, data_len, n_elements, zero_lo, one_lo, one_hi);
}

RankedBitmap::RankedBitmap(FILE* in) {
  deserialize(in);
}

void RankedBitmap::init(const char* data, ullint data_len, ullint n_elements, int zero_lo, int one_lo, int one_hi) {
  this->n_elements = n_elements;
  bitmask_sz = (n_elements + 7) >> 3; // ceil(n/8)
  bitmask.resize(bitmask_sz, 0);

  ullint pos = 0;
  ullint last_superbucket_0rank = 0;
  ullint zero_rank = 0;

  superbuckets.resize((n_elements + kBitmapSuperbucketValM1) >> kBitmapSuperbucketPow);
  buckets.resize((n_elements + kBitmapBucketValM1) >> kBitmapBucketPow);

  ullint superbucket_idx = 0;
  ullint bucket_idx = 0;

  for (ullint data_i = 0; data_i < data_len; ++data_i) {
    if (zero_lo <= data[data_i] && data[data_i] < one_hi) {

      if ((pos&kBitmapSuperbucketValM1) == 0) { // next superbucket
        last_superbucket_0rank = zero_rank;
        superbuckets[superbucket_idx++] = last_superbucket_0rank;
      }

      if ((pos&kBitmapBucketValM1) == 0) { // next bucket
        unsigned short val = (zero_rank - last_superbucket_0rank);
        assert((ullint)val == (zero_rank - last_superbucket_0rank));
        buckets[bucket_idx++] = val;
      }

      if (zero_lo <= data[data_i] && data[data_i] < one_lo) { // 0
        ++zero_rank;
      } else { // 1
        bitmask[pos >> 3] |= 1<<(pos&7);
      }

      ++pos;
    }
  }

  assert(pos == n_elements);
  assert(superbucket_idx == (ullint)superbuckets.size());
  assert(bucket_idx == (ullint)buckets.size());
}

// get bit in position pos, pos should be in [0, n_elements)
bool RankedBitmap::get_bit(ullint pos) {
  return (bitmask[pos >> 3] >> (pos&7)) & 1;
}

// if bit == 0: how many 0's in [0, 1, 2, ..., pos)
// else         how many 1's in [0, 1, 2, ..., pos)
ullint RankedBitmap::get_rank(bool bit, ullint pos) {
  ullint rank = 
    + superbuckets[pos >> kBitmapSuperbucketPow]
    + buckets[pos >> kBitmapBucketPow];

  thread_local int popCnt[256] = {-1};
  if (popCnt[0] == -1) {
    popCnt[0] = 0;
    for (int i = 1; i < 256; ++i)
      popCnt[i] = popCnt[i>>1] + (i&1);
  }

  ullint i_pos = pos&(~kBitmapBucketValM1);
  for (; i_pos+8 < pos; i_pos += 8) {
    assert((0xff & bitmask[i_pos >> 3]) < 256);
    rank += 8 - popCnt[0xff & bitmask[i_pos >> 3]];
  }

  int mask = (1 << (pos - i_pos)) - 1;
  assert((0xff & (bitmask[i_pos >> 3] | (~mask))) < 256);
  rank += 8 - popCnt[0xff & (bitmask[i_pos >> 3] | (~mask))];

  // ------------- This is a more naive version of the upper code --------------------
  // ullint brute_rank = 
  //   + superbuckets[pos >> kBitmapSuperbucketPow]
  //   + buckets[pos >> kBitmapBucketPow];
  // for (ullint i_pos = pos&(~kBitmapBucketValM1); i_pos < pos; ++i_pos) { // TODO: switch to popcount!!!
  //   brute_rank += (get_bit(i_pos) == 0);
  // }

  //  printf("bit = %d pos = %llu rank = %llu brute = %llu\n", bit, pos, rank, brute_rank);
  //  assert(rank == brute_rank);

  return (bit == 0) ? (rank) : (pos-rank);
}

void RankedBitmap::serialize(FILE* out) const {
  ::serialize(out, n_elements);
  ::serialize(out, bitmask_sz);
  serialize_vector(out, bitmask);
  serialize_vector(out, superbuckets);
  serialize_vector(out, buckets);
}

void RankedBitmap::deserialize(FILE* in) {
  ::deserialize(in, n_elements);
  ::deserialize(in, bitmask_sz);
  deserialize_vector(in, bitmask);
  deserialize_vector(in, superbuckets);
  deserialize_vector(in, buckets);
}
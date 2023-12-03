#ifndef _RANKED_BITMAP_H_
#define _RANKED_BITMAP_H_

#include <cstdio>
#include <vector>

typedef unsigned long long ullint;

class RankedBitmap {
public:
  RankedBitmap();

  // see function init(...)
  RankedBitmap(const char* data, ullint data_len, ullint n_elements, int zero_lo, int one_lo, int one_hi);

  RankedBitmap(FILE* in);

  // (called automatically from constructor)
  // initialize bitmask with those indices i in [0, data_len) such that zero_lo <= data[i] < one_hi
  // assertion: there must be n_elements such ZERO+ONE indices
  // if zero_lo <= data[i] < one_lo -> it's value is 0
  // if one_lo <= data[i] < one_hi  -> it's value is 1
  void init(const char* data, ullint data_len, ullint n_elements, int zero_lo, int one_lo, int one_hi);

  // get bit in position pos, pos should be in [0, n_elements)
  bool get_bit(ullint pos);

  // if bit == 0: how many 0's in [0, 1, 2, ..., pos)
  // else         how many 1's in [0, 1, 2, ..., pos)
  ullint get_rank(bool bit, ullint pos);

  void serialize(FILE* out) const;
  void deserialize(FILE* in);

private:
  ullint n_elements;
  ullint bitmask_sz;

  // 8 bits / uchar
  std::vector<unsigned char> bitmask;

  // superbucket, 2^16
  std::vector<unsigned long long int> superbuckets;
  
  // bucket, 2^4
  std::vector<unsigned short> buckets;
};

#endif // !_RANKED_BITMAP_H_
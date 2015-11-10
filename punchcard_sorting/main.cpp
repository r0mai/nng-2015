#include <iostream>

#include <array>
#include <vector>

#include <algorithm>
#include <chrono>
#include <iterator>
#include <string>

#include <future>

//Templated hybrid string_sort

//          Copyright Steven J. Ross 2001 - 2009.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

// See http://www.boost.org/libs/sort/ for library home page.

/*
Some improvements suggested by:
Phil Endecott and Frank Gennari
*/

#ifndef BOOST_STRING_SORT_HPP
#define BOOST_STRING_SORT_HPP
#include <algorithm>
#include <vector>
#include <cstring>
#include <limits>
// Details for a templated general-case hybrid-radix string_sort.

//          Copyright Steven J. Ross 2001 - 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

// See http://www.boost.org/libs/sort for library home page.

/*
Some improvements suggested by:
Phil Endecott and Frank Gennari
*/

/* inline spreadsort/detail/spread_sort.hpp */

#ifndef BOOST_SORT_SPREADSORT_DETAIL_SPREAD_SORT_HPP
#define BOOST_SORT_SPREADSORT_DETAIL_SPREAD_SORT_HPP
#include <algorithm>
#include <vector>
#include <cstring>
#include <limits>
#include <functional>

//constant definitions for the Boost Sort library

//          Copyright Steven J. Ross 2001 - 2014
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org/libs/sort for library home page.
#ifndef BOOST_SORT_SPREADSORT_DETAIL_CONSTANTS
#define BOOST_SORT_SPREADSORT_DETAIL_CONSTANTS
namespace boost {
namespace sort {
namespace spreadsort {
namespace detail {
//Tuning constants
//This should be tuned to your processor cache;
//if you go too large you get cache misses on bins
//The smaller this number, the less worst-case memory usage.
//If too small, too many recursions slow down spreadsort
enum { max_splits = 11,
//It's better to have a few cache misses and finish sorting
//than to run another iteration
max_finishing_splits = max_splits + 1,
//Sets the minimum number of items per bin.
int_log_mean_bin_size = 2,
//Used to force a comparison-based sorting for small bins, if it's faster.
//Minimum value 1
int_log_min_split_count = 9,
//This is the minimum split count to use spreadsort when it will finish in one
//iteration.  Make this larger the faster std::sort is relative to integer_sort.
int_log_finishing_count = 31,
//Sets the minimum number of items per bin for floating point.
float_log_mean_bin_size = 2,
//Used to force a comparison-based sorting for small bins, if it's faster.
//Minimum value 1
float_log_min_split_count = 8,
//This is the minimum split count to use spreadsort when it will finish in one
//iteration.  Make this larger the faster std::sort is relative to float_sort.
float_log_finishing_count = 4,
//There is a minimum size below which it is not worth using spreadsort
min_sort_size = 1000 };
}
}
}
}
#endif

/* inline spreadsort/detail/spreadsort_common.hpp */
// Contains get_min_count, the core optimization of the spreadsort algorithm.
// Also has other helper functions commonly useful across variants.

//          Copyright Steven J. Ross 2001 - 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

// See http://www.boost.org/libs/sort for library home page.

/*
Some improvements suggested by:
Phil Endecott and Frank Gennari
*/

#ifndef BOOST_SORT_SPREADSORT_DETAIL_SPREAD_SORT_COMMON_HPP
#define BOOST_SORT_SPREADSORT_DETAIL_SPREAD_SORT_COMMON_HPP
#include <algorithm>
#include <vector>
#include <cstring>
#include <limits>
#include <functional>

namespace boost {
namespace sort {
namespace spreadsort {
 namespace detail {
    //This only works on unsigned data types
    template <typename T>
    inline unsigned
    rough_log_2_size(const T& input)
    {
      unsigned result = 0;
      //The && is necessary on some compilers to avoid infinite loops
      //it doesn't significantly impair performance
      while ((input >> result) && (result < (8*sizeof(T)))) ++result;
      return result;
    }

    //Gets the minimum size to call spreadsort on to control worst-case runtime.
    //This is called for a set of bins, instead of bin-by-bin, to minimize
    //runtime overhead.
    //This could be replaced by a lookup table of sizeof(Div_type)*8 but this
    //function is more general.
    template<unsigned log_mean_bin_size,
      unsigned log_min_split_count, unsigned log_finishing_count>
    inline size_t
    get_min_count(unsigned log_range)
    {
      const size_t typed_one = 1;
      const unsigned min_size = log_mean_bin_size + log_min_split_count;
      //Assuring that constants have valid settings
      //if we can complete in one iteration, do so
      //This first check allows the compiler to optimize never-executed code out
      if (log_finishing_count < min_size) {
        if (log_range <= min_size && log_range <= max_splits) {
          //Return no smaller than a certain minimum limit
          if (log_range <= log_finishing_count)
            return typed_one << log_finishing_count;
          return typed_one << log_range;
        }
      }
      const unsigned base_iterations = max_splits - log_min_split_count;
      //sum of n to n + x = ((x + 1) * (n + (n + x)))/2 + log_mean_bin_size
      const unsigned base_range =
          ((base_iterations + 1) * (max_splits + log_min_split_count))/2
          + log_mean_bin_size;
      //Calculating the required number of iterations, and returning
      //1 << (iteration_count + min_size)
      if (log_range < base_range) {
        unsigned result = log_min_split_count;
        for (unsigned offset = min_size; offset < log_range;
          offset += ++result);
        //Preventing overflow; this situation shouldn't occur
        if ((result + log_mean_bin_size) >= (8 * sizeof(size_t)))
          return typed_one << ((8 * sizeof(size_t)) - 1);
        return typed_one << (result + log_mean_bin_size);
      }
      //A quick division can calculate the worst-case runtime for larger ranges
      unsigned remainder = log_range - base_range;
      //the max_splits - 1 is used to calculate the ceiling of the division
      unsigned bit_length = ((((max_splits - 1) + remainder)/max_splits)
        + base_iterations + min_size);
      //Preventing overflow; this situation shouldn't occur
      if (bit_length >= (8 * sizeof(size_t)))
        return typed_one << ((8 * sizeof(size_t)) - 1);
      //n(log_range)/max_splits + C, optimizing worst-case performance
      return typed_one << bit_length;
    }

    // Resizes the bin cache and bin sizes, and initializes each bin size to 0.
    // This generates the memory overhead to use in radix sorting.
    template <class RandomAccessIter>
    inline RandomAccessIter *
    size_bins(size_t *bin_sizes, std::vector<RandomAccessIter>
  &bin_cache, unsigned cache_offset, unsigned &cache_end, unsigned bin_count)
    {
      // Clear the bin sizes
      for (size_t u = 0; u < bin_count; u++)
        bin_sizes[u] = 0;
      //Make sure there is space for the bins
      cache_end = cache_offset + bin_count;
      if (cache_end > bin_cache.size())
        bin_cache.resize(cache_end);
      return &(bin_cache[cache_offset]);
    }
  }
}
}
}

#endif


namespace boost {
  template<bool B, class T=void>
  struct disable_if_c{};

  template<class T>
  struct disable_if_c<false, T> { using type = T; };
namespace sort {
namespace spreadsort {
  namespace detail {
    static const int max_step_size = 64;

    //Offsetting on identical characters.  This function works a chunk of
    //characters at a time for cache efficiency and optimal worst-case
    //performance.
    template<class RandomAccessIter, class Unsigned_char_type>
    inline void
    update_offset(RandomAccessIter first, RandomAccessIter finish,
                  size_t &char_offset)
    {
      const int char_size = sizeof(Unsigned_char_type);
      size_t nextOffset = char_offset;
      int step_size = max_step_size;
      while (true) {
        RandomAccessIter curr = first;
        do {
          //Ignore empties, but if the nextOffset would exceed the length or
          //not match, exit; we've found the last matching character
          //This will reduce the step_size if the current step doesn't match.
          if ((*curr).size() > char_offset) {
            if((*curr).size() <= (nextOffset + step_size)) {
              step_size = (*curr).size() - nextOffset - 1;
              if (step_size < 1) {
                char_offset = nextOffset;
                return;
              }
            }
            const int step_byte_size = step_size * char_size;
            if (memcmp(curr->data() + nextOffset, first->data() + nextOffset, 
                       step_byte_size) != 0) {
              if (step_size == 1) {
                char_offset = nextOffset;
                return;
              }
              step_size = (step_size > 4) ? 4 : 1;
              continue;
            }
          }
          ++curr;
        } while (curr != finish);
        nextOffset += step_size;
      }
    }

    //Offsetting on identical characters.  This function works a character
    //at a time for optimal worst-case performance.
    template<class RandomAccessIter, class Get_char, class Get_length>
    inline void
    update_offset(RandomAccessIter first, RandomAccessIter finish,
                  size_t &char_offset, Get_char getchar, Get_length length)
    {
      size_t nextOffset = char_offset;
      while (true) {
        RandomAccessIter curr = first;
        do {
          //ignore empties, but if the nextOffset would exceed the length or
          //not match, exit; we've found the last matching character
          if (length(*curr) > char_offset && (length(*curr) <= (nextOffset + 1)
            || getchar((*curr), nextOffset) != getchar((*first), nextOffset))) {
            char_offset = nextOffset;
            return;
          }
        } while (++curr != finish);
        ++nextOffset;
      }
    }

    //This comparison functor assumes strings are identical up to char_offset
    template<class Data_type, class Unsigned_char_type>
    struct offset_less_than {
      offset_less_than(size_t char_offset) : fchar_offset(char_offset){}
      inline bool operator()(const Data_type &x, const Data_type &y) const
      {
        size_t minSize = (std::min)(x.size(), y.size());
        for (size_t u = fchar_offset; u < minSize; ++u) {
          if (static_cast<Unsigned_char_type>(x[u]) !=
              static_cast<Unsigned_char_type>(y[u])) {
            return static_cast<Unsigned_char_type>(x[u]) < 
              static_cast<Unsigned_char_type>(y[u]);
          }
        }
        return x.size() < y.size();
      }
      size_t fchar_offset;
    };

    //Compares strings assuming they are identical up to char_offset
    template<class Data_type, class Unsigned_char_type>
    struct offset_greater_than {
      offset_greater_than(size_t char_offset) : fchar_offset(char_offset){}
      inline bool operator()(const Data_type &x, const Data_type &y) const
      {
        size_t minSize = (std::min)(x.size(), y.size());
        for (size_t u = fchar_offset; u < minSize; ++u) {
          if (static_cast<Unsigned_char_type>(x[u]) !=
              static_cast<Unsigned_char_type>(y[u])) {
            return static_cast<Unsigned_char_type>(x[u]) > 
              static_cast<Unsigned_char_type>(y[u]);
          }
        }
        return x.size() > y.size();
      }
      size_t fchar_offset;
    };

    //This comparison functor assumes strings are identical up to char_offset
    template<class Data_type, class Get_char, class Get_length>
    struct offset_char_less_than {
      offset_char_less_than(size_t char_offset) : fchar_offset(char_offset){}
      inline bool operator()(const Data_type &x, const Data_type &y) const
      {
        size_t minSize = (std::min)(length(x), length(y));
        for (size_t u = fchar_offset; u < minSize; ++u) {
          if (getchar(x, u) != getchar(y, u)) {
            return getchar(x, u) < getchar(y, u);
          }
        }
        return length(x) < length(y);
      }
      size_t fchar_offset;
      Get_char getchar;
      Get_length length;
    };

    //String sorting recursive implementation
    template <class RandomAccessIter, class Unsigned_char_type>
    inline void
    string_sort_rec(RandomAccessIter first, RandomAccessIter last,
                    size_t char_offset,
                    std::vector<RandomAccessIter> &bin_cache,
                    unsigned cache_offset, size_t *bin_sizes)
    {
      typedef typename std::iterator_traits<RandomAccessIter>::value_type
        Data_type;
      //This section makes handling of long identical substrings much faster
      //with a mild average performance impact.
      //Iterate to the end of the empties.  If all empty, return
      while ((*first).size() <= char_offset) {
        if (++first == last)
          return;
      }
      RandomAccessIter finish = last - 1;
      //Getting the last non-empty
      for (;(*finish).size() <= char_offset; --finish);
      ++finish;
      //Offsetting on identical characters.  This section works
      //a few characters at a time for optimal worst-case performance.
      update_offset<RandomAccessIter, Unsigned_char_type>(first, finish,
                                                          char_offset);
      
      const unsigned bin_count = (1 << (sizeof(Unsigned_char_type)*8));
      //Equal worst-case of radix and comparison is when bin_count = n*log(n).
      const unsigned max_size = bin_count;
      const unsigned membin_count = bin_count + 1;
      unsigned cache_end;
      RandomAccessIter * bins = size_bins(bin_sizes, bin_cache, cache_offset,
                                          cache_end, membin_count) + 1;

      //Calculating the size of each bin; this takes roughly 10% of runtime
      for (RandomAccessIter current = first; current != last; ++current) {
        if ((*current).size() <= char_offset) {
          bin_sizes[0]++;
        }
        else
          bin_sizes[static_cast<Unsigned_char_type>((*current)[char_offset])
                    + 1]++;
      }
      //Assign the bin positions
      bin_cache[cache_offset] = first;
      for (unsigned u = 0; u < membin_count - 1; u++)
        bin_cache[cache_offset + u + 1] =
          bin_cache[cache_offset + u] + bin_sizes[u];

      //Swap into place
      RandomAccessIter next_bin_start = first;
      //handling empty bins
      RandomAccessIter * local_bin = &(bin_cache[cache_offset]);
      next_bin_start +=  bin_sizes[0];
      RandomAccessIter * target_bin;
      //Iterating over each element in the bin of empties
      for (RandomAccessIter current = *local_bin; current < next_bin_start;
          ++current) {
        //empties belong in this bin
        while ((*current).size() > char_offset) {
          target_bin =
            bins + static_cast<Unsigned_char_type>((*current)[char_offset]);
          iter_swap(current, (*target_bin)++);
        }
      }
      *local_bin = next_bin_start;
      //iterate backwards to find the last bin with elements in it
      //this saves iterations in multiple loops
      unsigned last_bin = bin_count - 1;
      for (; last_bin && !bin_sizes[last_bin + 1]; --last_bin);
      //This dominates runtime, mostly in the swap and bin lookups
      for (unsigned u = 0; u < last_bin; ++u) {
        local_bin = bins + u;
        next_bin_start += bin_sizes[u + 1];
        //Iterating over each element in this bin
        for (RandomAccessIter current = *local_bin; current < next_bin_start;
            ++current) {
          //Swapping into place until the correct element has been swapped in
          for (target_bin = bins + static_cast<Unsigned_char_type>
              ((*current)[char_offset]);  target_bin != local_bin;
            target_bin = bins + static_cast<Unsigned_char_type>
              ((*current)[char_offset])) iter_swap(current, (*target_bin)++);
        }
        *local_bin = next_bin_start;
      }
      bins[last_bin] = last;
      //Recursing
      RandomAccessIter lastPos = bin_cache[cache_offset];
      //Skip this loop for empties
      for (unsigned u = cache_offset + 1; u < cache_offset + last_bin + 2;
          lastPos = bin_cache[u], ++u) {
        size_t count = bin_cache[u] - lastPos;
        //don't sort unless there are at least two items to Compare
        if (count < 2)
          continue;
        //using std::sort if its worst-case is better
        if (count < max_size)
          std::sort(lastPos, bin_cache[u],
              offset_less_than<Data_type, Unsigned_char_type>(char_offset + 1));
        else
          string_sort_rec<RandomAccessIter, Unsigned_char_type>(lastPos,
              bin_cache[u], char_offset + 1, bin_cache, cache_end, bin_sizes);
      }
    }

    //Sorts strings in reverse order, with empties at the end
    template <class RandomAccessIter, class Unsigned_char_type>
    inline void
    reverse_string_sort_rec(RandomAccessIter first, RandomAccessIter last,
                            size_t char_offset,
                            std::vector<RandomAccessIter> &bin_cache,
                            unsigned cache_offset,
                            size_t *bin_sizes)
    {
      typedef typename std::iterator_traits<RandomAccessIter>::value_type
        Data_type;
      //This section makes handling of long identical substrings much faster
      //with a mild average performance impact.
      RandomAccessIter curr = first;
      //Iterate to the end of the empties.  If all empty, return
      while ((*curr).size() <= char_offset) {
        if (++curr == last)
          return;
      }
      //Getting the last non-empty
      while ((*(--last)).size() <= char_offset);
      ++last;
      //Offsetting on identical characters.  This section works
      //a few characters at a time for optimal worst-case performance.
      update_offset<RandomAccessIter, Unsigned_char_type>(first, last,
                                                          char_offset);
      RandomAccessIter * target_bin;

      const unsigned bin_count = (1 << (sizeof(Unsigned_char_type)*8));
      //Equal worst-case of radix and comparison when bin_count = n*log(n).
      const unsigned max_size = bin_count;
      const unsigned membin_count = bin_count + 1;
      const unsigned max_bin = bin_count - 1;
      unsigned cache_end;
      RandomAccessIter * bins = size_bins(bin_sizes, bin_cache, cache_offset,
                                          cache_end, membin_count);
      RandomAccessIter * end_bin = &(bin_cache[cache_offset + max_bin]);

      //Calculating the size of each bin; this takes roughly 10% of runtime
      for (RandomAccessIter current = first; current != last; ++current) {
        if ((*current).size() <= char_offset) {
          bin_sizes[bin_count]++;
        }
        else
          bin_sizes[max_bin - static_cast<Unsigned_char_type>
            ((*current)[char_offset])]++;
      }
      //Assign the bin positions
      bin_cache[cache_offset] = first;
      for (unsigned u = 0; u < membin_count - 1; u++)
        bin_cache[cache_offset + u + 1] =
          bin_cache[cache_offset + u] + bin_sizes[u];

      //Swap into place
      RandomAccessIter next_bin_start = last;
      //handling empty bins
      RandomAccessIter * local_bin = &(bin_cache[cache_offset + bin_count]);
      RandomAccessIter lastFull = *local_bin;
      //Iterating over each element in the bin of empties
      for (RandomAccessIter current = *local_bin; current < next_bin_start;
          ++current) {
        //empties belong in this bin
        while ((*current).size() > char_offset) {
          target_bin =
            end_bin - static_cast<Unsigned_char_type>((*current)[char_offset]);
          iter_swap(current, (*target_bin)++);
        }
      }
      *local_bin = next_bin_start;
      next_bin_start = first;
      //iterate backwards to find the last non-empty bin
      //this saves iterations in multiple loops
      unsigned last_bin = max_bin;
      for (; last_bin && !bin_sizes[last_bin]; --last_bin);
      //This dominates runtime, mostly in the swap and bin lookups
      for (unsigned u = 0; u < last_bin; ++u) {
        local_bin = bins + u;
        next_bin_start += bin_sizes[u];
        //Iterating over each element in this bin
        for (RandomAccessIter current = *local_bin; current < next_bin_start;
            ++current) {
          //Swapping into place until the correct element has been swapped in
          for (target_bin =
            end_bin - static_cast<Unsigned_char_type>((*current)[char_offset]);
            target_bin != local_bin;
            target_bin =
            end_bin - static_cast<Unsigned_char_type>((*current)[char_offset]))
              iter_swap(current, (*target_bin)++);
        }
        *local_bin = next_bin_start;
      }
      bins[last_bin] = lastFull;
      //Recursing
      RandomAccessIter lastPos = first;
      //Skip this loop for empties
      for (unsigned u = cache_offset; u <= cache_offset + last_bin;
          lastPos = bin_cache[u], ++u) {
        size_t count = bin_cache[u] - lastPos;
        //don't sort unless there are at least two items to Compare
        if (count < 2)
          continue;
        //using std::sort if its worst-case is better
        if (count < max_size)
          std::sort(lastPos, bin_cache[u], offset_greater_than<Data_type,
                    Unsigned_char_type>(char_offset + 1));
        else
          reverse_string_sort_rec<RandomAccessIter, Unsigned_char_type>
    (lastPos, bin_cache[u], char_offset + 1, bin_cache, cache_end, bin_sizes);
      }
    }

    //String sorting recursive implementation
    template <class RandomAccessIter, class Unsigned_char_type, class Get_char,
              class Get_length>
    inline void
    string_sort_rec(RandomAccessIter first, RandomAccessIter last,
              size_t char_offset, std::vector<RandomAccessIter> &bin_cache,
              unsigned cache_offset, size_t *bin_sizes,
              Get_char getchar, Get_length length)
    {
      typedef typename std::iterator_traits<RandomAccessIter>::value_type
        Data_type;
      //This section makes handling of long identical substrings much faster
      //with a mild average performance impact.
      //Iterate to the end of the empties.  If all empty, return
      while (length(*first) <= char_offset) {
        if (++first == last)
          return;
      }
      RandomAccessIter finish = last - 1;
      //Getting the last non-empty
      for (;length(*finish) <= char_offset; --finish);
      ++finish;
      update_offset(first, finish, char_offset, getchar, length);

      const unsigned bin_count = (1 << (sizeof(Unsigned_char_type)*8));
      //Equal worst-case of radix and comparison is when bin_count = n*log(n).
      const unsigned max_size = bin_count;
      const unsigned membin_count = bin_count + 1;
      unsigned cache_end;
      RandomAccessIter * bins = size_bins(bin_sizes, bin_cache, cache_offset,
                                          cache_end, membin_count) + 1;

      //Calculating the size of each bin; this takes roughly 10% of runtime
      for (RandomAccessIter current = first; current != last; ++current) {
        if (length(*current) <= char_offset) {
          bin_sizes[0]++;
        }
        else
          bin_sizes[getchar((*current), char_offset) + 1]++;
      }
      //Assign the bin positions
      bin_cache[cache_offset] = first;
      for (unsigned u = 0; u < membin_count - 1; u++)
        bin_cache[cache_offset + u + 1] =
          bin_cache[cache_offset + u] + bin_sizes[u];

      //Swap into place
      RandomAccessIter next_bin_start = first;
      //handling empty bins
      RandomAccessIter * local_bin = &(bin_cache[cache_offset]);
      next_bin_start +=  bin_sizes[0];
      RandomAccessIter * target_bin;
      //Iterating over each element in the bin of empties
      for (RandomAccessIter current = *local_bin; current < next_bin_start;
          ++current) {
        //empties belong in this bin
        while (length(*current) > char_offset) {
          target_bin = bins + getchar((*current), char_offset);
          iter_swap(current, (*target_bin)++);
        }
      }
      *local_bin = next_bin_start;
      //iterate backwards to find the last bin with elements in it
      //this saves iterations in multiple loops
      unsigned last_bin = bin_count - 1;
      for (; last_bin && !bin_sizes[last_bin + 1]; --last_bin);
      //This dominates runtime, mostly in the swap and bin lookups
      for (unsigned ii = 0; ii < last_bin; ++ii) {
        local_bin = bins + ii;
        next_bin_start += bin_sizes[ii + 1];
        //Iterating over each element in this bin
        for (RandomAccessIter current = *local_bin; current < next_bin_start;
            ++current) {
          //Swapping into place until the correct element has been swapped in
          for (target_bin = bins + getchar((*current), char_offset);
              target_bin != local_bin;
              target_bin = bins + getchar((*current), char_offset))
            iter_swap(current, (*target_bin)++);
        }
        *local_bin = next_bin_start;
      }
      bins[last_bin] = last;

      //Recursing
      RandomAccessIter lastPos = bin_cache[cache_offset];
      //Skip this loop for empties
      for (unsigned u = cache_offset + 1; u < cache_offset + last_bin + 2;
          lastPos = bin_cache[u], ++u) {
        size_t count = bin_cache[u] - lastPos;
        //don't sort unless there are at least two items to Compare
        if (count < 2)
          continue;
        //using std::sort if its worst-case is better
        if (count < max_size)
          std::sort(lastPos, bin_cache[u], offset_char_less_than<Data_type,
                    Get_char, Get_length>(char_offset + 1));
        else
          string_sort_rec<RandomAccessIter, Unsigned_char_type, Get_char,
            Get_length>(lastPos, bin_cache[u], char_offset + 1, bin_cache,
                        cache_end, bin_sizes, getchar, length);
      }
    }

    //String sorting recursive implementation
    template <class RandomAccessIter, class Unsigned_char_type, class Get_char,
              class Get_length, class Compare>
    inline void
    string_sort_rec(RandomAccessIter first, RandomAccessIter last,
              size_t char_offset, std::vector<RandomAccessIter> &bin_cache,
              unsigned cache_offset, size_t *bin_sizes,
              Get_char getchar, Get_length length, Compare comp)
    {
      //This section makes handling of long identical substrings much faster
      //with a mild average performance impact.
      //Iterate to the end of the empties.  If all empty, return
      while (length(*first) <= char_offset) {
        if (++first == last)
          return;
      }
      RandomAccessIter finish = last - 1;
      //Getting the last non-empty
      for (;length(*finish) <= char_offset; --finish);
      ++finish;
      update_offset(first, finish, char_offset, getchar, length);

      const unsigned bin_count = (1 << (sizeof(Unsigned_char_type)*8));
      //Equal worst-case of radix and comparison is when bin_count = n*log(n).
      const unsigned max_size = bin_count;
      const unsigned membin_count = bin_count + 1;
      unsigned cache_end;
      RandomAccessIter * bins = size_bins(bin_sizes, bin_cache, cache_offset,
                                          cache_end, membin_count) + 1;

      //Calculating the size of each bin; this takes roughly 10% of runtime
      for (RandomAccessIter current = first; current != last; ++current) {
        if (length(*current) <= char_offset) {
          bin_sizes[0]++;
        }
        else
          bin_sizes[getchar((*current), char_offset) + 1]++;
      }
      //Assign the bin positions
      bin_cache[cache_offset] = first;
      for (unsigned u = 0; u < membin_count - 1; u++)
        bin_cache[cache_offset + u + 1] =
          bin_cache[cache_offset + u] + bin_sizes[u];

      //Swap into place
      RandomAccessIter next_bin_start = first;
      //handling empty bins
      RandomAccessIter * local_bin = &(bin_cache[cache_offset]);
      next_bin_start +=  bin_sizes[0];
      RandomAccessIter * target_bin;
      //Iterating over each element in the bin of empties
      for (RandomAccessIter current = *local_bin; current < next_bin_start;
          ++current) {
        //empties belong in this bin
        while (length(*current) > char_offset) {
          target_bin = bins + getchar((*current), char_offset);
          iter_swap(current, (*target_bin)++);
        }
      }
      *local_bin = next_bin_start;
      //iterate backwards to find the last bin with elements in it
      //this saves iterations in multiple loops
      unsigned last_bin = bin_count - 1;
      for (; last_bin && !bin_sizes[last_bin + 1]; --last_bin);
      //This dominates runtime, mostly in the swap and bin lookups
      for (unsigned u = 0; u < last_bin; ++u) {
        local_bin = bins + u;
        next_bin_start += bin_sizes[u + 1];
        //Iterating over each element in this bin
        for (RandomAccessIter current = *local_bin; current < next_bin_start;
            ++current) {
          //Swapping into place until the correct element has been swapped in
          for (target_bin = bins + getchar((*current), char_offset);
              target_bin != local_bin;
              target_bin = bins + getchar((*current), char_offset))
            iter_swap(current, (*target_bin)++);
        }
        *local_bin = next_bin_start;
      }
      bins[last_bin] = last;

      //Recursing
      RandomAccessIter lastPos = bin_cache[cache_offset];
      //Skip this loop for empties
      for (unsigned u = cache_offset + 1; u < cache_offset + last_bin + 2;
          lastPos = bin_cache[u], ++u) {
        size_t count = bin_cache[u] - lastPos;
        //don't sort unless there are at least two items to Compare
        if (count < 2)
          continue;
        //using std::sort if its worst-case is better
        if (count < max_size)
          std::sort(lastPos, bin_cache[u], comp);
        else
          string_sort_rec<RandomAccessIter, Unsigned_char_type, Get_char,
                          Get_length, Compare>
            (lastPos, bin_cache[u], char_offset + 1, bin_cache, cache_end,
             bin_sizes, getchar, length, comp);
      }
    }

    //Sorts strings in reverse order, with empties at the end
    template <class RandomAccessIter, class Unsigned_char_type, class Get_char,
              class Get_length, class Compare>
    inline void
    reverse_string_sort_rec(RandomAccessIter first, RandomAccessIter last,
              size_t char_offset, std::vector<RandomAccessIter> &bin_cache,
              unsigned cache_offset, size_t *bin_sizes,
              Get_char getchar, Get_length length, Compare comp)
    {
      //This section makes handling of long identical substrings much faster
      //with a mild average performance impact.
      RandomAccessIter curr = first;
      //Iterate to the end of the empties.  If all empty, return
      while (length(*curr) <= char_offset) {
        if (++curr == last)
          return;
      }
      //Getting the last non-empty
      while (length(*(--last)) <= char_offset);
      ++last;
      //Offsetting on identical characters.  This section works
      //a character at a time for optimal worst-case performance.
      update_offset(curr, last, char_offset, getchar, length);

      const unsigned bin_count = (1 << (sizeof(Unsigned_char_type)*8));
      //Equal worst-case of radix and comparison is when bin_count = n*log(n).
      const unsigned max_size = bin_count;
      const unsigned membin_count = bin_count + 1;
      const unsigned max_bin = bin_count - 1;
      unsigned cache_end;
      RandomAccessIter * bins = size_bins(bin_sizes, bin_cache, cache_offset,
                                          cache_end, membin_count);
      RandomAccessIter *end_bin = &(bin_cache[cache_offset + max_bin]);

      //Calculating the size of each bin; this takes roughly 10% of runtime
      for (RandomAccessIter current = first; current != last; ++current) {
        if (length(*current) <= char_offset) {
          bin_sizes[bin_count]++;
        }
        else
          bin_sizes[max_bin - getchar((*current), char_offset)]++;
      }
      //Assign the bin positions
      bin_cache[cache_offset] = first;
      for (unsigned u = 0; u < membin_count - 1; u++)
        bin_cache[cache_offset + u + 1] =
          bin_cache[cache_offset + u] + bin_sizes[u];

      //Swap into place
      RandomAccessIter next_bin_start = last;
      //handling empty bins
      RandomAccessIter * local_bin = &(bin_cache[cache_offset + bin_count]);
      RandomAccessIter lastFull = *local_bin;
      RandomAccessIter * target_bin;
      //Iterating over each element in the bin of empties
      for (RandomAccessIter current = *local_bin; current < next_bin_start;
          ++current) {
        //empties belong in this bin
        while (length(*current) > char_offset) {
          target_bin = end_bin - getchar((*current), char_offset);
          iter_swap(current, (*target_bin)++);
        }
      }
      *local_bin = next_bin_start;
      next_bin_start = first;
      //iterate backwards to find the last bin with elements in it
      //this saves iterations in multiple loops
      unsigned last_bin = max_bin;
      for (; last_bin && !bin_sizes[last_bin]; --last_bin);
      //This dominates runtime, mostly in the swap and bin lookups
      for (unsigned u = 0; u < last_bin; ++u) {
        local_bin = bins + u;
        next_bin_start += bin_sizes[u];
        //Iterating over each element in this bin
        for (RandomAccessIter current = *local_bin; current < next_bin_start;
            ++current) {
          //Swapping into place until the correct element has been swapped in
          for (target_bin = end_bin - getchar((*current), char_offset);
              target_bin != local_bin;
              target_bin = end_bin - getchar((*current), char_offset))
            iter_swap(current, (*target_bin)++);
        }
        *local_bin = next_bin_start;
      }
      bins[last_bin] = lastFull;
      //Recursing
      RandomAccessIter lastPos = first;
      //Skip this loop for empties
      for (unsigned u = cache_offset; u <= cache_offset + last_bin;
          lastPos = bin_cache[u], ++u) {
        size_t count = bin_cache[u] - lastPos;
        //don't sort unless there are at least two items to Compare
        if (count < 2)
          continue;
        //using std::sort if its worst-case is better
        if (count < max_size)
          std::sort(lastPos, bin_cache[u], comp);
        else
          reverse_string_sort_rec<RandomAccessIter, Unsigned_char_type,
                                  Get_char, Get_length, Compare>
            (lastPos, bin_cache[u], char_offset + 1, bin_cache, cache_end,
             bin_sizes, getchar, length, comp);
      }
    }

    //Holds the bin vector and makes the initial recursive call
    template <class RandomAccessIter, class Unsigned_char_type>
    inline typename std::enable_if< sizeof(Unsigned_char_type) <= 2, void
                                                                      >::type
    string_sort(RandomAccessIter first, RandomAccessIter last,
                Unsigned_char_type)
    {
      size_t bin_sizes[(1 << (8 * sizeof(Unsigned_char_type))) + 1];
      std::vector<RandomAccessIter> bin_cache;
      string_sort_rec<RandomAccessIter, Unsigned_char_type>
        (first, last, 0, bin_cache, 0, bin_sizes);
    }

    template <class RandomAccessIter, class Unsigned_char_type>
    inline typename boost::disable_if_c< sizeof(Unsigned_char_type) <= 2, void
                                                                       >::type
    string_sort(RandomAccessIter first, RandomAccessIter last,
                Unsigned_char_type)
    {
      //Warning that we're using std::sort, even though string_sort was called
      std::sort(first, last);
    }

    //Holds the bin vector and makes the initial recursive call
    template <class RandomAccessIter, class Unsigned_char_type>
    inline typename std::enable_if< sizeof(Unsigned_char_type) <= 2, void
                                                                      >::type
    reverse_string_sort(RandomAccessIter first, RandomAccessIter last,
                        Unsigned_char_type)
    {
      size_t bin_sizes[(1 << (8 * sizeof(Unsigned_char_type))) + 1];
      std::vector<RandomAccessIter> bin_cache;
      reverse_string_sort_rec<RandomAccessIter, Unsigned_char_type>
        (first, last, 0, bin_cache, 0, bin_sizes);
    }

    template <class RandomAccessIter, class Unsigned_char_type>
    inline typename boost::disable_if_c< sizeof(Unsigned_char_type) <= 2, void
                                                                       >::type
    reverse_string_sort(RandomAccessIter first, RandomAccessIter last,
                Unsigned_char_type)
    {
      typedef typename std::iterator_traits<RandomAccessIter>::value_type
        Data_type;
      //Warning that we're using std::sort, even though string_sort was called
      std::sort(first, last, std::greater<Data_type>());
    }

    //Holds the bin vector and makes the initial recursive call
    template <class RandomAccessIter, class Get_char, class Get_length,
              class Unsigned_char_type>
    inline typename std::enable_if< sizeof(Unsigned_char_type) <= 2, void
                                                                      >::type
    string_sort(RandomAccessIter first, RandomAccessIter last,
                Get_char getchar, Get_length length, Unsigned_char_type)
    {
      size_t bin_sizes[(1 << (8 * sizeof(Unsigned_char_type))) + 1];
      std::vector<RandomAccessIter> bin_cache;
      string_sort_rec<RandomAccessIter, Unsigned_char_type, Get_char,
        Get_length>(first, last, 0, bin_cache, 0, bin_sizes, getchar, length);
    }

    template <class RandomAccessIter, class Get_char, class Get_length,
              class Unsigned_char_type>
    inline typename boost::disable_if_c< sizeof(Unsigned_char_type) <= 2, void
                                                                       >::type
    string_sort(RandomAccessIter first, RandomAccessIter last,
                Get_char getchar, Get_length length, Unsigned_char_type)
    {
      //Warning that we're using std::sort, even though string_sort was called
      std::sort(first, last);
    }

    //Holds the bin vector and makes the initial recursive call
    template <class RandomAccessIter, class Get_char, class Get_length,
              class Compare, class Unsigned_char_type>
    inline typename std::enable_if< sizeof(Unsigned_char_type) <= 2, void
                                                                      >::type
    string_sort(RandomAccessIter first, RandomAccessIter last,
        Get_char getchar, Get_length length, Compare comp, Unsigned_char_type)
    {
      size_t bin_sizes[(1 << (8 * sizeof(Unsigned_char_type))) + 1];
      std::vector<RandomAccessIter> bin_cache;
      string_sort_rec<RandomAccessIter, Unsigned_char_type, Get_char
        , Get_length, Compare>
        (first, last, 0, bin_cache, 0, bin_sizes, getchar, length, comp);
    }

    //disable_if_c was refusing to compile, so rewrote to use enable_if_c
    template <class RandomAccessIter, class Get_char, class Get_length,
              class Compare, class Unsigned_char_type>
    inline typename std::enable_if< (sizeof(Unsigned_char_type) > 2), void
                                        >::type
    string_sort(RandomAccessIter first, RandomAccessIter last,
        Get_char getchar, Get_length length, Compare comp, Unsigned_char_type)
    {
      //Warning that we're using std::sort, even though string_sort was called
      std::sort(first, last, comp);
    }

    //Holds the bin vector and makes the initial recursive call
    template <class RandomAccessIter, class Get_char, class Get_length,
              class Compare, class Unsigned_char_type>
    inline typename std::enable_if< sizeof(Unsigned_char_type) <= 2, void
                                                                      >::type
    reverse_string_sort(RandomAccessIter first, RandomAccessIter last,
        Get_char getchar, Get_length length, Compare comp, Unsigned_char_type)
    {
      size_t bin_sizes[(1 << (8 * sizeof(Unsigned_char_type))) + 1];
      std::vector<RandomAccessIter> bin_cache;
      reverse_string_sort_rec<RandomAccessIter, Unsigned_char_type, Get_char,
                              Get_length, Compare>
        (first, last, 0, bin_cache, 0, bin_sizes, getchar, length, comp);
    }

    template <class RandomAccessIter, class Get_char, class Get_length,
              class Compare, class Unsigned_char_type>
    inline typename boost::disable_if_c< sizeof(Unsigned_char_type) <= 2, void
                                                                       >::type
    reverse_string_sort(RandomAccessIter first, RandomAccessIter last,
        Get_char getchar, Get_length length, Compare comp, Unsigned_char_type)
    {
      //Warning that we're using std::sort, even though string_sort was called
      std::sort(first, last, comp);
    }
  }
}
}
}

#endif

namespace boost {
namespace sort {
namespace spreadsort {

/*! \brief String sort algorithm using random access iterators, allowing character-type overloads.\n
  (All variants fall back to @c std::sort if the data size is too small, < @c detail::min_sort_size).

  \details @c string_sort is a fast templated in-place hybrid radix/comparison algorithm,
which in testing tends to be roughly 50% to 2X faster than @c std::sort for large tests (>=100kB).\n
\par
Worst-case performance is <em>  O(N * (lg(range)/s + s)) </em>,
so @c integer_sort is asymptotically faster
than pure comparison-based algorithms. @c s is @c max_splits, which defaults to 11,
so its worst-case with default settings for 32-bit integers is
<em> O(N * ((32/11) </em> slow radix-based iterations fast comparison-based iterations).\n\n
Some performance plots of runtime vs. n and log(range) are provided:\n
<a href="../../doc/graph/windows_string_sort.htm"> windows_string_sort</a>\n
<a href="../../doc/graph/osx_string_sort.htm"> osx_string_sort</a>

   \tparam RandomAccessIter <a href="http://www.cplusplus.com/reference/iterator/RandomAccessIterator/">Random access iterator</a>
   \tparam Unsigned_char_type  Unsigned character type used for string.
   \param[in] first Iterator pointer to first element.
   \param[in] last Iterator pointing to one beyond the end of data.
   \param[in] unused value with the same type as the result of the [] operator, defining the Unsigned_char_type.  The actual value is unused.

   \pre [@c first, @c last) is a valid range.
   \pre @c RandomAccessIter @c value_type is mutable.
   \pre @c RandomAccessIter @c value_type is <a href="http://en.cppreference.com/w/cpp/concept/LessThanComparable">LessThanComparable</a>
   \pre @c RandomAccessIter @c value_type supports the @c operator>>,
   which returns an integer-type right-shifted a specified number of bits.
   \post The elements in the range [@c first, @c last) are sorted in ascending order.

   \throws std::exception Propagates exceptions if any of the element comparisons, the element swaps (or moves),
   the right shift, subtraction of right-shifted elements, functors,
   or any operations on iterators throw.

   \warning Throwing an exception may cause data loss. This will also throw if a small vector resize throws, in which case there will be no data loss.
   \warning Invalid arguments cause undefined behaviour.
   \note @c spreadsort function provides a wrapper that calls the fastest sorting algorithm available for a data type,
   enabling faster generic-programming.

   \remark The lesser of <em> O(N*log(N)) </em> comparisons and <em> O(N*log(K/S + S)) </em>operations worst-case, where:
   \remark  *  N is @c last - @c first,
   \remark  *  K is the log of the range in bits (32 for 32-bit integers using their full range),
   \remark  *  S is a constant called max_splits, defaulting to 11 (except for strings where it is the log of the character size).

*/

  template <class RandomAccessIter, class Unsigned_char_type>
  inline void string_sort(RandomAccessIter first, RandomAccessIter last,
                          Unsigned_char_type unused)
  {
    //Don't sort if it's too small to optimize
    if (last - first < detail::min_sort_size)
      std::sort(first, last);
    else
      detail::string_sort(first, last, unused);
  }


/*! \brief String sort algorithm using random access iterators, wraps using default of unsigned char.
  (All variants fall back to @c std::sort if the data size is too small, < @c detail::min_sort_size).

  \details @c string_sort is a fast templated in-place hybrid radix/comparison algorithm,
which in testing tends to be roughly 50% to 2X faster than @c std::sort for large tests (>=100kB).\n
Worst-case performance is <em>  O(N * (lg(range)/s + s)) </em>,
so @c integer_sort is asymptotically faster
than pure comparison-based algorithms. @c s is @c max_splits, which defaults to 11,
so its worst-case with default settings for 32-bit integers is
<em> O(N * ((32/11) </em> slow radix-based iterations fast comparison-based iterations).\n\n
Some performance plots of runtime vs. n and log(range) are provided:\n
   <a href="../../doc/graph/windows_string_sort.htm"> windows_string_sort</a>
   \n
   <a href="../../doc/graph/osx_string_sort.htm"> osx_string_sort</a>

   \param[in] first Iterator pointer to first element.
   \param[in] last Iterator pointing to one beyond the end of data.

   \pre [@c first, @c last) is a valid range.
   \pre @c RandomAccessIter @c value_type is mutable.
   \pre @c RandomAccessIter @c value_type is <a href="http://en.cppreference.com/w/cpp/concept/LessThanComparable">LessThanComparable</a>
   \pre @c RandomAccessIter @c value_type supports the @c operator>>,
   which returns an integer-type right-shifted a specified number of bits.
   \post The elements in the range [@c first, @c last) are sorted in ascending order.

   \throws std::exception Propagates exceptions if any of the element comparisons, the element swaps (or moves),
   the right shift, subtraction of right-shifted elements, functors,
   or any operations on iterators throw.

   \warning Throwing an exception may cause data loss. This will also throw if a small vector resize throws, in which case there will be no data loss.
   \warning Invalid arguments cause undefined behaviour.
   \note @c spreadsort function provides a wrapper that calls the fastest sorting algorithm available for a data type,
   enabling faster generic-programming.

   \remark The lesser of <em> O(N*log(N)) </em> comparisons and <em> O(N*log(K/S + S)) </em>operations worst-case, where:
   \remark  *  N is @c last - @c first,
   \remark  *  K is the log of the range in bits (32 for 32-bit integers using their full range),
   \remark  *  S is a constant called max_splits, defaulting to 11 (except for strings where it is the log of the character size).

*/
  template <class RandomAccessIter>
  inline void string_sort(RandomAccessIter first, RandomAccessIter last)
  {
    unsigned char unused = '\0';
    string_sort(first, last, unused);
  }


/*! \brief String sort algorithm using random access iterators, allowing character-type overloads.

  (All variants fall back to @c std::sort if the data size is too small, < detail::min_sort_size).

  \details @c integer_sort is a fast templated in-place hybrid radix/comparison algorithm,
which in testing tends to be roughly 50% to 2X faster than @c std::sort for large tests (>=100kB).\n
Worst-case performance is <em>  O(N * (lg(range)/s + s)) </em>,
so @c integer_sort is asymptotically faster
than pure comparison-based algorithms. @c s is @c max_splits, which defaults to 11,
so its worst-case with default settings for 32-bit integers is
<em> O(N * ((32/11) </em> slow radix-based iterations fast comparison-based iterations).\n\n
Some performance plots of runtime vs. n and log(range) are provided:\n
   <a href="../../doc/graph/windows_integer_sort.htm"> windows_integer_sort</a>
   \n
   <a href="../../doc/graph/osx_integer_sort.htm"> osx_integer_sort</a>


   \tparam RandomAccessIter <a href="http://www.cplusplus.com/reference/iterator/RandomAccessIterator/">Random access iterator</a>
   \tparam Comp Functor type to use for comparison.
   \tparam Unsigned_char_type Unsigned character type used for string.

   \param[in] first Iterator pointer to first element.
   \param[in] last Iterator pointing to one beyond the end of data.
   \param[in] comp A binary functor that returns whether the first element passed to it should go before the second in order.
   \param[in] unused value with the same type as the result of the [] operator, defining the Unsigned_char_type.  The actual value is unused.

   \pre [@c first, @c last) is a valid range.
   \pre @c RandomAccessIter @c value_type is mutable.
   \pre @c RandomAccessIter @c value_type is <a href="http://en.cppreference.com/w/cpp/concept/LessThanComparable">LessThanComparable</a>
   \pre @c RandomAccessIter @c value_type supports the @c operator>>,
   which returns an integer-type right-shifted a specified number of bits.
   \post The elements in the range [@c first, @c last) are sorted in ascending order.

   \return @c void.

   \throws  std::exception Propagates exceptions if any of the element comparisons, the element swaps (or moves),
   the right shift, subtraction of right-shifted elements, functors,
   or any operations on iterators throw.

   \warning Throwing an exception may cause data loss. This will also throw if a small vector resize throws, in which case there will be no data loss.
   \warning Invalid arguments cause undefined behaviour.
   \note @c spreadsort function provides a wrapper that calls the fastest sorting algorithm available for a data type,
   enabling faster generic-programming.

   \remark The lesser of <em> O(N*log(N)) </em> comparisons and <em> O(N*log(K/S + S)) </em>operations worst-case, where:
   \remark  *  N is @c last - @c first,
   \remark  *  K is the log of the range in bits (32 for 32-bit integers using their full range),
   \remark  *  S is a constant called max_splits, defaulting to 11 (except for strings where it is the log of the character size).
*/
  template <class RandomAccessIter, class Compare, class Unsigned_char_type>
  inline void reverse_string_sort(RandomAccessIter first,
                RandomAccessIter last, Compare comp, Unsigned_char_type unused)
  {
    //Don't sort if it's too small to optimize.
    if (last - first < detail::min_sort_size)
      std::sort(first, last, comp);
    else
      detail::reverse_string_sort(first, last, unused);
  }


/*! \brief String sort algorithm using random access iterators,  wraps using default of @c unsigned char.

  (All variants fall back to @c std::sort if the data size is too small, < @c detail::min_sort_size).

  \details @c integer_sort is a fast templated in-place hybrid radix/comparison algorithm,
which in testing tends to be roughly 50% to 2X faster than @c std::sort for large tests (>=100kB).\n
Worst-case performance is <em>  O(N * (lg(range)/s + s)) </em>,
so @c integer_sort is asymptotically faster
than pure comparison-based algorithms. @c s is @c max_splits, which defaults to 11,
so its worst-case with default settings for 32-bit integers is
<em> O(N * ((32/11) </em> slow radix-based iterations fast comparison-based iterations).\n\n
Some performance plots of runtime vs. n and log(range) are provided:\n
   <a href="../../doc/graph/windows_integer_sort.htm"> windows_integer_sort</a>
   \n
   <a href="../../doc/graph/osx_integer_sort.htm"> osx_integer_sort</a>

   \param[in] first Iterator pointer to first element.
   \param[in] last Iterator pointing to one beyond the end of data.
   \param[in] comp A binary functor that returns whether the first element passed to it should go before the second in order.

   \pre [@c first, @c last) is a valid range.
   \pre @c RandomAccessIter @c value_type is mutable.
   \pre @c RandomAccessIter @c value_type is <a href="http://en.cppreference.com/w/cpp/concept/LessThanComparable">LessThanComparable</a>
   \pre @c RandomAccessIter @c value_type supports the @c operator>>,
   which returns an integer-type right-shifted a specified number of bits.
   \post The elements in the range [@c first, @c last) are sorted in ascending order.

   \return @c void.

   \throws  std::exception Propagates exceptions if any of the element comparisons, the element swaps (or moves),
   the right shift, subtraction of right-shifted elements, functors,
   or any operations on iterators throw.

   \warning Throwing an exception may cause data loss. This will also throw if a small vector resize throws, in which case there will be no data loss.
   \warning Invalid arguments cause undefined behaviour.
   \note @c spreadsort function provides a wrapper that calls the fastest sorting algorithm available for a data type,
   enabling faster generic-programming.

   \remark The lesser of <em> O(N*log(N)) </em> comparisons and <em> O(N*log(K/S + S)) </em>operations worst-case, where:
   \remark  *  N is @c last - @c first,
   \remark  *  K is the log of the range in bits (32 for 32-bit integers using their full range),
   \remark  *  S is a constant called max_splits, defaulting to 11 (except for strings where it is the log of the character size).
*/
  template <class RandomAccessIter, class Compare>
  inline void reverse_string_sort(RandomAccessIter first,
                                  RandomAccessIter last, Compare comp)
  {
    unsigned char unused = '\0';
    reverse_string_sort(first, last, comp, unused);
  }


/*! \brief String sort algorithm using random access iterators,  wraps using default of @c unsigned char.

  (All variants fall back to @c std::sort if the data size is too small, < @c detail::min_sort_size).

  \details @c integer_sort is a fast templated in-place hybrid radix/comparison algorithm,
which in testing tends to be roughly 50% to 2X faster than @c std::sort for large tests (>=100kB).\n
Worst-case performance is <em>  O(N * (lg(range)/s + s)) </em>,
so @c integer_sort is asymptotically faster
than pure comparison-based algorithms. @c s is @c max_splits, which defaults to 11,
so its worst-case with default settings for 32-bit integers is
<em> O(N * ((32/11) </em> slow radix-based iterations fast comparison-based iterations).\n\n
Some performance plots of runtime vs. n and log(range) are provided:\n
   <a href="../../doc/graph/windows_integer_sort.htm"> windows_integer_sort</a>
   \n
   <a href="../../doc/graph/osx_integer_sort.htm"> osx_integer_sort</a>

   \param[in] first Iterator pointer to first element.
   \param[in] last Iterator pointing to one beyond the end of data.
   \param[in] getchar Bracket functor equivalent to @c operator[], taking a number corresponding to the character offset.
   \param[in] length Functor to get the length of the string in characters.

   \pre [@c first, @c last) is a valid range.
   \pre @c RandomAccessIter @c value_type is mutable.
   \pre @c RandomAccessIter @c value_type is <a href="http://en.cppreference.com/w/cpp/concept/LessThanComparable">LessThanComparable</a>
   \pre @c RandomAccessIter @c value_type supports the @c operator>>,
   which returns an integer-type right-shifted a specified number of bits.
   \post The elements in the range [@c first, @c last) are sorted in ascending order.

   \return @c void.

   \throws  std::exception Propagates exceptions if any of the element comparisons, the element swaps (or moves),
   the right shift, subtraction of right-shifted elements, functors,
   or any operations on iterators throw.

   \warning Throwing an exception may cause data loss. This will also throw if a small vector resize throws, in which case there will be no data loss.
   \warning Invalid arguments cause undefined behaviour.
   \note @c spreadsort function provides a wrapper that calls the fastest sorting algorithm available for a data type,
   enabling faster generic-programming.

   \remark The lesser of <em> O(N*log(N)) </em> comparisons and <em> O(N*log(K/S + S)) </em>operations worst-case, where:
   \remark  *  N is @c last - @c first,
   \remark  *  K is the log of the range in bits (32 for 32-bit integers using their full range),
   \remark  *  S is a constant called max_splits, defaulting to 11 (except for strings where it is the log of the character size).

*/
  template <class RandomAccessIter, class Get_char, class Get_length>
  inline void string_sort(RandomAccessIter first, RandomAccessIter last,
                          Get_char getchar, Get_length length)
  {
    //Don't sort if it's too small to optimize
    if (last - first < detail::min_sort_size)
      std::sort(first, last);
    else {
      //skipping past empties, which allows us to get the character type
      //.empty() is not used so as not to require a user declaration of it
      while (!length(*first)) {
        if (++first == last)
          return;
      }
      detail::string_sort(first, last, getchar, length, getchar((*first), 0));
    }
  }



/*! \brief String sort algorithm using random access iterators,  wraps using default of @c unsigned char.

  (All variants fall back to @c std::sort if the data size is too small, < @c detail::min_sort_size).

  \details @c integer_sort is a fast templated in-place hybrid radix/comparison algorithm,
which in testing tends to be roughly 50% to 2X faster than @c std::sort for large tests (>=100kB).\n
Worst-case performance is <em>  O(N * (lg(range)/s + s)) </em>,
so @c integer_sort is asymptotically faster
than pure comparison-based algorithms. @c s is @c max_splits, which defaults to 11,
so its worst-case with default settings for 32-bit integers is
<em> O(N * ((32/11) </em> slow radix-based iterations fast comparison-based iterations).\n\n
Some performance plots of runtime vs. n and log(range) are provided:\n
   <a href="../../doc/graph/windows_integer_sort.htm"> windows_integer_sort</a>
   \n
   <a href="../../doc/graph/osx_integer_sort.htm"> osx_integer_sort</a>


   \param[in] first Iterator pointer to first element.
   \param[in] last Iterator pointing to one beyond the end of data.
   \param[in] getchar Bracket functor equivalent to @c operator[], taking a number corresponding to the character offset.
   \param[in] length Functor to get the length of the string in characters.
   \param[in] comp A binary functor that returns whether the first element passed to it should go before the second in order.


   \pre [@c first, @c last) is a valid range.
   \pre @c RandomAccessIter @c value_type is mutable.
   \pre @c RandomAccessIter @c value_type is <a href="http://en.cppreference.com/w/cpp/concept/LessThanComparable">LessThanComparable</a>
   \post The elements in the range [@c first, @c last) are sorted in ascending order.

   \return @c void.

   \throws std::exception Propagates exceptions if any of the element comparisons, the element swaps (or moves),
   the right shift, subtraction of right-shifted elements, functors,
   or any operations on iterators throw.

   \warning Throwing an exception may cause data loss. This will also throw if a small vector resize throws, in which case there will be no data loss.
   \warning Invalid arguments cause undefined behaviour.
   \note @c spreadsort function provides a wrapper that calls the fastest sorting algorithm available for a data type,
   enabling faster generic-programming.

   \remark The lesser of <em> O(N*log(N)) </em> comparisons and <em> O(N*log(K/S + S)) </em>operations worst-case, where:
   \remark  *  N is @c last - @c first,
   \remark  *  K is the log of the range in bits (32 for 32-bit integers using their full range),
   \remark  *  S is a constant called max_splits, defaulting to 11 (except for strings where it is the log of the character size).

*/
  template <class RandomAccessIter, class Get_char, class Get_length,
            class Compare>
  inline void string_sort(RandomAccessIter first, RandomAccessIter last,
                          Get_char getchar, Get_length length, Compare comp)
  {
    //Don't sort if it's too small to optimize
    if (last - first < detail::min_sort_size)
      std::sort(first, last, comp);
    else {
      //skipping past empties, which allows us to get the character type
      //.empty() is not used so as not to require a user declaration of it
      while (!length(*first)) {
        if (++first == last)
          return;
      }
      detail::string_sort(first, last, getchar, length, comp,
                          getchar((*first), 0));
    }
  }


/*! \brief Reverse String sort algorithm using random access iterators.

  (All variants fall back to @c std::sort if the data size is too small, < @c detail::min_sort_size).

  \details @c integer_sort is a fast templated in-place hybrid radix/comparison algorithm,
which in testing tends to be roughly 50% to 2X faster than @c std::sort for large tests (>=100kB).\n
Worst-case performance is <em>  O(N * (lg(range)/s + s)) </em>,
so @c integer_sort is asymptotically faster
than pure comparison-based algorithms. @c s is @c max_splits, which defaults to 11,
so its worst-case with default settings for 32-bit integers is
<em> O(N * ((32/11) </em> slow radix-based iterations fast comparison-based iterations).\n\n
Some performance plots of runtime vs. n and log(range) are provided:\n
   <a href="../../doc/graph/windows_integer_sort.htm"> windows_integer_sort</a>
   \n
   <a href="../../doc/graph/osx_integer_sort.htm"> osx_integer_sort</a>


   \param[in] first Iterator pointer to first element.
   \param[in] last Iterator pointing to one beyond the end of data.
   \param[in] getchar Bracket functor equivalent to @c operator[], taking a number corresponding to the character offset.
   \param[in] length Functor to get the length of the string in characters.
   \param[in] comp A binary functor that returns whether the first element passed to it should go before the second in order.


   \pre [@c first, @c last) is a valid range.
   \pre @c RandomAccessIter @c value_type is mutable.
   \pre @c RandomAccessIter @c value_type is <a href="http://en.cppreference.com/w/cpp/concept/LessThanComparable">LessThanComparable</a>
   \post The elements in the range [@c first, @c last) are sorted in ascending order.

   \return @c void.

   \throws std::exception Propagates exceptions if any of the element comparisons, the element swaps (or moves),
   the right shift, subtraction of right-shifted elements, functors,
   or any operations on iterators throw.

   \warning Throwing an exception may cause data loss. This will also throw if a small vector resize throws, in which case there will be no data loss.
   \warning Invalid arguments cause undefined behaviour.
   \note @c spreadsort function provides a wrapper that calls the fastest sorting algorithm available for a data type,
   enabling faster generic-programming.

   \remark The lesser of <em> O(N*log(N)) </em> comparisons and <em> O(N*log(K/S + S)) </em>operations worst-case, where:
   \remark  *  N is @c last - @c first,
   \remark  *  K is the log of the range in bits (32 for 32-bit integers using their full range),
   \remark  *  S is a constant called max_splits, defaulting to 11 (except for strings where it is the log of the character size).

*/
  template <class RandomAccessIter, class Get_char, class Get_length,
            class Compare>
  inline void reverse_string_sort(RandomAccessIter first,
    RandomAccessIter last, Get_char getchar, Get_length length, Compare comp)
  {
    //Don't sort if it's too small to optimize
    if (last - first < detail::min_sort_size)
      std::sort(first, last, comp);
    else {
      //skipping past empties, which allows us to get the character type
      //.empty() is not used so as not to require a user declaration of it
      while (!length(*(--last))) {
        //If there is just one non-empty at the beginning, this is sorted
        if (first == last)
          return;
      }
      //making last just after the end of the non-empty part of the array
      detail::reverse_string_sort(first, last + 1, getchar, length, comp,
                                  getchar((*last), 0));
    }
  }
}
}
}

#endif

const std::size_t maxLength = 64;

using Line = std::array<char, maxLength + 1>;

struct Timer {
#if !defined(_DEBUG)
    Timer(const std::string &) {}
    ~Timer() {}
#else
    Timer(const std::string& message)
        : start(std::chrono::system_clock::now()),
          message(message) {}

    ~Timer() {
        auto end = std::chrono::system_clock::now();
        std::chrono::duration<double> diff = end - start;
        std::cerr << message << " " << diff.count() << std::endl;
    }

    std::chrono::system_clock::time_point start;
    std::string message;
#endif
};

void sortRange(std::vector<Line>::iterator begin,
               std::vector<Line>::iterator end) {
    Timer t("Time to sort subrange of size " +
            std::to_string(std::distance(begin, end)));
    boost::sort::spreadsort::string_sort(begin, end, '\0');
}

struct LineFacade {
    LineFacade(std::size_t numberOfLines)
        : storage(new char[numberOfLines * (maxLength + 1)]), offset(storage) {}

    void operator=(const Line& line) {
        auto it = std::find(line.begin(), line.end(), '\0');

        std::size_t count = std::distance(line.begin(), it);

        std::memcpy(offset, line.data(), count);
        offset += count;
    }

    char* storage;
    char* offset;
};

class DataPrintIterator
    : public std::iterator<std::output_iterator_tag, LineFacade> {

public:
    DataPrintIterator(LineFacade& lineFacade) : lineFacade_(lineFacade) {}

    DataPrintIterator(const DataPrintIterator& rhs)
        : lineFacade_(rhs.lineFacade_) {}

    DataPrintIterator& operator=(const DataPrintIterator& rhs) {
        this->lineFacade_ = rhs.lineFacade_;
        return *this;
    }

    DataPrintIterator& operator++() { return *this; }
    DataPrintIterator& operator++(int) { return *this; }

    LineFacade& operator*() { return lineFacade_; }

    const LineFacade& lineFacade() { return lineFacade_; }

private:
    LineFacade& lineFacade_;
};

template <typename OutputIterator, typename Iterator>
OutputIterator threeWayMerge(OutputIterator outputIterator, Iterator begin1,
                             Iterator end1, Iterator begin2, Iterator end2,
                             Iterator begin3, Iterator end3) {
    for (; begin1 != end1; ++outputIterator) {
        if (begin2 == end2) {
            return std::merge(begin1, end1, begin3, end3, outputIterator);
        }

        if (begin3 == end3) {
            return std::merge(begin1, end1, begin2, end2, outputIterator);
        }

        const auto& one = *begin1;
        const auto& two = *begin2;
        const auto& three = *begin3;

        if (one <= two && one <= three) {
            *outputIterator = one;
            ++begin1;
        } else if (two <= one && two <= three) {
            *outputIterator = two;
            ++begin2;
        } else {
            *outputIterator = three;
            ++begin3;
        }
    }
    return std::merge(begin2, end2, begin3, end3, outputIterator);
}

template <typename OutputIterator, typename Iterator>
OutputIterator fourWayMerge(OutputIterator outputIterator, Iterator begin1,
                            Iterator end1, Iterator begin2, Iterator end2,
                            Iterator begin3, Iterator end3, Iterator begin4,
                            Iterator end4) {
    for (; begin1 != end1; ++outputIterator) {
        if (begin2 == end2) {
            return threeWayMerge(outputIterator, begin1, end1, begin3, end3,
                                 begin4, end4);
        }

        if (begin3 == end3) {
            return threeWayMerge(outputIterator, begin1, end1, begin2, end2,
                                 begin4, end4);
        }

        if (begin4 == end4) {
            return threeWayMerge(outputIterator, begin1, end1, begin2, end2,
                                 begin3, end3);
        }

        const auto& one = *begin1;
        const auto& two = *begin2;
        const auto& three = *begin3;
        const auto& four = *begin4;

        if (one <= two && one <= three && one <= four) {
            *outputIterator = one;
            ++begin1;
        } else if ( two <= one && two <= three && two <= four ) {
            *outputIterator = two;
            ++begin2;
        } else if (three <= one && three <= two && three <= four) {
            *outputIterator = three;
            ++begin3;
        } else {
            *outputIterator = four;
            ++begin4;
        }
    }
    return threeWayMerge(outputIterator, begin2, end2, begin3, end3, begin4,
                         end4);
}

std::pair<char*, std::size_t> sortAndPrintLines(std::vector<Line>& lines) {
    Timer t("Time to sort lines");
    auto firstPartition = lines.begin() + lines.size() / 4;
    auto secondPartition = firstPartition + lines.size() / 4;
    auto thirdPartition = secondPartition + lines.size() / 4;

    auto firstHandle =
        std::async(std::launch::async, [&lines, firstPartition]() {
            sortRange(lines.begin(), firstPartition);
        });

    auto secondHandle = std::async(std::launch::async,
                                   [&lines, firstPartition, secondPartition]() {
        sortRange(firstPartition, secondPartition);
    });

    auto thirdHandle = std::async(std::launch::async,
                                  [&lines, secondPartition, thirdPartition]() {
        sortRange(secondPartition, thirdPartition);
    });

    auto forthHandle = std::async(
        std::launch::async,
        [&lines, thirdPartition]() { sortRange(thirdPartition, lines.end()); });

    LineFacade lineFacade(lines.size());
    DataPrintIterator outIterator(lineFacade);

    std::vector<Line> firstMerge;
    firstMerge.reserve(lines.size()/2+1);

    auto firstMergeHandle = std::async(
        std::launch::async, [&firstHandle, &secondHandle, &lines, &firstMerge,
                             firstPartition, secondPartition]() {
            firstHandle.get();
            secondHandle.get();
            std::merge(lines.begin(), firstPartition, firstPartition,
                       secondPartition, std::back_inserter(firstMerge));
        });

    std::vector<Line> secondMerge;
    secondMerge.reserve(lines.size()/2+1);

    auto secondMergeHandle = std::async(
        std::launch::async, [&thirdHandle, &forthHandle, &lines, &secondMerge,
                             secondPartition, thirdPartition]() {
            thirdHandle.get();
            forthHandle.get();
            std::merge(secondPartition, thirdPartition, thirdPartition,
                       lines.end(), std::back_inserter(secondMerge));
        });

    firstMergeHandle.get();
    secondMergeHandle.get();

    std::merge(firstMerge.begin(), firstMerge.end(), secondMerge.begin(),
               secondMerge.end(), outIterator);

    std::size_t totalCount = lineFacade.offset - lineFacade.storage;

    return {lineFacade.storage, totalCount};

}

std::vector<Line> readLines(std::size_t numberOfLines) {
    std::vector<Line> lines;
    lines.reserve(numberOfLines);

    Timer t("Time to read lines");

    char* buffer = new char[numberOfLines * (maxLength + 1)];

    std::size_t length =
        std::fread(buffer, 1, numberOfLines * (maxLength + 1), stdin);

    std::size_t currentLineBegin = 0;

    for (std::size_t c_ = 0; c_ < length; ++c_) {
        if (buffer[c_] != '\n') {
            continue;
        }

        lines.push_back({});
        auto& line = lines.back();

        std::memcpy(line.data(), buffer + currentLineBegin,
                    c_ - currentLineBegin + 1);
        currentLineBegin = c_ + 1;
    }

    return lines;
}

int main() {
    Timer t("Total time spent");
    std::size_t numberOfLines = 0;

    std::array<char, 16> numberOfLinesAsString;
    std::cin.getline(numberOfLinesAsString.data(), 16);

    numberOfLines = std::atoi(numberOfLinesAsString.data());

    auto lines = readLines(numberOfLines);

    auto output = sortAndPrintLines(lines);
    {
        Timer t("Time to write results");
        std::fwrite(output.first, 1, output.second, stdout);
    }
}

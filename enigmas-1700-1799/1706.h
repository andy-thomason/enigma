
#include <iostream>
#include <bitset>
#include <cstdint>
#include <cassert>
#include <array>

// http://www.newscientist.com/article/mg21528731.600-enigma-number-1706.html#.VLwo9UesVtU

// 11 July 2012 by Adrian Somerfield
//
// In 1951 the Festival of Britain was held, with three main
// features at the exhibition site - the Dome of Discovery,
// the Skylon and the Royal Festival Hall.
//
// This inspired me to write down three positive whole numbers;
// altogether they use nine digits, with no digit repeated.
// One of the numbers is a perfect square and the other two
// are primes. They add up to 1951.

// What, in increasing order, are my three numbers?

class enigma1706 {
  int popcount(int x) {
    x = (x & 0x5555) + ((x>>1) & 0x5555);
    x = (x & 0x3333) + ((x>>2) & 0x3333);
    x = (x & 0x0f0f) + ((x>>4) & 0x0f0f);
    x = (x & 0xff) + ((x>>8) & 0xff);
    return x;
  }
public:
  enigma1706() {
    long long start = __rdtsc();
    std::bitset<1952> squares;
    std::array<char, 1952> num_digits;
    std::array<short, 1952> digits;

    for (int i = 0; i != 1952; ++i ) {
      num_digits[i] = i < 10 ? 1 : i < 100 ? 2 : i < 1000 ? 3 : 4;
      short result = 1 << (i % 10);
      if (i >= 10) result |= 1 << (i/10 % 10);
      if (i >= 100) result |= 1 << (i/100 % 10);
      if (i >= 1000) result |= 1 << 1;
      digits[i] = result;
    }

    // sieve for primes
    std::bitset<1952> primes_or_squares;
    primes_or_squares.set();
    for (int i = 2; i != 45; ++i) {
      if (primes_or_squares[i]) {
        for (int j = i*2; j < 1952; j += i) {
          primes_or_squares.reset(j);
        }
      }
    }

    for (int i = 0; i != 1952; ++i ) {
      if (popcount(digits[i]) != num_digits[i]) {
        primes_or_squares.reset(i);
      }
    }

    squares.reset();
    for (int i = 0; i != 45; ++i) {
      squares.set(i*i);
    }

    primes_or_squares |= squares;

    int num_solutions = 0;
    int last_i, last_j, last_k;

    for (int i = 0; i != 1951; ++i) {
      if (primes_or_squares[i]) {
        for (int j = i; j <= (1951-i)/2; ++j) {
          if (primes_or_squares[j]) {
            int k = 1951 - i - j;
            if (primes_or_squares[k]) {
              if (num_digits[i] + num_digits[j] + num_digits[k] == 9) {
                if (popcount(digits[i] | digits[j] | digits[k]) == 9) {
                  if ((squares[i] != 0) + (squares[j] != 0) + (squares[k] != 0) == 1) {
                    last_i = i; last_j = j; last_k = k;
                    num_solutions++;
                  }
                }
              }
            }
          }
        }
      }
    }

    if (num_solutions == 1) {
      long long end = __rdtsc();
      printf("enigma 1706 solved in %lld cycles\n", (long long)(end-start));
      printf("%d %d %d\n", last_i, last_j, last_k);
    }
  }
};




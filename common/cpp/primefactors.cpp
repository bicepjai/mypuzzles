#include <map>
#include <set>
#include <list>
#include <cmath>
#include <ctime>
#include <deque>
#include <queue>
#include <stack>
#include <bitset>
#include <cstdio>
#include <vector>
#include <cstdlib>
#include <numeric>
#include <sstream>
#include <iostream>
#include <string.h>
#include <algorithm>
#include <stdio.h>
#include <assert.h>
#include <utility> 
#include <climits>
#include <random>

using namespace std;

typedef unsigned long long ;

/// Modular multiplication
/// @param a The first factor, a < m
/// @param a The second factor, b < m
/// @param m The modulus
/// @return The reduced product, a b mod m < m
uint64 mulmod(uint64 a, uint64 b, uint64 m)
{
   // Perform 128 multiplication and division
   uint64 q; // q = ⌊a b / m⌋
   uint64 r; // r = a b mod m
   asm(
      "mulq %3;"
      "divq %4;"
      : "=a"(q), "=d"(r)
      : "a"(a), "rm"(b), "rm"(m));
   return r;
}

uint64 mulmoda(uint64 a, uint64 b, uint64 c){
    uint64 x = 0,y=a%c;
    while(b > 0){
        if(b%2 == 1) x = (x+y)%c;
        y = (y*2)%c;
        b /= 2;
    }
    return x%c;
}

/// Modular exponentiation
/// @param b The base, b < m
/// @param e The exponent
/// @param m The modulus
/// @returns The reduced power of a, a^b mod m
uint64 powmod(uint64 b, uint64 e, uint64 m)
{
   uint64 r = 1;
   for(; e; e >>= 1) {
      if(e & 1)
         r = mulmod(r, b, m);
      b = mulmod(b, b, m);
   }
   return r;
}


// Source: http://en.wikipedia.org/wiki/Binary_GCD_algorithm
uint64 gcd(uint64 u, uint64 v)
{
   if (u == 0 || v == 0)
      return u | v;
   // Remove common twos in u and v
   int shift;
   for (shift = 0; ((u | v) & 1) == 0; ++shift) {
      u >>= 1;
      v >>= 1;
   }
   // Remove twos from u
   while ((u & 1) == 0)
      u >>= 1;
   do {
      // Remove twos in v
      while ((v & 1) == 0)
         v >>= 1;
      // Now u and v are both odd, so diff(u, v) is even.
      // Let u = min(u, v), v = diff(u, v)/2.
      if (u < v) {
         v -= u;
      } else {
         uint64 diff = u - v;
         u = v;
         v = diff;
      }
      v >>= 1;
   } while (v != 0);
 
   return u << shift;
}

/// Miller-Rabin probabilistic primality testing
/// @param n The number to test for  primality
/// @param k The witness for primality
/// @returns True iff when n is a k-stong pseudoprime
bool MillerRabin(uint64 n, uint64 k)
{
   if(n==2) return true;
   // Factor n-1 as d*2^s
   uint64 s = 0;
   uint64 d = n - 1;
   for(; !(d & 1); s++)
      d >>= 1;
 
   // Verify x = k^(d 2^i) mod n != 1
   uint64 x = powmod(k % n, d, n);
   if(x == 1 || x == n-1)
      return true;
   while(s-- > 1) {
      // x = x^2 mod n
      x = mulmod(x, x, n);
      if(x == 1)
         return false;
      if(x == n-1)
         return true;
   }
   return false;
}

bool is_prime(uint64 n)
{
   return (n>73&&!(n%2&&n%3&&n%5&&n%7&&
   n%11&&n%13&&n%17&&n%19&&n%23&&n%29&&
   n%31&&n%37&&n%41&&n%43&&n%47&&n%53&&
   n%59&&n%61&&n%67&&n%71&&n%73))?false:
   MillerRabin(n, 2)&&MillerRabin(n, 7)
   &&MillerRabin(n, 61);
}

void brents_factor(uint64 n, vector<uint64>& f)
{
   if(is_prime(n)) {
      f.push_back(n);
      return;
   }
   uint64 a = rand() % n;
   uint64 x = rand() % n;
   uint64 y = 1;
   for(int i = 0; i*i / 2 < n; i++)
   {
      // x = x² + a mod n
      x = mulmod(x, x, n);
      x += a;
      if(x < a)
         x += (LLONG_MAX - n) + 1;
      x %= n;
      uint64 g = gcd(n, y - x);
      if(g != 1 && g != n) {
         n /= g;
         brents_factor(g, f);
         if(n != g)
            brents_factor(n, f);
         return;
      }
      if((i & (i-1)) == 0)
         y = x;
   }
   // Found no factors, yet n is not a prime, retry
   brents_factor(n, f);
}


int main()
{
   vector<uint64> factors;
   //cout << "==========" << endl;
   uint64 n = 18446744073709551424U;
   //cout << is_prime(n);
   brents_factor(n, factors);
   for(auto a: factors) {
      cout << a << " " << endl;
   }

   return 0;
}

/*
clear && cd /cygdrive/c/Users/jdurairaj/Documents/puzzles/common && rm -rf *.exe && rm -rf *.stackdump && g++ -g -std=c++11 primefactors.cpp -o primefactors && time ./primefactors.exe
*/


#include <map>
#include <unordered_map>
#include <set>
#include <list>
#include <stack>
#include <cmath>
#include <ctime>
#include <deque>
#include <queue>
#include <stack>
#include <bitset>
#include <cstdio>
#include <cstdlib>
#include <numeric>
#include <sstream>
#include <iostream>
#include <string>
#include <climits>
#include <algorithm>
#include <vector>
#include <utility>

#include <stdio.h>
#include <string.h>
//#include <cstring>
#include <assert.h>
#include <bitset>

using namespace std;
typedef unsigned long ul;


long great_xor_naive(long x)
{
   long n = 0;
   for (long i = 0; i < x; i++) {
      if ( (i ^ x) > x) {
         n++;
      }
   }
   return n;
}

long great_xor_best(long x)
{
   if (x <= 1) {
      return 0;
   }

   long n = 0;
   long lsb_mask = 0x0000000000000001;
   long temp_x = x;
   int bit_index = 0;

   // use test() to see the pattern where all the bit position that has 0
   // all the following bit combinations satisfy the condition
   // for answer just sum values of all 2 power bit_indices that has 0

   while (temp_x > 0) {
      if ( (temp_x & lsb_mask) == 0) {
         n += pow(2, bit_index);
      }
      temp_x >>= 1;
      bit_index++;
   }
   return n;
}

void test()
{
   long n = 0;
   long x = 4567;
   for (long i = x; i > 0; i--) {
      if ( (i ^ x) > x) {
         cout << i << " " << std::bitset<16>(x) << endl;
         n++;
      }
   }
   cout << n << endl;
   cout << great_xor_best(x) << endl;
}

void stress_test()
{
   while (true) {
      int q = rand() % 10;
      for (int i = 0; i < q; ++i) {
         long x = rand() % 100;
         long res1 = great_xor_naive(x);
         long res2 = great_xor_best(x);
         if (res1 != res2) {
            cerr << "Wrong answer: " << res1 << ' ' << res2 << "\n";
            break;
         }
         else {
            cerr << "OK\n";
         }

      }
   }
}

int main() {
   int q;
   cin >> q;
   for (int a0 = 0; a0 < q; a0++) {
      long x;
      cin >> x;
      // your code goes here
      cout << great_xor_best(x) << endl;
   }
   return 0;
   // test();
   // stress_test();
}

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
#include <iomanip>
#include <string.h>
#include <algorithm>
#include <stdio.h>
#include <assert.h>
#include <utility> 

using namespace std;
typedef unsigned long long ull;
typedef unsigned long ul;
typedef unsigned int ui;
typedef long double ld;

ui msbIndex(unsigned long x) {
   ui n=0;
   while(x > 0) {
      x = x>>1;
      n++;
   }
   return n;
}


int main(void) {

    string query;
    ui T,t;
    ull X, K, sm, one=1;
    ld ans,f,s;
    ui power;
    cin >> T;

   for(t=0; t<T; t++) {
      cin >> X;
      cin >> K;     
      power = msbIndex(K);
      //cout << K <<"===========" << power << endl;
      // and = f + sm*s
      // f = X / (2 to the powerof2 nearest to K or msb1 of k-counting from 1 as lsb)
      // sm is the multile of second term which is difference between k and same as explained before
      f = (ld) X / pow(2,power);
      sm = (one << power-1)-1 & K; // calculatinf difference using bitwise operation
      s = (ld) X*sm / pow(2,power-1);
      ans =  f + s;
      //cout << "f:" << f << " sm:" << sm << " s:" << s << endl;
      cout << std::fixed << std::setprecision(16) << ans << endl;
   }

   return 0;
}

/*
clear && cd /cygdrive/c/Users/jdurairaj/Documents/puzzles/codechef/nov14/ && rm -rf *.exe && rm -rf *.stackdump && g++ chefseg.cpp -o chefseg && ./chefseg.exe < input.in
*/
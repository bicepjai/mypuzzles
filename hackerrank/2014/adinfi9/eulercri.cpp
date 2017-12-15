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
#include <algorithm>
#include <vector>
#include <stdio.h>
//#include <assert.h>
#include <utility> 
using namespace std;

#define itr 	 	iterator
#define citr 		const_iterator

#define pib 		std::pair <int, bool>
#define pii 		std::pair <int, int>
#define piv 		std::pair <int, vector<int>>

#define umapiv 		std::unordered_map <int, vector<int>>
#define umapib 		std::unordered_map <int, bool>
#define vi 	 		std::vector <int>
#define vvi 		std::vector <vector<int>>

typedef long double ld;
typedef long long ll;
typedef unsigned long long ull;

ull modpow(ull base, ull exp, ull modulus) {
  base %= modulus;
  ull result = 1;
  while (exp > 0) {
    if (exp & 1) result = (result * base) % modulus;
    base = (base * base) % modulus;
    exp >>= 1;
  }
  return result;
}

int main(void) {
	ios_base::sync_with_stdio( false );
	int t, T;
	ull A, M;
	cin >> T;
	for(t=0; t<T; t++) {
		cin >> A;
		cin >> M;
		if(modpow(A,(M-1)/2,M) == 1)
			cout << "YES" << endl;
		else
			cout << "NO" << endl;
	}
}

/*
clear && pwd && ll && cd ~/Puzzles/hackerrank/2014/adinfi9/ && rm -rf *.dSYM *.log && g++ -g -std=c++11 eulercri.cpp -o eulercri && time ./eulercri < input.in
*/
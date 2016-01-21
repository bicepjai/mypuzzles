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

int main(void) {
	ios_base::sync_with_stdio( false );
	int t, T;
	int S, A;
	cin >> T;
	for(t=0; t<T; t++) {
		cin >> S;
		A = ((S*2) + (S*2/42)*2) %(1000000007);
		cout << A << endl;
	}
}

/*
clear && pwd && ll && cd ~/Puzzles/hackerrank/2014/adinfi9/ && rm -rf *.dSYM *.log && g++ -g -std=c++11 wetshark42.cpp -o wetshark42 && time ./wetshark42 < input.in
*/
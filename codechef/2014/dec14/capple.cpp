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
	int t, T, n, N, apples;
	set<int> uniqueTrees;
	cin >> T;
	for(t=0; t<T; t++) {
		cin >> N;
		uniqueTrees.clear();
		for(n=0; n<N; n++) {
			cin >> apples;
			uniqueTrees.insert(apples);
		}
		cout << uniqueTrees.size() << endl;
	}
}

/*
clear && pwd && ll && cd ~/Puzzles/codechef/2014/dec14/ && rm -rf *.dSYM *.log && g++ -g -std=c++11 capple.cpp -o capple && time ./capple < input.in
*/
#include <algorithm>
#include <stack>
#include <set>
#include <map>
#include <unordered_map>
#include <list>
#include <vector>
#include <deque>

#include <queue>
#include <stack>

#include <bitset>
#include <numeric>
#include <string>

#include <sstream>
#include <iostream>

#include <cmath>
#include <ctime>
#include <utility> 

#include <climits>
#include <cstdio>
#include <cstdlib>
#include <cstring>

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

using namespace std;

#define itr 	 	iterator
#define citr 		const_iterator

#define pib 		std::pair <int, bool>
#define pii 		std::pair <int, int>
#define piv 		std::pair <int, vector<int>>

#define umapiv 		std::unordered_map <int, vector<int>>
#define umapib 		std::unordered_map <int, bool>
#define vi 	 		std::vector <int>
#define vpii		std::vector <pii>
#define vull 		std::vector <ull>
#define vvi 		std::vector <vector<int>>

typedef long double ld;
typedef long long ll;
typedef unsigned long long ull;

#define MAX_SIZE 100000

int main(void) {
	ios_base::sync_with_stdio( false );
	ll t, T, M, N;
	cin >> T;
	
	for(t=0; t<T; t++) {
		cin << M;
		cin << N;
	}
	cout << N+M-1 << endl;

	return 0;
}

/*
clear && pwd && ll && cd ~/Puzzles/codechef/2015/cook54 && rm -rf *.dSYM *.log && g++ -g -std=c++1y anuthm.cpp -o anuthm && ./anuthm < input.in
*/

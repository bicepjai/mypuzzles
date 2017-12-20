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

bool wayToSort(ll i, ll j) { return i > j; }

int main(void) {
	ios_base::sync_with_stdio( false );
	ll t,T;
	int length;
	string str;
	bool ans=false;
	
	ll occurrences[256];
	memset(occurrences, 0, sizeof(occurrences));

	cin >> T;
	for(t=0; t<T; t++) {
		cin >> str;
		length = str.size();
		memset(occurrences, 0, sizeof(occurrences));
		ans=false;

		for (char c : str) {
			occurrences[(int)c]++;
		}

		sort(begin(occurrences), end(occurrences), wayToSort);
		
		for (int i=0; i<256;i++) {
			if(occurrences[i] == length - occurrences[i]){
				ans = true;
				break;
			}
			if(occurrences[i] == 0) break;
		}


		if(ans) {
			cout << "YES" << endl;
		} else {
			cout << "NO" << endl;
		}
	}
	

	return 0;
}

/*
clear && pwd && ll && cd ~/Puzzles/codechef/2015/ltime20 && rm -rf *.dSYM *.log && g++ -g -std=c++1y lch15jab.cpp -o lch15jab && ./lch15jab < input.in
*/

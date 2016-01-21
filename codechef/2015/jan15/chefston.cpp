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
#include <stdio.h>
#include <assert.h>
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
#define vull 		std::vector <ull>
#define vvi 		std::vector <vector<int>>

typedef long double ld;
typedef long long ll;
typedef unsigned long long ull;

#define MAX_STONES 100000

int main(void) {
	ios_base::sync_with_stdio( false );
	ll T,N,K;
	ll t,n,ans;
	ll A[MAX_STONES], B[MAX_STONES];

	cin >> T;

	for(t=0; t<T; t++) {
		cin >> N;
		cin >> K;
		ans = 0;
		for(n=0; n<N; n++) {
			cin >> A[n];
		}
		for(n=0; n<N; n++) {
			cin >> B[n];
			if( ((K / A[n]) * B[n]) > ans)
				ans = ((K / A[n]) * B[n]);
		}

		cout << ans << endl;
	}
}

/*
clear && pwd && ll && cd ~/Puzzles/codechef/2015/jan15 && rm -rf *.dSYM *.log && g++ -g -std=c++11 chefston.cpp -o chefston && time ./chefston < input.in
*/



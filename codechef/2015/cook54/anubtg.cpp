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
#define pb 	 		push_back

#define pib 		std::pair <int, bool>
#define pii 		std::pair <int, int>
#define piv 		std::pair <int, vector<int>>

#define umapiv 		std::unordered_map <int, vector<int>>
#define umapib 		std::unordered_map <int, bool>
#define vi 	 		std::vector <int>
#define vpii		std::vector <pii>
#define vull 		std::vector <ull>
#define vll 		std::vector <ll>
#define vvi 		std::vector <vector<int>>

typedef long double ld;
typedef long long ll;
typedef unsigned long long ull;

#define MAX_SIZE 100000

struct sortOrder {
  bool operator() (ll i,ll j) { return (i>j);}
} sortObject;

int main(void) {
	ios_base::sync_with_stdio( false );
	ll t, T, n, N, p, ans;
	cin >> T;

	vll prices;
	for(t=0; t<T; t++) {
		cin >> N;
		prices = vll();
		ans = 0;
		for(n=0; n<N; n++) {
			cin >> p;
			prices.pb(p);
		}
		std::sort (prices.begin(), prices.end(), sortObject);
		for(n=0;n<N;n++) {
			if(n%4 < 2)
				ans += prices[n];
		}
		cout << ans << endl;
	}

	return 0;
}

/*
clear && pwd && ll && cd ~/Puzzles/codechef/2015/cook54 && rm -rf *.dSYM *.log && g++ -g -std=c++1y anubtg.cpp -o anubtg &&  ./anubtg < input.in
*/

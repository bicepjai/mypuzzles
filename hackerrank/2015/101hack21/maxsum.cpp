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

#define MAX_SIZE 100010

int main(void) {
	ios_base::sync_with_stdio( false );
	ull t,T,n,N,M,ans,i,j;
	cin >> T;

	// ull** DP= new ull*[MAX_SIZE];

	ull DP[MAX_SIZE];
	ull A[MAX_SIZE];

	for(t=0; t<T; t++) {
		cin >> N;
		cin >> M;
		ans = 0;
		memset(DP, 0, sizeof(DP[0]) * MAX_SIZE);
		memset(A, 0, sizeof(A[0]) * MAX_SIZE);

		for(n=0; n<N; n++) {
			cin >> A[n];
			DP[n] = A[n];
			if(DP[n]%M > ans)
				ans = DP[n]%M;
		}
		
		// for(j=0;j<N;j++)
		// 	cout << DP[j] << " " ;
		// cout << endl;

		for(n=1; n<N-1; n++) {
			for(i=0; i<N; i++) {
				// cout << DP[i] << " + " << A[i];
				DP[i] = DP[i] + A[i+n];
				// cout << " = " << DP[i] << " (" << DP[i]%M << ") " << ans << endl;
				if(DP[i]%M > ans)
					ans = DP[i]%M;
			}
			// cout << endl;
		}
		cout << ans << endl;
	}

	return 0;
}

/*
clear && pwd && ll && cd ~/Puzzles/hackerrank/2015/101hack21 && rm -rf *.dSYM *.log && g++ -g -std=c++1y maxsum.cpp -o maxsum && ./maxsum < input.in
*/

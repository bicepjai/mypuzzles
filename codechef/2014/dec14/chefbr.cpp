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

int main(void) {
	ios_base::sync_with_stdio( false );
	long long N, X;
	long long brackets[101];
	long long dp[101][101];
	int n,i,j,k,seqLen;
	long long mod = 1000000007;

	cin >> N;
	for(n=0; n<N; n++) {
		cin >> X;
		brackets[n] = X;
	}

	for(seqLen=0;seqLen<N;seqLen++) {
		for(i=0;i<N;i++) {
			j = seqLen + i;
			if (j > N) continue;
			if( i == j) {
				dp[i][j] = 0;
				continue;
			}
			dp[i][j] = dp[i][j-1];
			for(k=i;k<j;k++) {
				if( (brackets[j] > 0) && (brackets[k] == -brackets[j])) {
					if(k == i)
						dp[i][j] = (dp[i][j]  + 1 + dp[k+1][j-1]) % mod;
					else
						dp[i][j] = ( dp[i][j] + ((1 + dp[k+1][j-1]) * (1 + dp[i][k-1])) % mod ) % mod ;
				}
			}
		}
	}

	cout << dp[0][N-1] +1;
	return 0;
}

/*
clear && pwd && ll && cd ~/Puzzles/codechef/2014/dec14/ && rm -rf *.dSYM *.log && g++ -g -std=c++11 chefbr.cpp -o chefbr && time ./chefbr < input.in
*/

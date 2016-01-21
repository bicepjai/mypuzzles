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

ll mulmoda(ll a, ll b, ll c){
    ll x = 0,y=a%c;
    while(b > 0){
        if(b%2 == 1) x = (x+y)%c;
        y = (y*2)%c;
        b /= 2;
    }
    return x%c;
}

ll powmod(ll b, ll e, ll m)
{
   ll r = 1;
   for(; e; e >>= 1) {
      if(e & 1)
         r = mulmoda(r, b, m);
      b = mulmoda(b, b, m);
   }
   return r;
}

#define MOD  1000000007
#define NMAX 10000001
int main(void) {
	ios_base::sync_with_stdio( false );
	ll T,N,M,L,R;
	ll t,d,k,S,ans,prev,quotient,Ad;

	// Number of possible arrays of size N whose GCD is divisible by D (index)
	// ll A[NMAX];
	ll* A = new ll[NMAX];
	// Number of possible arrays of size N whose GCD is D (index)
	// ll B[NMAX];
	ll* B = new ll[NMAX];

	cin >> T;
	for(t=0; t<T; t++) {
		cin >> N;
		cin >> M;
		cin >> L;
		cin >> R;
		ans = 0;

		A[0] = 0;
		B[0] = 0;
		prev = ULLONG_MAX;
		for(d=M;d>0;d--){
			quotient = M/d;
			if(quotient != prev){
				Ad = powmod(M/d,N,MOD);
				prev = quotient;
			}
			A[d] = Ad;
			S=0;
			k=2*d;
			while(k <= M) {
				S += B[k];
				if(S >= MOD) S %= MOD;
				k += d;
			}
			B[d]=A[d] - S;
			if(B[d] < 0) B[d] += MOD;
			if(B[d] >= MOD) B[d] %= MOD;
			if(d >= L && d <= R){
				ans += B[d];
				if(ans >= MOD) ans %= MOD;
			}
		}

		cout << ans << endl;
	}
}

/*
clear && pwd && ll && cd ~/Puzzles/codechef/2014/dec14/ && rm -rf *.dSYM *.log && g++ -g -std=c++11 seagcd.cpp -o seagcd && time ./seagcd < input.in
*/
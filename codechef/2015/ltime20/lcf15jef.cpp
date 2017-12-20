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
ull mulmod(ull a, ull b, ull c){
    ull x = 0,y=a%c;
    while(b > 0){
        if(b%2 == 1) x = (x+y)%c;
        y = (y*2)%c;
        b /= 2;
    }
    return x%c;
}

ull powmod(ull b, ull e, ull m)
{
   ull r = 1;
   for(; e; e >>= 1) {
      if(e & 1)
         r = mulmod(r, b, m);
      b = mulmod(b, b, m);
   }
   return r;
}

int main(void) {
	ios_base::sync_with_stdio( false );
	ull t, T, ans, B, BE, BE1, M;
	string S;
	int i, j, k, length;

	cin >> T;
	
	for(t=0; t<T; t++) {
		cin >> M;
		cin >> S;
		// cout << S << endl;;
		length = S.size();
		ans = 1;
		for(i=0; i<length; i++ ) {
			j=i;
			B = 0;
			while(S[j] >= '0' && S[j] <= '9') {
				B = mulmod(B,10,M);
				B += ull(S[j] - '0');
				B = B % M;
				// cout << "base:" << ull(S[j] - '0')<< " => " << B << endl;				
				j++;
			}
			
			// cout << "transition:" << i << " " << j << " " << S[j] << endl;
			j+=2; //**

			BE = 1;
			while(S[j] >= '0' && S[j] <= '9') {
				BE1 = powmod(BE,10,M);
				BE  = mulmod(powmod(B,ull(S[j] - '0'),M),BE1,M);
				

				// BE1 = 1;
				// for (int k=1; k<=10; k++)
				// 	BE1 = mulmod(BE, BE1, M);
				// BE = BE1;
				// for (int k=1; k <= S[j]-'0'; k++)
				// 	BE = mulmod(BE, B, M);

				// cout << "exp:" << ull(S[j] - '0') <<"= "<< BE1 <<" "<< BE << endl;				
				j++;
			}
			ans = mulmod(BE,ans,M);
			//*
			i=j;
		}
		cout << ans << endl;
	}
	
	return 0;
}

/*
clear && pwd && ll && cd ~/Puzzles/codechef/2015/ltime20 && rm -rf *.dSYM *.log && g++ -g -std=c++1y lcf15jef.cpp -o lcf15jef && ./lcf15jef < input.in
*/

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
#include <utility> 

#include <stdio.h>
#include <string.h>
//#include <cstring>
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
#define vull 		std::vector <ull>
#define vvi 		std::vector <vector<int>>

typedef long double ld;
typedef long long ll;
typedef unsigned long long ull;

#define MAX_STONES 100000

ll funcgcd(ll u, ll v)
{
   if (u == 0 || v == 0)
      return u | v;
   // Remove common twos in u and v
   ll shift;
   for (shift = 0; ((u | v) & 1) == 0; ++shift) {
      u >>= 1;
      v >>= 1;
   }
   // Remove twos from u
   while ((u & 1) == 0)
      u >>= 1;
   do {
      // Remove twos in v
      while ((v & 1) == 0)
         v >>= 1;
      // Now u and v are both odd, so diff(u, v) is even.
      // Let u = min(u, v), v = diff(u, v)/2.
      if (u < v) {
         v -= u;
      } else {
         ll diff = u - v;
         u = v;
         v = diff;
      }
      v >>= 1;
   } while (v != 0);
 
   return u << shift;
}

class SegmentTree
{
    ll *STree, *Lazy, size;

    public:
    SegmentTree(ll N) {
        ll x = (ll)(ceil(log2(N)))+1;
        size = 2*(ll)pow(2,x);
        STree = new ll[size];
        Lazy = new ll[size];
        memset(STree,-1,size * sizeof(ll));
        memset(Lazy,0,size * sizeof(ll));
    }

    void buildST(ll node, ll s, ll e, ll *array) {
    	if (s > e) return;

        if (s==e){
            STree[node] = array[s];
        	// cout << node << " => " << array[s] << " ->"   << STree[node] << endl;
            return;
        }
        ll m = (s+e)/2;
        buildST(2*node,s,m,array);
        buildST(2*node+1,1+m,e,array);

        STree[node] = funcgcd(STree[2*node], STree[2*node+1]);

        // cout << node << " => " << STree[2*node]   << "(" << 2*node << ")," 
        // 					   << STree[2*node+1] << "(" << 2*node+1 << ")"
        // 			 << " ->"   << STree[node] << endl;
    }

	void printST() {
		for(int n=0; n<10; n++) {
			cout << STree[n] << " " << endl;
		}		
	}

    /*
	void updateST(ll node, ll s, ll e, ll i, ll j, ll value) {
		if(Lazy[node] != 0) { // This node needs to be updated
			STree[node] += Lazy[node]; // Update it
			 
			if(s != e) {
			Lazy[node*2] += Lazy[node]; // Mark child as Lazy
			Lazy[node*2+1] += Lazy[node]; // Mark child as Lazy
			}
			 
			Lazy[node] = 0; // Reset it
		}
		if(s > e || s > j || e < i) // Current segment is not within range [i, j]
			return;
		if(s >= i && e <= j) { // Segment is fully within range
			STree[node] += value;
			 
			if(s != e) { // Not leaf node
				Lazy[node*2] += value;
				Lazy[node*2+1] += value;
			}
			return;
		}
		 
		updateST(node*2, s, (s+e)/2, i, j, value); // Updating left child
		updateST(1+node*2, 1+(s+e)/2, e, i, j, value); // Updating right child
		 
		STree[node] = max(STree[node*2], STree[node*2+1]); // Updating root with max value
	}
	*/

	ll queryST(ll s, ll e, ll i, ll j) {
		return _queryST(1, s, e, i, j);
	}

	private:
	ll _queryST(ll node, ll s, ll e, ll i, ll j) {
		if(s > e || s > j || e < i) return LLONG_MIN; // Out of range
		 
		// if(Lazy[node] != 0) { // This node needs to be updated
		// 	STree[node] += Lazy[node]; // Update it
			 
		// 	if(s != e) {
		// 		Lazy[node*2] += Lazy[node]; // Mark child as Lazy
		// 		Lazy[node*2+1] += Lazy[node]; // Mark child as Lazy
		// 	}
			 
		// 	Lazy[node] = 0; // Reset it
		// }
		 
		if(s >= i && e <= j) // Current segment is totally within range [i, j]
			return STree[node];
		ll m = (s+e)/2;
		ll q1 = _queryST(node*2, s, m, i, j); // Query left child
		ll q2 = _queryST(1+node*2, 1+m, e, i, j); // Query right child

		if (q1==LLONG_MIN)
            return q2;
        if (q2==LLONG_MIN)
            return q1;

		ll res = funcgcd(q1, q2); // Return final result
		return res; 
	} 

};


ll Is[MAX_STONES];
SegmentTree gcdST(MAX_STONES);

ll gcdNotQuery( ll L, ll R, ll N) {

	ll si1, ei1, si2, ei2, ans, ans1, ans2;

	if(L==R) {
		if(L>0) {
			si1 = 0;
			ei1 = L-1;
			si2 = R+1;
			ei2 = N-1;
		} else {
			si1 = -1;
			ei1 = -1;
			si2 = L+1; // or R+1
			ei2 = N-1;
		}
	} else {
		if(L==0) {
			si1 = -1;
			ei1 = -1;
			si2 = L+1; // or R+1
			ei2 = N-1;			
		} else {
			si1 = 0;
			ei1 = L-1;
			if(R==N-1) {
				si2 = ei2 = N;
			} else {
				si2 = R+1;
				ei2 = N-1;	
			}
		}
	}

	// cout << L<<"-"<< R<<"-"<< N<< " => "<< si1 << ":" << ei1 << " " << si2 << ":" << ei2 << endl;
	// cout << "*********************" << endl;
	if(si1 != -1) {
	 	// gcd of 1st section
	 	ans = ans1 = gcdST.queryST(0, N-1, si1, ei1);
		// cout << "si1:" << si1 << " ei1:" << ei1 << " ans:" << ans1 << endl;
		// cout << "================" << endl;
	}
	if(si2 != N){
		ans = ans2 = gcdST.queryST(0, N-1, si2, ei2);
		// cout << "si2:" << si2 << " ei2:" << ei2 << " ans:" << ans2 << endl;
		if(si1 != -1) {
			ans = funcgcd(ans2, ans1);
		}
	}

	return ans;
}

int main(void) {
	ios_base::sync_with_stdio( false );
	ll T,N,Q,L,R;
	ll t,n,gcd,ans;

	cin >> T;

	for(t=0; t<T; t++) {
		cin >> N;
		cin >> Q;
		ans = 0;

		for(n=0; n<N; n++) {
			cin >> Is[n];
		}
		gcdST.buildST(1,0,N-1,Is);
		// gcdST.printST();
		// cout << gcdST.queryST(0, N-1, 1, 2) << endl;
		for(n=0; n<Q; n++) {
			cin >> L;
			cin >> R;
			cout << gcdNotQuery(L-1,R-1,N) << endl;
		}

	}
}

/*
clear && pwd && ll && cd ~/Puzzles/codechef/2015/jan15 && rm -rf *.dSYM *.log && g++ -g -std=c++1y gcdq.cpp -o gcdq && time ./gcdq < input.in
*/



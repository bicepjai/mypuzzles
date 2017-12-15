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

#define MAX_STRLEN 100000

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
    void buildST(ll s, ll e, ll *array) {
        _buildST(1, s, e, array);
    }

    void printST() {
        for(int n=0; n<10; n++) {
            cout << STree[n] << " ";
        } cout << endl;
    }

	void updateST(ll s, ll e, ll i, ll j, ll value) {
		return  _updateST(1, s, e, i, j, value);
	}
    
    void updateIndex(ll lo, ll hi, ll index, ll value) {
    	return _updateIndex(1, lo, hi, index, value);
    }

    ll queryST(ll s, ll e, ll i, ll j) {
    	return _queryST(1, s, e, i, j);
    }

    private:
    void _updateST(ll node, ll s, ll e, ll i, ll j, ll value) {
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
         
        _updateST(node*2, s, (s+e)/2, i, j, value); // Updating left child
        _updateST(1+node*2, 1+(s+e)/2, e, i, j, value); // Updating right child
         
        STree[node] = STree[node*2] + STree[node*2+1]; // Updating root with max value
    }
    
    private:
	void _updateIndex(ll node, ll lo, ll hi, ll index, ll value) {
		if (lo == hi) {
			STree[node] = value;
			return;
		}
		ll left = 2 * node, right = left + 1, mid = (lo + hi) / 2;
		if (index <= mid)
			_updateIndex(left, lo, mid, index, value);
		else
			_updateIndex(right, mid+1, hi, index, value);
		STree[node] = STree[left] + STree[right];
	}

    private:
    void _buildST(ll node, ll s, ll e, ll *array) {
        if (s > e) return;

        if (s==e){
            STree[node] = array[s];
            return;
        }
        ll m = (s+e)/2;
        _buildST(2*node,s,m,array);
        _buildST(2*node+1,1+m,e,array);

        STree[node] = STree[2*node] + STree[2*node+1];
    }

    private:
    ll _queryST(ll node, ll s, ll e, ll i, ll j) {
        if(s > e || s > j || e < i) return LLONG_MIN; // Out of range
         
        if(Lazy[node] != 0) { // This node needs to be updated
         STree[node] += Lazy[node]; // Update it
             
         if(s != e) {
             Lazy[node*2] += Lazy[node]; // Mark child as Lazy
             Lazy[node*2+1] += Lazy[node]; // Mark child as Lazy
         }
             
         Lazy[node] = 0; // Reset it
        }
         
        if(s >= i && e <= j) // Current segment is totally within range [i, j]
            return STree[node];
        ll m = (s+e)/2;
        ll q1 = _queryST(node*2, s, m, i, j); // Query left child
        ll q2 = _queryST(1+node*2, 1+m, e, i, j); // Query right child

        if (q1==LLONG_MIN)
            return q2;
        if (q2==LLONG_MIN)
            return q1;

        ll res = q1 + q2; // Return final result
        return res; 
    } 

};



int main(void) {
	ios_base::sync_with_stdio( false );
	ll n,N,m,M,q,XC,YD, divsum;
	ll i,j,ans;
	char c;
	string s;

	cin >> N;
	cin >> M;
	ll *array = new ll[N];
	SegmentTree stree(N);

	for(n=0; n<N; n++) {
		cin >> c;
		s.append(1,c);
		// // cout << c << endl;
		array[n] = (ll)(c-'0');
	}
	cout << s << endl;
	stree.buildST(0,N-1,array);
	stree.printST();

	for(m=0; m<M; m++) {
		cin >> q;
		cin >> XC;
		cin >> YD;
		if(q == 1) {
			c = (char)(((ll)'0')+YD);
			ll value = YD - (ll)(s[XC-1]-'0');
			stree.updateIndex(0,N-1, XC-1, value);
			s.replace(XC-1,1,1,c);
			cout << "replaced pos " << XC-1 << " with " << c << "--" << value <<endl;
			cout << s << endl;
			stree.printST();

		} else if (q == 2) {
			ans = 0;
			cout << XC-1 << " to " << YD-1 << "=>" << s.substr(XC-1,YD-XC+1) << endl;
			if(XC == YD) {
				if (((ll)(s[XC-1]-'0'))%3 == 0)
					ans++;
			} else {
				divsum = 0;
				for(i=XC-1; i<=YD-1; i++){
					for(j=1; j<=YD-i; j++){
						cout << i << ":" << j << " (" << s.substr(i,j) << ") ";
						if(j == 1) {
							divsum = (ll)(s[i]-'0');
							cout << " one digit ";
							if (divsum%3 == 0) {
								cout << "divisible by 3 ";
								ans++;
							} cout << endl;
						} else {
							ll swts, swte;
							swts = i;
							swte = i+j-1;
							cout << swts << ":" << swte << "=>";
							cout << stree.queryST(0,N-1,swts,swte);
							if(stree.queryST(0,N-1,swts,swte) % 3 == 0){
								cout << " divisible by 3 ";
								ans++;
							} cout << endl;
						}
					}
				}
			}
			cout << ans << endl;
			cout << "===========" << endl;
		}

	}

	return 0;
}

/*
clear && pwd && ll && cd ~/Puzzles/codechef/2015/jan15 && rm -rf *.dSYM *.log && g++ -g -std=c++1y qset.cpp -o qset && time ./qset < input.in
*/



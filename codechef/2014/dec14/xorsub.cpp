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
	ull t, T, n, N, Ni, K, xorindex, ans;
	vull Ns;
	int bitindex;
	cin >> T;
	for(t=0; t<T; t++) {

		cin >> N;
		cin >> K;
		Ns.clear();
		for(n=0; n<N; n++) {
			cin >> Ni;
			Ns.push_back(Ni);
		}
		sort(Ns.begin(), Ns.end(), greater<ull>());
		ans = 0;

		int r, row=0, col=63;
		int pivoti, swap;
		while(row<N && col >= 0) {
			pivoti = -1;
			// find the pivot = row that has one at this position
			for(r=row; r<N; r++) {
				if((Ns[r] >> col) & 1){
					//swap the row
					pivoti = r;
					break;
				}
			}
			if(pivoti == -1){
				col--;
				continue;
			}
			if(pivoti != row){
				swap = Ns[pivoti];
				Ns[pivoti] = Ns[row];
				Ns[row] = swap;
			}
			for(r=row+1; r<N; r++) {
				if((Ns[r] >> col) & 1){
					Ns[r] ^= Ns[row];
				}
			}
			row++;	
			col--;
		}
		ans = K;
		for(r=0; r<N; r++) {
			if((ans^Ns[r]) > ans)
				ans ^= Ns[r];
		}
		cout << ans << endl;
	}
}

/*
clear && pwd && ll && cd ~/Puzzles/codechef/2014/dec14/ && rm -rf *.dSYM *.log && g++ -g -std=c++11 xorsub.cpp -o xorsub && time ./xorsub < input.in
*/
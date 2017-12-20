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
#include <string.h>
#include <algorithm>
#include <vector>
#include <stdio.h>
#include <assert.h>
#include <utility> 
using namespace std;

#define itr 	 		iterator
#define citr 		const_iterator

#define pib 		std::pair <int, bool>
#define pii 		std::pair <int, int>
#define piv 		std::pair <int, vector<int>>

#define umapiv 		std::unordered_map <int, vector<int>>
#define umapib 		std::unordered_map <int, bool>
#define vi 	 		std::vector <int>
#define vvi 		std::vector <vector<int>>

typedef long double ld;
typedef long long ll;

// ds

#define MAXSIZE 1000009
typedef struct _line {
	int x1, y1;
	int x2, y2;
	ld pythDis1, pythDis2;
} Coordinates;

int main(void) {
	ios_base::sync_with_stdio( false );
	int n,N,m,M;
    int i,j;
    ll r,x1,y1,x2,y2;
    ld pythDis1, pythDis2;
    int nofQs;

    vi Radii;
    Coordinates line;

	cin >> N;
	for(n=0; n<N; n++) {
		cin >> r;
		Radii.push_back(r);
	}

	nofQs = 0;
	cin >> M;
	for(m=0; m<M; m++) {
		cin >> x1; cin >> y1;
		cin >> x2; cin >> y2;
		pythDis1 = (ld)sqrt(x1 * x1 + y1 * y1);
		pythDis2 = (ld)sqrt(x2 * x2 + y2 * y2);

		//cout << pythDis1 << " " << pythDis2 << endl;
		if(pythDis1 > pythDis2)
			for(n=0; n<N; n++) {
				if(Radii[n] < pythDis1 && Radii[n] > pythDis2 )
					nofQs++;
			}
		else if(pythDis1 < pythDis2)		
			for(n=0; n<N; n++) {
				if(Radii[n] > pythDis1 && Radii[n] < pythDis2 )
					nofQs++;
			}
	}
	cout << nofQs << endl;
}

/*
pwd && ll && cd ~/Puzzles/hackerrank/2014/decquora/ && rm -rf *.dSYM *.log && g++ -g -std=c++11 archery.cpp -o archery && time ./archery < input.in
*/

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

#define MAX_ORDERS 100000

typedef struct {
	int Ai;
	int Bi;
	int diff;
} AB;

bool sortFunction(AB ab1, AB ab2) {
    return (ab1.diff > ab2.diff);
}

int main(void) {
	ios_base::sync_with_stdio( false );
	ll N,X,Y;
	ll n,ans;
	ll A[MAX_ORDERS], B[MAX_ORDERS];
	vector<AB> vAB;

	cin >> N;
	cin >> X;
	cin >> Y;
	for(n=0; n<N; n++) {
		cin >> A[n];
	}
	for(n=0; n<N; n++) {
		cin >> B[n];
		AB ab;
		ab.Ai = A[n];
		ab.Bi = B[n];
		ab.diff = A[n] - B[n];
		vAB.push_back(ab);
	}
	std::sort (vAB.begin(), vAB.end(), sortFunction);

	vector<AB>::iterator iter;
	AB ba;
	ll cntA = 0;

	for(iter=vAB.begin(); iter!=vAB.end();++iter){
    	ba = *iter;
    	if(ba.diff >= 0 && cntA < X)
    		ans += ba.Ai;
    	else
    		ans += ba.Bi;
    	cntA++;
    	if(cntA >= N) break;
    }

	cout << ans << endl;
}

/*
clear && pwd && ll && cd ~/Puzzles/codechef/2014/ltime19/ && rm -rf *.dSYM *.log && g++ -g -std=c++11 tadelive.cpp -o tadelive && time ./tadelive < input.in
*/
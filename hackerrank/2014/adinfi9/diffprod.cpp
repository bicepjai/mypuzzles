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
//#include <assert.h>
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
#define vvi 		std::vector <vector<int>>

typedef long double ld;
typedef long long ll;
typedef unsigned long long ull;

int main(void) {
	ios_base::sync_with_stdio( false );
	int t, T;
	int D, P, b2m4ac;
	cin >> T;
	for(t=0; t<T; t++) {
		cin >> D;
		cin >> P;
		if(D == 0) {
			if(P == 0)
				cout << "0" << endl;
			else if(P > 0)
				cout << "2" << endl;
			else
				cout << "0" << endl;
		} else if(D > 0){
			if(P == 0)
				cout << "4" << endl;
			else if(P > 0)
				cout << "4" << endl;
			else{
				b2m4ac = (D*D) - (4*P);
				if(b2m4ac == 0)
					cout << "2" << endl;
				else if(b2m4ac > 0)
					cout << "4" << endl;
				else
					cout << "0" << endl;
			}
		}else {
			cout << "0" << endl;
		}
	}
}

/*
clear && pwd && ll && cd ~/Puzzles/hackerrank/2014/adinfi9/ && rm -rf *.dSYM *.log && g++ -g -std=c++11 diffprod.cpp -o diffprod && time ./diffprod < input.in
*/
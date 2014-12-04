#include <map>
#include <set>
#include <list>
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
typedef long double ld;

int main(void) {

	int n,N,w;
    cin >> N;
    std::vector<int> weights;
    ld ans = 0;

	for(n=0; n<N; n++) {
		cin >> w;
		weights.push_back(w);
		ans += (ld) ( (ld) w / (ld)pow(2, n+1));
		if(n>1022)
			break;
	}

	cout << (int)ceil(ans) << endl;
	return 0;
}

/*
clear && cd ~/Puzzles/hackerrank/2014/week12/ && rm -rf chiefhopper && g++ -std=c++11 chiefhopper.cpp -o chiefhopper && ./chiefhopper < input.in
*/

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

int main(void) {

	int n,N,w;
    cin >> N;
    std::vector<int> weights;

	for(n=0; n<N; n++) {
		cin >> w;
		weights.push_back(w);
	}

	std::sort(weights.begin(), weights.end());

	// for (int w: weights) {
 //     	cout << "  " << w;
	// } cout	<< endl;

	int total = weights.size();
	int i,t = 0;
	int sets = 0;
	while(t < total) {
		w = weights[t];
		i = 0;
		while(weights[t+i] >= w && weights[t+i] <= w+4 ){
			//cout << "  " << weights[t+i];
			i++;
		}
		//cout << "\nhey " << i << " \n";
		sets++;
		t += i;
	}
	cout << sets;
	return 0;
}

/*
clear && cd /cygdrive/c/Users/jdurairaj/Documents/puzzles/hackerrank/week12/ && rm -rf *.exe && rm -rf *.stackdump && g++ -std=c++11 priToys.cpp -o priToys && ./priToys.exe < input.in
*/

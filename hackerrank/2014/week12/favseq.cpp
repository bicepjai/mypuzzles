#include <map>
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
typedef long double ld;

int main(void) {

	int n,N,k,K;
	int pv,v;
    std::map <int, list<int> > graph;
	
	cin >> N;
	for(n=0; n<N; n++) {
		cin >> K;
		for(k=0; k<K; k++) {
			cin >> v;
			if(k>0){
				if ( graph.count(pv) == 0 ) {
					list<int> adj;
					adj.push_back(v);
					graph.insert ( std::pair<int,list<int>>(pv,adj) );
				} else {
					graph[pv].push_back(v);
				}
			}
			pv = v;
		}
	}

	for ( std::map< int, list<int> >::const_iterator iter = graph.begin();
    iter != graph.end(); ++iter ) {
		cout << iter->first << " ==> [ ";
		list<int>::iterator i;
		list<int> lv = iter->second;
		for(i = lv.begin(); i != lv.end(); ++i)
			cout << *i << " ";
		cout << " ]" << endl;
    }

    

	return 0;
}

/*
clear && cd ~/Puzzles/hackerrank/2014/week12/ && rm -rf favseq && g++ -std=c++11 favseq.cpp -o favseq && ./favseq < input.in && rm -rf favseq
*/

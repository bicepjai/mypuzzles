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
#include <vector>
#include <cstdlib>
#include <numeric>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <stdio.h>
using namespace std;
int N;

#include <iostream>
using namespace std;

#define LOGSZ 18

int tree[(1<<LOGSZ)+1];
//int N = (1<<LOGSZ);

// add v to value at x
void setFWT(int x, int v) {
  while(x <= N) {
    tree[x] += v;
    x += (x & -x);
  }
}

// get cumulative sum up to and including x
int getFWT(int x) {
  int res = 0;
  while(x) {
    res += tree[x];
    x -= (x & -x);
  }
  return res;
}

// get largest value with cumulative sum less than or equal to x;
// for smallest, pass x-1 and add 1 to result
int getind(int x) {
  int idx = 0, mask = N;
  while(mask && idx < N) {
    int t = idx + mask;
    if(x >= tree[t]) {
      idx = t;
      x -= tree[t];
    }
    mask >>= 1;
  }
  return idx;
}

int main(void) {

    int n,in,q;//,s;
    int mx,ny,type;
    int L,R,Q,S;
    int LA[100000+10], RA[100000+10];

    cin >> N;
    //printf("%u\n", N);
	for(n=1; n<=N; n++) {
		cin >> in;
		//printf("%u\n", in);
		setFWT(n ,in);
	}
	// for(n=1; n<=N; n++) {
	// 	printf("%u ",tree[n]);
	// }printf("\n******************\n");

	for(n=1; n<=N; n++) {
		cin >> LA[n];
		cin >> RA[n];
	}

	cin >> Q;
	for(q=0; q<Q; q++) {
		cin >> type;
		cin >> mx;
		cin >> ny;
		if(type == 1){
			setFWT(mx ,abs(ny - getind(mx) -1));
			// for(n=1; n<=N; n++) {
			// 	printf("%u ",tree[n]);
			// }printf("\n******************\n");
		} else if(type == 2){
			S = 0;
			// printf("=====\n");
			for(n=mx; n<=ny; n++) {
				S += (getFWT(RA[n]) - getFWT(LA[n]-1));
				//printf("%ld %ld => %ld \n",LA[n],RA[n],S);
			}
			printf("%d\n", S);
		}
	}
	return 0;
}

/*
clear && cd /cygdrive/c/Users/jdurairaj/Documents/puzzles/codechef/nov14/ && rm -rf *.exe && rm -rf *.stackdump && g++ fncs.cpp -o fncs && ./fncs.exe < input.in
*/

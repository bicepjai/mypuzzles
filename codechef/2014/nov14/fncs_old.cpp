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
long fwt[100000+10];
long N;

void update(long idx ,long val){
	while (idx <= N){
		fwt[idx] += val;
		idx += (idx & -idx);
	}
}

long read(long idx){
	long sum = 0;
	while (idx > 0){
		sum += fwt[idx];
		// printf("read %ld sum %ld ", idx,sum,(idx & -idx));
		// cout << bitset< 4 >(idx) << " >> ";
		idx -= (idx & -idx);
		// cout << bitset< 4 >(idx) << endl;
	}
	return sum;
}

long readSingle(long idx){
	long sum = fwt[idx]; // sum will be decreased
	// printf("rds %ld sum ", idx);
	long z;
	if (idx > 1){ // special case
		z = idx - (idx & -idx); // make z first
		idx--; // idx is no important any more, so instead y, you can use idx
		while (idx != z){ // at some iteration idx (y) will become z
			sum -= fwt[idx]; 
			// substruct tree frequency which is between y and "the same path"
			idx -= (idx & -idx);
		}
	}
	// printf("%ld\n", idx,sum);
	return sum;
}

int main(void) {

    long n,in,q;//,s;
    long mx,ny,type;
    long L,R,Q,S;
    long LA[100000+10], RA[100000+10];

    cin >> N;
    //printf("%u\n", N);
	for(n=1; n<=N; n++) {
		cin >> in;
		//printf("%u\n", in);
		update(n ,in);
	}
	// for(n=1; n<=N; n++) {
	// 	printf("%u ",fwt[n]);
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
			update(mx ,abs(ny - readSingle(mx)));
			// for(n=1; n<=N; n++) {
			// 	printf("%u ",fwt[n]);
			// }printf("\n******************\n");
		} else if(type == 2){
			S = 0;
			// printf("=====\n");
			for(n=mx; n<=ny; n++) {
				S += (read(RA[n]) - read(LA[n]-1));
				// printf("%ld %ld => %ld \n",LA[n],RA[n],S);
			}
			printf("%ld\n", S);
		}
	}
	return 0;
}

/*
clear && cd /cygdrive/c/Users/jdurairaj/Documents/puzzles/codechef/nov14/ && rm -rf *.exe && rm -rf *.stackdump && g++ fncs.cpp -o fncs && ./fncs.exe < input.in
*/

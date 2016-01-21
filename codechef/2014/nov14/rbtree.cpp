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
#include <string.h>
#include <algorithm>
#include <stdio.h>
#include <assert.h>
#include <utility> 

using namespace std;

unsigned int nlz1a(unsigned int x) {
   unsigned int n;
	/* if (x == 0) return(32); */
   if ((unsigned int)x <= 0) return (~x >> 26) & 32;
   n = 1;
   if ((x >> 16) == 0) {n = n +16; x = x <<16;}
   if ((x >> 24) == 0) {n = n + 8; x = x << 8;}
   if ((x >> 28) == 0) {n = n + 4; x = x << 4;}
   if ((x >> 30) == 0) {n = n + 2; x = x << 2;}
   n = n - (x >> 31);
   return n;
}

bool isEven(unsigned int i) {
	if(i%2 == 0)
		return true;
	else
		return false;
}

pair <int,int> getMeQbr1Path(int Lx, int Lxy, unsigned int swap){
	int Qb, Qr, diff;
	Qb = 0;
	Qr = 0;

	// printf("Lx,Lxy: %d %d\n",Lx, Lxy);
	diff = abs(Lx - Lxy);
	if(diff == 0){
		if(!isEven(swap)) {
			if(isEven(Lx)) Qr++;
			else Qb++;
		} else {
			if(isEven(Lx)) Qb++;
			else Qr++;
		}
	} else if(diff == 1) {
		Qr++;
		Qb++;
	} else {
		// printf("diff, Qb, Qr: %d %d %d\n",diff, Qb, Qr);	
		if(!isEven(swap)) {
			if(isEven(Lx) && isEven(Lxy)) {
				Qr++;
			} else if (!isEven(Lx) && !isEven(Lxy)) {
				Qb++;
			} else {
				diff++;
			}
			Qb += diff/2;
			Qr += diff/2;
		} else {
			if(isEven(Lx) && isEven(Lxy)) {
				Qb++;
			} else if (!isEven(Lx) && !isEven(Lxy)) {
				Qr++;
			} else {
				diff++;
			}
			Qb += diff/2;
			Qr += diff/2;
		}
	}

	return std::make_pair (Qr,Qb);
}

pair <int,int> getMeQbr2Paths(int Lx, int Ly, int Lxy, unsigned int swap){
	int Qb, Qr, diff;
	pair <int,int> Qs;
	Qb = 0;
	Qr = 0;
	
	Qs = getMeQbr1Path(Lx, Lxy,swap);
	Qb += Qs.second;
	Qr += Qs.first;

	Qs = getMeQbr1Path(Ly, Lxy,swap);
	Qb += Qs.second;
	Qr += Qs.first;	

	// getting rid of extra LCA added 2wice on the paths
	if(!isEven(swap)) {
		if(isEven(Lxy)) Qr--;
		else Qb--;
	} else {
		if(isEven(Lxy)) Qb--;
		else Qr--;
	}

	return std::make_pair (Qr,Qb);
}

int main(void) {

    string query;
    unsigned int T,t,L;
    unsigned int x,y,tx,ty;
    unsigned int nlzx,nlzy,nlzxy;
    int Lx, Ly, Lxy;
    unsigned int swap = 1; // root is black if odd, red if even
    pair <int,int> Qs;

    L = 8*sizeof(unsigned int);

    cin >> T;

    //printf("%d %d\n", T, L);
	for(t=0; t<T; t++) {
		cin >> query;
		//cout << query << endl;
		if(query.compare("Qi")){
			cin >> x; tx=x;
			cin >> y; ty=y;
			nlzx = nlz1a(x);
			Lx = L - nlzx;
			nlzy = nlz1a(y);
			Ly = L - nlzy;
			//printf("NLZ (%d)%d (%d)%d\n", x, nlzx, y, nlzy);			
			if(nlzx > nlzy) {
				ty=ty>>(nlzx-nlzy);
			} else if(nlzx < nlzy) {
				tx=tx>>(nlzy-nlzx);
			}
			while(tx!=ty){
				tx = tx >> 1;
				ty = ty >> 1;
			}
			assert (tx==ty);
			nlzxy = nlz1a(ty);
			Lxy = L - nlzxy;

			Qs = getMeQbr2Paths(Lx, Ly, Lxy,swap);

			if(query.compare("Qb") == 0) {
				printf("%d\n",Qs.second);
			} else if (query.compare("Qr") == 0) {
				printf("%d\n",Qs.first);
			}

		} else {
			swap++;
			//printf("swaps %d\n",swap);
		}
	}

	return 0;
}

/*
clear && cd /cygdrive/c/Users/jdurairaj/Documents/puzzles/codechef/nov14/ && rm -rf *.exe && rm -rf *.stackdump && g++ rbtree.cpp -o rbtree && ./rbtree.exe < input.in
*/

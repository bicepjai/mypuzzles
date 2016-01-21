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


bool isPalin(string input) {
	if (input == string(input.rbegin(), input.rend())) {
	    return true;
	}
	return false;
}

int main(void) {

    int T,t,i;
    int length;
    string str;

    cin >> T;

	for(t=0; t<T; t++) {
  		cin >> str;
  		if(isPalin(str)){
  			cout << "YES" << endl;
  		} else {
  			length = str.length() - 1;
  			for(i=0;i<=length;i++){
  				if(str[i] != str[length-i]){
  					//cout << str.substr(i+1,length-i - i-1 + 1) << " " << isPalin(str.substr(i+1, length-i - i-1 + 1)) << endl;
  					//cout << str.substr(i,length-i-1 - i + 1) << " " << isPalin(str.substr(i,length-i-1 - i + 1)) << endl;
  					if(isPalin(str.substr(i+1, length-i - i-1 + 1)) || isPalin(str.substr(i,length-i-1 - i + 1))) {
  						cout << "YES" << endl;
  					} else {
  						cout << "NO" << endl;
  					}
  					break;
  				}
  			}
  			
  			//cout << length << " " << str << endl;
  		}


	}
	return 0;
}

/*
clear && cd /cygdrive/c/Users/jdurairaj/Documents/puzzles/codechef/nov14/ && rm -rf *.exe && rm -rf *.stackdump && g++ prpaln.cpp -o prpaln && ./prpaln.exe < input.in
*/

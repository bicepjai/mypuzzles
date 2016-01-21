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
#include <utility> 

#include <stdio.h>
#include <string.h>
//#include <cstring>
#include <assert.h>

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

#define MAX_STONES 100000

bool isAnagram(string s1, string s2) {
	
	if(s1.size() != s2.size())
        return false;

	int* hashtable = new int[26];
    memset(hashtable,0,26 * sizeof(int));

    for(auto c : s1)
        hashtable[c - 'a']++;

    for(auto c : s2)
    	if(hashtable[c - 'a'] > 0)
        	hashtable[c - 'a']--;
        else
        	return false;

    return true;
}

int cardinalityUnorderedSet(int  n) {
	int ans = 0;
	if (n > 1){
		n--;
		ans = int( double(n)/2 * double(n+1) );
	}
	return ans;
}

int main(void) {
	ios_base::sync_with_stdio( false );
	int T,t,i,j, slen;
	string S;
	std::unordered_map <string, int> substringsMaps;

	cin >> T;

	for(t=0; t<T; t++) {
		cin >> S;
		slen = S.size();
		substringsMaps.clear();
		for(i=0; i<slen; i++) {
			for(j=1; j<=slen-i; j++) {
				string sub = S.substr(i,j);
				sort(sub.begin(), sub.end());

				unordered_map<string,int>::const_iterator got = substringsMaps.find (sub);

				if ( got == substringsMaps.end() ){
					// substringsMaps.insert(make_pair<string,int>(sub,0));
					substringsMaps[sub] = 1;
				} else {
					substringsMaps[sub]++;
				}

			}
		}
		int ans = 0;
		for(auto kv : substringsMaps) {
			// cout << kv.first << "," << kv.second << endl;  
			if(kv.second > 0)
				ans += cardinalityUnorderedSet(kv.second);
		}
		cout << ans << endl;
	}


}

/*
clear && pwd && ll && cd ~/Puzzles/hackerrank/2015/wk13 && rm -rf *.dSYM *.log && g++ -g -std=c++1y sherlock_anagrams.cpp -o sherlock_anagrams && time ./sherlock_anagrams < input.in
*/



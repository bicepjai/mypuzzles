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
#define vpii		std::vector <pii>
#define vull 		std::vector <ull>
#define vvi 		std::vector <vector<int>>

typedef long double ld;
typedef long long ll;
typedef unsigned long long ull;

#define MAX_KINGDOMS 100000

struct scmp {
  	bool operator() (const pair<int, int>& f, const pair<int, int>& s) const
  	{
 		if(f.first == s.first){
 			return f.second < s.second;
 		}
 		return f.first < s.first;
	}
}ocmp;

typedef set<pair<int, int>, scmp> setK;

int main(void) {
	ios_base::sync_with_stdio( false );
	int t,T,n,N,f,s,ans,pivot;
	int i,j;
	bool lastOverlap, lastInside;
	vector<bool> valid;
	vpii kingdoms;
	setK setKingdoms;
	pair<int, int> mp;
	setK::iterator setItr1;

	cin >> T;
	
	for(t=0; t<T; t++) {
		ans = 0;
		setKingdoms.clear();
		kingdoms.clear();
		valid.clear();
		pivot = -1;
		lastOverlap = lastInside = false;
		cin >> N;
		for(n=0;n<N;n++) {
			cin >> f;
			cin >> s;
			mp = make_pair(f,s);
			setItr1 = setKingdoms.find(mp);
			if (setItr1 == setKingdoms.end()) {
				setKingdoms.insert(mp);
				valid.push_back(true);
			} else {
				ans++;
			}
		}

		std::copy(setKingdoms.begin(), setKingdoms.end(), std::back_inserter(kingdoms));

		for(i=0;i<kingdoms.size()-1;i++) {
			j = i+1;

			cout << i << ")" << kingdoms[i].first << ":" << kingdoms[i].second << " ";
			cout << j << ")" << kingdoms[j].first << ":" << kingdoms[j].second << endl;

			if(	(kingdoms[i].first == kingdoms[j].first &&
					kingdoms[i].second < kingdoms[j].second ) ||
				(kingdoms[i].first < kingdoms[j].first &&
					kingdoms[i].second == kingdoms[j].second ) ||
				(kingdoms[i].first < kingdoms[j].first &&
					kingdoms[i].second > kingdoms[j].second ) )
			{
				cout << "inside" << endl;
				if(kingdoms[i].first < kingdoms[j].first)
					kingdoms[j].first = kingdoms[i].first;
				if(kingdoms[i].second > kingdoms[j].second)
					kingdoms[j].second = kingdoms[i].second;
				lastInside = true;
				continue;
			} else 
			{
				// either overlap
				if(	kingdoms[j].first >= kingdoms[i].first &&
						kingdoms[j].first <= kingdoms[i].second &&
							kingdoms[i].second < kingdoms[j].second ) 
				{
					if(pivot < kingdoms[j].first){
						pivot = kingdoms[j].first;
						cout << "+++++ pivot addition" << endl;
						ans++;
					}
					lastOverlap =true;
				} else
				// either completely outside
				{
					cout << "+++++ new range addition" << endl;
					ans++;
					if(!lastOverlap && !lastInside && i==0) {
						cout << "+++++ new range addition since no prev overlap" << endl;
						ans++;
					}

					lastOverlap =false;
				}
				lastInside = false;
			}
		}
		if(lastInside && ans == 0) 
		{
			cout << "+++++ last new range addition" << endl;
			ans++;
		}

		cout << ans << endl;
		cout << "=============" << endl;
	}
	
	return 0;
}

/*
clear && pwd && ll && cd ~/Puzzles/codechef/2015/jan15 && rm -rf *.dSYM *.log && g++ -g -std=c++1y oneking.cpp -o oneking && time ./oneking < input.in
*/



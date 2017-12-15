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

// #define umapiv 		std::unordered_map <int, vector<int>>
// #define umapib 		std::unordered_map <int, bool>
#define vi 	 		std::vector <int>
#define vvi 		std::vector <vector<int>>

typedef long double ld;
typedef long long ll;
typedef unsigned long long ull;

// ds

ull indexInSeries(ull S, int index) {
	int len,slen;
	len = slen = (to_string(S)).length();
	ull no = S * (ull)len;
	// cout << no << " ";
	len--;
	while(len){
		no = no - (ull(pow(10,len)) - 1);
		// cout << no << " ";
		len--;
	}
	// cout << endl;
	if(index < slen)
		no = no - (slen-1-index);
	else
		no = no + (index+1-slen);
	return no;
}

pib findSeriesInString(string S) {

	ull firstNo, current, next, nexts, result;
	string nextString;
	int startIndex, getDigits, digits, Slen;
	bool seriesExist, nofSeriesInS;
	Slen = S.length();
	
	for(digits = 1; digits < Slen; digits++) {
		// cout << "digits: " << digits << endl;
		getDigits = digits;
		firstNo = current 	= stoull(S.substr(0,getDigits));
		startIndex 	= getDigits;
		seriesExist = true;
		nofSeriesInS = false;
		// tryingOptionMatched = 0;

		while(startIndex < Slen){
			next = current + 1;
			if(current == pow(10,getDigits) - 1){
				getDigits = getDigits + 1; 
			}
			if(startIndex + getDigits > Slen) {
				getDigits = (startIndex + getDigits) - Slen;
				nextString = to_string(next);
				string a = nextString.substr(0,getDigits);
				string b = S.substr(startIndex);
				if( a.compare(b) != 0) {
					seriesExist = false;
					// cout << "seriesExist = false;" << endl;
					break;
				}
			} else {
				nexts = stoull(S.substr(startIndex,getDigits));
				// cout << "next:" << next << " nexts:" << nexts << endl;
				if(nexts != next){
					seriesExist = false;
					// cout << "seriesExist = false;" << endl;
					break;
				}
				if(!nofSeriesInS)
				result = firstNo;
				nofSeriesInS = true;
			}
			current = next;
			startIndex = startIndex + getDigits;
		}
		if(seriesExist)
			break;
	}
	return make_pair(result, (seriesExist && nofSeriesInS));
}

int main(void) {
	ios_base::sync_with_stdio( false );
	int t,T;
	string S;

	int Slen, prefixDigits, tryIndex;
	string newS, subS;
	ull startOption, seriesNumber;
	bool found;
	pib result;

	cin >> T;

	for(t=0; t<T; t++) {
		cin >> S;
		// cout << "\n==================" << S << endl;

		Slen = S.length();
		found = false;
		result = findSeriesInString(S);
		if(result.second){
			// cout << "seriesExist: " << S << " => " << result.first << " Index: 0" << endl;
			found = true;
			seriesNumber = result.first;
			prefixDigits = 0;
		} else {
			// now we are gonna add numbers before S 
			// and figure out if anything becomes a part
			for (prefixDigits = 1; prefixDigits < Slen; prefixDigits++) {
				// possible values of this prefix depends on the 
				// next digit
				for(tryIndex = 0; tryIndex+prefixDigits <= Slen; tryIndex++) {
					subS = S.substr(tryIndex,prefixDigits);
					if(subS[0] != '0') {
						startOption = stoull(subS);
						vi options;
						options.push_back(startOption);
						options.push_back(startOption-1);
						for (ull tryOption: options ){
							newS = to_string(tryOption).append(S);
							// cout << "==============newS: " << newS << " tryIndex:" << tryIndex << endl;
							result = findSeriesInString(newS);
							if(result.second){
								// cout << "seriesExist: " << S << " => " << result.first << " Index: " << prefixDigits << endl;
								seriesNumber = result.first;
								found = true;
								break;
							}
						}
						if(found) break;
					}
				}
				if(found) break;
			}
		}
		if(found)
			// cout << seriesNumber << "==>" << indexInSeries(seriesNumber, prefixDigits) << endl;
			cout << indexInSeries(seriesNumber, prefixDigits) << endl;
	}
	return 0;
}

/*
clear && pwd && ll && cd ~/Puzzles/codechef/2014/nov-lunchtime/ && rm -rf *.dSYM *.log && g++ -g -std=c++11 gridconn.cpp -o gridconn && time ./gridconn < input.in
*/

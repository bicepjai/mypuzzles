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
#include <string.h>
#include <algorithm>
#include <vector>
#include <stdio.h>
#include <assert.h>
#include <utility> 
using namespace std;

#define itr 	 		iterator
#define citr 		const_iterator

#define pib 		std::pair <int, bool>
#define pii 		std::pair <int, int>
#define piv 		std::pair <int, vector<int>>

#define umapiv 		std::unordered_map <int, vector<int>>
#define umapib 		std::unordered_map <int, bool>
#define vi 	 		std::vector <int>
#define vvi 		std::vector <vector<int>>

typedef long double ld;
typedef long long ll;

// ds

#define MAXSIZE 1000009
typedef struct
{
   int deg;
   int id;
} Vertex;

struct cmp {
  bool operator() (const Vertex& v1, const Vertex& v2) const
  {
     if(v1.deg < v2.deg) return true;
     if(v1.deg == v2.deg && v1.id < v2.id) return true;
     return false;
  }
};

typedef set<Vertex, cmp> SetV;

void Print (const vector<int>& v){
  //vector<int> v;
  for (int i=0; i<v.size();i++){
    cout << v[i]+1 << endl;
  }
}

void printSet(SetV vertices){
	set<Vertex>::iterator iter;
    Vertex ver;
    for(iter=vertices.begin(); iter!=vertices.end();++iter){
    	ver = *iter;
    	cout << ver.id + 1 <<  "(" << ver.deg << ") ";
    } cout << endl;
}

int main(void) {
	ios_base::sync_with_stdio( false );
	int n,N,k,K;
	int u,v;
    int i,j;

	SetV	vertices;
	vi 		emptyadj;
	vvi 	graph(MAXSIZE, emptyadj);
	vi 		degree(MAXSIZE, -1);

	cin >> N;

	for(n=0; n<N; n++) {
		cin >> K;
		cin >> u; u--;
		if (degree[u] == -1)
			degree[u]=0;

		for(k=0; k<K-1; k++) {
			cin >> v; v--;
			graph[u].push_back(v);
			if(degree[v] == -1) degree[v] = 1;
			else degree[v]++;
			u = v;
		}
		if (degree[v] == -1)
			degree[v]=0;
	}

	Vertex ver;
	// order vertices based on degree and id
	for ( i=0;i<MAXSIZE;i++ ) {
		if(degree[i] != -1){
			// cout << i+1 << " =" ;
			// Print(graph[i]);
			ver.id = i;
			ver.deg = degree[i];
			vertices.insert(ver);
		}
	}
	// cout << endl;
	// printSet(vertices);
	int nofvertices = vertices.size();
    vi result(nofvertices, 0);
 	int id1, id2;
    SetV::iterator svi;

    for(i=0; i<nofvertices;i++){
    	svi = vertices.begin();
    	ver = *svi;
    	id1 = ver.id;
    	result[i] = id1+1;
		vertices.erase(ver);
		// cout << i+1 << " =+ " << graph[id1].size() << endl;
		
		for(j=0; j<graph[id1].size();j++){
			id2 = graph[id1][j];
			ver.id = id2;
			ver.deg = degree[id2];
			vertices.erase(ver);
			degree[id2]--;
			ver.deg--;
			vertices.insert(ver);
		}
		// printSet(vertices);
	}

	for(i=0;i<result.size();i++)
		cout << result[i] << " ";
	cout << endl;

	return 0;
}

/*
clear && pwd && ll && cd /cygdrive/c/Users/bicepjai/Puzzles/hackerrank/2014/week12/ && rm -rf *.exe *.stackdump *.log && g++ -g -std=c++11 favseq.cpp -o favseq && time ./favseq.exe < input.in

*/

/*
http://stackoverflow.com/questions/20153488/topological-sort-using-dfs-without-recursion
http://chasethered.com/2014/11/my-problem-for-hackerrank-weekly-challenge-12-favorite-sequence/

When you pick a node to push into the stack. This node must have no precessor( has a in-degree of 0). This means you are doing a DFS base on in-degree in stead of push all the adjacent nodes into the stack, you always pick the one with 0 in-degree

So you push every node that have no precessor in the stack. Pop one, print it and remove it from all its adjacent nodes' precessor list ( or decrease its adjacent nodes' in-degree by 1). This need you to edit your adjacent list. Than push all its adjacent nodes that has in-degree of 0 now in to the stack( this phase may fail but no problem, you still got some nodes in the stack). Then pop the next one. Repeat until the stack is empty. The node sequence that you printed is the topological sort result of the graph.
*/
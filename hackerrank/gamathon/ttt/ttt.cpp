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
#include <tuple>
#include <assert.h>

using namespace std;

enum {XPL=88,OPL=79,EMPTY=95,BORDER=100};

int convert9To25[9] = {
    6,7,8,
    11,12,13,
    16,17,18
};
int directions[4] = {1,4,5,6};
typedef std::tuple<int,int> pair;
/*
void initializeBoard(int* const iboard, vector <string> board);
void convert1dTo2d(int move);
int otherPlayer(int player);

int findInDir(const int* iboard, int player,int pos, int dir);
int find3InARow(const int* iboard, int player,int posIn9);

void isBoardFull(const int* iboard);
int didHeWin(const int* iboard, int player);

pair chooseMove (const int* iboard, int player);
*/
void initializeBoard(int* const iboard, vector <string> board) {
    int i,j,k;
    for(j=0;j<25;j++){
        iboard[j]=BORDER;
    }
    assert(board.size() == 3);
    k=0;
    for(i=0;i<3;i++){
        for(j=0;j<3;j++){
            iboard[k++] = board.at(i)[j];
        }
    }
}

void convert1dTo2d(int moveIn9){
    int xyMoves[9][2] = {
        {0,0},{0,1},{0,2},
        {1,0},{1,1},{1,2},
        {2,0},{2,1},{2,2}
    };
    assert(moveIn9 < 9 && moveIn9 >= 0);
    printf("%d %d",xyMoves[moveIn9][0],xyMoves[moveIn9][1]);
}

int otherPlayer(int player){
    int pl = 0;
    if(player == OPL){
        pl= XPL;
    }
    if(player == XPL){
        pl= OPL;
    }
    assert(player == OPL || player == XPL);
    return pl;
}

// zero if not full
int isBoardFull(const int* iboard) {
    int i;
    for(i=0;i<9;i++){
        if(iboard[convert9To25[i]]==EMPTY){
           return 0;
        }
    }
    return 1;
}

int findInDir(const int* iboard, int player,int posIn9, int dir){
    int i=convert9To25[posIn9];
    int count = 0;
    while(iboard[i] != BORDER){
        if(iboard[i] == otherPlayer(player)){
            break;
        }else{
            count++;
        }
        i=i+dir;
    }
    return count;
}

int find3InARow(const int* iboard, int player,int posIn9) {
    int idir;
    int threes;
    for(idir=0;idir<4;idir++){
        threes = 0;
        threes = threes + findInDir(iboard, player,posIn9, directions[idir]);
        threes = threes + findInDir(iboard, player,posIn9, -directions[idir]);
        if(threes == 3){
            return 1;
        }
    }
    return 0;
}

int didHeWin(const int* iboard, int player) {
    int i;
    for (i=0;i<9;i++){
        if(find3InARow(iboard,player,i) == 3){
            return 1;
        }
    }
    return 0;
}

int US;
int THEM;
// pair (score,move)
#define SCORE 0
#define MOVE 1
std::tuple<int,int> chooseMove (int* iboard, int player) {
    assert(player == XPL || player == OPL);
    
    std::tuple<int,int> myBest = make_tuple(0,0);
    std::tuple<int,int> reply = make_tuple(0,0);
    int i, move;
    int moveCount=0, moveList[9];
    
    if(didHeWin(iboard,player)) {
        return make_tuple(1,-1);
    }
    
    if(isBoardFull(iboard)) {
        return make_tuple(0,-1);
    }
    
    for(i = 0; i < 9; i++) {
		if( iboard[convert9To25[i]] == EMPTY) {
			moveList[moveCount++] = convert9To25[i];
		}
	}
    //score
    if(player == US){
        get<SCORE>(myBest) = -1;
    } else {
        get<SCORE>(myBest) = 1;
    }
    // any legal move
    get<MOVE>(myBest) = moveList[0];
    
    for(i=0; i < moveCount; i++) {
        move = moveList[i];
		iboard[move] = player;
        reply = chooseMove(iboard, otherPlayer(player));
        iboard[move] = EMPTY;
        if( // maximizinf by selecting opponents less score
            (player == US && get<SCORE>(myBest) > get<SCORE>(reply)) ||
            // minimizing by letting them select out high score
            (player == THEM && get<SCORE>(myBest) < get<SCORE>(reply))){
            get<SCORE>(myBest) = get<SCORE>(reply);
            get<MOVE>(myBest) = move;
        }
	}
    return myBest;
}

void nextMove(char player, vector <string> board){
    int iboard[25];
    std::tuple<int,int> best;
    initializeBoard(iboard, board);
    US = player;
    THEM = otherPlayer(US);
    best = chooseMove(iboard,player);
    convert1dTo2d(get<MOVE>(best));
}

int main(void) {

    char player;
    vector <string> board;

    //If player is X, I'm the first player.
    //If player is O, I'm the second player.
    cin >> player;

    //Read the board now. The board is a 3x3 array filled with X, O or _.
    for(int i=0; i<3; i++) {
      string s; cin >> s;
      board.push_back(s);
    }

   nextMove(player,board);

    return 0;
 }

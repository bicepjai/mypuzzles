#include <stdio.h>
#include <string.h>
#include <math.h>
#include "stdlib.h"


#define DEBUG
#ifndef DEBUG
#define ASSERT(n)
#else
#define ASSERT(n) \
if(!(n)) { \
printf("%s - Failed",#n); \
printf("On %s ",__DATE__); \
printf("At %s ",__TIME__); \
printf("In File %s ",__FILE__); \
printf("At Line %d\n",__LINE__); \
exit(1);}
#endif

typedef struct _pair {
    int score;
    int move;
} pair;

enum {XPL='X',OPL='O',EMPTY='_',BORDER='$'};

int convert9To25[9] = {
    6,7,8,
    11,12,13,
    16,17,18
};

int score[9] = {
    10,5,10,
    5,20,5,
    10,5,10
};
int convert25To9[25] = {
    -1,-1,-1,-1,-1,
    -1,0,1,2,-1,
    -1,3,4,5,-1,
    -1,6,7,8,-1,
    -1,-1,-1,-1,-1
};
int directions[4] = {1,5,6,4};
/*
void initializeBoard(int* const iboard, char[3][3] board);
void convert1dTo2d(int move);
int otherPlayer(int player);

int findInDir(const int* iboard, int player,int pos, int dir);
int find3InARow(const int* iboard, int player,int posIn9);

void isBoardFull(const int* iboard);
int didHeWin(const int* iboard, int player);

pair chooseMove (const int* iboard, int player);
*/
void initializeBoard(int *iboard, char board[3][3]) {
    int i,j,k;
    for(j=0;j<25;j++){
        iboard[j]=BORDER;
    }
    k=0;
    for(i=0;i<3;i++){
        for(j=0;j<3;j++){
            iboard[convert9To25[k++]] = board[i][j];
        }
    }
}

void convert1dTo2d(int moveIn25){
    int moveIn9 = convert25To9[moveIn25];
    int xyMoves[9][2] = {
        {0,0},{0,1},{0,2},
        {1,0},{1,1},{1,2},
        {2,0},{2,1},{2,2}
    };
    //printf("%d (%d %d)",moveIn9,xyMoves[moveIn9][0],xyMoves[moveIn9][1]);
    printf("%d %d\n",xyMoves[moveIn9][0],xyMoves[moveIn9][1]);
}

int otherPlayer(int player){
    int pl = 0;
    if(player == OPL){
        pl= XPL;
    }
    if(player == XPL){
        pl= OPL;
    }
    ASSERT(player == OPL || player == XPL);
    return pl;
}

// zero if not full
int isBoardFull(const int* iboard) {
    int i;
    for(i=0;i<9;i++){
        if(iboard[convert9To25[i]]==EMPTY){
            //printf("%d found not full\n",i );
            return 0;
        }
    }
    return 1;
}

int findInDir(const int* iboard, int player,int posIn25, int dir){
    int i= posIn25;
    int count = 0;
    //printf("\n");
    while(iboard[i] != BORDER){
        if(iboard[i] != player){
            //printf("broke ");
            break;
        }
        //printf("%d ",i);
        count++;
        i=i+dir;
    }
    //if(count)printf("\n");    
    return count;
}

int findCollinear3(const int* iboard, int player,int posIn25) {
    int idir,dir;
    int threes;
    ASSERT(posIn25 > 0 || posIn25 < 25);
    for(idir=0;idir<4;idir++){
        dir = directions[idir];
        threes = 1;
        threes += findInDir(iboard, player,posIn25+dir, dir);
        //printf("player:%c pos:%d idir:%d 3s: %d\n", player, posIn25, dir, threes);
        threes += findInDir(iboard, player,posIn25-dir, -1*dir);
        //printf("player:%c pos:%d idir:-%d total 3s: %d\n", player, posIn25, dir, threes);
        //printf("\n");
        if(threes == 3){
            //printf("found 3 in row\n\n");
            //printf("player:%c pos:%d idir:%d total 3s: %d\n", player, posIn25, dir, threes);
            break;
        }
    }
    return threes;
}

int didHeWin(const int* iboard, int player) {
    int i;
    for (i=0;i<9;i++){
        //printf("win check: %d\n", i);
        if(iboard[convert9To25[i]] == player) {
            //printf("%d\n", convert9To25[i]);
            if(findCollinear3(iboard,player,convert9To25[i]) == 3) {
                return 1; // can be 1 but added for minmax
            }
        }
    }
    //printf("did not find 3 in row\n");
    return 0;
}

void printboard (int* iboard){
    int i;
    printf("\n");
    for(i = 0; i < 9; i++) {
        printf("%c ", iboard[convert9To25[i]]);
        if((i+1) % 3 == 0) printf("\n");
    }
    printf("\n");
}

int US;
int THEM;

int depth = 0;
pair chooseMove (int* iboard, int player) {
    ASSERT(player == XPL || player == OPL);
    
    pair myBest = {0,-1};
    pair reply;
    int i, move;
    int moveCount=0, moveList[9];

    //default score
    if(player == US){
        myBest.score = -1;
    } else {
        myBest.score = 1;
    }

    if(didHeWin(iboard,US)) {
        //printf("%c WON\n",US);
        //printf("=====returning{1}====================\n");
        //printboard(iboard);
        pair temp;
        temp.score = 10;
        temp.move = -1;
        return temp;
    } else if(didHeWin(iboard,THEM)) {
        //printf("%c WON\n",THEM);
        //printf("=====returning{-1}====================\n");
        //printboard(iboard);
        pair temp;
        temp.score = -10;
        temp.move = -1;
        return temp;
    } else if(isBoardFull(iboard)) {
        //printf("FULL\n");
        //printf("=====returning{0}====================\n");
        pair temp;
        temp.score = 0;
        temp.move = -1;
        return temp;
    }
    
    // get legal moves
    for(i = 0; i < 9; i++) {
        if( iboard[convert9To25[i]] == EMPTY) {
            moveList[moveCount++] = convert9To25[i];
        }
    }

    // any legal move
    // TODO: get the best move as default
    //myBest.move = moveList[0];
    //printf("Move by %c;*********************************************\n",player);
    for(i=0; i < moveCount; i++) {
        //printf("%d ", moveList[i]);
    }
    //printf("\n");
    for(i=0; i < moveCount; i++) {
        move = moveList[i];
        iboard[move] = player;
        //printf("%c(to move(%d/%d) %d);best:%d ;reply:%d \n", 
        //    player,i+1,moveCount,move,myBest.score,reply.score);
        //printboard(iboard);
        reply = chooseMove(iboard, otherPlayer(player));
        iboard[move] = EMPTY;
        //printf("RESET %c(to move(%d/%d) %d);best:%d ;reply:%d \n", 
        //    player,i+1,moveCount,move,myBest.score,reply.score);
        if( // maximizinf by selecting opponents less score
            (player == US && myBest.score < reply.score) ||
            // minimizing by letting them select high score
            (player == THEM && myBest.score > reply.score)){
        //    printf("%c SCORE CHANGED (score:%d, best move:%d)!!\n",
        //        player,reply.score,move);
            myBest.score = reply.score;
            if(player == US)
                myBest.move = move;
        }
    }
    return myBest;
}

int ply = 0;
int positions = 0;
int maxPly = 0;

int MinMax(int *board, int side) {

    // check is a win
    // gen all moves for side
    // loop moves, make move, mimax() on move to get score
    // assess bestscore
    // end moves return bestscore
    
    int MoveList[9];
    int MoveCount = 0;
    int bestScore = -2;
    int score = -2;
    int bestMove = -1;
    int Move;
    int index;
    
    if(ply > maxPly) maxPly = ply;  
    positions++;
    
    if(ply > 0) {
        //score = EvalForWin(board, side);
        if(didHeWin(board,side)) {
            //printf("%c WON\n",side);
            //printboard(board);
            score=1;
        }
        if(didHeWin(board,otherPlayer(side))) {
            //printf("%c WON\n",side);
            //printboard(board);
            score=-1;
        }        
        if(score != 0) {                    
            return score;
        }       
    }
    
    // fill Move List
    for(index = 0; index < 9; ++index) {
        if( board[convert9To25[index]] == EMPTY) {
            MoveList[MoveCount++] = convert9To25[index];
        }
    }
    
    // loop all moves
    for(index = 0; index < MoveCount; ++index) {
        Move = MoveList[index];
        board[Move] = side; 
        
        ply++;
        score = -MinMax(board, otherPlayer(side));
        if(score > bestScore) {         
            bestScore = score;  
            bestMove = Move;
        }
        board[Move] = EMPTY;
        ply--;
    }
    
    if(MoveCount==0) {
        bestScore = didHeWin(board, side);   
    }
    
    if(ply!=0)
        return bestScore;   
    else 
        return bestMove;    
}

void nextMove(char player, char board[3][3]){
    int iboard[25];
    int i,j,move;
    pair best;
    initializeBoard(iboard, board);
    
    //printboard(iboard);
    /*
    if(didHeWin(iboard,player) || didHeWin(iboard,otherPlayer(player))) {
        printf("%c start WON\n", player);
        printboard(iboard);
    }
    
    if(isBoardFull(iboard)) {
        printf("start FULL\n");
    }
    */
    
    US = player;
    THEM = otherPlayer(US);

    best = chooseMove(iboard,player);
    convert1dTo2d(best.move);

    //move = MinMax(iboard,player);
    //convert1dTo2d(move);

    //printf("chooseMove: move:%d score:%d\n",best.move, best.score ); 
    //printf("MinMax: move:%d score:%d\n",best.move, best.score ); 
}

int main(void) {

    int i;
    char player;
    char board[3][3];
    char s[3];

    //If player is X, I'm the first player.
    //If player is O, I'm the second player.
    scanf("%c", &player);

    //Read the board now. The board is a 3x3 array filled with X, O or _.
    for(i=0; i<3; i++) {
        scanf("%s[^\n]%*c", board[i]);
    }
    nextMove(player,board);
    return 0;
}

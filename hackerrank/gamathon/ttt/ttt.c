#include <stdio.h>
#include <string.h>
#include <math.h>
#include "stdlib.h"
#include <limits.h>

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

int cellScoreOrdered[9] = {
    4,0,2,6,8,1,3,5,7
    /*50,25,50,
    25,100,25,
    50,25,50*/
};

int convert25To9[25] = {
    -1,-1,-1,-1,-1,
    -1,0,1,2,-1,
    -1,3,4,5,-1,
    -1,6,7,8,-1,
    -1,-1,-1,-1,-1
};
int directions[4] = {1,5,6,4};

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

int timesCalled = 0;

pair chooseMove(int* iboard, int player) {
    ASSERT(player == XPL || player == OPL);
    
    pair myBest = {0,-1};
    pair reply;
    int i, move;
    int moveCount=0, moveList[9];

    //default score
    if(player == US){
        myBest.score = INT_MIN;
    } else {
        myBest.score = INT_MAX;
    }

    timesCalled++;
    pair temp;
    temp.score = 10+timesCalled;
    temp.move = -1;    
    if(didHeWin(iboard,US)) {
        //printf("%c WON\n",US);
        //printf("=====returning{1}====================\n");
        //printboard(iboard);
        temp.score = 10+timesCalled;
        return temp;
    } else if(didHeWin(iboard,THEM)) {
        //printf("%c WON\n",THEM);
        //printf("=====returning{-1}====================\n");
        //printboard(iboard);
        temp.score = -10-timesCalled;
        return temp;
    } else if(isBoardFull(iboard)) {
        //printf("FULL\n");
        //printf("=====returning{0}====================\n");
        temp.score = 0;
        return temp;
    }
    
    // get legal moves
    for(i = 0; i < 9; i++) {
        // used for priority in choosing the cells
        if( iboard[convert9To25[cellScoreOrdered[i]]] == EMPTY) {
            moveList[moveCount++] = convert9To25[cellScoreOrdered[i]];
        }
    }

    // any legal move
    //myBest.move = pickValuedMove(moveList,moveCount);
    //printf("Move by %c;*********************************************\n",player);
    //for(i=0; i < moveCount; i++) {
        //printf("%d ", moveList[i]);
    //}
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
            myBest.move = move;
        }
    }
    return myBest;
}

pair chooseMoveEvaluate (int* iboard, int player) {
    ASSERT(player == XPL || player == OPL);
    
    pair myBest = {0,-1};
    pair reply;
    int i, move;
    int moveCount=0, moveList[9];

    //default score
    if(player == US){
        myBest.score = INT_MIN;
    } else {
        myBest.score = INT_MAX;
    }

    timesCalled++;
    pair temp;
    temp.score = 0;
    temp.move = -1;    
    if(didHeWin(iboard,US)) {
        //printf("%c WON\n",US);
        //printf("=====returning{1}====================\n");
        //printboard(iboard);
        //temp.score = 10+timesCalled;
        temp.score = evaluateBoard(iboard);
        return temp;
    } else if(didHeWin(iboard,THEM)) {
        //printf("%c WON\n",THEM);
        //printf("=====returning{-1}====================\n");
        //printboard(iboard);
        //temp.score = -10-timesCalled;
        temp.score = evaluateBoard(iboard);        
        return temp;
    } else if(isBoardFull(iboard)) {
        //printf("FULL\n");
        //printf("=====returning{0}====================\n");
        //temp.score = 0;
        return temp;
    }
    
    // get legal moves
    for(i = 0; i < 9; i++) {
        if( iboard[convert9To25[cellScoreOrdered[i]]] == EMPTY) {
            moveList[moveCount++] = convert9To25[cellScoreOrdered[i]];
        }
    }

    // for(i = 0; i < 9; i++) {
    //     if( iboard[convert9To25[i]] == EMPTY) {
    //         moveList[moveCount++] = convert9To25[i];
    //     }
    // }

    // any legal move
    //myBest.move = pickValuedMove(moveList,moveCount);
    //printf("Move by %c;*********************************************\n",player);
    //for(i=0; i < moveCount; i++) {
        //printf("%d ", moveList[i]);
    //}
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
            myBest.move = move;
        }
    }
    return myBest;
}

int evaluateLines(const int* board, int i1, int i2, int i3){
    int score = 0;

      // First cell
      if (board[i1] == US) {
         score = 1;
      } else if (board[i1] == THEM) {
         score = -1;
      }
 
      // Second cell
      if (board[i2] == US) {
         if (score == 1) {   // cell1 is US
            score = 10;
         } else if (score == -1) {  // cell1 is THEM
            return 0;
         } else {  // cell1 is empty
            score = 1;
         }
      } else if (board[i2] == US) {
         if (score == -1) { // cell1 is THEM
            score = -10;
         } else if (score == 1) { // cell1 is US
            return 0;
         } else {  // cell1 is empty
            score = -1;
         }
      }
 
      // Third cell
      if (board[i3] == US) {
         if (score > 0) {  // cell1 and/or cell2 is US
            score *= 10;
         } else if (score < 0) {  // cell1 and/or cell2 is THEM
            return 0;
         } else {  // cell1 and cell2 are empty
            score = 1;
         }
      } else if (board[i3] == THEM) {
         if (score < 0) {  // cell1 and/or cell2 is THEM
            score *= 10;
         } else if (score > 1) {  // cell1 and/or cell2 is US
            return 0;
         } else {  // cell1 and cell2 are empty
            score = -1;
         }
      }

    return score;
}

int evaluateBoard(const int* board){
    int score = 0;
    score += evaluateLines(board,6,7,8);
    score += evaluateLines(board,11,12,13);
    score += evaluateLines(board,16,17,18);
    score += evaluateLines(board,6,11,16);
    score += evaluateLines(board,7,12,17);
    score += evaluateLines(board,8,13,18);
    score += evaluateLines(board,6,12,18);
    score += evaluateLines(board,8,12,16);
    //printf("evaluated %d\n",score );
    return score;
}


const int Three_in_a_Row[8][3] = {
{ 0, 1, 2 },
{ 3, 4, 5 },
{ 6, 7, 8 },
{ 0, 3, 6 },
{ 1, 4, 7 },
{ 2, 5, 8 },
{ 0, 4, 8 },
{ 2, 4, 6 }
};
const int Heuristic_Array[4][4] = {
{ 0, -10, -100, -1000 },
{ 10, 0, 0, 0 },
{ 100, 0, 0, 0 },
{ 1000, 0, 0, 0 }
};
 
int evaluatePosition(int* iboard, int player) {
    char opponent = (player == 'X') ? 'O' : 'X', piece;
    int players, others, t = 0, i, j;
    for (i = 0; i < 8; i++) {
        players = others = 0;
        for (j = 0; j < 3; j++) {
            piece = iboard[convert9To25[Three_in_a_Row[i][j]]];
            if (piece == player)
                players++;
            else if (piece == opponent)
                others++;
            else
                t += 5;
        }
        t += Heuristic_Array[players][others];
    }
    return t;
}

pair chooseMoveAB (int* iboard, int player, int alpha, int beta) {
    ASSERT(player == XPL || player == OPL);
    
    pair myBest = {0,-1};
    pair reply;
    int i,j, move;
    int moveCount=0, moveList[9];

    //default score
    if(player == US){
        myBest.score = alpha;
    } else {
        myBest.score = beta;
    }


    timesCalled++;
    pair temp;
    //temp.score = evaluateBoard(iboard);
    temp.move = -1;

    // if(level == 0){
    //     temp.score = evaluateBoard(iboard);
    //     return temp;
    // }

    if(didHeWin(iboard,US)) {
        //printf("%c WON\n",US);
        //printboard(iboard);        
        //temp.score = evaluateBoard(iboard);
        temp.score = evaluatePosition(iboard,US);
        return temp;
    } else if(didHeWin(iboard,THEM)) {
        //printf("%c WON\n",THEM);
        //printboard(iboard);          
        //temp.score = evaluateBoard(iboard);
        temp.score = evaluatePosition(iboard,US);
        return temp;
    } else if(isBoardFull(iboard)) {
        //printf("FULL\n");
        //printboard(iboard);          
        temp.score = evaluatePosition(iboard,US);
        return temp;
    }
    
    // get legal moves in25
    for(i = 0; i < 9; i++) {
        if( iboard[convert9To25[i]] == EMPTY) {
            moveList[moveCount++] = convert9To25[i];
        }
    }

    // for(i = 0; i < 9; i++) {
    //     if( iboard[convert9To25[cellScoreOrdered[i]]] == EMPTY) {
    //         moveList[moveCount++] = convert9To25[cellScoreOrdered[i]];
    //     }
    // }

    myBest.move = moveList[0];
    for(i=0; i < moveCount; i++) {
        move = moveList[i];
        iboard[move] = player;
        reply = chooseMoveAB(iboard, otherPlayer(player),alpha,beta);

        iboard[move] = EMPTY;
        // maximum lower bound of possible solutions
        if(player == US && myBest.score < reply.score){
            alpha = reply.score;
            myBest.score = reply.score;
            myBest.move = move;            
        }
        // minimum upper bound of possible solutions 
        else if (player == THEM && myBest.score > reply.score){
            beta = reply.score;
            myBest.score = reply.score;
            myBest.move = move;            
        }

        if(alpha >= beta){
            return myBest;
        }
    }
    return myBest;
}

pair chooseMoveABDepth (int* iboard, int player, int alpha, int beta) {
    ASSERT(player == XPL || player == OPL);
    
    pair myBest = {0,-1};
    pair reply;
    int i,j, move;
    int moveCount=0, moveList[9];

    //default score
    if(player == US){
        myBest.score = alpha;
    } else {
        myBest.score = beta;
    }


    timesCalled++;
    pair temp;
    //temp.score = evaluateBoard(iboard);
    temp.move = -1;

    // if(level == 0){
    //     temp.score = evaluateBoard(iboard);
    //     return temp;
    // }

    if(didHeWin(iboard,US)) {
        //printf("%c WON\n",US);
        //printboard(iboard);        
        //temp.score = evaluateBoard(iboard);
        temp.score = evaluatePosition(iboard,US);
        return temp;
    } else if(didHeWin(iboard,THEM)) {
        //printf("%c WON\n",THEM);
        //printboard(iboard);          
        //temp.score = evaluateBoard(iboard);
        temp.score = evaluatePosition(iboard,US);
        return temp;
    } else if(isBoardFull(iboard)) {
        //printf("FULL\n");
        //printboard(iboard);          
        temp.score = evaluatePosition(iboard,US);
        return temp;
    }
    
    // get legal moves in25
    for(i = 0; i < 9; i++) {
        if( iboard[convert9To25[i]] == EMPTY) {
            moveList[moveCount++] = convert9To25[i];
        }
    }

    // for(i = 0; i < 9; i++) {
    //     if( iboard[convert9To25[cellScoreOrdered[i]]] == EMPTY) {
    //         moveList[moveCount++] = convert9To25[cellScoreOrdered[i]];
    //     }
    // }

    myBest.move = moveList[0];
    for(i=0; i < moveCount; i++) {
        move = moveList[i];
        iboard[move] = player;
        
        reply = chooseMoveAB(iboard, otherPlayer(player),alpha,beta);

        iboard[move] = EMPTY;
        // maximum lower bound of possible solutions
        if(player == US && myBest.score < reply.score){
            alpha = reply.score;
            myBest.score = evaluatePosition(iboard,US);
            myBest.move = move;            
        }
        // minimum upper bound of possible solutions 
        else if (player == THEM && myBest.score > reply.score){
            beta = reply.score;
            myBest.score = reply.score;
            myBest.move = move;            
        }

        if(alpha >= beta){
            return myBest;
        }
    }
    return myBest;
}

void nextMove(char player, char board[3][3]){
    int iboard[25];
    int i,j,move;
    pair best;
    initializeBoard(iboard, board);
    
    US = player;
    THEM = otherPlayer(US);

    timesCalled=0;
    //printboard(iboard); 
    best = chooseMoveAB(iboard,player,INT_MIN,INT_MAX);
    convert1dTo2d(best.move);
    printf("chooseMoveAB timesCalled: %d bestMove:%d\n", timesCalled,best.move);

    timesCalled=0;
    //printboard(iboard); 
    best = chooseMove(iboard,player);
    convert1dTo2d(best.move);
    printf("chooseMove timesCalled: %d bestMove:%d\n", timesCalled,best.move);

    timesCalled=0;
    //printboard(iboard); 
    best = chooseMoveEvaluate(iboard,player);
    convert1dTo2d(best.move);
    printf("chooseMoveEvaluate timesCalled: %d bestMove:%d\n", timesCalled,best.move);    

    timesCalled=0;
    //printboard(iboard); 
    best = chooseMoveABDepth(iboard,player,INT_MIN,INT_MAX);
    convert1dTo2d(best.move);
    printf("chooseMoveAB timesCalled: %d bestMove:%d\n", timesCalled,best.move);    

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


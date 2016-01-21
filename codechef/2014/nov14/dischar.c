
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "stdlib.h"
#include <limits.h>

#define NO_OF_CHARS 259

int longestUniqueSubsttr(char *str)
{
    int n = strlen(str);
    int cur_len = 1;  // To store the lenght of current substring
    int max_len = 1;  // To store the result
    int prev_index;  // To store the previous index
    int i;
    int *visited = (int *)malloc(sizeof(int)*NO_OF_CHARS);
 
    /* Initialize the visited array as -1, -1 is used to indicate that
       character has not been visited yet. */
    for (i = 0; i < NO_OF_CHARS;  i++)
        visited[i] = -1;
 
    /* Mark first character as visited by storing the index of first
       character in visited array. */
    visited[str[0]] = 0;
 
    /* Start from the second character. First character is already processed
       (cur_len and max_len are initialized as 1, and visited[str[0]] is set */
    for (i = 1; i < n; i++)
    {
        prev_index =  visited[str[i]];
 
        /* If the currentt character is not present in the already processed
           substring or it is not part of the current NRCS, then do cur_len++ */
        if (prev_index == -1 || i - cur_len > prev_index)
            cur_len++;
 
        /* If the current character is present in currently considered NRCS,
           then update NRCS to start from the next character of previous instance. */
        else
        {
            /* Also, when we are changing the NRCS, we should also check whether
              length of the previous NRCS was greater than max_len or not.*/
            if (cur_len > max_len)
                max_len = cur_len;
 
            cur_len = i - prev_index;
        }
 
        visited[str[i]] = i; // update the index of current character
    }
 
    // Compare the length of last NRCS with max_len and update max_len if needed
    if (cur_len > max_len)
        max_len = cur_len;
 
 
    free(visited); // free memory allocated for visited
 
    return max_len;
}

int dischar(char *str)
{
    int n = strlen(str);
    int cur_len = 0; 
    int i;
    int *visited = (int *)malloc(sizeof(int)*NO_OF_CHARS);
 
    for (i = 0; i <= NO_OF_CHARS;  i++)
        visited[i] = -1;

     for (i = 0; i < n;  i++)
        if(visited[str[i]] == -1){
            cur_len++;
            visited[str[i]]++;
            //printf("adding %c\n",str[i] );
        }
 
    free(visited); // free memory allocated for visited
 
    return cur_len;
}

int main(void) {

    int i,j;
    int testcases,cur_len;
    char c;

    int *visited = (int *)malloc(sizeof(int)*NO_OF_CHARS);
    for (i = 0; i <= NO_OF_CHARS;  i++)
        visited[i] = -1;

    scanf("%d", &testcases);
    //fflush(stdin);
    j = 0;
    cur_len = 0;

    while((c=getchar())!=EOF)
    {
        j++;
        //printf(" %d %d\n",j,c);
        if(c!=13 && j>2){
            //printf("        %d %d\n",j,c);
            if(c==10) {
                printf("%d\n",cur_len);
                for (i = 0; i <= NO_OF_CHARS;  i++)
                    visited[i] = -1;
                cur_len = 0;
            } else  if(visited[c] == -1){
                //printf("(%d) ",c);
                cur_len++;
                visited[c]++;
            }
        }    
    }
    return 0;
}


int oldmain(void) {

    int i;
    int testcases;
    char seq[100002];

    scanf("%d", &testcases);

    for(i=0; i<testcases; i++) {
        scanf("%c", seq);
        fflush(stdin);
        //printf("%s\n", seq);
        //printf("longestUniqueSubsttr %d\n",longestUniqueSubsttr(seq));
        printf("%d\n",dischar(seq));
    }

    
    return 0;
}

/*

clear && cd /cygdrive/c/Users/jdurairaj/Documents/puzzles/codechef/nov14/ && rm -rf dischar && gcc dischar.c -o dischar && ./dischar.exe < input.in


*/
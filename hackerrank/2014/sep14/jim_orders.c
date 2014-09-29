#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

typedef struct set_struct {
    int start_time;
    int time_taken;
    int time_at;
    int index;
} set;

void sort(set arr[], int size);
void quicksort(set arr[], int low, int high);
int partition(set arr[], int low, int high);
void swapit(set *a, set *b);

#define MAX_N 1001
set inputs[MAX_N];
int main() {

    /* Enter your code here. Read input from STDIN. Print output to STDOUT */
    int i,n;
    scanf("%d", &n);
    for(i=0;i<n;i++){
        scanf("%d", &inputs[i].start_time);
        scanf("%d", &inputs[i].time_taken);
        inputs[i].time_at = inputs[i].start_time + inputs[i].time_taken;
        inputs[i].index = i;
        //printf("%d,%d\n",inputs[i].start_time,inputs[i].time_taken);
    }
    sort(inputs, n);

    for(i=0;i<n;i++){
        printf("%d ", inputs[i].index+1);
    }
    printf("\n");
    return 0;
}

void sort(set arr[], int size) {
    quicksort(arr, 0, size-1);
}

void quicksort(set arr[], int low, int high) {
    if (low > high)
        return;

    int p = partition(arr, low, high);
    //printf("=> %d\n",p);
    quicksort(arr, low, p-1);
    quicksort(arr, p+1, high);
}

int partition(set arr[], int low, int high) {
    set pivot = arr[high];
    int pIndex = low;
    int i;
    int swap;
    for(i = low; i < high; i++) {
        if(arr[i].time_at <= pivot.time_at) {
            swapit(&arr[i],&arr[pIndex]);
            pIndex++;
        }
    }
    swapit(&arr[pIndex],&arr[high]);

    return pIndex;
}

void swapit(set *a, set *b){
    set t;
    t.index=a->index;  t.start_time=a->start_time; t.time_taken=a->time_taken; t.time_at=a->time_at;
    a->index=b->index ;a->start_time=b->start_time; a->time_taken=b->time_taken; a->time_at=b->time_at;
    b->index=t.index;  b->start_time=t.start_time; b->time_taken=t.time_taken; b->time_at=t.time_at;
}

//2015004075_김태형_11802
#include<stdio.h>
#include<stdlib.h>

int main(){
    int range_keys, num_keys, num_ranges, size, i, element, sum;
    int start, end;
    int result = 0;
    int *acc_idx;
    int *ranges;
    //input session
    scanf("%d %d %d", &num_keys, &range_keys,  &num_ranges);
    size = range_keys + 1;
    acc_idx = (int*)calloc(size, sizeof(int));
    ranges = (int*)calloc(2 * num_ranges, sizeof(int));
    for(i = 0; i < num_ranges; i++){
        scanf("%d %d", &ranges[2*i], &ranges[2*i + 1]);
    }
    for(i = 0; i < num_keys; i++){
        scanf("%d", &element);
        acc_idx[element] += 1; 
    }

    for(i = 1; i < size; i++){
        acc_idx[i] += acc_idx[i-1];
    }
    
    for(i = 0; i < num_ranges; i++){
        start = ranges[2*i];
        end = ranges[2*i+1];
        if (start == 0) sum = acc_idx[end];
        else sum = acc_idx[end] - acc_idx[start-1];
        if (sum < 0) sum = 0;
        printf("%d\n", sum);
    }
    free(acc_idx);
    free(ranges);
    return 0;
}
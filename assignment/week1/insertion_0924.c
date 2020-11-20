//2015004075_김태형_
#include <stdio.h>
#include <stdlib.h>
int main(){
    int n, i, j, temp;
    int *arr;

    // 배열의 길이 입력받고 동적할당 
    scanf("%d",&n);
    arr = (int *)malloc(sizeof(int) * n);
    for(i = 0; i < n; i++){
        scanf("%d",&temp);
        arr[i] = temp;
    }

    for(i = 1; i < n; i++){
        temp = arr[i];
        j = i-1;
        while(j>=0 && temp >= arr[j]){
            arr[j+1] = arr[j];
            j = j-1;
        }
        arr[j + 1] = temp;
    }

    for(i = 0; i < n; i++){
        printf("%d\n", arr[i]);
    }
    //cout<<endl;
    free(arr);
    return 0;
}
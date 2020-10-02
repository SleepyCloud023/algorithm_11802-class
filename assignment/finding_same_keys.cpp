#include<stdio.h>
#include<stdlib.h>

int main(){
    int m, n, size, i, element;
    int result = 0;
    int *dict;
    //input session
    scanf("%d %d", &m, &n);
    size = m;
    if (m < n) size = n;
    dict = (int*)calloc(size, sizeof(bool));
    for(i = 0; i < m; i++){
        scanf("%d", &element);
        dict[element] = true;
    }
    for(i = 0; i < n; i++){
        scanf("%d", &element);
        if(dict[element]) result++;
    }
    printf("%d", result);
    return 0;
}
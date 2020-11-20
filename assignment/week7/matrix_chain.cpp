//2015004075_김태형_11802
#include<stdio.h>
#include<stdlib.h>

void spaced_print(int **s, int i, int j){
    if (i == j){
        printf("%d ", i+1);
    }
    else{
        printf("( ");
        spaced_print(s, i, s[i][j]);
        spaced_print(s, s[i][j] + 1, j);
        printf(") ");
    }
}

int main(){
    int num_matrix, i, j, l, k, element;
    int *p, **m, **s;
    //input session
    scanf("%d", &num_matrix);
    p = (int*)calloc(num_matrix + 1, sizeof(int));
    for(i = 0; i < num_matrix + 1; i++){
        scanf("%d", &element);
        p[i] = element;
    }
    m = (int**)calloc(num_matrix, sizeof(int*));
    s = (int**)calloc(num_matrix, sizeof(int*));
    for(i = 0; i < num_matrix; i++){
        m[i] = (int*)calloc(num_matrix, sizeof(int));
        s[i] = (int*)calloc(num_matrix, sizeof(int));
        m[i][i] = 0;
    }
    // j - i + 1 = l, i ... j 인덱스 사이의 개수: l
    for(l = 2; l <= num_matrix; l++){
        for(i = 0; i <= num_matrix - l; i++){
            j = i + l - 1;
            m[i][j] = 0x7fffffff;
            for(k = i; k <= j - 1; k++){
                // Ai Ai+1 Ai+2 ... Ak * Ak+1 Ak+2 ... Aj, pi * pk+1 * pj+1
                element = m[i][k] + m[k+1][j] + p[i] * p[k+1] * p[j+1];
                if (element < m[i][j]){
                    m[i][j] = element;
                    s[i][j] = k;
                }
            }
            //printf("%d %d %d \n",i, j, m[i][j]);
        }
    }
    printf("%d\n",m[0][num_matrix - 1]);
    spaced_print(s, 0, num_matrix - 1);
    return 0;
}
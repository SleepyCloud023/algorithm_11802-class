//2015004075_김태형_11802
#include<stdio.h>
#include<stdlib.h>

void reverse_print(int* l1, int* l2, int n_station, int l_last){
    if (n_station >= 0){
        if (l_last == 1){
            reverse_print(l1, l2, n_station - 1, l1[n_station]);
        }
        if (l_last == 2){
            reverse_print(l1, l2, n_station - 1, l2[n_station]);
        }
        printf("%d %d\n", l_last, n_station + 1);
    }
}

int main(){
    int n_station, e1, e2, x1, x2, i, j, u_path, d_path;
    int *a1, *a2, *t1, *t2, *s1, *s2, *l1, *l2;
    //input session
    scanf("%d", &n_station);
    scanf("%d %d", &e1, &e2);
    scanf("%d %d", &x1, &x2);
    a1 = (int*)calloc(n_station, sizeof(int));
    a2 = (int*)calloc(n_station, sizeof(int));
    s1 = (int*)calloc(n_station, sizeof(int));
    s2 = (int*)calloc(n_station, sizeof(int));
    l1 = (int*)calloc(n_station, sizeof(int));
    l2 = (int*)calloc(n_station, sizeof(int));
    t1 = (int*)calloc(n_station - 1, sizeof(int));
    t2 = (int*)calloc(n_station - 1, sizeof(int));
    for(i = 0; i < n_station; i++){
        scanf("%d", &j);
        a1[i] = j;
    }
    for(i = 0; i < n_station; i++){
        scanf("%d", &j);
        a2[i] = j;
    }
    for(i = 0; i < n_station - 1; i++){
        scanf("%d", &j);
        t1[i] = j;
    }
    for(i = 0; i < n_station - 1; i++){
        scanf("%d", &j);
        t2[i] = j;
    }
    s1[0] = e1 + a1[0];
    s2[0] = e2 + a2[0];
    for (j = 1; j < n_station; j++){
        //s1
        u_path = s1[j-1];
        d_path = s2[j-1] + t2[j-1];
        if (u_path <= d_path){
            s1[j] = u_path + a1[j];
            l1[j] = 1;
        }
        else{
            s1[j] = d_path + a1[j];
            l1[j] = 2;
        }
        //s2
        u_path = s1[j-1] + t1[j-1];
        d_path = s2[j-1];
        if (u_path <= d_path){
            s2[j] = u_path + a2[j];
            l2[j] = 1;
        }
        else{
            s2[j] = d_path + a2[j];
            l2[j] = 2;
        }
    }
    //exit
    if (s1[n_station - 1] + x1 <= s2[n_station - 1] + x2){
        i = s1[n_station - 1] + x1;
        j = 1;
    }
    else{
        i = s2[n_station - 1] + x2;
        j = 2;
    }
    printf("%d\n", i);
    reverse_print(l1, l2, n_station - 1, j);
    return 0;
}
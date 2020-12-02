//2015004075_김태형_A
#include<stdio.h>
#include<stdlib.h>

void dfs(int root, unsigned short *visited, unsigned short **adj){
    int i, num_adj, next_root;
    if(!visited[root]){
        visited[root] = 1;
        num_adj = adj[root][0];
        for(i = 1; i <= num_adj; i++){
            next_root = adj[root][i];
            dfs(next_root, visited, adj);
        }
    }
}

int main(){
    int num_V, num_E, i, j, k, idx_next;
    int src, dst;
    unsigned short **adj;
    unsigned short *visited;

    int result = 0;

    scanf("%d %d", &num_V, &num_E);
    adj = (unsigned short**)malloc((num_V + 1) * sizeof(unsigned short*));
    
    //input session
    for(i = 0; i <= num_V; i++){
        //adj[i]: adj_nums(n), dst1, dst2, dst3, dst4, ... dst(n)
        adj[i] = (unsigned short*)calloc(num_V + 1, sizeof(unsigned short));    
    }
    visited = adj[0];

    for(i = 0; i < num_E; i++){
        scanf("%d %d", &src, &dst);
        //idx_next = ++adj[src][0];
        //Is it undirected graph?
        adj[src][++adj[src][0]] = (unsigned short)dst;
        adj[dst][++adj[dst][0]] = (unsigned short)src;
    }

    //dfs search
    for(i = 1; i <= num_V; i++){
        if(!visited[i]){
            dfs(i, visited, adj);
            result++;
        }
    }

    //check visit
    // printf("visited info: ");
    // for(i = 1; i <= num_V; i++){
    //     printf("%hu ",visited[i]);
    // }
    // printf("\n");

    // for(i = 1; i <= num_V; i++){
    //     k = adj[i][0];
    //     printf("node %hu's adjacent: ", i);
    //     for(j = 1; j <= k; j++){
    //         printf("%hu ", adj[i][j]);
    //     }
    //     printf("\n");
    // }
    // //fin.
    printf("%d\n", result);
    return 0;
}
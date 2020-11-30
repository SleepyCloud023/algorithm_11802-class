//2015004075_김태형_A
#include<stdio.h>
#include<stdlib.h>

//stack_push ops
void push(unsigned short *stack, int node){
    int idx_top = ++stack[0];
    stack[idx_top] = node;
}

//stack_pop ops
unsigned short pop(unsigned short *stack){
    int idx_top = stack[0]--;
    unsigned short node_popped = stack[idx_top]; 
    
    return node_popped;
}

int main(){
    int num_V, num_E, i, j, k, num_out_degree;
    int idx_next, idx_top, idx_result;
    int src, dst;
    unsigned short **adj;
    unsigned short *stack, *in_degree, *result;

    int cnt_result = 0;

    scanf("%d %d", &num_V, &num_E);
    adj = (unsigned short**)malloc((num_V + 1) * sizeof(unsigned short*));
    //stack[0]: size of stack
    stack = (unsigned short*)calloc(num_V + 1, sizeof(unsigned short));
    in_degree = (unsigned short*)calloc(num_V + 1, sizeof(unsigned short));
    result = (unsigned short*)calloc(num_V + 1, sizeof(unsigned short));
    //input session
    for(i = 1; i <= num_V; i++){
        //adj[i]: adj_nums(n), dst1, dst2, dst3 ... dst(n)
        adj[i] = (unsigned short*)calloc(num_V + 1, sizeof(unsigned short));
        in_degree[i] = 0;
    }

    for(i = 0; i < num_E; i++){
        scanf("%d %d", &src, &dst);
        //out-dgree: adj[src][0] 
        //in-degree: in_degree[node]
        idx_next = ++adj[src][0];
        adj[src][idx_next] = dst;
        // int idx_new = idx_next - 1;
        // while(dst < adj[src][idx_new] && idx_new > 0){
        //     adj[src][idx_new + 1] = adj[src][idx_new];
        //     idx_new--;
        // }
        // adj[src][idx_new + 1] = dst;
        in_degree[dst] += 1;
    }

    //stack init (in_degree[node] == 0) points are pushed
    for(i = 1; i <= num_V; i++){
        if(in_degree[i] == 0){
            //pushed if in_dgree is zero
            push(stack, i);
        }
    }

    //until stack is empty
    while(stack[0]){
        //pop 1 node(:src) from stack
        src = pop(stack);
        //store in result array
        result[cnt_result++] = src;
        num_out_degree = adj[src][0];
        //decrease in-degree of dst iterating outgoing edge of src 
        for(i = 1; i <= num_out_degree; i++){
            dst = adj[src][i];
            //if in-degree of dst is zero, push to stack
            if(in_degree[dst] == 1){
                push(stack, dst);
            }
            in_degree[dst] -= 1;
        }
    }

    if(cnt_result != num_V){
        //DCG case
        printf("0\n");
    }
    else{
        //DAG case
        printf("1\n");
        for(i = 0; i < cnt_result; i++){
            printf("%hu ", result[i]);
        }
    }
    return 0;
}
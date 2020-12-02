//2015004075_김태형_A
#include<stdio.h>
#include<stdlib.h>

int has_cycle = 0;

void merge(unsigned short *arr, int low, int high, int mid);
void merge_sort(unsigned short *arr, int low, int high);

int compare(const void *x, const void *y){
    return *(unsigned short *)x - *(unsigned short *)y;
}

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

void dfs(int root, char *is_visit, unsigned short **adj, unsigned short *stack){
    int num_outgoing = adj[root][0];
    int connected;
    if(is_visit[root] == 0){
        is_visit[root] = 1;
        for(int i = 1; i <= num_outgoing; i++){
            connected = adj[root][i];
            //has cycle
            if(is_visit[connected] == 1){
                has_cycle = 1;
            }
            if(is_visit[connected] == 0){
                dfs(connected, is_visit, adj, stack);
            }
        }
        is_visit[root] = 2;
        push(stack, root);
    }
}

int main(){
    int num_V, num_E, i, j, k, num_out_degree;
    int idx_next, idx_top, idx_result;
    int src, dst;
    unsigned short **adj;
    unsigned short *stack, *in_degree, *result;
    char *is_visit;

    scanf("%d %d", &num_V, &num_E);
    adj = (unsigned short**)malloc((num_V + 1) * sizeof(unsigned short*));
    is_visit = (char*)malloc((num_V + 1) * sizeof(char));
    //stack[0]: size of stack
    stack = (unsigned short*)calloc(num_V + 1, sizeof(unsigned short));
    stack[0] = 0;
    //input session
    for(i = 1; i <= num_V; i++){
        //adj[i]: adj_nums(n), dst1, dst2, dst3 ... dst(n)
        adj[i] = (unsigned short*)calloc(num_V + 1, sizeof(unsigned short));
        adj[i][0] = 0;
        is_visit[i] = 0;
    }

    for(i = 0; i < num_E; i++){
        scanf("%d %d", &src, &dst);
        idx_next = ++adj[src][0];
        adj[src][idx_next] = dst;
    }

    for(i = 1; i <= num_V; i++){
        //sort idx increasing order
        num_out_degree = adj[i][0];
        merge_sort(&adj[i][1], 0, num_out_degree - 1);
    }

    for(i = 1; i <= num_V; i++){
        if(is_visit[i] == 0){
            dfs(i, is_visit, adj, stack);
        }
    }

    if(has_cycle){
        //DCG case
        printf("0\n");
    }
    else{
        //DAG case
        printf("1\n");
        for(i = stack[0]; i > 0; i--){
            printf("%i ", stack[i]);
        }
    }
    return 0;
}


// 분할
void merge_sort(unsigned short *arr, int low, int high){
    // 길이 1짜리 arr은 이미 정렬된 상태
    if (low < high){
        int mid = (low + high) / 2;
        merge_sort(arr, low, mid);
        merge_sort(arr, mid + 1, high);
        merge(arr, low, high, mid);
    }
}
// 합치면서 정렬, 두 arr의 0번째 원소 비교하며 정렬
// 1 <= N <= 100000 이므로 정렬에 사용될 빈 배열의 길이를 100000으로 고정하거나 동적할당
void merge(unsigned short *arr, int low, int high, int mid){
    int idx_left, idx_right, idx_merge, left, right;
    int *space_for_merge = (int*)malloc(sizeof(int) * (high-low + 1));
    //int space_for_merge[100000];
    idx_left = low;
    idx_right = mid + 1;
    idx_merge = 0;

    while(idx_left <= mid && idx_right <= high){
        // left, right = arr[idx_left], arr[idx_right]; => 잘못된 systax... 조심할것
        if (arr[idx_left] <= arr[idx_right]){
            space_for_merge[idx_merge++] = arr[idx_left++];
        }
        else{
            space_for_merge[idx_merge++] = arr[idx_right++];
        }
    }
    //low~ mid 구간이 mid~ high 구간보다 길 때
    while(idx_left <= mid){
        space_for_merge[idx_merge++] = arr[idx_left++];
    }
    //mid~ high 구간이 low~ mid 구간보다 길 때
    while(idx_right <= high){
        space_for_merge[idx_merge++] = arr[idx_right++];
    }

    for(int i=0; i < idx_merge; i++){
        arr[low+i] = space_for_merge[i];
    }
    free(space_for_merge);
}
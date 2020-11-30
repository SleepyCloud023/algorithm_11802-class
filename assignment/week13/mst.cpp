//2015004075_김태형_A
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct _mst
{
    short x;
    short y;
    short weight;
}xy_weight;

typedef struct _node
{
    _node *parent;
    short rank;
}node;

typedef int (*fp)(xy_weight, xy_weight);

void merge(xy_weight *arr, int low, int high, int mid, fp is_left_small);
void merge_sort(xy_weight *arr, int low, int high, fp is_left_small);
int xy_is_left_small(xy_weight left, xy_weight right);
int weight_is_left_small(xy_weight left, xy_weight right);
node* find_set(node *t_node);
void union_set(node *left, node *right);

int main(){
    int num_V, num_E, i, j, k;
    int idx_next, idx_result;
    int src, dst, weight;
    xy_weight *edge_weights, *result;
    xy_weight smallest;

    node **arr_node;
    node *node_src, *node_dst;
    node *p_src, *p_dst;
    idx_next = 0;

    scanf("%d %d", &num_V, &num_E);
    //init session
    edge_weights = (xy_weight*)malloc((num_E) * sizeof(xy_weight));
    result = (xy_weight*)malloc((num_V - 1) * sizeof(xy_weight));
    arr_node = (node **)calloc(num_V + 1 , sizeof(node*));
    for(i = 1; i <= num_V; i++){
        arr_node[i] = (node*)malloc(sizeof(node));
        arr_node[i]->parent = arr_node[i];
        arr_node[i]->rank = 0;
    }
    //input_session
    for(i = 0; i < num_E; i++){
        scanf("%d %d %d", &src, &dst, &weight);
        if(src > dst){
            //swap
            k = dst; dst = src; src = k;
        }
        edge_weights[i].x = src;
        edge_weights[i].y = dst;
        edge_weights[i].weight = weight;
    }

    //merge sort is stable
    //sort by x,y by increasing order
    merge_sort(edge_weights, 0, num_E - 1, xy_is_left_small);
    //sort by weight increasing order
    merge_sort(edge_weights, 0, num_E - 1, weight_is_left_small);

    //find V-1 edges
    for(i = 0; i < num_V - 1; i++){
        while(true){
            smallest = edge_weights[idx_next++];
            node_src = arr_node[smallest.x]; 
            node_dst = arr_node[smallest.y];
            p_src = find_set(node_src);
            p_dst = find_set(node_dst);
            if(p_src != p_dst) break;
        }
        union_set(p_src, p_dst);
        result[i] = smallest;
    }

    printf("%d\n", num_V - 1);
    for(i = 0; i < num_V - 1; i++){
        xy_weight t = result[i];
        printf("%i %i %i\n", t.x, t.y, t.weight);
    }

    return 0;
}

//find set ops
node* find_set(node *t_node){
    //path compression ver.
    if(t_node->parent != t_node){
        t_node->parent = (find_set(t_node->parent));
    }
    return t_node->parent;
}

//union set ops
void union_set(node *x, node *y){
    if (x->rank > y->rank){
        y->parent = x;
    }
    else{
        x->parent = y;
        if(x->rank == y->rank){
            y->rank += 1;
        }
    }
}


// 분할
void merge_sort(xy_weight *arr, int low, int high, fp is_left_small){
    // 길이 1짜리 arr은 이미 정렬된 상태
    if (low < high){
        int mid = (low + high) / 2;
        merge_sort(arr, low, mid, is_left_small);
        merge_sort(arr, mid + 1, high, is_left_small);
        merge(arr, low, high, mid, is_left_small);
    }
}

// 합치면서 정렬, 두 arr의 0번째 원소 비교하며 정렬
// 1 <= N <= 499500 이므로 동적할당
void merge(xy_weight *arr, int low, int high, int mid, fp is_left_small){
    int idx_left, idx_right, idx_merge, left, right;
    xy_weight *space_for_merge = (xy_weight*)malloc(sizeof(xy_weight) * (high - low + 1));
    
    idx_left = low;
    idx_right = mid + 1;
    idx_merge = 0;

    while(idx_left <= mid && idx_right <= high){
        // left, right = arr[idx_left], arr[idx_right]; => 잘못된 systax... 조심할것
        if (is_left_small(arr[idx_left] , arr[idx_right])){
            //memcpy is needed?
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

//return 1 if left.x <= right.x or (left.x == right.x and left.y <= right.y)
int xy_is_left_small(xy_weight left, xy_weight right){
    int is_small = 0;
    if(left.x < right.x) is_small = 1;
    if(left.x == right.x && left.y < right.y) is_small = 1;
    return is_small;
}

//return 1 if left.weight < right.weight
int weight_is_left_small(xy_weight left, xy_weight right){
    int is_small = 0;
    if(left.weight <= right.weight) is_small = 1;
    return is_small;
}


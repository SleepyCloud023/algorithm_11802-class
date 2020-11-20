//2015004075_김태형_11802
#include <stdio.h>
#include <stdlib.h>

// build min_heap
void build_heap(int *arr, int size);
void heapify(int *arr, int root, int size);
void heap_sort(int *arr, int size);

int main(){
    int n, k, i;
    int *arr;

    // input session
    scanf("%d %d", &n, &k);
    arr = (int*)malloc(sizeof(int) * n);

    for(i = 0; i < n; i++){
        scanf("%d", &arr[i]);
    }

    for(i = 0; i < n; i++){
        arr[i] = arr[i];
    }

    // build max-heap
    build_heap(arr, n);
    heap_sort(arr, n);

    for(i = 0; i < k; i++){
        printf("%d ", arr[i]);
    }
    printf("\n");
    for(i = k; i < n; i++){
        printf("%d ", arr[i]);
    }
    
    free(arr);
    return 0;
}

void build_heap(int *arr, int size){
    int i;
    int last_parent_node = (size / 2) - 1;
    for (i = last_parent_node; i >= 0; i--){
        heapify(arr, i, size);
    }
}
void heapify(int *arr, int idx_root, int size){
    int left_child, root, right_child, has_left, has_right;
    int idx_min = idx_root;
    int idx_left = idx_root * 2 + 1;
    int idx_right = idx_root * 2 + 2;

    has_left = idx_left < size;
    has_right = idx_right < size;

    root = arr[idx_root];
    if (has_left) left_child = arr[idx_left];
    if (has_right) right_child = arr[idx_right];
    
    // min heap
    if (has_left && arr[idx_min] > left_child){
        idx_min = idx_left;
    }
    if (has_right && arr[idx_min] > right_child){
        idx_min = idx_right;
    }

    if (idx_min != idx_root){
        arr[idx_root] = arr[idx_min];
        arr[idx_min] = root;
        heapify(arr, idx_min, size);
    }
    
}

// min heap이면 decreasing order로 정렬
void heap_sort(int *arr, int size){
    // pop root node, swap last_idx node, reduce size of heap
    // repeat until size of heap becomes 1
    int root_node;
    while(size >= 2){
        root_node = arr[0];
        arr[0] = arr[size-1];
        arr[size-1] = root_node;
        size--;
        heapify(arr, 0, size);
    }
}
//2015004075_김태형_11802
#include <stdio.h>
#include <stdlib.h>

// build max_heap
void build_heap(int *arr, int size);
void heapify(int *arr, int root, int size);
void heap_sort(int *arr, int size);
void heap_insert(int *arr, int size, int element);
int heap_pop(int *arr, int size);

int main(){
    int input, i;
    int oper1, oper2;
    int *prior_q, *extracted;
    int max_size = 100000;
    prior_q = (int*)malloc(sizeof(int) * max_size);
    extracted = (int*)malloc(sizeof(int) * max_size);

    bool terminate = false;
    int size = 0;
    int size_ext = 0;
    // input section
    while(!terminate){
        scanf("%d", &input);
        switch (input)
        {
        case 0: // 프로그램 종료, 1st line: 추출된 elements 출력, 2nd line: q에 남은 elements 출력
            for(i = 0; i < size_ext; i++){
                printf("%d ", extracted[i]);
            }
            printf("\n");
            for(i =0; i < size; i++){
                printf("%d ", prior_q[i]);
            }
            terminate = true;
            break;
        case 1: // prior_q에 element insert
            scanf("%d", &oper1);
            size++;
            heap_insert(prior_q, size, oper1);
            break;
        
        case 2: // prior_q의 popped element를 extracted 배열에 저장
            extracted[size_ext] = heap_pop(prior_q, size);
            size_ext++;
            size--;
            break;

        case 3: // prior_q[oper1] = oper2, max_heap 유지
            scanf("%d %d", &oper1, &oper2);
            i = oper1 - 1;
            if (prior_q[i] < oper2){
                heap_insert(prior_q, i + 1, oper2);
            }
            else{
                prior_q[i] = oper2;
                heapify(prior_q, i, size);
            }
            break;
        
        default:
            break;
        }
        
        
    }

    free(prior_q);
    free(extracted);
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
    
    // max heap :: test case 2, 4, 6 wrong answer 의 경우 자식 노드의 값이 같을때 오른쪽 자식을 선택해주면 pass...;;;
    if (has_right && arr[idx_min] < right_child){
        idx_min = idx_right;
    }
    if (has_left && arr[idx_min] < left_child){
        idx_min = idx_left;
    }
    if (idx_min != idx_root){
        arr[idx_root] = arr[idx_min];
        arr[idx_min] = root;
        heapify(arr, idx_min, size);
    }
    
}

// min heap이면 decreasing order로 정렬
// max heap이면 increasing order
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

void heap_insert(int *arr, int size, int element){
    int temp;
    int child_idx = size - 1;
    int parent_idx = (child_idx - 1) / 2;
    arr[child_idx] = element;
    // parent node 들과의 비교
    while(arr[parent_idx] < arr[child_idx] && child_idx != 0){
        temp = arr[parent_idx];
        arr[parent_idx] = arr[child_idx];
        arr[child_idx] = temp;        
        child_idx = parent_idx;
        parent_idx = (child_idx - 1) / 2;
    }
}

int heap_pop(int *arr, int size){
    int root_node;
    root_node = arr[0];
    arr[0] = arr[size-1];
    heapify(arr, 0, size - 1);
    return root_node;
}
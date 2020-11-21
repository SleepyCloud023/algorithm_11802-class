//2015004075_김태형_11802
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct 
{
    char chars[5];
    int freq;
    node *left;
    node *right;
}node;

void build_heap(node *arr, int size);
void heapify(node *arr, int root, int size);
node heappop(node *arr, int size);
int dfs_search(node *root_node, int level);

int main(){
    int num_char, i, j,freq, size;
    node *min_heap;
    int origin_bit;
    int total_bits = 0;
    int total_compressed_bits = 0;
    char alpha_4[5];

    //input session
    scanf("%d", &num_char);
    size = num_char;
    min_heap = (node*)calloc(num_char, sizeof(node));
    for(i = 0; i < num_char; i++){
        scanf("%s %d", alpha_4, freq);
        strcpy(min_heap[i].chars, alpha_4);
        min_heap[i].freq = freq;
        min_heap[i].left = NULL;
        min_heap[i].right = NULL;
    }
    scanf("%d", &total_bits);

    //calculate origin bits
    j = num_char;
    while(j){
        origin_bit += 1;
        j >>= 1;
    }
    total_bits *= origin_bit;

    // construct huffman tree
    while(size > 1){
        
    }


    total_compressed_bits = dfs_search(&min_heap[0], 0);
    printf("%d\n", total_bits);
    printf("%d\n", total_compressed_bits);
    return 0;
}


int dfs_search(node *root_node, int level){
    int compressed_bits = 0;
    if (root_node->left == NULL && root_node->right == NULL){
        compressed_bits = level * root_node->freq;
    }
    else{
        compressed_bits = dfs_search(root_node->left, level + 1) + dfs_search(root_node->right, level + 1);
    }
    free(root_node);
    return compressed_bits;
}

void build_heap(node *arr, int size){
    int i;
    int last_parent_node = (size / 2) - 1;
    for (i = last_parent_node; i >= 0; i--){
        heapify(arr, i, size);
    }
}

void heapify(node *arr, int idx_root, int size){
    node left_child, root, right_child; 
    int has_left, has_right;
    int idx_min = idx_root;
    int idx_left = idx_root * 2 + 1;
    int idx_right = idx_root * 2 + 2;

    has_left = idx_left < size;
    has_right = idx_right < size;

    root = arr[idx_root];
    if (has_left) left_child = arr[idx_left];
    if (has_right) right_child = arr[idx_right];
    
    // min heap
    if (has_left && arr[idx_min].freq > left_child.freq){
        idx_min = idx_left;
    }
    if (has_right && arr[idx_min].freq > right_child.freq){
        idx_min = idx_right;
    }

    if (idx_min != idx_root){
        arr[idx_root] = arr[idx_min];
        arr[idx_min] = root;
        heapify(arr, idx_min, size);
    }
    
}

//수정 필요
void heap_insert(node *arr, int size, node element){
    node temp;
    int child_idx = size - 1;
    int parent_idx = (child_idx - 1) / 2;
    arr[child_idx] = element;
    // parent node 들과의 비교
    while(arr[parent_idx].freq < arr[child_idx].freq && child_idx != 0){
        temp->freq = arr[parent_idx];
        arr[parent_idx] = arr[child_idx];
        arr[child_idx] = temp;        
        child_idx = parent_idx;
        parent_idx = (child_idx - 1) / 2;
    }
}

node heappop(node *arr, int size){
    node temp = arr[0];
    arr[0] = arr[size-1];
    heapify(arr, 0, size - 1);
    return temp;
}
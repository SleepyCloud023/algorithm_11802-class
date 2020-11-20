//2015004075_김태형_11802
#include<stdio.h>
#include<stdlib.h>

typedef struct 
{
    char chars[5];
    int freq;
}node;

void build_heap(int *arr, int size);
void heapify(int *arr, int root, int size);
void heappop(int *arr, int size);

int main(){
    int num_char, i, j;
    int *freq_chars, *compressed_bits;
    int origin_bit;
    int total_bits = 0;
    int total_compressed_bits = 0;
    char alpha_4[5];
    //input session
    scanf("%d", &num_char);
    freq_chars = (int*)calloc(num_char, sizeof(int));
    compressed_bits = (int*)calloc(num_char, sizeof(int));
    for(i = 0; i < num_char; i++){
        scanf("%s %d", alpha_4, &freq_chars[i]);
    }
    scanf("%d", &total_bits);

    //calculate origin bits
    j = num_char;
    while(j){
        origin_bit += 1;
        j >>= 1;
    }
    total_bits *= origin_bit;

    //calculate compressed bits



    for(i = 0; i < num_char; i++){
        total_compressed_bits += freq_chars[i] * compressed_bits[i];
    }
    printf("%d\n", total_bits);
    printf("%d\n", total_compressed_bits);
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

int heappop(int *)
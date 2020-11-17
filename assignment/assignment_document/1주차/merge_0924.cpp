//2015004075_김태형_11802
#include <stdio.h>
#include <iostream>

void merge(int *arr, int low, int high, int mid);
void merge_sort(int *arr, int low, int high);

int main(){
    int n, i, j, temp;
    int *arr;

    // input section
    std::cin>>n;
    arr = new int[n];
    for(i = 0; i < n; i++){
        std::cin>>arr[i];
    }
    // sort
    merge_sort(arr, 0, n-1);

    for(i = 0; i < n; i++){
        std::cout<<arr[i]<<std::endl; 
    }
    delete[] arr;
    return 0;
}

// 분할
void merge_sort(int *arr, int low, int high){
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
void merge(int *arr, int low, int high, int mid){
    int idx_left, idx_right, idx_merge, left, right;
    int *space_for_merge = new int[high-low + 1];
    //int space_for_merge[100000];
    idx_left = low;
    idx_right = mid + 1;
    idx_merge = low;

    while(idx_left <= mid && idx_right <= high){
        // left, right = arr[idx_left], arr[idx_right]; => 잘못된 systax... 조심할것
        left = arr[idx_left];
        right = arr[idx_right];
        if (left > right){
            space_for_merge[idx_merge] = left;
            idx_left++;
        }
        else{
            space_for_merge[idx_merge] = right;
            idx_right++;
        }
        idx_merge++;
    }
    //low~ mid 구간이 mid~ high 구간보다 길 때
    while(idx_left <= mid){
        space_for_merge[idx_merge] = arr[idx_left];
        idx_left++;
        idx_merge++;
    }
    //mid~ high 구간이 low~ mid 구간보다 길 때
    while(idx_right <= high){
        space_for_merge[idx_merge] = arr[idx_right];
        idx_right++;
        idx_merge++;
    }

    for(int i=low; i < idx_merge; i++){
        arr[low+i] = space_for_merge[i];
    }

    delete[] space_for_merge;
}
//2015004075_김태형_11802
#include<stdio.h>
#include<stdlib.h>

void reverse_print(int *optimal_divide_amout, int length_rod){
    if (length_rod <= 0) return;
    int i = optimal_divide_amout[length_rod];
    printf("%d ", i);
    reverse_print(optimal_divide_amout, length_rod - i);
}

int main(){
    int length_rod, i, j, price, optimal_price;
    int *price_i;
    int *optimal_price_i;
    int *optimal_divide_amout;
    //input session
    scanf("%d", &length_rod);
    price_i = (int*)calloc(length_rod + 1, sizeof(int));
    optimal_price_i = (int*)calloc(length_rod + 1, sizeof(int));
    optimal_divide_amout = (int*)calloc(length_rod + 1, sizeof(int));
    for(i = 0; i < length_rod; i++){
        scanf("%d", &price);
        price_i[i + 1] = price;
        optimal_price_i[i + 1] = price;
        optimal_divide_amout[i + 1] = i + 1; 
    }
    for(i = 1; i <= length_rod; i++){
        optimal_price = price_i[i];
        for (j = 1; j <= i; j++){
            price = optimal_price_i[j] + optimal_price_i[i - j];
            if (optimal_price < price){
                optimal_price = price;
                optimal_divide_amout[i] = j;
            }
        }
        optimal_price_i[i] = optimal_price;
    }
    printf("%d\n", optimal_price_i[length_rod]);
    reverse_print(optimal_divide_amout, length_rod);
    printf("\n");
    return 0;
}
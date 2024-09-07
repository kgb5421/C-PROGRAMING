#include <stdio.h>

#define MAX_PRODUCTS 100

int main() {
    int productCount;          
    int stock[MAX_PRODUCTS];    
    int* pStock = stock;         

    do {
        printf("상품의 종류를 입력하세요 (1 ~ 100): ");
        scanf("%d", &productCount);
    } while (productCount < 1 || productCount > 100);

    for (int i = 0; i < productCount; i++) {
        printf("상품 ID %d의 입고 수량을 입력하세요: ", i + 1);
        scanf("%d", pStock + i);  
    }

    for (int i = 0; i < productCount; i++) {
        int sales;
        printf("상품 ID %d의 당일 판매 수량을 입력하세요: ", i + 1);
        scanf("%d", &sales);
        *(pStock + i) -= sales;  
    }

    int queryID;
    printf("재고를 확인할 상품 ID를 입력하세요: ");
    scanf("%d", &queryID);

    if (queryID >= 1 && queryID <= productCount) {
        printf("%d\n", *(pStock + (queryID - 1)));
    }
    else {
        printf("유효하지 않은 상품 ID입니다.\n");
        
    }

    for (int i = 0; i < productCount; i++) {
        printf("%d ", *(pStock + i));
    }
    printf("\n");

    return 0;
}
/* 쇼핑몰 재고 관리_#1 */
#include <stdio.h>

#define MAX_PRODUCTS 100

int main() {
    int numProducts;
    int stock[MAX_PRODUCTS] = {0};   // 입고 수량
    int sold[MAX_PRODUCTS] = {0};    // 판매 수량
    int remainingStock[MAX_PRODUCTS] = {0}; // 남은 재고

    // 1. 상품 종류 설정
    printf("관리할 상품의 종류 수를 입력하세요 (1 ~ 100): ");
    scanf_s("%d", &numProducts);

    if (numProducts < 1 || numProducts > MAX_PRODUCTS) {
        printf("상품 종류는 1에서 100 사이여야 합니다.\n");
        return 1;
    }

    // 2. 입고 수량 입력
    printf("\n상품별 입고 수량을 입력하세요:\n");
    for (int i = 0; i < numProducts; i++) {
        printf("ID %d 상품 입고 수량: ", i + 1);
        scanf_s("%d", &stock[i]);
        remainingStock[i] = stock[i]; // 초기 재고 설정
    }

    // 3. 판매 수량 입력
    printf("\n당일 판매 수량을 입력하세요:\n");
    for (int i = 0; i < numProducts; i++) {
        printf("ID %d 상품 판매 수량: ", i + 1);
        scanf_s("%d", &sold[i]);

        // 남은 재고 계산
        remainingStock[i] -= sold[i];
        if (remainingStock[i] < 0) {
            printf("경고: ID %d 상품의 판매 수량이 재고보다 많습니다. 재고는 음수가 됩니다.\n", i + 1);
        }
    }

    // 4. 특정 ID 상품의 재고 확인
    int queryID;
    printf("\n재고를 확인할 상품 ID를 입력하세요 (1 ~ %d): ", numProducts);
    scanf_s("%d", &queryID);

    if (queryID < 1 || queryID > numProducts) {
        printf("잘못된 상품 ID입니다.\n");
    } else {
        printf("ID %d 상품의 남은 재고: %d\n", queryID, remainingStock[queryID - 1]);
    }

    // 5. 전체 재고 출력
    int totalStock = 0;
    for (int i = 0; i < numProducts; i++) {
        totalStock += remainingStock[i];
    }
    printf("전체 재고 수량: %d\n", totalStock);

    return 0;
}

/* 쇼핑몰 재고 관리_#2 */
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
    printf("\n모든 상품의 재고 수량:\n");
    int totalStock = 0;
    for (int i = 0; i < numProducts; i++) {
        printf("ID %d: %d개\n", i + 1, remainingStock[i]);
        totalStock += remainingStock[i];
    }

    // 6. 전체 판매량 계산
    int totalSold = 0;
    for (int i = 0; i < numProducts; i++) {
        totalSold += sold[i];
    }
    printf("\n전체 판매량: %d개\n", totalSold);

    // 7. 전체 판매율 계산
    double totalStockIn = 0; // 전체 입고 수량 합산
    for (int i = 0; i < numProducts; i++) {
        totalStockIn += stock[i];
    }
    double totalSalesRate = (totalSold / totalStockIn) * 100;
    printf("전체 판매율: %.2f%%\n", totalSalesRate);

    // 8. 최대 판매량 및 최소 판매량 상품 출력
    int maxSold = sold[0], minSold = sold[0];
    int maxID = 1, minID = 1;
    for (int i = 1; i < numProducts; i++) {
        if (sold[i] > maxSold) {
            maxSold = sold[i];
            maxID = i + 1;
        }
        if (sold[i] < minSold) {
            minSold = sold[i];
            minID = i + 1;
        }
    }
    printf("\n최대 판매량 상품: ID %d, 판매량 %d개\n", maxID, maxSold);
    printf("최소 판매량 상품: ID %d, 판매량 %d개\n", minID, minSold);

    // 9. 재고 부족 경고
    printf("\n재고 부족 상품 경고 (재고 2 이하):\n");
    for (int i = 0; i < numProducts; i++) {
        if (remainingStock[i] <= 2) {
            printf("ID %d: 재고 %d개\n", i + 1, remainingStock[i]);
        }
    }

    return 0;
}

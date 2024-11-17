/* 쇼핑몰 재고 관리_#3 */
#include <stdio.h>

#define MAX_PRODUCTS 5

int main() {
    int stock[MAX_PRODUCTS] = {0};   // 입고 수량
    int sold[MAX_PRODUCTS] = {0};    // 판매 수량
    int remainingStock[MAX_PRODUCTS] = {0}; // 남은 재고
    int choice, subChoice, productID, quantity;

    while (1) {
        // 메뉴 출력
        printf("\n원하는 메뉴를 선택하세요.\n");
        printf("1. 입고\n");
        printf("2. 판매\n");
        printf("3. 상품현황\n");
        printf("4. 프로그램 종료\n");
        printf("선택: ");
        scanf_s("%d", &choice);

        if (choice == 1) {
            // 1. 입고
            printf("\n1. 전체 상품 입고\n2. 개별 상품 입고\n선택: ");
            scanf_s("%d", &subChoice);

            if (subChoice == 1) {
                // 전체 상품 입고
                printf("\n모든 상품에 입고 수량을 입력하세요:\n");
                for (int i = 0; i < MAX_PRODUCTS; i++) {
                    printf("ID %d 상품 입고 수량: ", i + 1);
                    scanf_s("%d", &quantity);
                    stock[i] += quantity; // 입고 수량 추가
                    remainingStock[i] += quantity; // 재고 수량 업데이트
                }
            } else if (subChoice == 2) {
                // 개별 상품 입고
                printf("\n입고할 상품의 ID를 입력하세요 (1 ~ 5): ");
                scanf_s("%d", &productID);

                if (productID < 1 || productID > MAX_PRODUCTS) {
                    printf("잘못된 상품 ID입니다. 1부터 5까지의 ID를 입력하세요.\n");
                } else {
                    printf("ID %d 상품의 입고 수량을 입력하세요: ", productID);
                    scanf_s("%d", &quantity);
                    stock[productID - 1] += quantity; // 입고 수량 추가
                    remainingStock[productID - 1] += quantity; // 재고 수량 업데이트
                }
            } else {
                printf("잘못된 선택입니다. 다시 입력하세요.\n");
            }
        }
        else if (choice == 2) {
            // 2. 판매
            printf("\n1. 전체 상품 판매\n2. 개별 상품 판매\n선택: ");
            scanf_s("%d", &subChoice);

            if (subChoice == 1) {
                // 전체 상품 판매
                printf("\n모든 상품에 대해 판매 수량을 입력하세요:\n");
                for (int i = 0; i < MAX_PRODUCTS; i++) {
                    printf("ID %d 상품 판매 수량: ", i + 1);
                    scanf_s("%d", &quantity);

                    if (quantity <= remainingStock[i]) {
                        sold[i] += quantity; // 판매 수량 기록
                        remainingStock[i] -= quantity; // 재고 차감
                    } else {
                        printf("경고: ID %d 상품의 판매 수량이 재고보다 많습니다. 재고는 %d개입니다.\n", 
                               i + 1, remainingStock[i]);
                    }
                }
            } else if (subChoice == 2) {
                // 개별 상품 판매
                printf("\n판매할 상품의 ID를 입력하세요 (1 ~ 5): ");
                scanf_s("%d", &productID);

                if (productID < 1 || productID > MAX_PRODUCTS) {
                    printf("잘못된 상품 ID입니다. 1부터 5까지의 ID를 입력하세요.\n");
                } else {
                    printf("ID %d 상품의 판매 수량을 입력하세요: ", productID);
                    scanf_s("%d", &quantity);

                    if (quantity <= remainingStock[productID - 1]) {
                        sold[productID - 1] += quantity; // 판매 수량 기록
                        remainingStock[productID - 1] -= quantity; // 재고 차감
                    } else {
                        printf("경고: ID %d 상품의 판매 수량이 재고보다 많습니다. 재고는 %d개입니다.\n", 
                               productID, remainingStock[productID - 1]);
                    }
                }
            } else {
                printf("잘못된 선택입니다. 다시 입력하세요.\n");
            }
        }
        else if (choice == 3) {
            // 3. 상품현황
            printf("\n상품 현황:\n");
            int maxSold = sold[0], minSold = sold[0];
            int maxSoldID = 1, minSoldID = 1;
            int totalSold = 0; // 총 판매량 계산
            int totalStock = 0; // 총 입고량 계산

            // 상품 현황 출력 및 가장 많이/적게 팔린 상품 계산
            for (int i = 0; i < MAX_PRODUCTS; i++) {
                printf("ID %d 상품 - 입고 수량: %d, 판매 수량: %d, 남은 재고: %d\n", 
                        i + 1, stock[i], sold[i], remainingStock[i]);

                totalSold += sold[i]; // 총 판매량 누적
                totalStock += stock[i]; // 총 입고량 누적

                // 가장 많이 팔린 상품
                if (sold[i] > maxSold) {
                    maxSold = sold[i];
                    maxSoldID = i + 1;
                }
                // 가장 적게 팔린 상품
                if (sold[i] < minSold) {
                    minSold = sold[i];
                    minSoldID = i + 1;
                }
            }

            // 총 판매량 출력
            printf("\n총 판매량: %d\n", totalSold);

            // 판매율 출력
            printf("판매율:\n");
            for (int i = 0; i < MAX_PRODUCTS; i++) {
                if (stock[i] > 0) {
                    double salesRate = (double)sold[i] / stock[i] * 100; // 판매율 계산
                    printf("ID %d 상품 - 판매율: %.2f%%\n", i + 1, salesRate);
                }
            }

            // 전체 판매율 계산
            if (totalStock > 0) {
                double overallSalesRate = (double)totalSold / totalStock * 100; // 전체 판매율 계산
                printf("\n전체 판매율: %.2f%%\n", overallSalesRate);
            }

            // 가장 많이 판매된 상품과 가장 적게 판매된 상품 출력
            printf("\n가장 많이 판매된 상품: ID %d, 판매 수량: %d\n", maxSoldID, maxSold);
            printf("가장 적게 판매된 상품: ID %d, 판매 수량: %d\n", minSoldID, minSold);

            // 재고 부족 상품 한 번에 출력
            printf("\n재고 부족 상품 (남은 재고 2 이하):\n");
            for (int i = 0; i < MAX_PRODUCTS; i++) {
                if (remainingStock[i] <= 2) {
                    printf("ID %d 상품은 재고 부족 (남은 재고: %d)\n", i + 1, remainingStock[i]);
                }
            }

        }
        else if (choice == 4) {
            // 4. 종료
            printf("프로그램을 종료합니다.\n");
            break;
        }
        else {
            printf("잘못된 선택입니다. 다시 입력하세요.\n");
        }
    }

    return 0;
}

/* 쇼핑몰 재고 관리_#3 */
#include <stdio.h>
#include <stdlib.h>

#define MAX_PRODUCTS 5

// 상품 정보를 저장할 구조체 정의
typedef struct {
    int id;               // 상품 ID (일련번호)
    char name[100];       // 상품명
    int price;            // 상품가격
    int stock;            // 재고량
    int sold;             // 판매량
    int totalSalesAmount; // 총판매금액 (판매량 * 가격)
    float salesRate;      // 판매율
} Product;

int main() {
    Product products[MAX_PRODUCTS];  // 5개의 상품 정보 배열
    int choice, productID, quantity;
    float totalSales = 0;  // 전체 판매금액
    float totalStock = 0;  // 전체 입고량
    float totalSold = 0;   // 전체 판매량

    // 상품 초기화
    for (int i = 0; i < MAX_PRODUCTS; i++) {
        products[i].id = i + 1;
        products[i].stock = 0;
        products[i].sold = 0;
        products[i].totalSalesAmount = 0;
        products[i].salesRate = 0;
        products[i].price = 0;  // 가격 초기화
        products[i].name[0] = '\0';  // 상품명 초기화 (빈 문자열)
    }

    while (1) {
        // 메뉴 출력
        printf("\n원하는 메뉴를 선택하세요.\n");
        printf("1. 입고\n");
        printf("2. 판매\n");
        printf("3. 개별상품정보\n");
        printf("4. 전체상품정보\n");
        printf("5. 저장\n");
        printf("6. 불러오기\n");
        printf("7. 종료\n");
        printf("선택: ");
        scanf_s("%d", &choice);

        if (choice == 1) {
            // 1. 입고
            printf("\n입고할 상품 정보를 입력하세요.\n");
            printf("상품 ID (1 ~ 5): ");
            scanf_s("%d", &productID);

            if (productID < 1 || productID > MAX_PRODUCTS) {
                printf("잘못된 상품 ID입니다. 1부터 5까지의 ID를 입력하세요.\n");
            } else {
                if (products[productID - 1].name[0] == '\0') {
                    printf("상품명을 입력하세요: ");
                    scanf_s("%s", products[productID - 1].name, sizeof(products[productID - 1].name));
                }
                printf("입고 수량: ");
                scanf_s("%d", &quantity);
                printf("판매 가격: ");
                scanf_s("%d", &products[productID - 1].price);

                products[productID - 1].stock += quantity; // 입고 수량 추가
                printf("ID %d 상품이 %d개 입고되었습니다.\n", productID, quantity);
            }
        }
        else if (choice == 2) {
            // 2. 판매
            printf("\n판매할 상품의 ID를 입력하세요 (1 ~ 5): ");
            scanf_s("%d", &productID);

            if (productID < 1 || productID > MAX_PRODUCTS) {
                printf("잘못된 상품 ID입니다. 1부터 5까지의 ID를 입력하세요.\n");
            } else {
                printf("판매 수량을 입력하세요: ");
                scanf_s("%d", &quantity);

                if (quantity <= products[productID - 1].stock) {
                    products[productID - 1].sold += quantity; // 판매 수량 추가
                    products[productID - 1].stock -= quantity; // 재고 차감
                    products[productID - 1].totalSalesAmount += quantity * products[productID - 1].price; // 판매금액 누적
                    totalSales += quantity * products[productID - 1].price;
                    totalSold += quantity;
                    printf("ID %d 상품이 %d개 판매되었습니다.\n", productID, quantity);
                } else {
                    printf("경고: 재고가 부족합니다. 현재 재고는 %d개입니다.\n", products[productID - 1].stock);
                }
            }
        }
        else if (choice == 3) {
            // 3. 개별상품정보
            printf("\n개별 상품 정보를 출력합니다.\n");
            printf("상품 ID를 입력하세요 (1 ~ 5): ");
            scanf_s("%d", &productID);

            if (productID < 1 || productID > MAX_PRODUCTS) {
                printf("잘못된 상품 ID입니다. 1부터 5까지의 ID를 입력하세요.\n");
            } else {
                if (products[productID - 1].name[0] == '\0') {
                    printf("상품명: 상품명 없음\n");
                } else {
                    printf("상품명: %s\n", products[productID - 1].name);
                }
                printf("가격: %d원\n", products[productID - 1].price);
                printf("재고 수량: %d개\n", products[productID - 1].stock);
                printf("판매된 금액: %d원\n", products[productID - 1].totalSalesAmount);
            }
        }
        else if (choice == 4) {
            // 4. 전체상품정보
            printf("\n전체 상품 정보를 출력합니다.\n");
            float totalRate = 0;
            float totalRevenue = 0; // 전체 판매금액

            for (int i = 0; i < MAX_PRODUCTS; i++) {
                printf("\nID %d 상품 정보:\n", products[i].id);

                if (products[i].name[0] == '\0') {
                    printf("상품명: 상품명 없음\n");
                } else {
                    printf("상품명: %s\n", products[i].name);
                }

                printf("가격: %d원\n", products[i].price);
                printf("입고량: %d개\n", products[i].stock);
                printf("판매량: %d개\n", products[i].sold);
                printf("총 판매금액: %d원\n", products[i].totalSalesAmount);

                // 판매율 계산 (재고가 0인 경우 0%로 설정)
                if (products[i].stock + products[i].sold > 0) {
                    products[i].salesRate = (float)products[i].sold / (products[i].stock + products[i].sold) * 100;
                } else {
                    products[i].salesRate = 0;  // 판매되지 않은 상품은 판매율 0으로 처리
                }

                totalRate += products[i].salesRate;
                totalRevenue += products[i].totalSalesAmount;
                printf("판매율: %.2f%%\n", products[i].salesRate);
            }

            // 총 판매율 계산
            printf("\n전체 판매율: %.2f%%\n", totalRate / MAX_PRODUCTS);
            printf("전체 판매금액: %.0f원\n", totalRevenue);  // 총 판매된 금액 출력
        }
        else if (choice == 5) {
            // 5. 저장
            printf("\n상품 정보를 저장합니다...\n");
            FILE *file = fopen("products.dat", "wb");
            if (file == NULL) {
                printf("파일 열기에 실패했습니다.\n");
                continue;
            }
            fwrite(products, sizeof(Product), MAX_PRODUCTS, file);
            fclose(file);
            printf("상품 정보가 저장되었습니다.\n");
        }
        else if (choice == 6) {
            // 6. 불러오기
            printf("\n상품 정보를 불러옵니다...\n");
            FILE *file = fopen("products.dat", "rb");
            if (file == NULL) {
                printf("파일이 존재하지 않습니다. 이전에 저장된 데이터가 없습니다.\n");
                continue;
            }
            fread(products, sizeof(Product), MAX_PRODUCTS, file);
            fclose(file);
            printf("상품 정보가 불러와졌습니다.\n");
        }
        else if (choice == 7) {
            // 7. 종료
            printf("프로그램을 종료합니다.\n");
            break;
        }
        else {
            printf("잘못된 선택입니다. 다시 입력하세요.\n");
        }
    }

    return 0;
}

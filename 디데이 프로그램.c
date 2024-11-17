/* 디데이 프로그램(시간처리 함수 활용) */
#include <stdio.h>
#include <time.h>

// 날짜 구조체 정의
typedef struct {
    int year;
    int month;
    int day;
} Date;

// 날짜와 현재 날짜 차이 계산 함수
int calculateDaysLeft(Date targetDate) {
    // 현재 시간 얻기
    time_t now;
    struct tm current;
    time(&now);

    // current를 localtime_s로 변환
    localtime_s(&current, &now);

    // 목표 날짜 설정
    struct tm target = {0};
    target.tm_year = targetDate.year - 1900; // tm_year는 1900년 기준
    target.tm_mon = targetDate.month - 1;    // tm_mon은 0부터 시작
    target.tm_mday = targetDate.day;

    // 목표 날짜와 현재 날짜를 time_t로 변환
    time_t targetTime = mktime(&target);
    double seconds = difftime(targetTime, now);

    // 남은 일수 계산
    return seconds / (60 * 60 * 24); // 초 단위로 계산 후 일수로 변환
}

int main() {
    Date targetDate;

    // 사용자로부터 년, 월, 일 입력받기
    printf("디데이 날짜를 입력하세요:\n");
    printf("년: ");
    scanf_s("%d", &targetDate.year);
    printf("월: ");
    scanf_s("%d", &targetDate.month);
    printf("일: ");
    scanf_s("%d", &targetDate.day);

    // 남은 일수 계산
    int daysLeft = calculateDaysLeft(targetDate);

    // 결과 출력
    if (daysLeft > 0) {
        printf("디데이까지 남은 일수: %d일\n", daysLeft);
    } else if (daysLeft == 0) {
        printf("디데이가 오늘입니다!\n");
    } else {
        printf("디데이는 이미 지났습니다. %d일 지났습니다.\n", -daysLeft);
    }

    return 0;
}

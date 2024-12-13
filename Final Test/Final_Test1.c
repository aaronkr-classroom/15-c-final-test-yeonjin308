//Final_Test1.c
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STUDENTS 100

typedef struct {
    char name[20];
    int korean;
    int english;
    int math;
    int total;
    float average;
    int rank;
} Student;

Student students[MAX_STUDENTS];
int student_count = 0;

void load_data(const char* filename) {
    FILE* file = fopen(filename, "rb");
    if (!file) {
        printf("파일을 열 수 없습니다.\n");
        return;
    }
    fread(&student_count, sizeof(int), 1, file);
    fread(students, sizeof(Student), student_count, file);
    fclose(file);
    printf("데이터를 성공적으로 읽었습니다.\n");
}

void save_data(const char* filename) {
    FILE* file = fopen(filename, "wb");
    if (!file) {
        printf("파일을 열 수 없습니다.\n");
        return;
    }
    fwrite(&student_count, sizeof(int), 1, file);
    fwrite(students, sizeof(Student), student_count, file);
    fclose(file);
    printf("데이터를 성공적으로 저장했습니다.\n");
}

void add_student() {
    if (student_count >= MAX_STUDENTS) {
        printf("학생 목록이 가득 찼습니다.\n");
        return;
    }

    Student s;
    printf("학생 이름: ");
    scanf("%s", s.name);
    printf("국어 점수: ");
    scanf("%d", &s.korean);
    printf("영어 점수: ");
    scanf("%d", &s.english);
    printf("수학 점수: ");
    scanf("%d", &s.math);
    s.total = s.korean + s.english + s.math;
    s.average = s.total / 3.0f;
    students[student_count++] = s;
    printf("학생 정보를 추가했습니다.\n");
}

void calculate_ranks() {
    for (int i = 0; i < student_count; i++) {
        students[i].rank = 1; // 초기화
        for (int j = 0; j < student_count; j++) {
            if (students[i].total < students[j].total) {
                students[i].rank++;
            }
        }
    }
}

void display_grades() {
    if (student_count == 0) {
        printf("학생 정보가 없습니다.\n");
        return;
    }

    calculate_ranks();
    printf("학생 성적 목록:\n");
    printf("이름\t국어\t영어\t수학\t총점\t평균\t등수\n");
    for (int i = 0; i < student_count; i++) {
        printf("%s\t%d\t%d\t%d\t%d\t%.2f\t%d\n",
            students[i].name,
            students[i].korean,
            students[i].english,
            students[i].math,
            students[i].total,
            students[i].average,
            students[i].rank);
    }
}

int main() {
    int choice;
    const char* filename = "students.dat";

    while (1) {
        printf("\n[Menu]\n");
        printf("1. .dat 파일에서 데이터 읽기\n");
        printf("2. 추가 학생 정보 입력\n");
        printf("3. .dat 파일 저장\n");
        printf("4. 성적 확인 (평균 계산 등)\n");
        printf("5. 종료\n");
        printf("-------------------\n");
        printf("선택(1~5): ");
        scanf("%d", &choice);

        switch (choice) {
        case 1:
            load_data(filename);
            break;
        case 2:
            add_student();
            break;
        case 3:
            save_data(filename);
            break;
        case 4:
            display_grades();
            break;
        case 5:
            printf("프로그램을 종료합니다.\n");
            return 0;
        default:
            printf("잘못된 선택입니다. 다시 시도하세요.\n");
        }
    }
    return 0;
}

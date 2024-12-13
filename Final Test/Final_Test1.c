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
        printf("������ �� �� �����ϴ�.\n");
        return;
    }
    fread(&student_count, sizeof(int), 1, file);
    fread(students, sizeof(Student), student_count, file);
    fclose(file);
    printf("�����͸� ���������� �о����ϴ�.\n");
}

void save_data(const char* filename) {
    FILE* file = fopen(filename, "wb");
    if (!file) {
        printf("������ �� �� �����ϴ�.\n");
        return;
    }
    fwrite(&student_count, sizeof(int), 1, file);
    fwrite(students, sizeof(Student), student_count, file);
    fclose(file);
    printf("�����͸� ���������� �����߽��ϴ�.\n");
}

void add_student() {
    if (student_count >= MAX_STUDENTS) {
        printf("�л� ����� ���� á���ϴ�.\n");
        return;
    }

    Student s;
    printf("�л� �̸�: ");
    scanf("%s", s.name);
    printf("���� ����: ");
    scanf("%d", &s.korean);
    printf("���� ����: ");
    scanf("%d", &s.english);
    printf("���� ����: ");
    scanf("%d", &s.math);
    s.total = s.korean + s.english + s.math;
    s.average = s.total / 3.0f;
    students[student_count++] = s;
    printf("�л� ������ �߰��߽��ϴ�.\n");
}

void calculate_ranks() {
    for (int i = 0; i < student_count; i++) {
        students[i].rank = 1; // �ʱ�ȭ
        for (int j = 0; j < student_count; j++) {
            if (students[i].total < students[j].total) {
                students[i].rank++;
            }
        }
    }
}

void display_grades() {
    if (student_count == 0) {
        printf("�л� ������ �����ϴ�.\n");
        return;
    }

    calculate_ranks();
    printf("�л� ���� ���:\n");
    printf("�̸�\t����\t����\t����\t����\t���\t���\n");
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
        printf("1. .dat ���Ͽ��� ������ �б�\n");
        printf("2. �߰� �л� ���� �Է�\n");
        printf("3. .dat ���� ����\n");
        printf("4. ���� Ȯ�� (��� ��� ��)\n");
        printf("5. ����\n");
        printf("-------------------\n");
        printf("����(1~5): ");
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
            printf("���α׷��� �����մϴ�.\n");
            return 0;
        default:
            printf("�߸��� �����Դϴ�. �ٽ� �õ��ϼ���.\n");
        }
    }
    return 0;
}

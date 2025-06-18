#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Student {
    int roll;
    char name[50];
    struct Student* next;
};

struct Student* head = NULL;

void insertStudent(int roll, char name[]) {
    struct Student* newStudent = (struct Student*)malloc(sizeof(struct Student));
    newStudent->roll = roll;
    strcpy(newStudent->name, name);
    newStudent->next = head;
    head = newStudent;
    printf("Student inserted successfully.\n");
}

void deleteStudent(int roll) {
    struct Student *temp = head, *prev = NULL;

    if (temp != NULL && temp->roll == roll) {
        head = temp->next;
        free(temp);
        printf("Student deleted successfully.\n");
        return;
    }

    while (temp != NULL && temp->roll != roll) {
        prev = temp;
        temp = temp->next;
    }

    if (temp == NULL) {
        printf("Student not found.\n");
        return;
    }

    prev->next = temp->next;
    free(temp);
    printf("Student deleted successfully.\n");
}

void searchStudent(int roll) {
    struct Student* temp = head;
    while (temp != NULL) {
        if (temp->roll == roll) {
            printf("Student Found: Roll: %d, Name: %s\n", temp->roll, temp->name);
            return;
        }
        temp = temp->next;
    }
    printf("Student not found.\n");
}

void displayStudents() {
    struct Student* temp = head;
    if (temp == NULL) {
        printf("No records to display.\n");
        return;
    }

    printf("All Student Records:\n");
    while (temp != NULL) {
        printf("Roll: %d, Name: %s\n", temp->roll, temp->name);
        temp = temp->next;
    }
}

int main() {
    int choice, roll;
    char name[50];

    do {
        printf("\n--- Student Record System ---\n");
        printf("1. Insert Student\n");
        printf("2. Delete Student\n");
        printf("3. Search Student\n");
        printf("4. Display All Students\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter roll number: ");
                scanf("%d", &roll);
                printf("Enter name: ");
                scanf(" %[^\n]", name);
                insertStudent(roll, name);
                break;
            case 2:
                printf("Enter roll number to delete: ");
                scanf("%d", &roll);
                deleteStudent(roll);
                break;
            case 3:
                printf("Enter roll number to search: ");
                scanf("%d", &roll);
                searchStudent(roll);
                break;
            case 4:
                displayStudents();
                break;
            case 5:
                printf("Exiting program.\n");
                break;
            default:
                printf("Invalid choice.\n");
        }
    } while (choice != 5);

    return 0;
}

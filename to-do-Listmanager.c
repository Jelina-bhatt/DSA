#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Task {
    char name[100];
    struct Task *next;
};

struct Task *head = NULL;

void addTask() {
    struct Task *newTask = (struct Task *)malloc(sizeof(struct Task));
    printf("Enter task name: ");
    scanf(" %[^\n]", newTask->name);
    newTask->next = NULL;

    if (head == NULL) {
        head = newTask;
    } else {
        struct Task *temp = head;
        while (temp->next != NULL)
            temp = temp->next;
        temp->next = newTask;
    }
    printf("Task added!\n");
}

void viewTasks() {
    if (head == NULL) {
        printf("No tasks added.\n");
        return;
    }
    printf("\n--- Your To-Do List ---\n");
    int count = 1;
    struct Task *temp = head;
    while (temp != NULL) {
        printf("%d. %s\n", count++, temp->name);
        temp = temp->next;
    }
}

void deleteTask() {
    int pos, i = 1;
    printf("Enter task number to delete: ");
    scanf("%d", &pos);

    struct Task *temp = head, *prev = NULL;

    if (pos == 1 && head != NULL) {
        head = head->next;
        free(temp);
        printf("Task deleted.\n");
        return;
    }

    while (temp != NULL && i < pos) {
        prev = temp;
        temp = temp->next;
        i++;
    }

    if (temp == NULL) {
        printf("Invalid task number.\n");
    } else {
        prev->next = temp->next;
        free(temp);
        printf("Task deleted.\n");
    }
}

int main() {
    int choice;
    do {
        printf("\n1. Add Task\n2. View Tasks\n3. Delete Task\n4. Exit\nChoose: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: addTask(); break;
            case 2: viewTasks(); break;
            case 3: deleteTask(); break;
            case 4: printf("Goodbye!\n"); break;
            default: printf("Invalid choice.\n");
        }
    } while (choice != 4);

    return 0;
}

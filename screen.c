#include <stdio.h>
#include <string.h>

#define MAX_TASKS 20
#define TEXT_SIZE 100

typedef struct {
    char taskName[TEXT_SIZE];
    char area[TEXT_SIZE];     // e.g., Screen, Projector, Audio
    char status[20];          // Pending / Completed
} MaintenanceTask;

void showMenu();
void addTask(MaintenanceTask tasks[], int *taskCount);
void viewTasks(MaintenanceTask tasks[], int taskCount);
void updateTask(MaintenanceTask tasks[], int taskCount);

int main() {
    MaintenanceTask tasks[MAX_TASKS];
    int taskCount = 0;
    int choice;

    while (1) {
        showMenu();
        printf("\nEnter choice: ");
        scanf("%d", &choice);
        getchar(); // consume newline

        switch (choice) {
            case 1:
                addTask(tasks, &taskCount);
                break;
            case 2:
                viewTasks(tasks, taskCount);
                break;
            case 3:
                updateTask(tasks, taskCount);
                break;
            case 4:
                printf("Exiting system.\n");
                return 0;
            default:
                printf("Invalid choice. Try again.\n");
        }
    }

    return 0;
}

void showMenu() {
    printf("\n--- Theater Screen & Sound Maintenance System ---\n");
    printf("1. Add Maintenance Task\n");
    printf("2. View All Tasks\n");
    printf("3. Update Task Status\n");
    printf("4. Exit\n");
}

void addTask(MaintenanceTask tasks[], int *taskCount) {
    if (*taskCount >= MAX_TASKS) {
        printf("Task list full.\n");
        return;
    }

    MaintenanceTask newTask;

    printf("Enter task name: ");
    fgets(newTask.taskName, TEXT_SIZE, stdin);
    newTask.taskName[strcspn(newTask.taskName, "\n")] = 0;

    printf("Enter area (Screen/Projector/Speakers/Amplifier): ");
    fgets(newTask.area, TEXT_SIZE, stdin);
    newTask.area[strcspn(newTask.area, "\n")] = 0;

    strcpy(newTask.status, "Pending");

    tasks[*taskCount] = newTask;
    (*taskCount)++;

    printf("Task added successfully.\n");
}

void viewTasks(MaintenanceTask tasks[], int taskCount) {
    if (taskCount == 0) {
        printf("No tasks available.\n");
        return;
    }

    printf("\nCurrent Maintenance Tasks:\n");
    for (int i = 0; i < taskCount; i++) {
        printf("%d. [%s] %s — Area: %s\n",
               i + 1, tasks[i].status, tasks[i].taskName, tasks[i].area);
    }
}

void updateTask(MaintenanceTask tasks[], int taskCount) {
    if (taskCount == 0) {
        printf("No tasks to update.\n");
        return;
    }

    int taskNum;
    printf("Enter task number to update: ");
    scanf("%d", &taskNum);
    getchar();

    if (taskNum < 1 || taskNum > taskCount) {
        printf("Invalid task number.\n");
        return;
    }

    printf("Mark task as (1) Completed or (2) Pending: ");
    int statusChoice;
    scanf("%d", &statusChoice);
    getchar();

    if (statusChoice == 1)
        strcpy(tasks[taskNum - 1].status, "Completed");
    else
        strcpy(tasks[taskNum - 1].status, "Pending");

    printf("Task status updated.\n");
}

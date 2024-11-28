#include<stdio.h>
#include<stdlib.h>
#include<string.h>
typedef int bool;
#define true 1
#define false 0

struct Task {
	int task_id;
	char description[100];
	char due_date[20];
	char status[20];
};

struct Task tasks[100];
int task_count = 0;

void add_task() {
	struct Task new_task;
	new_task.task_id = task_count + 1;
	printf("Enter Task Description: ");
	getchar();
	fgets(new_task.description, sizeof(new_task.description), stdin);
	new_task.description[strcspn(new_task.description, "\n")] = '\0';
	printf("Enter due date (press enter for no due date): ");
	fgets(new_task.due_date, sizeof(new_task.due_date), stdin);
	new_task.due_date[strcspn(new_task.due_date, "\n")] = '\0';
	strcpy(new_task.status, "Not Completed");
	tasks[task_count] = new_task;
	task_count++;
	printf("Task added successfully!\n\n");
}

void view_all_tasks() {
	if (task_count == 0) {
		printf("No tasks available!\n\n");
		return;
	}
	for (int i = 0; i < task_count; i++) {
		printf("Task ID: %d\n", tasks[i].task_id);
		printf("Description: %s\n", tasks[i].description);
		if (strlen(tasks[i].due_date) > 0) {
			printf("Due Date: %s\n", tasks[i].due_date);
		}
		printf("Status: %s\n", tasks[i].status);
		printf("---------------------------------\n");
	}
}

void mark_task_completed() {
	int task_id;
	printf("Enter task ID to mark as completed: ");
	scanf("%d", &task_id);
	bool found = false;
	for (int i = 0; i < task_count; i++) {
		if (tasks[i].task_id == task_id) {
			strcpy(tasks[i].status, "Completed");
			printf("Task marked as completed!\n\n");
			found = true;
			break;
		}
	}
	if (!found) {
		printf("Task not found!\n\n");
	}
}

void delete_task() {
	int task_id;
	printf("Enter task ID to delete: ");
	scanf("%d", &task_id);
	bool found = false;
	for (int i = 0; i < task_count; i++) {
		if (tasks[i].task_id == task_id) {
			for (int j = i; j < task_count - 1; j++) {
				tasks[j] = tasks[j + 1];
			}
			task_count--;
			printf("Task deleted successfully!\n\n");
			found = true;
			break;
		}
	}
	if (!found) {
		printf("Task not found!\n\n");
	}
}

bool confirm_exit() {
	char ans[3];
	printf("Are you sure you want to exit? (Y/N) ");
	scanf("%s", ans);
	if (ans[0] == 'y' || ans[0] == 'Y') {
		return true;
	}
	return false;
}

int main() {
	int sel;
	while (1 == 1) {
		printf("1. Add task\n2. View all tasks\n3. Mark task as completed\n4. Delete task\n5. Exit\nEnter Choice: ");
		scanf("%d", &sel);
		switch (sel) {
			case 1:
				add_task();
				break;
			case 2:
				view_all_tasks();
				break;
			case 3:
				mark_task_completed();
				break;
			case 4:
				delete_task();
				break;
			case 5:
				bool ans = confirm_exit();
				if (ans == true) {
					return 0;
				}
				continue;
				break;
			default:
				printf("Invalid coice, try again! \n");
				continue;
		}
	}
	return 0;
}

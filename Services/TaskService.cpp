#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../Objects/Task.cpp"

const char* taskFile = "Task.txt";

int start() {
	FILE* file = fopen(taskFile, "r");
	if (!file) {
		file = fopen(taskFile, "w");
		fclose(file);
		return 0;
	}
	return 1;
}

int getCount() {
	FILE* file = fopen(taskFile, "r");

	int count = 0;
	char buf[256];

	while (fgets(buf, sizeof(buf), file) != NULL) {
		count++;
	}

	fclose(file);

	return count == 0 ? 0 : (count + 1) / 7;
}

Task* getTasks(int* count) {
	*count = getCount();
	if (*count == 0) return NULL;

	FILE* file = fopen(taskFile, "r");
	
	Task* tasks = (Task*)malloc(*count * sizeof(Task));
	char buf[256];

	for (int i = 0; i < *count; i++) {
		fgets(buf, sizeof(buf), file);
		tasks[i].id = atoi(buf);

		fgets(buf, sizeof(buf), file);
		buf[strcspn(buf, "\r\n")] = 0;
		snprintf(tasks[i].name, sizeof(tasks[i].name), "%s", buf);

		fgets(buf, sizeof(buf), file);
		buf[strcspn(buf, "\r\n")] = 0;
		snprintf(tasks[i].text, sizeof(tasks[i].text), "%s", buf);

		fgets(buf, sizeof(buf), file);
		buf[strcspn(buf, "\r\n")] = 0;
		snprintf(tasks[i].datetime, sizeof(tasks[i].datetime), "%s", buf);

		fgets(buf, sizeof(buf), file);
		tasks[i].isDone = atoi(buf);

		fgets(buf, sizeof(buf), file);
		tasks[i].priority = atoi(buf);

		if (i < *count - 1) {
			fgets(buf, sizeof(buf), file);
		}
	}

	fclose(file);
	return tasks;
}

int createTask(Task* task) {
	int count = 0;
	Task* tasks = getTasks(&count);
	
	if (count == 0) task->id = 1;
	else {
		task->id = tasks[count - 1].id + 1;
		free(tasks);
	}

	FILE* file = fopen(taskFile, "a");

	if (count > 0) fprintf(file, "\n");

	fprintf(file, "%d\n", task->id);
	fprintf(file, "%s\n", task->name);
	fprintf(file, "%s\n", task->text);
	fprintf(file, "%s\n", task->datetime);
	fprintf(file, "%d\n", task->isDone);
	fprintf(file, "%d\n", task->priority);

	fclose(file);
	return 1;
}

int deleteTask(int id) {
	int count = 0;
	Task* tasks = getTasks(&count);

	FILE* file = fopen(taskFile, "w");

	int currentCount = 0;

	for (int i = 0; i < count; i++) {
		if (tasks[i].id == id) continue;

		if (currentCount > 0) fprintf(file, "\n");

		fprintf(file, "%d\n", tasks[i].id);
		fprintf(file, "%s\n", tasks[i].name);
		fprintf(file, "%s\n", tasks[i].text);
		fprintf(file, "%s\n", tasks[i].datetime);
		fprintf(file, "%d\n", tasks[i].isDone);
		fprintf(file, "%d\n", tasks[i].priority);

		currentCount++;
	}

	fclose(file);
	free(tasks);
	return 1;
}

int updateTask(Task* task) {
	int count = 0;
	Task* tasks = getTasks(&count);

	FILE* file = fopen(taskFile, "w");
	Task* current;

	for (int i = 0; i < count; i++) {
		if (i > 0) fprintf(file, "\n");

		current = &tasks[i];
		if (tasks[i].id == task->id) current = task;

		fprintf(file, "%d\n", current->id);
		fprintf(file, "%s\n", current->name);
		fprintf(file, "%s\n", current->text);
		fprintf(file, "%s\n", current->datetime);
		fprintf(file, "%d\n", current->isDone);
		fprintf(file, "%d\n", current->priority);
	}

	fclose(file);
	free(tasks);
	return 1;
}

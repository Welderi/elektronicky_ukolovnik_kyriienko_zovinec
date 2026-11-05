#include <stdio.h>
#include <stdlib.h>
#include "../Objects/Task.cpp"

const char* taskFile = "../Database/Task.txt";

int getCount() {
	FILE* file = fopen(taskFile, "r");

	int count = 0;
	char buf[256];
	int is_empty = 1;

	while (fgets(buf, sizeof(buf), file) != NULL) {
		is_empty = 0;

		if (buf[0] == '\n') {
			count++;
		}
	}

	fclose(file);

	return is_empty ? 0 : count + 1;
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
		snprintf(tasks[i].name, sizeof(tasks[i].name), "%s", buf);

		fgets(buf, sizeof(buf), file);
		snprintf(tasks[i].text, sizeof(tasks[i].text), "%s", buf);

		fgets(buf, sizeof(buf), file);
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
	fprintf(file, "%s", task->name);
	fprintf(file, "%s", task->text);
	fprintf(file, "%s", task->datetime);
	fprintf(file, "%d\n", task->isDone);
	fprintf(file, "%d\n", task->priority);

	fclose(file);
	return 1;
}
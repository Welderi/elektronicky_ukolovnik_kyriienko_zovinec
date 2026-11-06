#include "Elektronicky_ukolovnik_kyriienko_zovinec.h"
#include <iostream>

using namespace std;

int main()
{
    // -- These rows are neccessery for work --
    start();
    int count = 0;
    Task* tasks;
    // -- --

    // -- Creating a Task --
    Task task1 = {
        .name = "First Task",
        .text = "My plans for today",
        .datetime = "2026-06-07 12:00",
        .isDone = 1,
        .priority = 1
    };

    Task task2 = {
        .name = "Second Task",
        .text = "My plans for tomorrow",
        .datetime = "2026-07-07 12:00",
        .isDone = 0,
        .priority = 2
    };

    createTask(&task1);
    createTask(&task2);
    // -- --

    // -- Getting the Tasks --
    tasks = getTasks(&count);

    printf("ALL TASKS\n");
    for (int i = 0; i < count; i++) {
        printf("%d\n", tasks[i].id);
        printf("%s\n", tasks[i].name);
        printf("%s\n", tasks[i].text);
        printf("%s\n", tasks[i].datetime);
        printf("%d\n", tasks[i].isDone);
        printf("%d\n", tasks[i].priority);
        printf("\n");
    }
    // -- --

    // -- Updating the Task --
    Task updated = {
        .id = 1, // NECCESSERY! ID of a Task, that we want to update
        .name = "First Task UPDATED",
        .text = "My plans for today UPDATED",
        .datetime = "2026-07-07 15:50",
        .isDone = 0,
        .priority = 1
    };

    updateTask(&updated);
    // -- --

    // -- Deleting of the Task
    deleteTask(2); // ID of a Task, that we want to delete
    // -- --

    // -- Checking Tasks after update
    free(tasks);
    tasks = getTasks(&count);

    printf("ALL TASKS\n");
    for (int i = 0; i < count; i++) {
        printf("%d\n", tasks[i].id);
        printf("%s\n", tasks[i].name);
        printf("%s\n", tasks[i].text);
        printf("%s\n", tasks[i].datetime);
        printf("%d\n", tasks[i].isDone);
        printf("%d\n", tasks[i].priority);
        printf("\n");
    }
    // -- --

    // --These rows are neccessery for work --
    if (tasks != NULL) {
        free(tasks);
    }
    // -- --
    return 0;
}
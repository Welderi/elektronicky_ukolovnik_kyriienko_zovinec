#include <iostream>
#include <sqlite3.h>
#include "../Objects/Task.cpp"
#include "../Objects/DefaultCategory.cpp"

char query[512];

int createTask(sqlite3* db, Task* task) {
    char* error = NULL;

    snprintf(query, sizeof(query),
        "INSERT INTO Categories (name, text, datetime, priority)"
        "VALUES ('%s', '%s', '%s', '%d', '%d');",
        task->name,
        task->text,
        task->datetime,
        task->isDone,
        task->priority
    );

    int rc = sqlite3_exec(db, query, 0, 0, &error);

    if (rc == SQLITE_OK) {
        return 1;
    }
    else {
        sqlite3_free(error);
        return 0;
    }
}

int removeTask(sqlite3* db, int id) {
    char* error = NULL;

    snprintf(query, sizeof(query), "UPDATE Tasks SET category_id = %d WHERE id == %d;", TRASH, id);

    int rc = sqlite3_exec(db, query, 0, 0, &error);

    if (rc == SQLITE_OK) {
        return 1;
    }
    else {
        sqlite3_free(error);
        return 0;
    }
}

int removeTrash(sqlite3* db) {
    char* error = NULL;

    snprintf(query, sizeof(query), "DELETE FROM Tasks WHERE category_id == %d;", TRASH);

    int rc = sqlite3_exec(db, query, 0, 0, &error);

    if (rc == SQLITE_OK) {
        return 1;
    }
    else {
        sqlite3_free(error);
        return 0;
    }
}




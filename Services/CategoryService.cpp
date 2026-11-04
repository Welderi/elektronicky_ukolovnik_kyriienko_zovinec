#include <iostream>
#include <sqlite3.h>
#include "../Objects/Category.cpp"

char query[512];

int createCategory(sqlite3* db, Category* category) {
    char* error = NULL;

    snprintf(query, sizeof(query), "INSERT INTO Categories (name) VALUES ('%s');", category->name);

    int rc = sqlite3_exec(db, query, 0, 0, &error);

    if (rc == SQLITE_OK) {
        return 1;
    }
    else {
        sqlite3_free(error);
        return 0;
    }
}

int removeCategory(sqlite3* db, int id) {
    char* error = NULL;

    snprintf(query, sizeof(query), "DELETE FROM Categories WHERE id == %d;", id);

    int rc = sqlite3_exec(db, query, 0, 0, &error);

    if (rc == SQLITE_OK) {
        return 1;
    }
    else {
        sqlite3_free(error);
        return 0;
    }
}




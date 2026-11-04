#include <sqlite3.h>
#include <iostream>
#include "../Services/TaskService.cpp"
#include "../Services/CategoryService.cpp"

using namespace std;

void createDefaultValues(sqlite3* db) {
    // Default Categories
    Category cat1 = { .name = "Another" };
    Category cat2 = { .name = "Archive" };
    Category cat3 = { .name = "Trash" };

    createCategory(db, &cat1);
    createCategory(db, &cat2);
    createCategory(db, &cat3);

    // Default Tasks
    Task task = {.name = "Welcome Task!", .text = "Welcome to the Elektronicky Ukolovnik!"};

    createTask(db, &task);

    return;
}

sqlite3* createDb() {
    sqlite3* db = NULL;

    sqlite3_open("database.db", &db);
    sqlite3_exec(db, "PRAGMA foreign_keys = ON;", 0, 0, NULL);

    // Create Categories
    sqlite3_exec(db, 
        "CREATE TABLE IF NOT EXISTS Categories"
        "(id INTEGER PRIMARY KEY AUTOINCREMENT,"
        "name TEXT NOT NULL);", 0, 0, NULL);

    // Create Tasks
    sqlite3_exec(db,
        "CREATE TABLE IF NOT EXISTS Tasks ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT,"
        "name TEXT NOT NULL,"
        "text TEXT,"
        "datetime TEXT NOT NULL DEFAULT (datetime('now', 'localtime')),"
        "is_done INTEGER DEFAULT 0,"
        "priority INTEGER DEFAULT 0,"
        "category_id INTEGER,"
        "FOREIGN KEY (category_id) REFERENCES Categories(id) ON DELETE SET NULL"
        ");", 0, 0, NULL);

    return db;
}

int start()
{
    // Create the database if not exists
    sqlite3* db = createDb();

    // Create default values for the DB
    createDefaultValues(db);

    sqlite3_close(db);

    return 0;
}
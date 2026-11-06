// Elektronicky_ukolovnik_kyriienko_zovinec.h : Include file for standard system include files,
// or project specific include files.

#pragma once

#include <iostream>
#include "Objects/Task.cpp"

Task* getTasks(int* count);
int createTask(Task* task);
int start();
int updateTask(Task* task);
int deleteTask(int id);



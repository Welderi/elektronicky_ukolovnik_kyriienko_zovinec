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


// Interface prototypy
void vypis_menu();
void pridat_ukol();
void zobrazit_dnes();
void zobrazit_den();
void zobrazit_vse();
void oznacit_hotovo();
void zmenit_prioritu();
void zmenit_datum();
void odstranit_ukol();
void kalendar_tyden();
void pockej();
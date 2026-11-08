#include "Elektronicky_ukolovnik_kyriienko_zovinec.h"
#include <iostream>
#include <stdio.h> 
#include <stdlib.h> // free
#include <string.h>
#include <time.h> // dnesni datum

using namespace std;

int main()
{
	int volba;

	start();   // pripravi soubor Task.txt (pokud neexistuje, vytvori prazdny)

	do {
		vypis_menu();
		scanf("%d", &volba);

		switch (volba) {
		case 1: pridat_ukol(); break;
		case 2: zobrazit_dnes(); break;
		case 3: zobrazit_den(); break;
		case 4: zobrazit_vse(); break;
		case 5: oznacit_hotovo(); break;
		case 6: zmenit_prioritu(); break;
		case 7: zmenit_datum(); break;
		case 8: odstranit_ukol(); break;
		case 9: kalendar_tyden(); break;
		case 0: printf("Nashledanou!\n"); break;
		default: printf("Neplatna volba.\n");
		}
		if (volba != 0) {
			pockej();
		}
	} while (volba != 0);

	return 0;
}


// Vypise nadpis a nabidku moznosti.
void vypis_menu()
{
	system("cls"); // Smaze vse na obrazovce
	printf("\n");
	printf("  _   _ _         _                  _ _    \n");
	printf(" | | | | | _____ | | _____   ___ __ (_) | __\n");
	printf(" | | | | |/ / _ \\| |/ _ \\ \\ / / '_ \\| | |/ /\n");
	printf(" | |_| |   < (_) | | (_) \\ V /| | | | |   < \n");
	printf("  \\___/|_|\\_\\___/|_|\\___/ \\_/ |_| |_|_|_|\\_\\\n");
	printf("\n");
	printf(" +-----------------------------------------+\n");
	printf(" |  1) Pridat ukol                         |\n");
	printf(" |  2) Zobrazit ukoly na dnes              |\n");
	printf(" |  3) Zobrazit ukoly pro jiny den         |\n");
	printf(" |  4) Zobrazit vsechny ukoly              |\n");
	printf(" |  5) Oznacit ukol jako hotovy            |\n");
	printf(" |  6) Zmenit prioritu                     |\n");
	printf(" |  7) Zmenit datum ukolu                  |\n");
	printf(" |  8) Odstranit ukol                      |\n");
	printf(" |  9) Kalendar (tyden)                    |\n");
	printf(" |-----------------------------------------|\n");
	printf(" |  0) Konec                               |\n");
	printf(" +-----------------------------------------+\n");
	printf(" Volba: ");
}

void pockej() // ceka na Enter a teprve pak znovu vypise menu
{
	printf("\nStiskni Enter pro pokracovani...");
	while (getchar() != '\n')   // zahodi zbytek radku po scanf
		;
	getchar();                  // ceka, az uzivatel zmackne Enter
}

// Vypise vsechny ukoly ze souboru v tabulce
void zobrazit_vse()
{
	system("cls");   // smaze menu, aby byl videt jen vypis

	int count;
	int i;
	Task* tasks = getTasks(&count);   // nacte ukoly do pole alokovaneho pres malloc, pocet zapise do count

	if (count == 0) { // if prazdny soubor
		printf("\nZadne ukoly.\n");
		return;
	}

	// hlavicka tabulky
	printf("\n  ID  Hotovo  Datum a cas        Priorita  Nazev\n");
	printf(" ---------------------------------------------------------\n");

	// pruchod vsemi ukoly v poli
	for (i = 0; i < count; i++) {
		printf(" %3d   ", tasks[i].id); // cislo zarovnane doprava na 3 znaky

		if (tasks[i].isDone == 1) {
			printf("[x]   ");
		}
		else {
			printf("[ ]   ");
		}

		// %-17s = retezec zarovnany doleva na 17 znaku
		printf("%-17s  %d         %s\n",
			tasks[i].datetime,
			tasks[i].priority,
			tasks[i].name);

		// popis se vypise na dalsi radek, jen pokud neni prazdny
		if (strlen(tasks[i].text) > 0) {
			printf("             - %s\n", tasks[i].text);
		}
	}

	free(tasks);   // uvolneni pameti, kterou alokovala getTasks
}

void pridat_ukol() {
	system("cls");

	// novy ukol s prazdnymi poli (id doplni createTask)
	Task task1 = {
		.name = "",
		.text = "",
		.datetime = "",
		.isDone = 0,
		.priority = 1
	};

	printf("Pridavani ukolu:\n");

	printf("Zadej nazev ukolu: ");
	scanf(" %99[^\n]", task1.name); // name[100];

	printf("Zadej popis ukolu: ");
	scanf(" %254[^\n]", task1.text); // text[255];

	printf("Zadej datum a cas ukolu (YYYY-MM-DD HH:MM): ");
	scanf(" %19[^\n]", task1.datetime); // datetime[20];

	printf("Zadej prioritu ukolu (1-3): ");
	scanf("%d", &task1.priority);

	createTask(&task1);   // ulozi do souboru a doplni task id

	// vypis pridaneho ukolu
	printf("\nUkol byl uspesne pridan:\n");
	printf("\n  ID  Hotovo  Datum a cas        Priorita  Nazev\n");
	printf(" ---------------------------------------------------------\n");
	printf(" %3d   [ ]   %-17s  %d         %s\n",
		task1.id,
		task1.datetime,
		task1.priority,
		task1.name);
}

void zobrazit_dnes() {
	system("cls");

	// ziskani dnesniho data ve formatu YYYY-MM-DD (knihovna <time.h>)
	char dnes[11]; // "RRRR-MM-DD\0"
	time_t ted = time(NULL);
	strftime(dnes, 11, "%Y-%m-%d", localtime(&ted));    //localtime(&ted) je aktuální čas rozložený na části, strftime si z něj bere hodnoty

	int count;
	int i;
	Task* tasks = getTasks(&count);   // nacte ukoly do pole alokovaneho pres malloc, pocet zapise do count

	// if prazdny soubor
	if (count == 0) {
		printf("\nZadne ukoly.\n");
		return;
	}

	printf("Dnesni datum: %s", dnes);
	printf("\nUkoly na dnesni den:\n");
	printf("\n  ID  Hotovo  Datum a cas        Priorita  Nazev\n");
	printf(" ---------------------------------------------------------\n");

	for (i = 0; i < count; i++) {
		if (strncmp(tasks[i].datetime, dnes, 10) == 0) { // porovna prvnich 10 znaku (YYYY-MM-DD) s dnesnim datem
			printf(" %3d   ", tasks[i].id); // cislo zarovnane doprava na 3 znaky

			if (tasks[i].isDone == 1) {
				printf("[x]   ");
			}
			else {
				printf("[ ]   ");
			}

			printf("%-17s  %d         %s\n",
				tasks[i].datetime,
				tasks[i].priority,
				tasks[i].name);

			// popis se vypise na dalsi radek, jen pokud neni prazdny
			if (strlen(tasks[i].text) > 0) {
				printf("             - %s\n", tasks[i].text);
			}
		}
	}

	free(tasks);   // uvolneni pameti, kterou alokovala getTasks
}

void zobrazit_den() { printf("Zatim neni hotovo.\n"); }
void oznacit_hotovo() { printf("Zatim neni hotovo.\n"); }
void zmenit_prioritu() { printf("Zatim neni hotovo.\n"); }
void zmenit_datum() { printf("Zatim neni hotovo.\n"); }
void odstranit_ukol() { printf("Zatim neni hotovo.\n"); }
void kalendar_tyden() { printf("Zatim neni hotovo.\n"); }
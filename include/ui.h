#ifndef _ui_h
#define _ui_h

#include "dBstructs.h"

void executeCommands(Database *database);
void printWelcomeMessage();
void displayMainMenu();

void listDBStatistics(Database* database);
void sortDatabase(Database *database);
static void swapDragons(Database *database, int startidx);
static void sortDragonsByID(Database *database, int *j);
static void sortDragonsByName(Database *database, int *i, int *j);
static void nextDragon(int *i, int *j);

#endif
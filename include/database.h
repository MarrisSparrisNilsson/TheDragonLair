#ifndef _database_h
#define _database_h

#include "dBstructs.h"

#define INITIAL_CAPACITY 10
#define GROWTH_FACTOR 2

#define MAX_FILENAME 20
#define NAME_SIZE 10

Database* createDatabase();
void getDatabaseFilename(char filename[MAX_FILENAME]);
void loadDatabase(char *filename, Database *database);
void expandDatabase(Database *database);
void saveDatabase(char *filename, Database *database);
void destroyDatabase(Database *database);
void listDBStatistics(Database* database);
void sortDatabase(Database *database);
static void swapDragon(Database *database, int startidx);
static void sortDragonByName(Database *database, int *i, int *j);
static void nextDragon(int *i, int *j);

#endif

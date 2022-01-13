#ifndef _database_h
#define _database_h

#include "dBstructs.h"

#define INITIAL_CAPACITY 10
#define GROWTH_FACTOR 2

#define MAX_FILENAME 99
#define NAME_SIZE 10

Database* createDatabase();
void getDatabaseFilename(char filename[MAX_FILENAME]);
void loadDatabase(char *filename, Database *database);
void createDatabaseFile(char filename[MAX_FILENAME], Database* database);
void expandDatabase(Database *database);
void saveDatabase(char *filename, Database *database);
void destroyDatabase(Database *database);

#endif
#ifndef _database_h
#define _database_h

// #include "dragon.h" 
#include "dBstructs.h"

#define INITIAL_CAPACITY 10
#define GROWTH_FACTOR 2

#define MAX_FILENAME 20


// #define MAX_COLOURS 5
#define NAME_SIZE 10

// typedef struct {
//     Dragon *dragons;
//     unsigned int capacity;
//     unsigned int size;
//     unsigned int nextId;
// } Database;

Database* createDatabase();
void destroyDatabase(Database *database);
void loadDatabase(char *filename, Database *database);
static void expandDB(Database *database);
void saveDatabase(char *filename, Database *database);
void listDBStatistics(Database* database);
void sortDB(Database* database);

void getDatabaseFilename(char filename[MAX_FILENAME]);

#endif

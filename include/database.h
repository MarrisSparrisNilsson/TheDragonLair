#ifndef _database_h
#define _database_h

#include "dBstructs.h"

#define INITIAL_CAPACITY 10 // Initial capacity of dragons in the database.
#define GROWTH_FACTOR 2 // The multiplier for increasing the database capacity.

#define MAX_FILENAME 99 // The maximum number of characters that the file name can consist of.
#define NAME_SIZE 10 // The maximum number of characters a name can consist of.

// Creates a pointer to the allocated database.
Database *createDatabase();
// Promts the user to enter a filename for where the data should be stored.
void getDatabaseFilename(char filename[MAX_FILENAME]);
// Loads the data stored in the file into the database structs.
void loadDatabase(char *filename, Database *database);
// Expands the database's capacity
void expandDatabase(Database *database);
// Overrides and writes each field from the database to the file
void saveDatabase(char *filename, Database *database);
// Releases the database's allocated memory from the heap.
void destroyDatabase(Database *database);

#endif // End of database.h
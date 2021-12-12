#ifndef _filehandling_h
#define _filehandling_h

#include "database.h"

void destroyDatabase(Database*);
Database* createDatabase();
void getDatabaseFilename(char *filename);
void loadDatabase(char *filename, Database*);
void saveDatabase(char *filename, Database*);

#endif

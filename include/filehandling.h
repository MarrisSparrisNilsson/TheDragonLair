#ifndef _filehandling_h
#define _filehandling_h

#include "database.h"


void destroyDatabase(Database* dB);
Database* createDatabase();
void getDatabaseFilename(char *filename);
void loadDatabase(char *filename, Database* dB);
void saveDatabase(char *filename, Database* dB);

#endif

#ifndef _database_h
#define _database_h

#include "dragon.h"

#define INITIAL_CAPACITY 10
#define GROWTH_FACTOR 2

typedef struct Database {
    Dragon *dragons;
    unsigned int capacity;
    unsigned int size;
    unsigned int nextId;
} Database;

#endif

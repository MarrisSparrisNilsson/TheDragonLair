#ifndef _dBstructs_h
#define _dBstructs_h

#define MAX_COLOURS 5

typedef struct Dragon {
    unsigned int id;
    char *name;
    char isVolant;
    unsigned int fierceness;
    unsigned int numColours;
    char *colours[MAX_COLOURS];
} Dragon;

typedef struct Database {
    Dragon *dragons;
    unsigned int capacity;
    unsigned int size;
    unsigned int nextId;
} Database;

#endif // end of dBstructs
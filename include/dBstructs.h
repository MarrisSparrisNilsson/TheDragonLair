#ifndef _dBstructs_h
#define _dBstructs_h

#define MAX_COLOURS 5 // Maximum number of colours a dragon can have.

typedef struct Dragon { // This is a typedef for a dragon struct that contains all abilities a dragon can have.
    unsigned int id; // A dragons id as a non negative number starting at 1.
    char *name; // A dragons name as a string.
    char isVolant; // A character that shows if a dragon can fly or not.
    unsigned int fierceness; // A non negative number that shows how fierce a dragon is.
    unsigned int numColours; // A non negative number that shows how many colours a dragon have.
    char *colours[MAX_COLOURS]; // A character array that stores colours belonging to a dragon.
} Dragon;

typedef struct Database { // This is a typedef for a database struct that contains a pointer to the dragon struct, capacity, size, nextId.
    Dragon *dragons; // A pointer to the dragon struct dragons.
    unsigned int capacity; // A non negative number that shows how many dragons the database can hold.
    unsigned int size; // A non negative number that shows how many dragons currently in the database.
    unsigned int nextId; // A non negative number that shows the nextId the the next dragon inserted to the database will recieve.
} Database;

#endif // End of dBstructs.h
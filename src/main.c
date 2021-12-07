#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "database.h"

#define MAX_FILENAME 20

int main(void) {

    char filename[MAX_FILENAME];

    Database *database = createDatabase(); // empty database on the heap returns a database pointer to it.
    // Note that the function createDatabase should allocate memory on the heap for both the
    // Database struct and the dynamic array contained in its member dragons! Also initialise its
    // members capacity to the INITIAL_CAPACITY, size to 0, and nextId to 1.

    getDatabaseFilename(filename); // prompts the user for a database filname e.g dragons.txt 
    loadDatabase(filename, database); // uses file and pointer to load record

    printWelcomeMessage(); //contains welcomeMessage (display mainmenu)
    executeCommands(database); // switch (mainmenu)

    saveDatabase(filename, database); // database overwritten
    destroyDatabase(database); // free database from heap
    return 0;
}




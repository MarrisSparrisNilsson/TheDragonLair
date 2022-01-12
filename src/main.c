#include <stdio.h>
#include "database.h"
#include "ui.h"

int main(void) {

    char filename[MAX_FILENAME];

    Database *database = createDatabase(); // Returns a pointer to the database struct that was created
    getDatabaseFilename(filename); // Prompts the user for a database filname e.g dragons.txt
    loadDatabase(filename, database); // Uses file and pointer to load record

    printWelcomeMessage(); // Contains welcomeMessage (display mainmenu)
    executeCommands(database); // switch (mainmenu)

    saveDatabase(filename, database); // database overwritten
    destroyDatabase(database); // free database from heap

    fflush(stdin);
    getchar();
    return 0;
}




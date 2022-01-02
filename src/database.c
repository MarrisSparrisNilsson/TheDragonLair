#include <stdio.h>
#include <stdlib.h>
#include "database.h"

// Start of function createDatabase.
Database* createDatabase() {
    Database *database = (Database*) malloc(sizeof(Database)); // Allocates memory on the heap for a Database.
    if (database == NULL) return NULL;

    database->capacity = INITIAL_CAPACITY;

    return database;
} // End of function createDatabase.

void loadDatabase(char filename[MAX_FILENAME], Database* dB) {
    FILE *fPtr = fopen(filename, "r");

    if (fPtr == NULL) {
        printf("Could not find database");
        exit(-1);
    }
    
    // char *size;
    // fscanf(fPtr, "%s", size);
    fscanf(fPtr, "%u", &dB->size);
    // dB->size = strtol(size, &endPtr, 10);
    // size;
    // dB->size = size;
    dB->dragons = malloc(sizeof(Dragon) * dB->size);
    // dB->dragons->name = malloc((char) NAME_SIZE);
    for (size_t i = 0; !feof(fPtr); i++) {
        fscanf(fPtr, "%u", &dB->dragons[i].id);
        // fscanf(fPtr, "%s", name);
        // dB->dragons[i].name = malloc(sizeof(name));
        // fPtr--;
        dB->dragons[i].name = malloc(sizeof(char [NAME_SIZE]));
        fscanf(fPtr, "%s", dB->dragons[i].name);
        // printf("%d", sizeof(dB->dragons[i].name));

        fscanf(fPtr, "\n%c", &dB->dragons[i].isVolant);
        fscanf(fPtr, "%u", &dB->dragons[i].fierceness);
        fscanf(fPtr, "%u", &dB->dragons[i].numColours);
        int colors = dB->dragons[i].numColours;
        for (size_t j = 0; j < colors; j++) {
            dB->dragons[i].colours[j] = malloc(sizeof(NAME_SIZE));
            // dB->dragons[i].colours[j] = malloc(sizeof(*fPtr));
            fscanf(fPtr, "%s", dB->dragons[i].colours[j]);
        }
    }
}

void saveDatabase(char *filename, Database* dB) {

}
// Start of function destroyDatabase.
void destroyDatabase(Database* dB) {
    if(dB != NULL) {
        free(dB); // Deallocates the memory for the fMatrix on the heap.
    }
    dB = NULL; // Sets the fMatrix to NULL.
} // End of function destroyDatabase.

void listDBStatistics(Database* database) {
    puts("---------------------------------------------------");
    puts("Size MinFierceness MaxFierceness #Volant #NonVolant");
    puts("---------------------------------------------------");

    int max_fierceness = 0;
    int min_fierceness = 10;
    int volant = 0;
    int nonVolant = 0;
    for (size_t i = 0; i < database->size; i++) {
        if (max_fierceness < database->dragons[i].fierceness) {
            max_fierceness = database->dragons[i].fierceness;
        }
        if (min_fierceness > database->dragons[i].fierceness) {
            min_fierceness = database->dragons[i].fierceness;
        }
        if (database->dragons[i].isVolant == 'Y') volant++;
        if (database->dragons[i].isVolant == 'N') nonVolant++;
    }

    printf("%4d %13d %13d %7d %10d\n", database->size, min_fierceness, max_fierceness, volant, nonVolant);
}

// void sortDB(Database* database) {

// }

// Each time a dragon is added to the database (i.e. the dynamic array dragons),
// the database’s size is incremented. Then, when the database’s size reaches its current capacity,
// the database is grown as describe above. To do this, you can use the functions malloc or realloc
// in stdlib.h.

void getDatabaseFilename(char filename[MAX_FILENAME]) {

    printf("Please enter filename: ");
    scanf("%s", filename);

    // FILE *fPtrText = fopen("filename", "w");
    
    // for(int i=0; i<MAX_FILENAME; ++i) {
    //     fprintf(fPtrText, "%d %.1f %c %s\n",
    //     data[i].d, data[i].f, data[i].c, data[i].s);
    // }
    // fclose(fPtrText);
}   
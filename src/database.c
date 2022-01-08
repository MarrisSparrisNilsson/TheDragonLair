#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "database.h"

// Start of function createDatabase.
Database* createDatabase() {
    Database *dBPtr = (Database*) malloc(sizeof(Database)); // Allocates memory on the heap for a Database.
    if (dBPtr == NULL) return NULL;

    dBPtr->dragons = (Dragon*) calloc(INITIAL_CAPACITY, sizeof(Dragon)); // Allocates memory on the heap for a Database.
    if (dBPtr->dragons == NULL) return NULL;

    dBPtr->capacity = INITIAL_CAPACITY;
    dBPtr->size = 0;
    dBPtr->nextId = 1;

    return dBPtr;
} // End of function createDatabase.

void getDatabaseFilename(char filename[MAX_FILENAME]) {
    printf("Please enter filename: ");
    scanf("%20s", filename);
}

void loadDatabase(char filename[MAX_FILENAME], Database* database) {
    FILE *fPtr = fopen(filename, "r");

    if (fPtr == NULL) {
        printf("Could not find database");
        exit(-1);
    }

    fscanf(fPtr, "%u\n", &database->size);

    while (database->size > database->capacity) {
        expandDatabase(database);
    }

    for (size_t i = 0; i < database->size; i++) {
        fscanf(fPtr, "%u\n", &database->dragons[i].id);

        database->dragons[i].name = malloc(sizeof(char [NAME_SIZE]));
        fscanf(fPtr, "%s\n", database->dragons[i].name);
        fscanf(fPtr, "%c\n", &database->dragons[i].isVolant);
        fscanf(fPtr, "%u\n", &database->dragons[i].fierceness);
        fscanf(fPtr, "%u\n", &database->dragons[i].numColours);
        for (size_t j = 0; j < database->dragons[i].numColours; j++) {
            database->dragons[i].colours[j] = malloc(sizeof(NAME_SIZE));
            fscanf(fPtr, "%s\n", database->dragons[i].colours[j]);
        }
    }
    fscanf(fPtr, "%u\n", &database->nextId);
    fclose(fPtr);
}

// Each time a dragon is added to the database (i.e. the dynamic array dragons),
// the database’s size is incremented. Then, when the database’s size reaches its current capacity,
// the database is grown as described above. To do this, you can use the functions malloc or realloc
// in stdlib.h.

void expandDatabase(Database *database) {

    // Create new database of size: current capacity * GROWTH_FACTOR
    Dragon *dragonPtr = (Dragon*) calloc(GROWTH_FACTOR * database->capacity, sizeof(Dragon));
    if (dragonPtr == NULL) printf("Could not expand database");

    // Add dragons into the new database
    for (int i = 0; i < database->size; i++) dragonPtr[i] = database->dragons[i];

    // Free the old database from the heap memory
    free(database->dragons);
    // Set the new database to be part of the active database
    // Increase current capacity
    database->dragons = dragonPtr;
    database->capacity = database->capacity * GROWTH_FACTOR;
}

void saveDatabase(char *filename, Database* database) {
    FILE *fPtr = fopen(filename, "w");

    if (fPtr == NULL) {
        printf("Could not find database");
        exit(-1);
    }
    fprintf(fPtr, "%u\n", database->size);
    for (size_t i = 0; i < database->size; i++) {
        fprintf(fPtr, "%u\n", database->dragons[i].id);
        fprintf(fPtr, "%s\n", database->dragons[i].name);
        fprintf(fPtr, "%c\n", database->dragons[i].isVolant);
        fprintf(fPtr, "%u\n", database->dragons[i].fierceness);
        fprintf(fPtr, "%u\n", database->dragons[i].numColours);
        int colors = database->dragons[i].numColours;
        for (size_t j = 0; j < colors; j++) {
            fprintf(fPtr, "%s\n", database->dragons[i].colours[j]);
        }
    }
    fprintf(fPtr, "%u\n", database->nextId);
    fclose(fPtr);
}

void destroyDatabase(Database* database) {
    if(database != NULL) {
        if (database->dragons != NULL) {
            for (size_t i = 0; i < database->size; i++) {
                free(database->dragons[i].name);
                for (size_t j = 0; j < database->dragons[i].numColours; j++) {
                    free(database->dragons[i].colours[j]);
                }
            }
            free(database->dragons);
        }
        free(database);
    }
    database = NULL; // Sets the database to NULL.
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

// Start of function sortDatabase.
void sortDatabase(Database *database) {// Sorts a database in ascending order based on id or name.

    int input = -1;

    while (input != 0 && input != 1) {
        printf("Enter sort by id (0) or name (1): ");
        fflush(stdin);
        scanf("%d", &input);
        if (input != 0 && input != 1) puts("Invalid input, please try again!");
    }
    for (unsigned int h = 0; h < database->size-1; ++h) { // loop to control comparisons during each pass
        for (int j = 0, i = 0; j < database->size-1;) {
            if (input == 0) {
                if (database->dragons[j].id > database->dragons[j+1].id) {
                    swapDragon(database, j);
                }
                j++;
            }
            else if(input == 1) sortDragonByName(database, &i, &j);        
        }   
    }
    puts("Database sorted.");
}

// Start of function swap.
static void swapDragon(Database *database, int startidx) { // Swaps dragons in database.
    Dragon tempDragon = database->dragons[startidx];
    database->dragons[startidx] = database->dragons[startidx+1];
    database->dragons[startidx+1] = tempDragon;
} // End of function swap.

static void sortDragonByName(Database *database, int *i, int *j) {

    int dragNameLen1 = strlen(database->dragons[*j].name);
    int dragNameLen2 = strlen(database->dragons[*j+1].name);
    int diff = dragNameLen1 - dragNameLen2;
    int nameLen = (diff <= 0) ? dragNameLen1 : dragNameLen2;

    if (*i < nameLen) {
        if (database->dragons[*j].name[*i] > database->dragons[*j+1].name[*i]) {
            if (nameLen == dragNameLen1) swapDragon(database, *j);
            else swapDragon(database, *j+1);
            nextDragon(i, j);
        }
        else {
            if(database->dragons[*j].name[*i] == database->dragons[*j+1].name[*i]) {
                *i+=1;
                if (*i == nameLen) nextDragon(i, j);
            }
            else nextDragon(i, j);
        }
    }
}
static void nextDragon(int *i, int *j) {
    *j+=1; *i = 0;
}
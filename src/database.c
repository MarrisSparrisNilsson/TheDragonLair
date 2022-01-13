#include <stdio.h>
#include <stdlib.h>
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
        puts("Could not find database file, creating new database file!");
        createDatabaseFile(filename, database);
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

void createDatabaseFile(char filename[MAX_FILENAME], Database* database) {
    FILE *fPtr = fopen(filename, "w");

    if (fPtr == NULL) {
        printf("Could not create database file");
        exit(-1);
    }
    fprintf(fPtr, "%u\n", database->size);
    fprintf(fPtr, "%u\n", database->nextId);
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

    // Free the old array of dragons from the heap memory
    free(database->dragons);
    // Set the new array of dragons to be part of the active database
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
        free(database); // Frees memory from the memory allocated database strut.
        database = NULL; // Sets the pointer to the database to NULL.
    }
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "database.h"

// Creates a file given by the provided file name.
static void createDatabaseFile(char filename[MAX_FILENAME], Database* database);

// Creates a pointer to the allocated database
Database* createDatabase() {
    Database *dBPtr = (Database*) malloc(sizeof(Database)); // Allocates memory on the heap for the Database.
    if (dBPtr == NULL) return NULL;

    dBPtr->dragons = (Dragon*) calloc(INITIAL_CAPACITY, sizeof(Dragon)); // Allocates memory on the heap for the dragons array.
    if (dBPtr->dragons == NULL) return NULL;

    dBPtr->capacity = INITIAL_CAPACITY; // Sets the initial capacity of the database
    dBPtr->size = 0; // Start size is set to 0
    dBPtr->nextId = 1; // The id for the next dragon to be inserted is set to 1

    return dBPtr;
}

// Promts the user for a filename and concatinates the directory name in front of the file name.
void getDatabaseFilename(char filename[MAX_FILENAME]) {
    printf("Please enter filename: ");
    scanf("%s", filename);

    char tempStr[MAX_FILENAME];
    strcpy(tempStr, "Database/");
    strcat(tempStr, filename);
    strcpy(filename, tempStr);
}

// Loads the data stored in the file into the database structs.
void loadDatabase(char filename[MAX_FILENAME], Database* database) {
    FILE *fPtr = fopen(filename, "r");

    // If the file couldn't be found
    if (fPtr == NULL) {
        puts("Could not find database file, creating new database file!");
        createDatabaseFile(filename, database); // If a file couldn't be found, the file is created.
    }
    else {
        fscanf(fPtr, "%u\n", &database->size);

        // Increases database capacity if current capacity limit is reached.
        while (database->size > database->capacity) {
            expandDatabase(database);
        }
        // Inserts the values from the file to each dragon's fields.
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
        fclose(fPtr); // When done reading the file the connection to the file is closed.
    }
}

// Creates a file given by the provided file name.
void createDatabaseFile(char filename[MAX_FILENAME], Database* database) {
    FILE *fPtr = fopen(filename, "w");

    // If the file couldn't be created
    if (fPtr == NULL) {
        printf("Could not create database file");
        exit(-1);
    }
    fprintf(fPtr, "%u\n", database->size);
    fprintf(fPtr, "%u\n", database->nextId);
    fclose(fPtr);
}

// Expands the database's capacity
void expandDatabase(Database *database) {

    // Allocate memory for the newly created Dragons array with a capacity twice as big than previously. 
    Dragon *dragonPtr = (Dragon*) calloc(GROWTH_FACTOR * database->capacity, sizeof(Dragon));
    if (dragonPtr == NULL) printf("Could not expand database");

    // Move dragons from old array to new array
    for (int i = 0; i < database->size; i++) dragonPtr[i] = database->dragons[i];

    // Free the old array of dragons from the heap memory
    free(database->dragons);
    // Set the new array of dragons to be part of the active database
    database->dragons = dragonPtr;
    // Increase current capacity
    database->capacity = database->capacity * GROWTH_FACTOR;
}

// Overrides and writes each field from the database to the file
void saveDatabase(char *filename, Database* database) {
    FILE *fPtr = fopen(filename, "w");

    // If the file couldn't be found
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

// Releases the database's allocated memory from the heap
void destroyDatabase(Database* database) {
    if(database != NULL) {
        free(database); // Frees memory from the memory allocated database strut.
        database = NULL; // Sets the pointer to the database to NULL.
    }
}
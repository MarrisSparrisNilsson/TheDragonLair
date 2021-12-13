#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>
#include "database.h"
#include "dragon.h"

// Start of function createDatabase.
Database* createDatabase() {
    Database *database = (Database*) malloc(sizeof(Database)); // Allocates memory on the heap for a Database.
    if (database == NULL) return NULL;
    return database;
} // End of function createDatabase.

// void getDatabaseFilename(char *filename){

//     printf("Please enter filename");
//     scanf("%s", &filename);

//     FILE *fPtrText = fopen("filename", "w");
    
//     for(int i=0; i<SIZE; ++i) {
//         fprintf(fPtrText, "%d %.1f %c %s\n",
//         data[i].d, data[i].f, data[i].c, data[i].s);
//     }
//     fclose(fPtrText);
// }   

void loadDatabase(char *filename, Database* dB) {

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
#ifndef _dragon_h
#define _dragon_h

#include "dBstructs.h"

// #define MAX_COLOURS 5
#define NAME_SIZE 10
enum ListType { DETAILED, BRIEF };
static enum ListType listType;


// typedef struct {
//     unsigned int id;
//     char *name;
//     char isVolant;
//     unsigned int fierceness;
//     unsigned int numColours;
//     char *colours[MAX_COLOURS];
// } Dragon;

void insertDragon();
void setDragonName(char dragonName[NAME_SIZE]);
// void setDragonName(char *dragonName[NAME_SIZE]);
char setIsVolant();
int setFierceness();
void setDragonColor(char **dragonColor, unsigned int *numColors);
void printDragon(Dragon dragon, enum ListType listType);
// void printDragon(Dragon dragon, char *listType);

// void setDragonColor(char *dragonColor[MAX_COLOURS]);

// void updateDragon(Database* database);
void deleteDragon(Database *database);
static void stringToUpr(char *string);
static int findBinaryInterative(int key, int array[], int left, int right);
static void swapDragon(Database *database, size_t i);
void listBriefDragons(Database* database);
void listDetailedDragons(Database* database);
void showDragonDetail(Database* database);

#endif
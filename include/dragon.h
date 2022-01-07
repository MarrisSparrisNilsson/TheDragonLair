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

void insertDragon(Database *database);
// static void setDragonName(char dragonName[NAME_SIZE]);
static void setDragonName(Database *database, unsigned int dragonIndex);
// void setDragonName(char *dragonName[NAME_SIZE]);
static char setIsVolant(Database *database, unsigned int dragonIndex);
static int setFierceness(Database *database, unsigned int dragonIndex);
// static void setDragonColor(char **dragonColor, unsigned int *numColors);
static void setDragonColor(Database * database, unsigned int dragonIndex);
static void formatColorStr(char *string);
static void printDragon(Dragon dragon, enum ListType listType);
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
static void findDragon(char dragon[NAME_SIZE], Database *database, Dragon *dragonArray);


#endif
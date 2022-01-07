#ifndef _dragon_h
#define _dragon_h

#include <stdbool.h>
#include "dBstructs.h"

#define NAME_SIZE 10
enum ListType { DETAILED, BRIEF };

void insertDragon(Database *database);
static void setDragonName(Database *database, unsigned int dragonIndex);
static char setIsVolant(Database *database, unsigned int dragonIndex);
static int setFierceness(Database *database, unsigned int dragonIndex);
static void setDragonColor(Database * database, unsigned int dragonIndex);
static void formatColorStr(char *string, bool *isValidInput);


// void updateDragon(Database* database);
void deleteDragon(Database *database);
static int getDragonIndex(char dragon[NAME_SIZE], Database *database, bool *foundDragon);
void printDragons(char dragon[NAME_SIZE], Database *database, int dragonIdx, int *numDragons, enum ListType listType);
static void stringToUpr(char *string);
static void swapDragon(Database *database, int startIdx);
void listBriefDragons(Database* database);
void listDetailedDragons(Database* database);
void showDragonDetail(Database* database);
static void findDragon(char dragon[NAME_SIZE], Database *database, Dragon *dragonArray);
static void printDragon(Dragon dragon, enum ListType listType);
static void printHeader(enum ListType listType);


#endif
#ifndef _dragon_h
#define _dragon_h

#include "dBstructs.h"

#define NAME_SIZE 10
enum ListType { DETAILED, BRIEF };

void insertDragon(Database *database);
static void setDragonName(Database *database, unsigned int dragonIndex);
static char setIsVolant(Database *database, unsigned int dragonIndex);
static int setFierceness(Database *database, unsigned int dragonIndex);
static void setDragonColor(Database * database, unsigned int dragonIndex);
static void formatColorStr(char *string);


// void updateDragon(Database* database);
void deleteDragon(Database *database);
static void stringToUpr(char *string);
static int findLinear(int key, int array[], size_t size);
static int findBinaryInterative(int key, int array[], int left, int right);
static void swapDragon(Database *database, int id1, int id2);
void listBriefDragons(Database* database);
void listDetailedDragons(Database* database);
void showDragonDetail(Database* database);
static void findDragon(char dragon[NAME_SIZE], Database *database, Dragon *dragonArray);
static void printDragon(Dragon dragon, enum ListType listType);


#endif
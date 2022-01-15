#ifndef _dragon_h
#define _dragon_h

#include "dBstructs.h"
#define NAME_SIZE 10
// This enumeration represents different print methods.
enum ListType { DETAILED, BRIEF };

// This function inserts a dragon to the database and returns void.
void insertDragon(Database *database);
// This function updates an existing dragon in the database and returns void.
void updateDragon(Database* database);
// This function deletes an existing dragon in the database and returns void.
void deleteDragon(Database *database);
// This function is a helper function to deleteDragon, it helps with the deleteing process of a dragon. 
// The function swaps the position of two adjecent dragons in the database and returns void.
void swapDragons(Database *database, int startIdx);
// This function shows a BRIEF list of the dragons existing in the database and returns void.
void listBriefDragons(Database* database);
// This function shows a DETAILED list of the dragons existing in the database and returns void.
void listDetailedDragons(Database* database);
// This function shows all details for a specific dragon existing in the database and returns void.
void showDragonDetail(Database* database);

#endif
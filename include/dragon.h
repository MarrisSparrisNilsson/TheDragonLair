#ifndef _dragon_h
#define _dragon_h

#define MAX_COLOURS 5

typedef struct Dragon {
    unsigned int id;
    char *name;
    char isVolant;
    unsigned int fierceness;
    unsigned int numColours;
    char *colours[MAX_COLOURS];
} Dragon;

void insertDragon(Database* database);
char setDragonName();
char setIsVolant();
int setFierceness();
char setDragonColor();

void updateDragon(Database* database, Dragon dragon);
void deleteDragon(Database* database, Dragon dragon);
void listBriefDragons(Database* database, Dragon dragon);
void listDetailedDragons(Database* database, Dragon dragon);
void showDragonDetail(Database* database, Dragon dragon);

#endif
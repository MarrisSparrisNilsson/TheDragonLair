#ifndef _dragon_h
#define _dragon_h

#define MAX_COLOURS 5
#define NAME_SIZE 10

typedef struct Dragon {
    unsigned int id;
    char *name;
    char isVolant;
    unsigned int fierceness;
    unsigned int numColours;
    char *colours[MAX_COLOURS];
} Dragon;

void insertDragon();
void setDragonName(char dragonName[NAME_SIZE]);
// void setDragonName(char *dragonName[NAME_SIZE]);
char setIsVolant();
int setFierceness();
void setDragonColor(char dragonColor[MAX_COLOURS]);
// void setDragonColor(char *dragonColor[MAX_COLOURS]);

// void updateDragon(Database* database, Dragon dragon);
// void deleteDragon(Database* database, Dragon dragon);
// void listBriefDragons(Database* database, Dragon dragon);
// void listDetailedDragons(Database* database, Dragon dragon);
// void showDragonDetail(Database* database, Dragon dragon);

#endif
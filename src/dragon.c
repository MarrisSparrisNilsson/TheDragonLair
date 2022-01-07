#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>
#include "dragon.h"

void insertDragon(Database *database) {
    
    if (database->size+1 > database->capacity) {
        // expand
    }
    int dragonIndex = database->size;
    
    setDragonName(database, dragonIndex);
    setIsVolant(database, dragonIndex);
    setFierceness(database, dragonIndex);
    setDragonColor(database, dragonIndex);

    database->dragons[dragonIndex].id = database->nextId;
    printf("The dragon %s was entered into the database!", database->dragons[dragonIndex].name);

    database->size++;
    database->nextId++;

    // When all the dragon’s attributes have been supplied by the user, the dragon should be inserted
    // (entered) into the database, and the user notified about this. The database should assign a
    // unique id to the dragon, when inserting it into the database (the id should not be entered by
    // the user). A dragon’s id will never change, as long as the dragon is in the database (even when
    // loading the database from a text file).
}

// When the user chooses to insert (add) a new dragon to the database, the user should be asked to
// enter the dragon’s name (i.e. a string only containing letters from the English alphabet).
// If the user doesn’t enter a valid name (i.e. anything but letters from the English alphabet), the
// program should output an error message and ask the user to try again.
static void setDragonName(Database *database, unsigned int dragonIndex) {
    char dragonName[NAME_SIZE];
    bool isValidName = false;

    while (!isValidName) {
        isValidName = true;
        printf("Please enter the name of your dragon: ");
        fflush(stdin);
        scanf("%10s", dragonName);
        
        size_t i = 0;
        while (dragonName[i] != '\0' && isValidName) {
            if (!isalpha((dragonName[i]))) { // If the character on position i is NOT an alpha character, the name is invalid.
                isValidName = false;
                puts("\nInvalid name! Allowed characters are: (A-Z, a-z).\n");
            }
            else { 
                isValidName = true;
                dragonName[i] = toupper(dragonName[i]);
                i++;
            }
        }
    }
    database->dragons[dragonIndex].name = malloc(sizeof(char [NAME_SIZE]));
    strcpy(database->dragons[dragonIndex].name, dragonName);
}


// When a valid name has been entered, the program should ask the user to enter if the dragon
// can fly or not, i.e. isVolant. Only the characters 'Y' or 'N' (or their lower case equivalents 'y')
// or 'n') are valid. An invalid choice is again handled with an error message and asking the user to
// try again.
static char setIsVolant(Database *database, unsigned int dragonIndex) {
    char isVolant;
    do {
        printf("Is your dragon volant? (Y/N): ");
        fflush(stdin);
        scanf("%c", &isVolant);

        isVolant = toupper(isVolant);

        if (isVolant != 'Y' && isVolant != 'N') 
            puts("Invalid input! Please try again.\n");

    } while (isVolant != 'Y' && isVolant != 'N');

    database->dragons[dragonIndex].isVolant = isVolant;
}

// Next, the program should ask the user to enter the dragon’s fierceness, where the only valid
// values are in the integer range 1-10. An invalid choice is yet again handled with an error message
// and asking the user to try again.
static int setFierceness(Database *database, unsigned int dragonIndex) {
    unsigned int fierceness;
    do {
        printf("How fierce is your dragon? (1-10): ");
        fflush(stdin);
        scanf("%u", &fierceness);

        if (fierceness > 10)
            puts("Invalid input! Please enter numbers of the given range.\n");

    } while (fierceness < 0 || fierceness > 10);

    database->dragons[dragonIndex].fierceness = fierceness;
}

static void setDragonColor(Database *database, unsigned int dragonIndex) {

    unsigned int numColours = 0;
    char color[NAME_SIZE];

    while (numColours < MAX_COLOURS) {
        bool isValidInput = true;
        printf("Please enter dragon color #%d (of 5): ", numColours+1);
        fflush(stdin);
        fgets(color, sizeof(color), stdin);
        
        int colorLength = strlen(color)-1;
        color[colorLength] = '\0';

        if (numColours == 0 && color[0] == '\0') 
            puts("Please enter atleast one color!\n");
        else if (numColours > 0 && color[0] == '\0') break;
        else {
            formatColorStr(color, &isValidInput);
            database->dragons[dragonIndex].colours[numColours] = malloc(sizeof(char) * colorLength);
            strcpy(database->dragons[dragonIndex].colours[numColours], color);

            if (isValidInput) numColours++;
        }
    }
    database->dragons[dragonIndex].numColours = numColours;
}

static void formatColorStr(char *string, bool *isValidInput) {
    int i = 0;
    while (string[i] != '\0' && *isValidInput) {
        if (!isalpha(string[i])) {
            puts("Invalid input! Colour must contain characters of A-Z");
            *isValidInput = false;
        }
        else {
            string[i] = toupper(string[i]);
            i++;
            *isValidInput = true;
        }
    }
}

void updateDragon(Database* database) {
    // When the user chooses to update a dragon, the user should be asked to enter the id or name of
    // a dragon. The user should not first be asked if an id or name should be entered. Instead the
    // program should read in the entry as a search string, and interpret the search string as an id
    // or name (remember, an id is an integer, and a valid name only contains letters from the English
    // alphabet).

    // char dragon[NAME_SIZE];

    // printf("Please enter id or name of dragon: ");
    // scanf("%s", dragon);

    // // database->size
    // Dragon dragons[database->size];
    // findDragon(dragon, database, dragons);

    // if (sizeof(dragons)/sizeof(dragons[0]) > 2) {
    //     /* code */
    // }
    
}

void deleteDragon(Database *database) {

    bool foundDragon = false;
    char dragon[NAME_SIZE];
    int dragonIdx = -1;

    while (!foundDragon) {
        printf("Please enter a id or a name of the dragon you want to delete: ");
        fflush(stdin);
        scanf("%s", dragon);


        if (isdigit(dragon[0])) {
            dragonIdx = getDragonIndex(dragon, database, &foundDragon);
            printf("The dragon with id %d has been deleted!\n", database->dragons[dragonIdx].id);
            swapDragon(database, dragonIdx);
        }
        else {
            stringToUpr(dragon);
            printHeader(BRIEF);
            int numDragons = 0;

            dragonIdx = getDragonIndex(dragon, database, &foundDragon);
            printDragons(dragon, database, dragonIdx, &numDragons, BRIEF);

            if (numDragons > 1) {
                dragonIdx = -1;
                while (dragonIdx == -1) {
                    printf("Please choose which id matching the dragon you want to delete: ");
                    fflush(stdin);
                    scanf("%s", &dragon);

                    dragonIdx = getDragonIndex(dragon, database, &foundDragon);
                    if (dragonIdx != -1) {
                        printf("The dragon with id: %d has been deleted!\n", database->dragons[dragonIdx].id);
                        swapDragon(database, dragonIdx);
                    }
                    else puts("Couldn't find dragon match, please try again!");
                }
            }
            else {
                swapDragon(database, dragonIdx);
                if (foundDragon) printf("The dragon with name %s has been deleted!\n", dragon);
            }
        }
        if (foundDragon) database->size--;
        else puts("Could not find a matching dragon, please try again!\n");
    }
}

static void stringToUpr(char *string) {
    for (size_t i = 0; string[i] != '\0'; i++) {
        string[i] = toupper(string[i]);
    }
}

// Start of function swap.
static void swapDragon(Database *database, int startIdx) { // Swaps elements in an intArray.
    for (size_t i = startIdx; i < database->size; i++) {
        Dragon tempDragon = database->dragons[i];
        database->dragons[i] = database->dragons[i+1];
        database->dragons[i+1] = tempDragon;
    }
} // End of function swap.

void listBriefDragons(Database* database) {
    printHeader(BRIEF);

    for (size_t i = 0; i < database->size; i++) {
        printDragon(database->dragons[i], BRIEF);
    }
}

void listDetailedDragons(Database* database) {
    printHeader(DETAILED);

    for (size_t i = 0; i < database->size; i++) {
        printDragon(database->dragons[i], DETAILED);
    }
}

void showDragonDetail(Database* database) {
    bool foundDragon = false;
    char dragon[NAME_SIZE];
    int numDragons = 0;

    printf("Please enter id or name of dragon: ");
    fflush(stdin);
    scanf("%s", dragon);

    printHeader(DETAILED);

    int dragonIdx = getDragonIndex(dragon, database, &foundDragon);
    // printDragon(database->dragons[dragonIdx], DETAILED);
    if (dragonIdx != 1) {
        printDragons(dragon, database, dragonIdx, &numDragons, DETAILED);
    }
   
    if (!foundDragon) printf("Could not find a dragon match.");
}

static int getDragonIndex(char dragon[NAME_SIZE], Database *database, bool *foundDragon) {
    char *endPtr;

    if (isdigit(dragon[0])) {
        int dragonID = strtol(dragon, &endPtr, 10);
        for (size_t i = 0; i < database->size; i++) {
            if (dragonID == database->dragons[i].id) {
                *foundDragon = true;
                return i;
            }
        }
    }
    else if (isalpha(dragon[0])) {
        for (size_t i = 0; i < database->size; i++) {
            stringToUpr(dragon);
            if (strcmp(dragon, database->dragons[i].name) == 0) {
                *foundDragon = true;
                return i;
            }
        }
    }
    return -1;
}

void printDragons(char dragon[NAME_SIZE], Database *database, int dragonIdx, int *numDragons, enum ListType listType) {
    char *endPtr;
    for (size_t i = dragonIdx; i < database->size; i++) {
        if (strcmp(dragon, database->dragons[i].name) == 0) {
            printDragon(database->dragons[i], listType);
            *numDragons+=1;
        }
        else if (strtol(dragon, &endPtr, 10) == database->dragons[i].id) {
            printDragon(database->dragons[i], listType);
            return;
        } 
    }
}

static void printDragon(Dragon dragon, enum ListType listType) {
    if (listType == DETAILED) {
        printf("%2d %-*s \t %6c %10u %8d ",
        dragon.id,
        NAME_SIZE,
        dragon.name,
        dragon.isVolant,
        dragon.fierceness,
        dragon.numColours
        );
        for (size_t j = 0; j < dragon.numColours; j++) {
            printf("%-s ", dragon.colours[j]);
        }
    }
    else {
        printf("%2d %-*s",
        dragon.id,
        NAME_SIZE,
        dragon.name);
    }
    printf("\n");
}

static void printHeader(enum ListType listType) {
    if (listType == DETAILED) {
        puts("--------------------------------------------------------------------------------");
        puts("ID Name \t Volant Fierceness #Colours Colours");
        puts("--------------------------------------------------------------------------------");
    }
    else {
        puts("--------------------------------------------------------------------------------");
        puts("ID Name");
        puts("--------------------------------------------------------------------------------");
    }    
}

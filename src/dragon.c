#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>
#include "dragon.h"

void insertDragon(Database *database) {
    
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
        printf("Please enter the name of your dragon: ");
        scanf("%10s", dragonName);
        
        for (size_t i = 0; dragonName[i] != '\0'; i++) {
            if (!isalpha((dragonName[i]))) { // If the character on position i is NOT an alpha character, the name is invalid.
                puts("\nInvalid name! Allowed characters are: (A-Z, a-z).\n");
                isValidName == false;
                break;
            }        
            isValidName = true;
            dragonName[i] = toupper(dragonName[i]);
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
        printf("Please enter dragon color #%d (of 5): ", numColours+1);
        fflush(stdin);
        fgets(color, sizeof(color), stdin);
        
        int colorLength = strlen(color)-1;
        color[colorLength] = '\0';

        if (numColours == 0 && color[0] == '\0') 
            puts("Please enter atleast one color!\n");
        else if (numColours > 0 && color[0] == '\0') break;
        else {
            formatColorStr(color);
            database->dragons[dragonIndex].colours[numColours] = malloc(sizeof(char) * colorLength);
            strcpy(database->dragons[dragonIndex].colours[numColours], color);

            numColours++;
        }
    }
    database->dragons[dragonIndex].numColours = numColours;
}

static void formatColorStr(char *string) {
    for (size_t i = 0; string[i] != '\0'; i++) {
        if (!isalpha(string[i])) {
            puts("Invalid input! Color must contain characters of A-Z");
            break;
        }
        string[i] = toupper(string[i]);
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
    char *endPtr = NULL;

    while (!foundDragon) {
        printf("Please enter a id or a name of the dragon you want to delete: ");
        scanf("%s", dragon);

        if (isdigit(dragon[0])) {
            int dragonID = strtol(dragon, &endPtr, 10);
            for (size_t i = 0; i < database->size; i++) {
                if (dragonID == database->dragons[i].id) {
                    for (size_t j = i; j < database->size; j++) {
                        swapDragon(database, j, j+1);
                    }
                    foundDragon = true;
                    printf("The dragon with id: %d has been deleted!\n", dragonID);
                }
            }
            if (foundDragon) database->size--;
        }
        else if (isalpha(dragon[0])) {
                stringToUpr(dragon);
                    puts("--------------------------------------------------------------------------------");
                    puts("ID Name");
                    puts("--------------------------------------------------------------------------------");
                    int martin;
                    int j = 0;
                    int *idxArray = malloc(sizeof(database->size)+1);
                    int dragonID = 0;
                    for (size_t h = 0; h < database->size; h++) {
                        if (strcmp(dragon, database->dragons[h].name) == 0) {
                            // idxArray[j] = h;
                            martin = h;
                            printDragon(database->dragons[h], BRIEF);
                            foundDragon = true;
                            j++;
                        }
                    }
                    if (j > 1) {
                            int matchingIDidx = -1;
                        while (matchingIDidx == -1) {
                            printf("Please choose which id matching the dragon you want to delete: ");
                            fflush(stdin);
                            scanf("%d", &dragonID);
                            for (size_t i = 0; i < database->size; i++) {
                                if (dragonID == database->dragons[i].id) {
                                    matchingIDidx = i;
                                }
                            }
                            if (matchingIDidx != -1) {
                                printf("The dragon with id: %d has been deleted!\n", dragonID);
                                for (size_t i = matchingIDidx; i < database->size; i++) {
                                    swapDragon(database, i, i+1);
                                }
                            }
                            else puts("Couldn't find dragon match, please try again!");
                        }
                    }
                    else {
                        for (size_t i = martin; i < database->size; i++) {
                            swapDragon(database, i, i+1);
                        }
                        if (foundDragon) printf("The dragon with name: %s has been deleted!\n", dragon);
                    }
            if (foundDragon) database->size--;
        }
        if (!foundDragon) puts("Could not find a matching dragon, please try again!");
    }
}

// static int findLinear(int key, int array[], size_t size)
// {
// int i;
// // Loop through all elements (first to last)
// for (i = 0; i < size; i++)
// {
// // If key found return its index
// if (key == array[i])
// return i;
// }
// return -1; // Key not found
// }

// static int findBinaryInterative(int dragonID, int idxArray[], int left, int right) {
//     while (left <= right) {
//         int mid = (left + right) / 2;
//         printf("%d\n", idxArray[mid]);
//         // If dragonID is present at mid (split point)
//         if (dragonID == idxArray[mid])
//         return mid;
//         // If dragonID > mid-entry, skip left subarray
//         if (dragonID > idxArray[mid])
//         left = mid + 1;
//         // If dragonID < mid-entry, skip right subarray
//         else
//         right = mid - 1;
//     }
//     return -1; // DragonID not in array
// }

static void stringToUpr(char *string) {
    for (size_t i = 0; string[i] != '\0'; i++) {
        string[i] = toupper(string[i]);
    }
}

// Start of function swap.
static void swapDragon(Database *database, int id1, int id2) { // Swaps elements in an intArray.
    Dragon tempDragon = database->dragons[id1];
    database->dragons[id1] = database->dragons[id2];
    database->dragons[id2] = tempDragon;
} // End of function swap.

// SIMPLIFY
// static void swapDragon(Database *database, size_t i) {
//     database->dragons[i-1].name = database->dragons[i].name;
//     database->dragons[i-1].id = database->dragons[i].id;
//     database->dragons[i-1].isVolant = database->dragons[i].isVolant;
//     database->dragons[i-1].fierceness = database->dragons[i].fierceness;
//     database->dragons[i-1].numColours = database->dragons[i].numColours;
//     for (size_t j = 0; j < database->dragons[i].numColours; j++) {
//         database->dragons[i-1].colours[j] = malloc(sizeof(NAME_SIZE));
//         database->dragons[i-1].colours[j] = database->dragons[i].colours[j];
//     }
// }

void listBriefDragons(Database* database) {
    puts("--------------------------------------------------------------------------------");
    puts("ID Name");
    puts("--------------------------------------------------------------------------------");

    for (size_t i = 0; i < database->size; i++) {
        printDragon(database->dragons[i], BRIEF);
    }
}

void listDetailedDragons(Database* database) {
    puts("--------------------------------------------------------------------------------");
    puts("ID Name \t Volant Fierceness #Colours Colors");
    puts("--------------------------------------------------------------------------------");

    for (size_t i = 0; i < database->size; i++) {
        printDragon(database->dragons[i], DETAILED);
    }
}

void showDragonDetail(Database* database) {
    bool foundDragon = false;
    char dragon[NAME_SIZE];
    char *endPtr;

    printf("Please enter id or name of dragon: ");
    scanf("%s", dragon);

    puts("--------------------------------------------------------------------------------");
    puts("ID Name \t Volant Fierceness #Colours Colors");
    puts("--------------------------------------------------------------------------------");

    
    
    if (isdigit(dragon[0])) {
        int dragonID = strtol(dragon, &endPtr, 10);
        for (size_t i = 0; i < database->size; i++) {
            if (dragonID == database->dragons[i].id) {
                printDragon(database->dragons[i], DETAILED);
                return;
            }
        }
    }
    else if (isalpha(dragon[0])) {
        for (size_t i = 0; i < database->size; i++) {
            for (size_t j = 0; dragon[j] != '\0'; j++) {
                dragon[j] = toupper(dragon[j]);
            }
            if (strcmp(dragon, database->dragons[i].name) == 0) {
                printDragon(database->dragons[i], DETAILED);
                foundDragon = true;
            }
        }
    }
    else printf("Invalid input.");

    if (!foundDragon) printf("Could not find a dragon match.");

    // Dragon dragons[database->size];
    // size_t i = 0;
    // for (; i < database->size;) {
    //     dragons[i] = findDragon(dragon, database, &i);
    // }

    // for (size_t i = 0; i < database->size; i++) {
    //     printDragon(findDragon(dragon, database, &i), DETAILED);
    // }

    // while (sizeof(dragons)/sizeof(dragons[0]) > 0) {
    //     printDragon(database->dragons[i], DETAILED);
    // }
}

// (updateDragon)
// static void findDragon(char dragon[NAME_SIZE], Database *database, Dragon *dragonArray) {
//     char *endPtr;
//     if (isdigit(dragon[0])) {
//         int dragonID = strtol(dragon, &endPtr, 10);
//         for (size_t i = 0; i < database->size; i++) {
//             if (dragonID == database->dragons[i].id) {
//                 // printDragon(database->dragons[i], DETAILED);
//                 *(dragonArray+i) = database->dragons[i];
//                 // dragonArray[i] = database->dragons[i];
//                 return;
//             }
//         }
//     }
//     else if (isalpha(dragon[0])) {
//         for (size_t i = 0; i < database->size; i++) {
//             for (size_t j = 0; dragon[j] != '\0'; j++) {
//                 dragon[j] = toupper(dragon[j]);
//             }
//             if (strcmp(dragon, database->dragons[i].name) == 0) {
//                 // printDragon(database->dragons[i], DETAILED);
//                 // foundDragon = true;
//                 *(dragonArray+i) = database->dragons[i];
//                 // return database->dragons[i];
//             }
//         }
//     }
// }

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
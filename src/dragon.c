#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>
// #include "database.h"
#include "dragon.h"

void insertDragon() {

    // char *dragonName[NAME_SIZE];
    // char *dragonName;
    char dragonName[NAME_SIZE];
    setDragonName(dragonName);
    char isVolant;
    setIsVolant(&isVolant);
    unsigned int fierceness;
    setFierceness(&fierceness);
    // char dragonColor[MAX_COLOURS];
    unsigned int numColors = 0;
    char *dragonColor[MAX_COLOURS];
    setDragonColor(dragonColor, &numColors);
    // Insert into database
    // printf("%c", dragonColor[0][0]);
    // printf("%c", dragonColor[0][1]);
    // printf("%c", dragonColor[0][2]);
    printf("\n%s", dragonColor[0]);
    printf("\n%s", dragonColor[1]);
    printf("\n%s", dragonColor[2]);
    printf("\n%s", dragonColor[3]);
    printf("\n%s", dragonColor[4]);
    // printf("%s\n", *(dragonColor[1]));
    // printf("%s\n", *(dragonColor[2]));
    // printf("%s\n", *(dragonColor[3]));
    // printf("%s\n", *(dragonColor[4]));
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
// void setDragonName(char *dragonName) {
void setDragonName(char dragonName[NAME_SIZE]) {
    bool isValidName = false;
    printf("Please enter the name of your dragon: ");

    while (isValidName == false) {
        scanf("%s", dragonName);
        
        for (size_t i = 0; dragonName[i] != '\0'; i++) {
            if (!isalpha((dragonName[i]))) { // If the character on position i is NOT an alpha character, the name is invalid.
                puts("\nInvalid name! Allowed characters are: (A-Z, a-z).\n");
                printf("Please enter the name of your dragon: ");
                isValidName == false;
                break;
            }        
            isValidName = true;
            dragonName[i] = toupper(dragonName[i]);
        }
    }
}


// When a valid name has been entered, the program should ask the user to enter if the dragon
// can fly or not, i.e. isVolant. Only the characters 'Y' or 'N' (or their lower case equivalents 'y')
// or 'n') are valid. An invalid choice is again handled with an error message and asking the user to
// try again.
char setIsVolant(char *isVolant) {
    // char isVolant;

    do {
        printf("Is your dragon volant? (Y/N): ");
        fflush(stdin);
        scanf("%c", isVolant);

        *isVolant = toupper(*isVolant);

        if (*isVolant != 'Y' && *isVolant != 'N') 
            puts("Invalid input! Please try again.\n");

    } while (*isVolant != 'Y' && *isVolant != 'N');
    
    // return isVolant;
}

// Next, the program should ask the user to enter the dragon’s fierceness, where the only valid
// values are in the integer range 1-10. An invalid choice is yet again handled with an error message
// and asking the user to try again.
int setFierceness(unsigned int *fierceness) {
    // unsigned int fierceness;

    do {
        printf("How fierce is your dragon? (1-10): ");
        scanf("%u", fierceness);

        if (*fierceness > 10)
            puts("Invalid input! Please enter numbers of the given range.\n");

    } while (*fierceness < 0 || *fierceness > 10);
    
    // return *fierceness;
}

// Finally, the program should ask the user to supply between 1-5 colours for the dragon (where
// a colour is an arbitrary string representing a colour). The user should not select the number
// of colours to enter, prior to entering the colours. Instead, the program should stop asking for
// additional colours when the user enters an empty string, or when 5 colours have been entered.
// void setDragonColor(char* dragonColor) {
void setDragonColor(char **dragonColor, unsigned int *numColors) {
    // char *color;
    char color[NAME_SIZE];
    // char **colorPtr = dragonColor;
    // char *colorPtr[MAX_COLOURS];
    // *colorPtr = *dragonColor;

    // || color[i] != '\0'
    for (size_t i = 0; i < MAX_COLOURS; i++) {
        printf("Please enter dragon color #%d (of 5): ", i+1);
        // scanf("%s", &color);
        fflush(stdin);
        fgets(color, sizeof(color), stdin);
        
        int colorLength = strlen(color)-1;
        color[colorLength] = '\0';

        if (*numColors == 0 && color[0] == '\0') {
            puts("Please enter atleast one color!\n");
            i--;
        }
        else if (*numColors > 0 && color[0] == '\0') {
            return;
        }
        else {
            *numColors += 1;
            for (size_t j = 0; color[j] != '\0'; j++) {
                if (!isalpha(color[j])) {
                    puts("Invalid input! Color must contain characters of A-Z");
                    break;
                }
                color[j] = toupper(color[j]);
            }

            // *(colorPtr+i) = malloc(sizeof(color));
            // printf("%p\n", *(dragonColor+i));
            // *(colorPtr+i) = color;
            // colorPtr[i] = color;
            // *(dragonColor+i) = malloc(sizeof(color));
            // printf("%d\n", sizeof(color));
            dragonColor[i] = malloc(sizeof(color)*3);
            if(dragonColor[i] == NULL) {
                printf("Error: couldn't allocate memory.");
                exit(-1); // terminate the program
            }
            // *(dragonColor+i) = color;
            for (size_t j = 0; color[j] != '\0'; j++) {
                dragonColor[i][j] = color[j];
                // printf("%c", dragonColor[i][j]);

                // *(*(dragonColor+i) + j) = color[j];
            }
            

            // printf("\n%s\n", *(dragonColor+i));
            // printf("%p\n", *(dragonColor+i));
            // colorPtr+colorLength;
        }
    }
}

// void setDragonColor(char dragonColor[MAX_COLOURS]) {
//  toupper
//     int count = 0;
//     char colorInput[NAME_SIZE];
    
//     for (; count > MAX_COLOURS || *colorInput + count != '\0'; ) {
//         printf("PleaseS enter between 1-5 colours to the dragon");
//         scanf("%s", &colorInput);
//         dragonColor = colorInput;
//         count++;
//     }
// }

void updateDragon(Database* database) {
    // When the user chooses to update a dragon, the user should be asked to enter the id or name of
    // a dragon. The user should not first be asked if an id or name should be entered. Instead the
    // program should read in the entry as a search string, and interpret the search string as an id
    // or name (remember, an id is an integer, and a valid name only contains letters from the English
    // alphabet).

    // database->size
    // Dragon dragons[database->size] = findDragon();

    // if (sizeof(dragons)/sizeof(dragons[0]) > 2) {
    //     /* code */
    // }
    
}

void deleteDragon(Database *database) {

    int nextId = 0;
    char dragon[NAME_SIZE];
    char *endPtr = NULL;
    bool foundDragon = false;

    printf("Please enter a id or a name of the dragon you want to delete: ");
    scanf("%s", dragon);

    if (isdigit(dragon[0])) {
        int dragonID = strtol(dragon, &endPtr, 10);
        for (size_t i = 0; i < database->size; i++) {
            if (dragonID == database->dragons[i].id) {
                for (size_t i = dragonID; i < database->size; i++) {
                    swapDragon(database, i);
                    nextId = i;
                }
                foundDragon = true;
                printf("The dragon with id: %d has been deleted!\n", i+1);
            }
        }
        database->size--;
    }
    else if (isalpha(dragon[0])) {
            stringToUpr(dragon);
                puts("--------------------------------------------------------------------------------");
                puts("ID Name");
                puts("--------------------------------------------------------------------------------");
                int count = 0;
                int *array = malloc(sizeof(database->size)+1);
                int j = 0;
                for (size_t h = 0; h < database->size; h++) {
                    if (strcmp(dragon, database->dragons[h].name) == 0) {
                        array[j] = database->dragons[h].id;
                        printDragon(database->dragons[h], BRIEF);
                        count++;
                        j++;
                    }
                }
                array[j] = -1;
                foundDragon = true;
                if (count > 1) {
                        int dragonID = 0;
                        int matchingID = -1;
                        int arraySize = 0;
                        for (size_t i = 0; array[i+1] != -1; i++) arraySize++;
                    while (matchingID == -1) {
                        int i;
                        printf("Please choose which id matching the dragon you want to delete: ");
                        scanf("%d", &dragonID);
                        matchingID = findBinaryInterative(dragonID, array, 0, arraySize-1);
                        if (matchingID != -1) {
                            printf("The dragon with id: %d has been deleted!\n", dragonID);
                            for (size_t i = dragonID; i < database->size; i++) {
                                swapDragon(database, i);
                                nextId = i;
                            }
                        }
                        else puts("Invalid input, please try again");
                    }
                }
                else {
                    for (size_t i = array[0]; i < database->size; i++) {
                        swapDragon(database, i);
                        nextId = i;
                    }
                    printf("The dragon with name: %s has been deleted!\n", dragon);
                }
        database->size--;
        database->nextId = nextId + 1;
    }
    else printf("Invalid input.");
    if (!foundDragon) printf("Could not find a matching dragon.");
}
static int findBinaryInterative(int key, int array[], int left, int right) {
    while (left <= right) {
        int mid = (left + right) / 2;
        // If key is present at mid (split point)
        if (key == array[mid])
        return mid;
        // If key > mid-entry, skip left subarray
        if (key > array[mid])
        left = mid + 1;
        // If key < mid-entry, skip right subarray
        else
        right = mid - 1;
    }
    return -1; // Key not in array
}

static void stringToUpr(char *string) {
    for (size_t i = 0; string[i] != '\0'; i++) {
        string[i] = toupper(string[i]);
    }
}

static void swapDragon(Database *database, size_t i) {
    database->dragons[i-1].name = database->dragons[i].name;
    database->dragons[i-1].id = database->dragons[i].id;
    database->dragons[i-1].isVolant = database->dragons[i].isVolant;
    database->dragons[i-1].fierceness = database->dragons[i].fierceness;
    database->dragons[i-1].numColours = database->dragons[i].numColours;
    for (size_t j = 0; j < database->dragons[i].numColours; j++) {
        database->dragons[i-1].colours[j] = malloc(sizeof(NAME_SIZE));
        database->dragons[i-1].colours[j] = database->dragons[i].colours[j];
    }
} 

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
// Dragon findDragon(char dragon[NAME_SIZE], Database *database, size_t *i) {
//     char *endPtr;
//     if (isdigit(dragon[0])) {
//         int dragonID = strtol(dragon, &endPtr, 10);
//         for (; *i < database->size; *i++) {
//             if (dragonID == database->dragons[*i].id) {
//                 // printDragon(database->dragons[*i], DETAILED);
//                 return database->dragons[*i];
//             }
//         }
//     }
//     else if (isalpha(dragon[0])) {
//         for (; *i < database->size; *i++) {
//             for (size_t j = 0; dragon[j] != '\0'; j++) {
//                 dragon[j] = toupper(dragon[j]);
//             }
//             if (strcmp(dragon, database->dragons[*i].name) == 0) {
//                 // printDragon(database->dragons[*i], DETAILED);
//                 // foundDragon = true;
//                 return database->dragons[*i];
//             }
//         }
//     }
// }

void printDragon(Dragon dragon, enum ListType listType) {
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
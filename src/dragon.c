#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>
#include "dragon.h"
#include "database.h"

// This function sets the name of the dragon that is inserted or updated and returns void.
static void setDragonName(Database *database, unsigned int dragonIndex);
// This function sets if the dragon can fly or not and returns a char.
static char setIsVolant(Database *database, unsigned int dragonIndex);
// This function sets the fierceness of the dragon from 1-10 and returns an int.
static int setFierceness(Database *database, unsigned int dragonIndex);
// This function sets the colors of a dragon (maximum 5) and returns void.
static void setDragonColor(Database * database, unsigned int dragonIndex);
// This function is a helper function to setDragonColor that helps with the format of the colors and it returns void.
static void formatColorStr(char *string, bool *isValidInput);
// This function is a helper function to deleteDragon, it helps with the deleteing process of a dragon. 
// The function swaps the position of two adjecent dragons in the database and returns void.
static void swapDragons(Database *database, int startIdx);
// This function prints a BRIEF or DETAILED header.
static void printHeader(enum ListType listType);
// This function is a helper function to updateDragon, deleteDragon and listDetailedDragon. 
// The function searches for an id or a name of a dragon and returns the index as an int of that dragon. 
// If no dragon was found the function returns -1.
static int findDragonIndex(char dragon[NAME_SIZE], Database *database);
// This function is a helper function to findDragonIndex. 
// Returns the index as an int of the first occurence of a dragon if serached by name.
// If the user inputs an id it returns the index of the dragon with matching id. 
// If the function doesn't find any dragon it returns -1.
static int getDragonIndex(char dragon[NAME_SIZE], Database *database);
// This function finds all matching dragons based on id or name and prints them in an BRIEF list.
// The function also counts how many dragons that was found and returns void.
static void printDragonMatches(char dragon[NAME_SIZE], Database *database, int dragonIdx, int *dragonMatches, enum ListType listType);
// This function basically prints info BRIEF or DETAILED about a dragon and returns void.
static void printDragon(Dragon dragon, enum ListType listType);
// This function converts a string to uppercase and returns void.
static void stringToUpr(char *string);

// Start of function insertDragon.
void insertDragon(Database *database) {
    
    //Expands database when capacity reached its maximum
    if (database->size == database->capacity) expandDatabase(database); 
    int dragonIndex = database->size;
    
    setDragonName(database, dragonIndex); // Sets name of the dragon.
    setIsVolant(database, dragonIndex); // Sets if the the dragon can fly or not.
    setFierceness(database, dragonIndex); // Sets fierceness of the dragon.
    setDragonColor(database, dragonIndex); // Sets the colors of the dragon. 

    database->dragons[dragonIndex].id = database->nextId; //Gives the inserted dragon the correct ID.
    printf("The dragon %s was entered into the database!\n", database->dragons[dragonIndex].name);

    database->size++; //Increases the size of the database when a dragon have been inserted.
    database->nextId++; //Increases the nextID of the database when a dragon have been inserted.
}// End of function insertDragon.
// Start of function setDragonName.
static void setDragonName(Database *database, unsigned int dragonIndex) { // Sets name of the dragon.
    char dragonName[NAME_SIZE];
    bool isValidName = false;

    while (!isValidName) { // Loops as long as the user tries to insert a incorrect name.
        isValidName = true;
        printf("Please enter the name of your dragon: ");
        fflush(stdin);
        scanf("%10s", dragonName);
        
        int i = 0;
        while (dragonName[i] != '\0' && isValidName) {// Loops until the whole string is checked if it is valid.
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
    database->dragons[dragonIndex].name = malloc(sizeof(char [NAME_SIZE])); // Allocates memory on the heap for the dragons name.
    strcpy(database->dragons[dragonIndex].name, dragonName); // Sets the name of the dragon in the correct position of the database.
}// End of function setDragonName.
// Start of function setIsVolant.
static char setIsVolant(Database *database, unsigned int dragonIndex) { // Sets if the the dragon can fly or not.
    char isVolant;
    do { // Prompts the user first and if the input is invalid the function loops until a valid character is entered. 
        printf("Is your dragon volant? (Y/N): ");
        fflush(stdin);
        scanf("%c", &isVolant);

        isVolant = toupper(isVolant);

        if (isVolant != 'Y' && isVolant != 'N') 
            puts("Invalid input! Please try again.\n");

    } while (isVolant != 'Y' && isVolant != 'N');

    database->dragons[dragonIndex].isVolant = isVolant; // Sets Y or N in correct position of the database.
}// End of function setIsVolant.
// Start of function setFierceness.
static int setFierceness(Database *database, unsigned int dragonIndex) { // Sets fierceness of the dragon.
    unsigned int fierceness;
    do { // Prompts the user first and if the input is invalid the function loops until a valid integer is entered. 
        printf("How fierce is your dragon? (1-10): ");
        fflush(stdin);
        scanf("%u", &fierceness);

        if (fierceness > 10)
            puts("Invalid input! Please enter numbers of the given range.\n");

    } while (fierceness < 0 || fierceness > 10);

    database->dragons[dragonIndex].fierceness = fierceness; // Sets inputed integer in the correct position of the database.
}// End of function setFierceness.
// Start of function setDragonColor.
static void setDragonColor(Database *database, unsigned int dragonIndex) { // Sets the colors of the dragon.

    unsigned int numColours = 0;
    char color[NAME_SIZE];

    while (numColours < MAX_COLOURS) { // Loops until maximum number of colors is reached.
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
            formatColorStr(color, &isValidInput); // Controls if the user is inserting valid colors.
            // Allocates memory on the heap for the number of colors inserted.
            database->dragons[dragonIndex].colours[numColours] = malloc(sizeof(char) * colorLength);
            // Sets inputed colors in the correct positions of the database.
            strcpy(database->dragons[dragonIndex].colours[numColours], color);

            if (isValidInput) numColours++;
        }
    }
    database->dragons[dragonIndex].numColours = numColours; // Changes the number of colors a dragon has.
}// End of function setDragonColor.
// Start of function formatColorStr.
static void formatColorStr(char *string, bool *isValidInput) { // Checks if the color is entered in a valid format.
    int i = 0;
    while (string[i] != '\0' && *isValidInput) {
        if (!isalpha(string[i])) { // If any character in the color entered is not part of the english alphabet input is invalid.
            puts("Invalid input! Colour must contain characters of A-Z");
            *isValidInput = false;
        }
        else {
            string[i] = toupper(string[i]);
            i++;
            *isValidInput = true;
        }
    }
}// End of function formatColorStr.
// Start of function updateDragon.
void updateDragon(Database* database) { // Updates an dragon in the database.    
    
    char input[NAME_SIZE];
    int dragonIdx = -1;

    while (dragonIdx == -1) { // Loops as long as no dragon is found.
        printf("Please enter a id or a name of the dragon you want to update: ");
        fflush(stdin);
        scanf("%s", input);

        dragonIdx = findDragonIndex(input, database); // Returns a dragon's index or -1 if no dragon was found.

        if (dragonIdx != -1) { // If dragon was found user can update the dragon's abilities.
            setIsVolant(database, dragonIdx); // Sets if the the dragon can fly or not.
            setFierceness(database, dragonIdx); // Sets fierceness of the dragon.
            setDragonColor(database, dragonIdx); // Sets the colors of the dragon.

            isdigit(input[0])
            ? printf("The dragon with id %d has been updated!\n", database->dragons[dragonIdx].id)
            : printf("The dragon with name %s has been updated!\n", database->dragons[dragonIdx].name);
        }
        else puts("Could not find a matching dragon, please try again!\n");
    }
}// End of function updateDragon.
// Start of function deleteDragon.
void deleteDragon(Database *database) { // Deletes a dragon from the database.

    char input[NAME_SIZE];
    int dragonIdx = -1;

    while (dragonIdx == -1) { // Loops as long as no dragon is found.
        printf("Please enter a id or a name of the dragon you want to delete: ");
        fflush(stdin);
        scanf("%s", input);

        dragonIdx = findDragonIndex(input, database); // Returns a dragon's index or -1 if no dragon was found.

        if (dragonIdx != -1) { // If dragon was found the dragon is deleted from the database.
            isdigit(input[0])
            ? printf("The dragon with id %d has been deleted!\n", database->dragons[dragonIdx].id)
            : printf("The dragon with name %s has been deleted!\n", database->dragons[dragonIdx].name);
            // Moves the dragon that the user wants to delete to the end of the database.
            for (size_t i = dragonIdx; i < database->size; i++) {
                swapDragons(database, i);
            }
            database->size--; // Dercreasing the size of the database and completes the deletion of the dragon.
        }
        else puts("Could not find a matching dragon, please try again!\n");
    }
}// End of function deleteDragon.
// Start of function swapDragons.
static void swapDragons(Database *database, int i) { // Swaps the position of two adjecent dragons in the database.
    Dragon tempDragon = database->dragons[i];
    database->dragons[i] = database->dragons[i+1];
    database->dragons[i+1] = tempDragon;
} // End of function swapDragons.
// Start of function listBriefDragons.
void listBriefDragons(Database* database) { // Lists all dragons in the database BRIEF.
    printHeader(BRIEF);

    for (size_t i = 0; i < database->size; i++) { // Prints the dragons to the screen.
        printDragon(database->dragons[i], BRIEF);
    }
}// End of function listBriefDragons.
// Start of function listDetailedDragons.
void listDetailedDragons(Database* database) { // Lists all dragons in the database DETAILED.
    printHeader(DETAILED);

    for (size_t i = 0; i < database->size; i++) { // Prints the dragons to the screen.
        printDragon(database->dragons[i], DETAILED);
    }
}// End of function listDetailedDragons.
// Start of function showDragonDetail.
void showDragonDetail(Database *database) { // Shows all details of one specific dragon.

    char input[NAME_SIZE];

    printf("Please enter id or name of dragon: ");
    fflush(stdin);
    scanf("%s", input);

    int dragonIdx = findDragonIndex(input, database); // Returns a dragon's index or -1 if no dragon was found.
    if (dragonIdx != -1) {
        printHeader(DETAILED);
        printDragon(database->dragons[dragonIdx], DETAILED);
    }
    if (dragonIdx == -1) printf("Could not find a dragon match.");
}// End of function showDragonDetail.
// Start of function printHeader.
static void printHeader(enum ListType listType) { // Prints a header BRIEF or DETAILED.
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
} // End of function printHeader.
// Start of function findDragonIndex.
// Searches for a dragon by name or id and returns its index if found orelse it returns -1.
static int findDragonIndex(char input[NAME_SIZE], Database *database) {
    int dragonIdx = -1;

    if (isdigit(input[0])) return dragonIdx = getDragonIndex(input, database);
    else {
        stringToUpr(input); // Converts input string to uppercase letters.
        unsigned int dragonMatches = 0;
        // Searches for a dragon by name and returns the index of the first occurance of that name or if no dragon found returns -1.
        dragonIdx = getDragonIndex(input, database);
        printDragonMatches(input, database, dragonIdx, &dragonMatches, BRIEF); // Prints all dragons with the same name.

        if (dragonMatches > 1) { // If we have more than one dragon with the same name.
            int dragonID = -1;
            while (dragonID == -1) { // Loops until user inputs a valid id provided from the list printed to the screen.
                printf("Please enter the id matching the dragon you want to select: ");
                fflush(stdin);
                scanf("%d", &dragonID);
                // Loops through the whole database until a dragon with the correct name and id is found.
                for (size_t i = 0; i < database->size; i++) {
                    if (dragonID == database->dragons[i].id && strcmp(input, database->dragons[i].name) == 0) {
                        dragonID = 0;
                        return i;
                    }
                }
                if (dragonID != 0) {
                    dragonID = -1; 
                    puts("Invalid input! Please select one of the listed selections above.\n");
                }
            }
        }
        else return dragonIdx;
    }
}// End of function findDragonIndex.
// Start of function getDragonIndex.
// Returns dragon index based on name, id or if no dragon found returns -1.
static int getDragonIndex(char input[NAME_SIZE], Database *database) {
    char *endPtr;
    int dragonIdx = -1;

    if (isdigit(input[0])) { // Checks if the string is a id.
        int dragonID = strtol(input, &endPtr, 10);
        for (size_t i = 0; i < database->size; i++) {
            if (dragonID == database->dragons[i].id) {
                return i;
            }
        }
    }
    else if (isalpha(input[0])) { // Checks if the string is a name.
        for (size_t i = 0; i < database->size; i++) {
            stringToUpr(input); // Converts the string to uppercase letters.
            if (strcmp(input, database->dragons[i].name) == 0) {
                return i;
            }
        }
    }
    return dragonIdx;
}// End of function getDragonIndex.
// Start of function printDragonMatches.
// Prints all dragons with the same name or one dragon based on id.
static void printDragonMatches(char input[NAME_SIZE], Database *database, int dragonIdx, int *dragonMatches, enum ListType listType) {
    char *endPtr;
    for (size_t i = dragonIdx; i < database->size; i++) { // Prints dragons based on id or name.
        if (strtol(input, &endPtr, 10) == database->dragons[i].id) {
            printDragon(database->dragons[i], listType);
            return;
        } 
        else if (strcmp(input, database->dragons[i].name) == 0) {
            printDragon(database->dragons[i], listType);
            *dragonMatches+=1; // Counts number of dragons with the same name found.
        }
    }
} // End of function printDragonMatches.
// Start of function printDragon.
static void printDragon(Dragon dragon, enum ListType listType) { // Prints info of a dragon DETAILED or BRIEF.
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
}// End of function printDragon.
// Start of function stringToUpr.
static void stringToUpr(char *string) { // Converts strings to uppercase letters.
    for (size_t i = 0; string[i] != '\0'; i++) {
        string[i] = toupper(string[i]);
    }
}// End of function stringToUpr.
#include <stdio.h>
#include <string.h>
#include "database.h"
#include "dragon.h"
#include "ui.h"

void executeCommands(Database *database) {
    int inputValue = 0;
   
    displayMainMenu(); // Displays the different options you have.

    while (inputValue != -1) {
        printf("\n?: ");
        fflush(stdin);
        scanf("%d", &inputValue);

        switch (inputValue) {
            case 0: displayMainMenu(); break;
            case 1: insertDragon(database); break;
            case 2: updateDragon(database); break;
            case 3: deleteDragon(database); break;
            case 4: listBriefDragons(database); break;
            case 5: listDetailedDragons(database); break;
            case 6: showDragonDetail(database); break;
            case 7: listDBStatistics(database); break;
            case 8: sortDatabase(database); break;
            case -1: puts("Have a good one! See ya!"); break;
            default: puts("Invalid selection. Please try again!"); break;   
        }
    }
} // End of the function executeCommands

void printWelcomeMessage() {
    puts(
        "\n=========================================================================="
        "\n  This program helps organize information about dragons. You may add and"
        "\n  remove dragons and their attributes, list the dragons currently in the"
        "\n  database, and their attributes, look up the attributes of an individual"
        "\n  dragon, get statistics from the database, or sort the database."
        "\n==========================================================================\n"
    );
}

void displayMainMenu() { // Displays the main menu and promtps the user to select an option.
    printf(
        "\n== Main Menu ==\n"
        "0. Display menu.\n"
        "1. Insert a dragon.\n"
        "2. Update a dragon.\n"
        "3. Delete a dragon.\n"
        "4. List all dragons (brief).\n"
        "5. List all dragons (detailed).\n"      
        "6. Show details for a specific dragons.\n"      
        "7. List database statistics.\n"
        "8. Sort database.\n"      
        "-1. Quit.\n"
    );
} // End of displayMainMenu

void listDBStatistics(Database* database) {
    puts("---------------------------------------------------");
    puts("Size MinFierceness MaxFierceness #Volant #NonVolant");
    puts("---------------------------------------------------");

    int max_fierceness = 0;
    int min_fierceness = 10;
    int volant = 0;
    int nonVolant = 0;
    for (size_t i = 0; i < database->size; i++) {
        if (max_fierceness < database->dragons[i].fierceness)
            max_fierceness = database->dragons[i].fierceness;

        if (min_fierceness > database->dragons[i].fierceness)
            min_fierceness = database->dragons[i].fierceness;
        if (database->dragons[i].isVolant == 'Y') volant++;
        if (database->dragons[i].isVolant == 'N') nonVolant++;
    }

    printf("%4d %13d %13d %7d %10d\n", database->size, min_fierceness, max_fierceness, volant, nonVolant);
}

// Start of function sortDatabase.
void sortDatabase(Database *database) { // Sorts a database in ascending order based on id or name.
    int input = -1;

    while (input != 0 && input != 1) {
        printf("Enter sort by id (0) or name (1): ");
        fflush(stdin);
        scanf("%d", &input);
        if (input != 0 && input != 1) puts("Invalid input, please try again!");
    }

    for (unsigned int h = 0; h < database->size-1; ++h) { // loop to control comparisons during each pass
        for (int j = 0, i = 0; j < database->size-1;) {
            if (input == 0) sortDragonsByID(database, &j);
            else if (input == 1) sortDragonsByName(database, &i, &j);        
        }   
    }
    puts("Database sorted.");
}

// Start of function swap.
static void swapDragon(Database *database, int startidx) { // Swaps dragons in database.
    Dragon tempDragon = database->dragons[startidx];
    database->dragons[startidx] = database->dragons[startidx+1];
    database->dragons[startidx+1] = tempDragon;
} // End of function swap.

static void sortDragonsByID(Database *database, int *j) {
    if (database->dragons[*j].id > database->dragons[*j+1].id) {
        swapDragon(database, *j);
    }
    *j+=1;
}

static void sortDragonsByName(Database *database, int *i, int *j) {
    int dragNameLen1 = strlen(database->dragons[*j].name);
    int dragNameLen2 = strlen(database->dragons[*j+1].name);
    int diff = dragNameLen1 - dragNameLen2; // Calculates the length difference between the two strings.
    int nameLen = (diff <= 0) ? dragNameLen1 : dragNameLen2; // Sets the name length to the shortest name string.

    // If all characters in the name strings were equal, move on to the next dragon
    if (*i == nameLen) nextDragon(i, j);
    else {
        // Checks if the characters on position i in both s
        if (database->dragons[*j].name[*i] > database->dragons[*j+1].name[*i]) {
            if (nameLen == dragNameLen1) swapDragon(database, *j);
            else swapDragon(database, *j+1);
            nextDragon(i, j);
        }
        // If characters are equal continue comparing the next set of characters
        else if (database->dragons[*j].name[*i] == database->dragons[*j+1].name[*i]) *i+=1;
        else nextDragon(i, j);
    }
}

static void nextDragon(int *i, int *j) {
    *j+=1; *i = 0;
}
#include <stdio.h>
#include <string.h>
#include "database.h"
#include "dragon.h"
#include "ui.h"

static void sortDragonsByID(Database *database, int *j);
static void sortDragonsByName(Database *database, int *i, int *j);
static void nextDragon(int *i, int *j);

// Handles the execution of the program depending on the input from the user.
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
}

// Prints a welcome message.
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

// Displays the main menu.
void displayMainMenu() { 
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
}

// Displays statistics about the database.
void listDBStatistics(Database* database) {
    puts("---------------------------------------------------");
    puts("Size MinFierceness MaxFierceness #Volant #NonVolant");
    puts("---------------------------------------------------");

    unsigned int max_fierceness = 0;
    unsigned int min_fierceness = database->size == 0 ? 0 : database->dragons[0].fierceness;
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

// Sorts the database either by id or name in acending order.
void sortDatabase(Database *database) {
    int input = -1;

    // Loops until the user enters a valid option.
    while (input != 0 && input != 1) {
        printf("Enter sort by id (0) or name (1): ");
        fflush(stdin);
        scanf("%d", &input);
        if (input != 0 && input != 1) puts("Invalid input, please try again!");
    }

    for (unsigned int h = 0; h < database->size-1; ++h) { // loop to control comparisons during each pass.
        for (int j = 0, i = 0; j < database->size-1;) {
            if (input == 0) sortDragonsByID(database, &j); // If 0 is entered, dragons are sorted by id.
            else sortDragonsByName(database, &i, &j); // Otherwise dragons are sorted by name.
        }   
    }
    puts("Database sorted.");
}

// Sorts database by id order.
static void sortDragonsByID(Database *database, int *j) {
    if (database->dragons[*j].id > database->dragons[*j+1].id) {
        swapDragons(database, *j);
    }
    *j+=1;
}

// Sorts database by name order.
static void sortDragonsByName(Database *database, int *i, int *j) {
    int dragNameLen1 = strlen(database->dragons[*j].name);
    int dragNameLen2 = strlen(database->dragons[*j+1].name);
    int diff = dragNameLen1 - dragNameLen2; // Calculates the length difference between the two strings.
    int minLength = (diff <= 0) ? dragNameLen1 : dragNameLen2; // Sets the name length to the shortest name string.

    // If all characters in both name strings were equal, move on to the next dragon.
    if (*i == minLength) nextDragon(i, j);
    else {
        // If the character of position i in the first string comes after the character of position i in the second string in alphabetic order, the dragons swap positions.
        if (database->dragons[*j].name[*i] > database->dragons[*j+1].name[*i]) swapDragons(database, *j);
        // Else if characters of position i are equal continue comparing the next set of characters.
        else if (database->dragons[*j].name[*i] == database->dragons[*j+1].name[*i]) *i+=1;
        // Else order is correct, continue to the next pair of dragons.
        else nextDragon(i, j); 
    }
}

// Helper function that manipulates the i and j variable to proceed to the next dragon in the sort function.
static void nextDragon(int *i, int *j) {
    *j+=1; *i = 0;
}
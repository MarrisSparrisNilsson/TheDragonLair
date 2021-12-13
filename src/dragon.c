#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include "database.h"

#define NAME_SIZE 10

void insertDragon(Database* database) {

    char dragonName = setDragonName();
    char isVolant = setIsVolant();
    int fierceness = setFierceness();
    char dragonColor = setDragonColor();

    // Insert into database

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
char setDragonName() {
    char dragonName[NAME_SIZE];
    bool isValidName = false;
    printf("Please enter the name of your dragon: ");

    while (isValidName == false) {
        scanf("%s", &dragonName);
        
        for (size_t i = 0; i < NAME_SIZE; i++) {
            if (!isalpha(dragonName[i])) { // If the character on position i is NOT an alpha character, the name is invalid.
                puts("\nInvalid name! Allowed characters are: (A-Z, a-z).\n");
                printf("Please enter the name of your dragon: ");
                break;
            }        
            isValidName = true;
        }
    }
    return dragonName;
}


// When a valid name has been entered, the program should ask the user to enter if the dragon
// can fly or not, i.e. isVolant. Only the characters 'Y' or 'N' (or their lower case equivalents 'y')
// or 'n') are valid. An invalid choice is again handled with an error message and asking the user to
// try again.
char setIsVolant() {
    char isVolant[1];

    do {
        printf("Is your dragon volant? (Y/N): ");
        scanf("%c", &isVolant);

        toupper(isVolant);

        if (isVolant != 'Y' || isVolant != 'N') 
            puts("Invalid input! Please try again.\n");

    } while (isVolant != 'Y' || isVolant != 'N');
    
    return isVolant;
}

// Next, the program should ask the user to enter the dragon’s fierceness, where the only valid
// values are in the integer range 1-10. An invalid choice is yet again handled with an error message
// and asking the user to try again.
int setFierceness() {
    unsigned int fierceness;

    do {
        printf("How fierce is your dragon? (1-10): ");
        scanf("%u", &fierceness);

        if (fierceness > 10)
            puts("Invalid input! Please enter numbers of the given range.\n");

    } while (fierceness != 'Y' || fierceness != 'N');
    
    return fierceness;
}

// Finally, the program should ask the user to supply between 1-5 colours for the dragon (where
// a colour is an arbitrary string representing a colour). The user should not select the number
// of colours to enter, prior to entering the colours. Instead, the program should stop asking for
// additional colours when the user enters an empty string, or when 5 colours have been entered.
char setDragonColor() {

}

void updateDragon(Database* database, Dragon dragon) {

}

void deleteDragon(Database* database, Dragon dragon) {
    
}

void listBriefDragons(Database* database, Dragon dragon) {
    
}

void listDetailedDragons(Database* database, Dragon dragon) {
    
}

void showDragonDetail(Database* database, Dragon dragon) {
    
}
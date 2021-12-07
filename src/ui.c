#include "database.h"
#include "dragon.h"

// #define NAME_SIZE 10

void executeCommands(database) { 
    puts("Welcome to the dragon lair!");

    int inputValue = 0;
   
    displayMainMenu(); // Displays the different options you have.

    while (inputValue != -1) {
        printf("?: ");
        scanf("%d", &inputValue);

        switch (inputValue) {
            
            case 0: 
                displayMainMenu();
                break;

            case 1:
                // char input[NAME_SIZE];

                // for (size_t i = 0; i < NAME_SIZE; i++) {
                // printf("Please enter the name of your dragon: ");
                // scanf("%s", &input);
                //     while (something) {
                    
                //         if (!isalpha(input[i])) {
                //             printf("Invalid input! Allowed characters are: (A-Z, a-z).");
                //             break;
                //         }
                    
                //     }
                // }
                

                break;

            case 2: 
            
                break;
                
            case 3:
                
                break;
            
            case 4:
                
                break;

            case 5:
                break;

            case 6:
                break;

            case 7: 
                
                break;
            
            case 8:
                
                break;

            case -1:
                printf("Have a good one! See ya!");
                break;

            default:
                puts("Invalid selection. Please try again.!\n");
                break;   
        }
    }
} // End of the function executeCommands

void printWelcomeMessage() {
    puts(
        "=========================================================================="
        "\n  This program helps organize information about dragons. You may add and"
        "\n  remove dragons and their attributes, list the dragons currently in the"
        "\n  database, and their attributes, look up the attributes of an individual"
        "\n  dragon, get statistics from the database, or sort the database."
        "\n=========================================================================="
    );
}

void displayMainMenu() { // Displays the main menu and promtps the user to select an option.
   puts("\n== Main Menu ==\n"
   "0. Display menu.\n"
   "1. Insert a dragon.\n"
   "2. Update a dragon.\n"
   "3. Delete a dragon.\n"
   "4. List all dragons (brief).\n"
   "5. List all dragons (detailed).\n"      
   "6. Show details for a specific dragons.\n"      
   "7. List database statistics.\n"
   "8. Sort database.\n"      
   "-1. Quit.\n");      
} // End of displayMainMenu


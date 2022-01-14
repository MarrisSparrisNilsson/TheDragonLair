#ifndef _ui_h
#define _ui_h

#include "dBstructs.h"

// Handles the execution of the program depending on the input from the user.
void executeCommands(Database *database);
// Prints a welcome message.
void printWelcomeMessage();
// Displays the main menu.
void displayMainMenu();
// Displays statistics about the database.
void listDBStatistics(Database* database);
// Sorts the database either by id or name in acending order.
void sortDatabase(Database *database);

#endif
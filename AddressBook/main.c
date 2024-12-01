/*Documentation
NAME : ANUBHAV ANAND

TITLE : C - Project "ADDRESS BOOK"

DESCRIPTION : It keeps track of names and telephone/mobile numbers and e-mail addresses.

FILES : main.c, contact.c, Extra_Functions.c, file.c, contact.h, file.h

FILE DESCRIPTION:
1. main.c : It is the main file containing the main function and initialization, It is responsible for performing main operations in Address Book
2. contact.c : It contains all the function definition and code logic for for main menu and all the sub menus inside Address Book
3. Extra_Functions.c : This file contains all the sub functions for supporting the main functions responisble for performing different operations inside Address Book
4. file.c : It contains function definition and code logic for saving data in the CSV file and fetching data from the CSV file
5. contact.h : It contains Address Book structure for storing names, phone numbers and email address, it also contains all the function declaration
5. file.h : It contains the function declation for save contact in file function and load contact for file function present in file.c

DATE : 01-12-2024

EXECUTION :
1. Compile : To compile the all the codes present inside the Address Book directory, Type gcc *c in terminal and press enter this will generate an OUTPUT file in the same directory
2. Run : To run the generated output file type ./(Output File name).out and the main menu of Address Book will pop up

*/


#include <stdio.h>
#include "contact.h" // Include contact header file having AddressBook structure and function declarations

int main()
{
    int choice;
    AddressBook addressBook; // Declare the variable name for AddressBook structure
    initialize(&addressBook); // Initialize the address book

    do // The block of code will be extecuted once and then the condition will be evaluated
    {
        // AddressBook Menu for performing different operations in AddressBook
        printf("\nAddress Book Menu:\n");
        printf("1. Create contact\n");
        printf("2. Search contact\n");
        printf("3. Edit contact\n");
        printf("4. Delete contact\n");
        printf("5. List all contacts\n");
        printf("6. Save&Exit\n");
        printf("\nEnter your choice: ");
        scanf("%d", &choice); // Read the input from the user inside the choice variable
        getchar();

        switch (choice) // Using switch case with value of choice variable to navigate through different operations in AddressBook
        {
        case 1:
            createContact(&addressBook);
            break;
        case 2:
            searchContact(&addressBook, NULL); // search contact function takes addressbook and integer pointer as arguments, pass NULL while calling the function from main function
            break;
        case 3:
            editContact(&addressBook);
            break;
        case 4:
            deleteContact(&addressBook);
            break;
        case 5:
            listContacts(&addressBook);
            break;
        case 6:
            printf("Saving and Exiting...\n");
            saveAndExit(&addressBook);
            break;
        default:
            printf("Invalid choice. Please try again.\n"); 
        }
    } while (choice != 6); // Run the loop untill the value of choice variable is not equal to 6

    return 0;
}
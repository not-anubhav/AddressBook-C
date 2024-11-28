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
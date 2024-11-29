#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "contact.h"
#include "file.h"

int listContacts(AddressBook *addressBook)
{
    // List all the contacts present in the AddressBook
    if (addressBook->contactCount == 0) { // If the contact count is zero i.e no contacts are present in the address book
        printf("No Contacts Found\n"); // Print the message
    }
    else {
        for (int i = 0; i < addressBook->contactCount; i++) // Run the loop till contact count and print all the contacts present in address book
        {
            printf("Contact %d: %s, Phone: %s, Email ID: %s\n", i + 1, addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email);
        }
    }
    return 0;
}

void initialize(AddressBook *addressBook) // This function is called at the very start of the program and loads the contacts from the CSV file
{
    addressBook->contactCount = 0; // Initialize the contact count to zero and append all the contacts from the file

    // Load contacts from file during initialization (After files)
    loadContactsFromFile(addressBook);
}

void saveAndExit(AddressBook *addressBook)
{
    saveContactsToFile(addressBook); // Save contacts to file
    exit(EXIT_SUCCESS);              // Exit the program
}

void createContact(AddressBook *addressBook)
{
    /* Define the logic to create a Contacts */

    int n_flag = 0; // Name Flag
    int ph_flag = 0; // Phone Flag
    int e_flag = 0; // Email Flag
    do
    {
        char name[50]; // Create a temporary character array name for reading contact name
        printf("Enter the Contact Name : ");
        scanf("%[^\n]", name); // Read the name in character array
        n_flag = read_name(addressBook, name); //  Call the name function and assign the return value to name flag
        if (n_flag == 1) // If the return value is 1
        {
            strcpy(addressBook->contacts[addressBook->contactCount].name, name); // Append the name in the structure member name of address book
        }
        else
        {
            printf("Invalid Name.\n"); // If the return value is 0 print the error message
        }
        getchar();
    } while (n_flag == 0); // Loop will run based on this evaluated condition

    do
    { 
        char mob[11]; // Create a temporary character array for reading contact phone number
        printf("Enter the Mobile Number : ");
        scanf("%s", mob); // Read the input in character array
        ph_flag = read_mob(addressBook, mob); // Call the read_mob function and assign its return value to phone flag
        if (ph_flag == 1) // If return value is 1
        {
            int v_p = validate_phone(addressBook, mob); // Declare an integer variable v_p(validate phone) and store the return value of validate phone function in it
            if (v_p == 1) // If the function returns 1
            {
                ph_flag = 0; // Reset the phone flag value to 0
            }
            else
            {
                strcpy(addressBook->contacts[addressBook->contactCount].phone, mob); /* If the v_p function returns 0 then Append the input phone number 
                in structure member phone of address book*/
            }
        }
        else
        {
            printf("Enter Valid Phone Number.\n"); // If the read_mob function returns 0 the print the error message
        }
        getchar();
    } while (ph_flag == 0); // Loop will run based on this evaluated condition

    do
    {
        char email[50]; // Create a temporary character array for reading contact email id
        printf("Enter the Email ID: ");
        scanf("%s", email); // Read the input in character array
        e_flag = read_email(addressBook, email); // Call the read_email function and assign its return value to email flag
        if (e_flag == 1) // If return value is 1
        {
            int v_e = validate_email(addressBook, email); // Declare an integer variable v_e(validate email) and store the return value of validate email function in it
            if (v_e == 1) // If the function returns 1
            {
                e_flag = 0; // Reset the email flag value to 0
            }
            else
            {
                strcpy(addressBook->contacts[addressBook->contactCount].email, email); /* If the v_e function returns 0 the Append the input email id
                in structure member email of address book*/
            }
        }
    } while (e_flag == 0); // Loop will run based on this evaluated condition

    addressBook->contactCount++;
}

int searchContact(AddressBook *addressBook, int *foundindices) // If search function is being call from main function then NULL will be passed in found indices
{
    /* Define the logic for search */
    int option; // option variable to navigate through different operations of search menu
    int foundCount = 0; // Contacts index found count
    int search_n = 0; // search name flag
    int search_p = 0; // search phone flag
    int search_e = 0; // search email flag
    do
    {
        printf("\nSearch Menu:\n");
        printf("1. Search By Name\n");
        printf("2. Search By Phone no.\n");
        printf("3. Search By Email ID\n");
        printf("4. Exit\n");
        printf("\nEnter your choice: ");
        scanf("%d", &option);
        getchar();

        switch (option)
        {
        case 1:
            do
            {   /* Create a temporary character array for storing input name and then pass the address book, name, foundindices and found count
                variable as arguments inside search name function and store it's return value inside the search name flag, use the flag value to 
                run the loop
                */
                char name[50];
                printf("Enter the Contact Name: ");
                scanf("%[^\n]", name);
                if (read_name(addressBook, name) == 1)
                {
                    search_n = search_name(addressBook, name, foundindices, &foundCount);
                }
                else
                {
                    printf("Invalid Name.\n");
                }
                getchar();
            } while (search_n == 0);
            return foundCount;
        case 2:
            do
            {   /* Create a temporary character array for storing input phone number and then pass the address book, phone, foundindices and found count
                variable as arguments inside search phone function and store it's return value inside the search phone flag, use the flag value to 
                run the loop
                */
                char phone[11];
                printf("Enter the Contact Phone no.: ");
                scanf("%s", phone);
                if (read_mob(addressBook, phone) == 1)
                {
                    search_p = search_phone(addressBook, phone, foundindices, &foundCount);
                }
                else
                {
                    printf("Invalid Phone no.\n");
                }
                getchar();
            } while (search_p == 0);
            return foundCount;
        case 3:
            do
            {   /* Create a temporary character array for storing input email id and then pass the address book, email, foundindices and found count
                variable as arguments inside search email function and store it's return value inside the search email flag, use the flag value to 
                run the loop
                */
                char email[50];
                printf("Enter the Contact Email ID.: ");
                scanf("%s", email);
                if (read_email(addressBook, email) == 1)
                {
                    search_e = search_email(addressBook, email, foundindices, &foundCount);
                }
                else
                {
                    printf("Invalid Email ID.\n");
                }
                // getchar();
            } while (search_e == 0);
            return foundCount; // Return the found count value from case 1, case 2, case 3
        case 4:
            return -1; // For input option 4 return to main menu
        default:
            printf("Invalid choice. Please try again.\n");
        }
    } while (option != 4);
}

void editContact(AddressBook *addressBook)
{
    /* Define the logic for Editcontact */

    int foundindices[100]; // Create an integer array for storing the contact indices of found contacts  
    int foundCount = searchContact(addressBook, foundindices);
    /* Call the search function with found indices array and store the return value inside the found count
    also store the index of searched contacts inside the found indices array*/

    if (foundCount <= 0) // If found count is less than or equal to zero i.e no contact found from the search
    {
        printf("No contact found\n"); // Print error message
        return; // Return to the previous menu
    }

    int editindex = 0; // Create a edit index variable for storing the index place user wants to edit
    int edit_flag = 0;

    do
    {
        printf("Enter the contact no. you want to edit : ");
        scanf("%d", &editindex);
        getchar();
        int actualindex = editindex - 1; // The actual index of the contact is 1 index less that the contact value displayed for user
        for (int i = 0; i < foundCount; i++) // Run the loop from start index till last index in found indices array
        {
            if (actualindex == foundindices[i]) // If the actual index is present in the found indices
            {
                edit_flag = 1; // Make the edit flag as 1
                break; // Break the loop
            }
        }
        if (edit_flag == 1) // If the edit flag is 1 then call the edit contact function and pass the index value you want to edit
        {
            edit_contact(addressBook, actualindex);
        }
        else
        {
            printf("Enter Valid Contact no.\n"); // If it is 0 print the error message
        }

    } while (edit_flag == 0); // Run the loop based on the evaluated condition
}

void deleteContact(AddressBook *addressBook)
{
    /* Define the logic for deletecontact */
    int foundindices[100];  // Create an integer array for storing the contact indices of found contacts  

    /* Call the search function with found indices array and store the return value inside the found count
    also store the index of searched contacts inside the found indices array*/
    int foundCount = searchContact(addressBook, foundindices);


    if (foundCount <= 0) // If found count is less than or equal to zero i.e no contact found from the search
    {
        printf("No contact found\n"); // Print error message
        return; // Return to the previous menu
    }

    int deleteindex = 0;
    int del_flag = 0;
    do
    {
        printf("Enter the contact no. you want to delete : ");
        scanf("%d", &deleteindex); // Read the index user wants to delete from the contact list
        getchar();
        int actualindex = deleteindex - 1; // The actual index of the contact is 1 index less that the contact value displayed for user

        for (int i = 0; i < foundCount; i++)
        {
            if (actualindex == foundindices[i]) // If the actual index is found in the found indices array
            {
                del_flag = 1; // Make the delete flag as 1
                break;
            }
        }
        if (del_flag == 1) // If delete flag is 1
        {
            for (int j = actualindex; j < addressBook->contactCount - 1; j++) // Run the loop from actual index till contact count 
            {
                addressBook->contacts[j] = addressBook->contacts[j + 1]; // Left shift every contact from actual index till last the last contact
            }
            addressBook->contactCount--; // Decrement the addressbook contact count
            printf("Contact deleted successfully.\n");
        }
        else
        {
            printf("Enter Valid Contact no.\n");
        }
    } while (del_flag == 0); // Run the loop based on the evaluated condition
}

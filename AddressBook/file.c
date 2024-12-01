#include <stdio.h>
#include "file.h" // Include file.h header file with function declarations for saveContactsToFile and loadContactsFromFile

void saveContactsToFile(AddressBook *addressBook) //Function Definition of saveContactsToFile for storing the contacts informations inside a file
{
    FILE* fptr = fopen("contacts.csv", "w"); // Take a file pointer for storing the file address, open the CSV file in write mode

    fprintf(fptr, "#%d NAME,PHONE,EMAIL\n", addressBook->contactCount); // In the 1st line of CSV file write the contact count with following strings and move the offset to next line

    //Run the loop from 0 to contactCount and write every contact detail inside the file

    for ( int i = 0; i < addressBook->contactCount; i++)
    {
        // Use comma as seperators for storing each detail inside different columns of CSV file and newline after printing each contact detail for moving offset to newline
        fprintf(fptr, "%s,%s,%s\n", addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email);
    }

    fclose(fptr); // Close the file after operation is completed
}

int loadContactsFromFile(AddressBook *addressBook) //Function Definition of loadContactsFromFile for reading the contacts informations from a file
{
    FILE* fptr = fopen("contacts.csv", "r"); // Take a file pointer for storing the file address, open the CSV file in read mode

    if(fptr == NULL) // Check is the file is existing by checking the return address of file, if it returns NULL that mean file does not exist or is inaccessible
    {
        printf("\n>>>>FILE DOES NOT EXIST<<<<\n"); // Print the error message
        return 0; // return to main menu
    }

    // Use the same format used for writing and read the value of count from 1st row of file and store it inside contactCount variable
    fscanf(fptr, "#%d NAME,PHONE,EMAIL\n", &addressBook->contactCount); 
    for(int i = 0; i < addressBook->contactCount; i++)
    {
        // Read the strings from the file and store it in their respective structure members

        fscanf(fptr, "%[a-z A-Z],%[0-9],%s\n", addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email);
    }
    fclose(fptr); // Close the file after operation is completed
}

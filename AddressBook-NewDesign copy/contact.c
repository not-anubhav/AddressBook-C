#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "contact.h"
#include "file.h"
#include "populate.h"

void listContacts(AddressBook *addressBook)
{
    // Sort contacts based on the chosen criteria
    for (int i = 0; i < addressBook->contactCount; i++) {
        printf("Contact %d: %s, Phone: %s, Email ID: %s\n", i + 1, addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email);
    }
}

void initialize(AddressBook *addressBook) {
    addressBook->contactCount = 0;
    populateAddressBook(addressBook);

    // Load contacts from file during initialization (After files)
    loadContactsFromFile(addressBook);
}

void saveAndExit(AddressBook *addressBook) {
    saveContactsToFile(addressBook); // Save contacts to file
    exit(EXIT_SUCCESS); // Exit the program
}

void createContact(AddressBook *addressBook)
{
	/* Define the logic to create a Contacts */

	int n_flag = 0;
	int ph_flag = 0;
	int e_flag = 0;
	do
	{
	    char name[50];
        printf("Enter the Contact Name : ");
        scanf("%[^\n]", name);
	    n_flag = read_name(addressBook, name);
		if(n_flag == 1)
		{
			strcpy(addressBook->contacts[addressBook->contactCount].name, name);
		}
		else {
			printf("Invalid Name.\n");
		}
		getchar();
	}while(n_flag == 0);

	do {
        char mob[11];
        printf("Enter the Mobile Number : ");
        scanf("%s", mob);
        ph_flag = read_mob(addressBook, mob);
        if(ph_flag == 1)
        {
            int v_p = validate_phone(addressBook, mob);
            if(v_p == 1)
            {
                ph_flag = 0;
            }
        }
        else
        {
            printf("Enter Valid Phone Number.\n");
        }
        getchar();
	}while (ph_flag == 0);

	do {
	    char email[50];
		printf("Enter the Email ID: ");
        scanf("%s", email);
	    e_flag = read_email(addressBook, email);
		if(e_flag == 1)
		{
		    int v_e = validate_email(addressBook, email);
            if(v_e == 1)
            {
                e_flag = 0;
            }
		}
	}while (e_flag == 0);

	addressBook->contactCount++;
}

int searchContact(AddressBook *addressBook, int* foundindices)
{
    /* Define the logic for search */
    int option;
    int foundCount = 0;
    int search_n = 0;
    int search_p = 0;
    int search_e = 0;
    do {
        printf("\nSearch Menu:\n");
        printf("1. Search By Name\n");
        printf("2. Search By Phone no.\n");
        printf("3. Search By Email ID\n");
        printf("4. Exit\n");
        printf("\nEnter your choice: ");
        scanf("%d", &option);
        getchar();

        switch (option) {
            case 1:
                do
                {
                    char name[50];
                    printf("Enter the Contact Name: ");
                    scanf("%[^\n]", name);
                    if(read_name(addressBook, name) == 1)
                    {
                        search_n = search_name(addressBook, name, foundindices, &foundCount);
                    }
                    else{
                        printf("Invalid Name.\n");
                    }
                    getchar();
                }while(search_n == 0);
                return foundCount;
            case 2:
                do
                {
                    char phone[10];
                    printf("Enter the Contact Phone no.: ");
                    scanf("%s", phone);
                    if(read_mob(addressBook, phone) == 1)
                    {
                        search_p = search_phone(addressBook, phone, foundindices, &foundCount);
                    }
                    else {
                        printf("Invalid Phone no.\n");
                    }
                    getchar();
                }while(search_p == 0);
                return foundCount;
            case 3:
                do
                {
                    char email[50];
                    printf("Enter the Contact Email ID.: ");
                    scanf("%s", email);
                    if(read_email(addressBook, email) == 1)
                    {
                        search_e = search_email(addressBook, email, foundindices, &foundCount);
                    }
                    else {
                        printf("Invalid Email ID.\n");
                    }
                    //getchar();
                }while(search_e == 0);
                return foundCount;
            case 4:
                return -1;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (option != 4);
}

void editContact(AddressBook *addressBook)
{
	/* Define the logic for Editcontact */


}

void deleteContact(AddressBook *addressBook)
{
	/* Define the logic for deletecontact */
	int foundindices[100];
	int foundCount = searchContact(addressBook, foundindices);
	if (foundCount <=0)
	{
	   printf("No contact found\n");
	   return;
	}

	int deleteindex = 0;
	int del_flag = 0;
	do {
        printf("Enter the contact no. you want to delete : ");
        scanf("%d", &deleteindex);
        getchar();
        int actualindex = deleteindex - 1;
        for (int i = 0; i <= foundCount; i++) {
            if (actualindex == foundindices[i])
            {
                del_flag = 1;
                break;
            }
        }
        if(del_flag == 1)
        {
            for ( int j = actualindex; j <=addressBook-> contactCount; j++ ){
            addressBook->contacts[j] = addressBook->contacts[j + 1];
            }
            addressBook->contactCount--;
            printf("Contact deleted successfully.\n");
        }
        else{
            printf("Enter Valid Contact no.\n");
        }
	}while (del_flag == 0);

}
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
	    n_flag = read_name(addressBook);
	}while(n_flag == 0);

	do {
	    ph_flag = read_mob(addressBook);
	}while (ph_flag == 0);

	do {
	    e_flag = read_email(addressBook);
	}while (e_flag == 0);

	addressBook->contactCount++;
}

void searchContact(AddressBook *addressBook)
{
    /* Define the logic for search */
}

void editContact(AddressBook *addressBook)
{
	/* Define the logic for Editcontact */

}

void deleteContact(AddressBook *addressBook)
{
	/* Define the logic for deletecontact */

}


int read_name(AddressBook *addressBook)
{
    int name_flag = 1;
    char name[50];
    printf("Enter the Contact Name : ");
	scanf("%[^\n]", name);
	if (name[0] == ' ' || name[strlen(name) - 1] == ' ')
	{
	   name_flag = 0;
    }else
    {
        for ( int i = 0; name[i] != '\0'; i++){
            if (!((name[i] >= 'a' && name[i] <= 'z') || (name[i] >= 'A' && name[i] <= 'Z') || name[i] == ' '))
            {
                name_flag = 0;
                break;
            }
            if(i > 0 && name[i] == ' ')
            {
                if(name[i + 1] == ' ')
                {
                    name_flag = 0;
                    break;
                }
            }
        }
    }
	if(name_flag == 1)
	{
		strcpy(addressBook->contacts[addressBook->contactCount].name, name);
		//addressBook->contactCount++;
	}
	else {
		printf("Invalid Name.\n");
	}
	getchar();
	return name_flag;
}

int read_mob(AddressBook *addressBook)
{
    int mob_flag = 1;
    char mob[11];
    printf("Enter the Mobile Number : ");
	scanf("%s", mob);
	if (strlen(mob) != 10 || mob[0] == '0')
	{
		mob_flag = 0;
	}
	else {
        for( int j = 0; mob[j] != '\0'; j++)
        {
            if(!(mob[j] >= '0' && mob[j] <= '9'))
            {
                mob_flag = 0;
                break;
            }
        }
	}
	if(mob_flag == 1)
	{
		int already_present = 0;
		for ( int k = 0; k < addressBook->contactCount; k++){
		    if(strcmp(addressBook->contacts[k].phone, mob) == 0)
			{
				already_present = 1;
				break;
			}
		}
		if(already_present == 0)
		{
			strcpy(addressBook->contacts[addressBook->contactCount].phone, mob);
		}
		else {
			printf("Phone Number already present.\n");
			mob_flag = 0;
		}
	}
	else
	{
		printf("Enter Valid Phone Number.\n");
	}
	getchar();
	return mob_flag;
}

int read_email(AddressBook *addressBook) {
    int mail_flag = 1;
    int at_index = -1;
    int dot_index = -1;
    char email[50];

    printf("Enter the Email ID: ");
    scanf("%s", email);

    if (email[0] == '@' || email[0] == '.' || email[0] == ' ' || email[0] == '\t' ||
        email[strlen(email) - 1] == '@' || email[strlen(email) - 1] == '.') {
        printf("Enter a valid Email ID.\n");
        return 0;
    }

    for (int e = 0; email[e] != '\0'; e++) {
        if (email[e] == ' ' || email[e] == '\t') {
            printf("Enter a valid Email ID.\n");
            return 0;
        }
        if (email[e] == '@') {
            if (at_index != -1) {
                printf("Enter a valid Email ID.\n");
                return 0;
            }
            at_index = e;
        }
        if (email[e] == '.') {
            dot_index = e;
        }
    }

    if (at_index == -1 || dot_index == -1 || at_index > dot_index) {
        printf("Enter a valid Email ID.\n");
        return 0;
    }

    for (int e = 0; e < at_index; e++) {
        if (!isalnum(email[e])) {
            printf("Enter a valid Email ID.\n");
            return 0;
        }
    }

    if (!(email[at_index + 1] >= 'a' && email[at_index + 1] <= 'z')) {
        printf("Enter a valid Email ID.\n");
        return 0;
    }

    for (int d = at_index + 1; d < dot_index; d++) {
        if (!(email[d] >= 'a' && email[d] <= 'z')) {
            printf("Enter a valid Email ID.\n");
            return 0;
        }
    }

    for (int d = dot_index + 1; email[d] != '\0'; d++) {
        if (!(email[d] >= 'a' && email[d] <= 'z')) {
            printf("Enter a valid Email ID.\n");
            return 0;
        }
    }

    int already_present = 0;
    for (int e = 0; e < addressBook->contactCount; e++) {
        if (strcmp(addressBook->contacts[e].email, email) == 0) {
            already_present = 1;
            break;
        }
    }

    if (already_present == 0) {
        strcpy(addressBook->contacts[addressBook->contactCount].email, email);
    } else {
        printf("Email ID already present.\n");
        mail_flag = 0;
    }
    getchar();
    return mail_flag;
}

//#include "contact.h"
#include <stdio.h>
#include <string.h>
#include <ctype.h>

typedef struct {
    char name[50];
    char phone[11]; // Assuming phone number is 10 digits + 1 for null terminator
    char email[50];
}Contact;

typedef struct {
    Contact contacts[100]; // Adjust size as needed
    int contactCount;
} AddressBook;

void createContact(AddressBook *addressBook);
int searchContact(AddressBook *addressBook, int*);
void listContacts(AddressBook *addressBook);
void deleteContact(AddressBook *addressBook);
int read_name(AddressBook *addressBook, char []);
int read_mob(AddressBook *addressBook, char []);
int read_email(AddressBook *addressBook, char []);
int search_name(AddressBook *addressBook, char [], int*, int*);
int search_phone(AddressBook *addressBook, char [], int*, int*);
int search_email(AddressBook *addressBook, char [], int*, int*);
void validate_phone(AddressBook *addressBook, char []);
void validate_email(AddressBook *addressBook, char []);

int main() {
    int choice;
    AddressBook addressBook;
    addressBook.contactCount = 0;
    createContact(&addressBook);
    do {
        printf("\nAddress Book Menu:\n");
        printf("1. Create contact\n");
        printf("2. Search contact\n");
        printf("3. Edit contact\n");
        printf("4. Delete contact\n");
        printf("5. List all contacts\n");
        printf("6. Exit\n");
        printf("\nEnter your choice: ");
        scanf("%d", &choice);
        getchar();

        switch (choice) {
            case 1:
                createContact(&addressBook);
                break;
            case 2:
                searchContact(&addressBook, NULL);
                break;
            // case 3:
            //     editContact(&addressBook);
            //     break;
            case 4:
                deleteContact(&addressBook);
                break;
            case 5:
                listContacts(&addressBook);
                break;
            case 6:
                printf("Saving and Exiting...\n");
                //saveContactsToFile(&addressBook);
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 6);
    return 0;
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
			//addressBook->contactCount++;
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
            validate_phone(addressBook, mob);
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
		    validate_email(addressBook, email);
		}
	}while (e_flag == 0);

	addressBook->contactCount++;
}

void listContacts(AddressBook *addressBook)
{
    // Sort contacts based on the chosen criteria
    for (int i = 0; i < addressBook->contactCount; i++) {
        printf("Contact %d: %s, Phone: %s, Email ID: %s\n", i + 1, addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email);
    }
}

int read_name(AddressBook *addressBook, char name[])
{
    int name_flag = 1;
 //    char name[50];
 //    printf("Enter the Contact Name : ");
	// scanf("%[^\n]", name);
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
	return name_flag;
}

int read_mob(AddressBook *addressBook, char mob[])
{
    int mob_flag = 1;

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
	return mob_flag;
}

void validate_phone(AddressBook *addressBook, char mob[])
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
    }
}

int read_email(AddressBook *addressBook, char email[]) {
    int mail_flag = 1;
    int at_index = -1;
    int dot_index = -1;


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
    getchar();
    return mail_flag;
}

void validate_email(AddressBook *addressBook, char email[])
{
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
    }
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
                    char phone[50];
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
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (option != 4);
}

int search_name(AddressBook *addressBook, char name[], int* foundindices, int* foundCount)
{

    int flag_found = 0;
    for (int i = 0; i < addressBook->contactCount; i++)
    {
        if (strcmp(addressBook->contacts[i].name, name) == 0)
        {
            flag_found = 1;
            if (foundindices != NULL){
                foundindices[*foundCount] = i;
                (*foundCount)++;
            }
            printf("Contact %d: %s, Phone: %s, Email ID: %s\n", i + 1, addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email);
        }
    }
    if (flag_found == 0) {
        printf("Contact not Found.\n");
    }
    return flag_found;
}

int search_phone(AddressBook *addressBook, char phone[],int* foundindices, int* foundCount)
{
    int flag_found = 0;

    for (int i = 0; i < addressBook->contactCount; i++)
    {
        if(strcmp(addressBook->contacts[i].phone, phone) == 0)
        {
            flag_found = 1;
            if (foundindices != NULL){
                foundindices[*foundCount] = i;
                (*foundCount)++;
            }
            printf("Contact %d: %s, Phone: %s, Email ID: %s\n", i + 1, addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email);
        }
    }
    if (flag_found == 0) {
        printf("Contact not Found.\n");
    }
    return flag_found;
}

int search_email(AddressBook *addressBook, char email[], int* foundindices, int* foundCount)
{
    int flag_found = 0;
    for (int i = 0; i < addressBook->contactCount; i++)
    {
        if(strcmp(addressBook->contacts[i].email, email) == 0)
        {
            flag_found = 1;
            if (foundindices != NULL){
                foundindices[*foundCount] = i;
                (*foundCount)++;
            }
            printf("Contact %d: %s, Phone: %s, Email ID: %s\n", i + 1, addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email);
        }
    }
    if (flag_found == 0) {
        printf("Contact not Found.\n");
    }
    return flag_found;
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

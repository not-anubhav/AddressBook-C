#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "contact.h"

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

	if (strlen(mob) != 10)
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

int validate_phone(AddressBook *addressBook, char mob[])
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
    return already_present;
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

int validate_email(AddressBook *addressBook, char email[])
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
    return already_present;
}

int search_name(AddressBook *addressBook, char name[])
{

    int flag_found = 0;
    for (int i = 0; i < addressBook->contactCount; i++)
    {
        if (strcmp(addressBook->contacts[i].name, name) == 0)
        {
            flag_found = 1;
            printf("Contact %d: %s, Phone: %s, Email ID: %s\n", i + 1, addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email);
        }
    }
    if (flag_found == 0) {
        printf("Contact not Found.\n");
    }
    return flag_found;
}

int search_phone(AddressBook *addressBook, char phone[])
{
    int flag_found = 0;

    for (int i = 0; i < addressBook->contactCount; i++)
    {
        if(strcmp(addressBook->contacts[i].phone, phone) == 0)
        {
            flag_found = 1;
            printf("Contact %d: %s, Phone: %s, Email ID: %s\n", i + 1, addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email);
        }
    }
    if (flag_found == 0) {
        printf("Contact not Found.\n");
    }
    return flag_found;
}

int search_email(AddressBook *addressBook, char email[])
{
    int flag_found = 0;
    for (int i = 0; i < addressBook->contactCount; i++)
    {
        if(strcmp(addressBook->contacts[i].email, email) == 0)
        {
            flag_found = 1;
            printf("Contact %d: %s, Phone: %s, Email ID: %s\n", i + 1, addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email);
        }
    }
    if (flag_found == 0) {
        printf("Contact not Found.\n");
    }
    return flag_found;
}
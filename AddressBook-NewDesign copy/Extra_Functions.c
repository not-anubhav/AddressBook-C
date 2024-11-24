#include "contact.h"
#include <stdio.h>
#include <ctype.h>
#include <string.h>

int read_name(AddressBook *addressBook, char name[])
{
    int name_flag = 1;
    if (name[0] == ' ' || name[strlen(name) - 1] == ' ' || strlen(name) > 49)
    {
        name_flag = 0;
    }
    else
    {
        for (int i = 0; name[i] != '\0'; i++)
        {
            if (!((name[i] >= 'a' && name[i] <= 'z') || (name[i] >= 'A' && name[i] <= 'Z') || name[i] == ' '))
            {
                name_flag = 0;
                break;
            }
            if (i > 0 && name[i] == ' ')
            {
                if (name[i + 1] == ' ')
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
    else
    {
        for (int j = 0; mob[j] != '\0'; j++)
        {
            if (!(mob[j] >= '0' && mob[j] <= '9'))
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
    for (int k = 0; k < addressBook->contactCount; k++)
    {
        if (strcmp(addressBook->contacts[k].phone, mob) == 0)
        {
            already_present = 1;
            break;
        }
    }
    if (already_present == 1)
    {
        printf("Phone Number already present.\n");
    }
    // if(already_present == 0)
    // {
    //     strcpy(addressBook->contacts[addressBook->contactCount].phone, mob);
    // }
    // else {
    //     printf("Phone Number already present.\n");
    // }
    return already_present;
}

int read_email(AddressBook *addressBook, char email[])
{
    int mail_flag = 1;
    int at_index = -1;
    int dot_index = -1;

    if (strlen(email) > 49 || email[0] == '@' || email[0] == '.' || email[0] == ' ' || email[0] == '\t' ||
        email[strlen(email) - 1] == '@' || email[strlen(email) - 1] == '.')
    {
        printf("Enter a valid Email ID.\n");
        return 0;
    }

    for (int e = 0; email[e] != '\0'; e++)
    {
        if (email[e] == ' ' || email[e] == '\t')
        {
            printf("Enter a valid Email ID.\n");
            return 0;
        }
        if (email[e] == '@')
        {
            if (at_index != -1)
            {
                printf("Enter a valid Email ID.\n");
                return 0;
            }
            at_index = e;
        }
        if (email[e] == '.')
        {
            dot_index = e;
        }
    }

    if (at_index == -1 || dot_index == -1 || at_index > dot_index)
    {
        printf("Enter a valid Email ID.\n");
        return 0;
    }

    for (int e = 0; e < at_index; e++)
    {
        if (!isalnum(email[e]))
        {
            printf("Enter a valid Email ID.\n");
            return 0;
        }
    }

    if (!(email[at_index + 1] >= 'a' && email[at_index + 1] <= 'z'))
    {
        printf("Enter a valid Email ID.\n");
        return 0;
    }

    for (int d = at_index + 1; d < dot_index; d++)
    {
        if (!(email[d] >= 'a' && email[d] <= 'z'))
        {
            printf("Enter a valid Email ID.\n");
            return 0;
        }
    }

    for (int d = dot_index + 1; email[d] != '\0'; d++)
    {
        if (!(email[d] >= 'a' && email[d] <= 'z'))
        {
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
    for (int e = 0; e < addressBook->contactCount; e++)
    {
        if (strcmp(addressBook->contacts[e].email, email) == 0)
        {
            already_present = 1;
            break;
        }
    }
    if (already_present == 1)
    {
        printf("Email ID already present.\n");
    }
    // if (already_present == 0) {
    //     strcpy(addressBook->contacts[addressBook->contactCount].email, email);
    // } else {
    //     printf("Email ID already present.\n");
    // }
    return already_present;
}

int search_name(AddressBook *addressBook, char name[], int *foundindices, int *foundCount)
{

    int flag_found = 0;
    for (int i = 0; i < addressBook->contactCount; i++)
    {
        if (strcmp(addressBook->contacts[i].name, name) == 0)
        {
            flag_found = 1;
            if (foundindices != NULL)
            {
                foundindices[*foundCount] = i;
                (*foundCount)++;
            }
            printf("Contact %d: %s, Phone: %s, Email ID: %s\n", i + 1, addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email);
        }
    }
    if (flag_found == 0)
    {
        printf("Contact not Found.\n");
    }
    return flag_found;
}

int search_phone(AddressBook *addressBook, char phone[], int *foundindices, int *foundCount)
{
    int flag_found = 0;

    for (int i = 0; i < addressBook->contactCount; i++)
    {
        if (strcmp(addressBook->contacts[i].phone, phone) == 0)
        {
            flag_found = 1;
            if (foundindices != NULL)
            {
                foundindices[*foundCount] = i;
                (*foundCount)++;
            }
            printf("Contact %d: %s, Phone: %s, Email ID: %s\n", i + 1, addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email);
        }
    }
    if (flag_found == 0)
    {
        printf("Contact not Found.\n");
    }
    return flag_found;
}

int search_email(AddressBook *addressBook, char email[], int *foundindices, int *foundCount)
{
    int flag_found = 0;
    for (int i = 0; i < addressBook->contactCount; i++)
    {
        if (strcmp(addressBook->contacts[i].email, email) == 0)
        {
            flag_found = 1;
            if (foundindices != NULL)
            {
                foundindices[*foundCount] = i;
                (*foundCount)++;
            }
            printf("Contact %d: %s, Phone: %s, Email ID: %s\n", i + 1, addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email);
        }
    }
    if (flag_found == 0)
    {
        printf("Contact not Found.\n");
    }
    return flag_found;
}

void edit_contact(AddressBook *addressBook, int index)
{
    int option;
    int edit_n = 0;
    int edit_p = 0;
    int edit_e = 0;
    do
    {
        printf("\nEdit Menu:\n");
        printf("1. Edit Name\n");
        printf("2. Edit Phone no.\n");
        printf("3. Edit Email ID\n");
        printf("4. Exit\n");
        printf("\nEnter your choice: ");
        scanf("%d", &option);
        getchar();

        switch (option)
        {
        case 1:
            do
            {
                char name[50];
                printf("Enter the New Name: ");
                scanf("%[^\n]", name);
                if (read_name(addressBook, name) == 1)
                {
                    strcpy(addressBook->contacts[index].name, name);
                    edit_n = 1;
                }
                else
                {
                    printf("Invalid Name.\n");
                }
                getchar();
            } while (edit_n == 0);
            break;

        case 2:
            do
            {
                char phone[11];
                printf("Enter the New Phone no. : ");
                scanf("%s", phone);
                if (read_mob(addressBook, phone) == 1)
                {
                    int v_p = validate_phone(addressBook, phone);
                    if (v_p == 1)
                    {
                        edit_p = 0;
                    }
                    else
                    {
                        strcpy(addressBook->contacts[index].phone, phone);
                        edit_p = 1;
                    }
                }
                else
                {
                    printf("Invalid Phone no.\n");
                }
                getchar();
            } while (edit_p == 0);
            break;

        case 3:
            do
            {
                char email[50];
                printf("Enter the New Email ID. : ");
                scanf("%s", email);
                if (read_email(addressBook, email) == 1)
                {
                    int v_e = validate_email(addressBook, email);
                    if (v_e == 1)
                    {
                        edit_e = 0;
                    }
                    else
                    {
                        strcpy(addressBook->contacts[index].email, email);
                        edit_e = 1;
                    }
                }
                else
                {
                    printf("Invalid Email ID.\n");
                }
                // getchar();
            } while (edit_e == 0);
            break;

        case 4:
            break;

        default:
            printf("Invalid choice. Please try again.\n");
        }
    } while (option != 4);
}

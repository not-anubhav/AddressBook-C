#include "contact.h"
#include <stdio.h>
#include <ctype.h>
#include <string.h>

int read_name(AddressBook *addressBook, char name[]) // Read name function takes addressbook address and a character array as formal argument
{
    int name_flag = 1;
    if (name[0] == ' ' || name[strlen(name) - 1] == ' ' || strlen(name) > 49) // Check if the name is starting with space or ending with space
    {
        name_flag = 0; // If condition evaluates to true reset the name flag
    }
    else
    {
        for (int i = 0; name[i] != '\0'; i++) // Run a loop from starting character till the null character in name string
        {
            if (!((name[i] >= 'a' && name[i] <= 'z') || (name[i] >= 'A' && name[i] <= 'Z') || name[i] == ' '))  // If name does not contains lowercase, uppercase and space
            {
                name_flag = 0; // Reset the name flag
                break; // Break the loop
            }
            if (i > 0 && name[i] == ' ') // If the above condition evaluates to false, check for multiple spaces in name
            {
                if (name[i + 1] == ' ')
                {
                    name_flag = 0; // If multiple spaces are present reset the name flag
                    break;
                }
            }
        }
    }
    return name_flag; // Return the name flag value from the function
}

int read_mob(AddressBook *addressBook, char mob[]) // Read mob function takes addressbook address and a character array as formal argument
{
    int mob_flag = 1; // Take a phone flag

    if (strlen(mob) != 10) //If the string length of input string is not equal to 10
    {
        mob_flag = 0; // Reset the phone flag
    }
    else
    {
        for (int j = 0; mob[j] != '\0'; j++)
        {
            if (!(mob[j] >= '0' && mob[j] <= '9')) //Check if the characters present in the mob are only digits
            {
                mob_flag = 0; //If the condition evaluates to true reset the phone flag
                break; 
            }
        }
    }
    return mob_flag; // Return the phone flag value from the function
}

int validate_phone(AddressBook *addressBook, char mob[]) // This function is used to validate if the input phone number is already present in the address book or not
{
    int already_present = 0; // Declare a already present flag and initialize it to 0
    for (int k = 0; k < addressBook->contactCount; k++)
    {
        if (strcmp(addressBook->contacts[k].phone, mob) == 0) // Compare the mob with already present phone numbers inside the addressbook
        {
            already_present = 1; // If condition evaluates true that means the phone number is already present inside the addressbook, make the already present flag as 1
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
    return already_present; // Return the flag value from the function
}

int read_email(AddressBook *addressBook, char email[]) // This Function check for the input email id as a valid input
{
    int mail_flag = 1; // Take a mail flag and initialize it with 1
    int at_index = -1; // Take an index for storing the "@" index value
    int dot_index = -1; // Take an index for storing the "." index value

    if (strlen(email) > 49 || email[0] == '@' || email[0] == '.' || email[0] == ' ' || email[0] == '\t' ||
        email[strlen(email) - 1] == '@' || email[strlen(email) - 1] == '.') 
    {
        printf("Enter a valid Email ID.\n"); // If any of the above condition is evaluated true then print this message and return to main menu
        return 0;
    }
    
    // Code for finding the "@" and "." index and checking it for multiple inputs

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

    if (at_index == -1 || dot_index == -1 || at_index > dot_index) /* If this condition evaluates to true that means 
    either it contains multiple "@" or "." or "@" is present after "." */
    {
        printf("Enter a valid Email ID.\n"); // Print the error message
        return 0; // Return to previous menu
    }

    for (int e = 0; e < at_index; e++) //Check if the input email contains alpha numeric input till "@" index
    {
        if (!isalnum(email[e]))
        {
            printf("Enter a valid Email ID.\n");
            return 0;
        }
    }

    if (!(email[at_index + 1] >= 'a' && email[at_index + 1] <= 'z')) // Check if the next character after "@" is character or not
    {
        printf("Enter a valid Email ID.\n");
        return 0;
    }

    for (int d = at_index + 1; d < dot_index; d++) // Check if the characters after "@" are only lowercase alphabets
    {
        if (!(email[d] >= 'a' && email[d] <= 'z'))
        {
            printf("Enter a valid Email ID.\n");
            return 0;
        }
    }

    for (int d = dot_index + 1; email[d] != '\0'; d++) // Check if the characters after "." are only lowercase alphabets
    {
        if (!(email[d] >= 'a' && email[d] <= 'z'))
        {
            printf("Enter a valid Email ID.\n");
            return 0;
        }
    }
    getchar();
    return mail_flag; // return the mail flag value from the function
}

int validate_email(AddressBook *addressBook, char email[]) // This function checks if the input email id is already assigned to any contact in address book
{
    int already_present = 0;
    for (int e = 0; e < addressBook->contactCount; e++)
    {
        if (strcmp(addressBook->contacts[e].email, email) == 0) // Compare the input email with all the emails in the address book
        {
            already_present = 1; //If above condition evaluates to true that means contact with same email is already present
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
    return already_present; // return the already present flag value from the function
}

int search_name(AddressBook *addressBook, char name[], int *foundindices, int *foundCount) /*  This function is called with the search contact function
    it searches for the name in the address book and prints all the contacts with that name inside the address book, it also store the indices of contacts 
    found and keeps a count of found contacts */
{

    int flag_found = 0;
    for (int i = 0; i < addressBook->contactCount; i++)
    {
        if (strcmp(addressBook->contacts[i].name, name) == 0) // Compare the name to search with all the contact names present in address book
        {
            flag_found = 1; // If condition evaluates true then make the found flag as 1
            if (foundindices != NULL) // Also if the foundindices passed to this function is not NULL address
            {
                foundindices[*foundCount] = i; // Store the contact index at the found count index of found indices array
                (*foundCount)++; // Dereference the found count and increment it's value
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

int search_phone(AddressBook *addressBook, char phone[], int *foundindices, int *foundCount)  /*  This function is called with the search contact function
    it searches for the phone number in the address book and prints the contact details belonging to that number inside the address book, it also store the indices of contacts 
    found and keeps a count of found contacts */
{
    int flag_found = 0;

    for (int i = 0; i < addressBook->contactCount; i++)
    {
        if (strcmp(addressBook->contacts[i].phone, phone) == 0)  // Compare the phone number to search with all the contact phone numbers present in address book
        {
            flag_found = 1; // If condition evaluates true then make the found flag as 1
            if (foundindices != NULL)  // Also if the foundindices passed to this function is not NULL address
            {
                foundindices[*foundCount] = i; // Store the contact index at the found count index of found indices array
                (*foundCount)++;  // Dereference the found count and increment it's value
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

int search_email(AddressBook *addressBook, char email[], int *foundindices, int *foundCount)  /*  This function is called with the search contact function
    it searches for the email id in the address book and prints the contact details belonging to that email id inside the address book, it also store the indices of contacts 
    found and keeps a count of found contacts */
{
    int flag_found = 0;
    for (int i = 0; i < addressBook->contactCount; i++)
    {
        if (strcmp(addressBook->contacts[i].email, email) == 0) // Compare the email id to search with all the contact email id's present in address book
        {
            flag_found = 1;  // If condition evaluates true then make the found flag as 1
            if (foundindices != NULL)  // Also if the foundindices passed to this function is not NULL address
            {
                foundindices[*foundCount] = i;  // Store the contact index at the found count index of found indices array
                (*foundCount)++; // Dereference the found count and increment it's value
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

void edit_contact(AddressBook *addressBook, int index)  /* This function is called from the edit contact function in contact.c file 
    and prompts the user to edit the contact information using their name, phone and email id, Here the index contains the contact 
    index which we want to edit*/
{
    int option; // Variable for switching through edit menu
    int edit_n = 0; // Name edit flag
    int edit_p = 0; // Phone edit flag
    int edit_e = 0; // email edit flag
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
                    strcpy(addressBook->contacts[index].name, name); // If the new input name is valid then copy that name inside the name member of that contact inside address book
                    edit_n = 1; //Update the edit flag to 1
                }
                else
                {
                    printf("Invalid Name.\n");
                }
                getchar();
            } while (edit_n == 0); // Run the loop based on the evaluated condition
            break;

        case 2:
            do
            {
                char phone[11];
                printf("Enter the New Phone no. : ");
                scanf("%s", phone);
                if (read_mob(addressBook, phone) == 1) // check if the new input phone is valid or not
                {
                    int v_p = validate_phone(addressBook, phone); // if valid, Check wheather it is already assigned to any other contact
                    if (v_p == 1)
                    {
                        edit_p = 0; // If it is assigned, reset the phone edit flag
                    }
                    else
                    {
                        strcpy(addressBook->contacts[index].phone, phone); //If not assigned, then copy the phone inside the phone member of that contact inside address book
                        edit_p = 1; // Update the edit flag to 1
                    }
                }
                else
                {
                    printf("Invalid Phone no.\n");
                }
                getchar();
            } while (edit_p == 0); // Run the loop based on the evaluated condition
            break;

        case 3:
            do
            {
                char email[50];
                printf("Enter the New Email ID. : ");
                scanf("%s", email); 
                if (read_email(addressBook, email) == 1)  // check If the new input email is valid or not
                {
                    int v_e = validate_email(addressBook, email); //If it is valid, then check whether it is already assigned or not
                    if (v_e == 1)
                    {
                        edit_e = 0; // If already assigned, reset the email edit flag value
                    }
                    else
                    {
                        strcpy(addressBook->contacts[index].email, email); // If it is not assigned then copy the email id inside the email id of that contact inside address book
                        edit_e = 1;
                    }
                }
                else
                {
                    printf("Invalid Email ID.\n");
                }
                // getchar();
            } while (edit_e == 0); // Run the loop based on the evaluated condition
            break;

        case 4:
            break;

        default:
            printf("Invalid choice. Please try again.\n");
        }
    } while (option != 4);
}

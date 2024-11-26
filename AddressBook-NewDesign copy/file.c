#include <stdio.h>
#include "file.h"

void saveContactsToFile(AddressBook *addressBook)
{
    FILE* fptr = fopen("contacts.csv", "w");

    fprintf(fptr, "Count: %d\n", addressBook->contactCount);
    fprintf(fptr, "%s,%s,%s\n", "NAME", "PHONE", "EMAIL");
    for ( int i = 0; i < addressBook->contactCount; i++)
    {
        fprintf(fptr, "%s,%s,%s\n", addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email);
    }

    fclose(fptr);
}

int loadContactsFromFile(AddressBook *addressBook)
{
    FILE* fptr = fopen("contacts.csv", "r");

    if(fptr == NULL)
    {
        printf("File does not exist\n");
        return 0;
    }

    fscanf(fptr, "Count: %d\n", &addressBook->contactCount);
    fseek(fptr, 26, SEEK_SET);
    for(int i = 0; i < addressBook->contactCount; i++)
    {
        fscanf(fptr, "%[a-z A-Z],%[0-9],%s\n", addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email);
    }
    fclose(fptr);
}
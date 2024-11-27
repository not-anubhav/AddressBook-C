#include <stdio.h>
#include "file.h"
void saveContactsToFile(AddressBook *addressBook)
{
    FILE* fptr = fopen("contacts.csv", "w");

    fprintf(fptr, "%s,%s,%d\n", "Contact", "Count", addressBook->contactCount);
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
        printf("\n>>>>FILE DOES NOT EXIST<<<<\n");
        return 0;
    }
    fseek(fptr, 14, SEEK_SET);
    fscanf(fptr, "%d\n", &addressBook->contactCount);
    for(int i = 0; i < addressBook->contactCount; i++)
    {
        fscanf(fptr, "%[a-z A-Z],%[0-9],%s\n", addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email);
    }
    fclose(fptr);
}

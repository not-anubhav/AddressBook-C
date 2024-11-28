#ifndef FILE_H
#define FILE_H // Define a header file with name file.h

#include "contact.h" // // Include contact header file having AddressBook structure

void saveContactsToFile(AddressBook *addressBook); // Function Declaration for saveContactsToFile Function
int loadContactsFromFile(AddressBook *addressBook); // Function Declaration for loadContactsFromFile Function

#endif
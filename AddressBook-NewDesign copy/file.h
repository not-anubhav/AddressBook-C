#ifndef FILE_H
#define FILE_H

#include "contact.h"

void saveContactsToFile(AddressBook *addressBook);
int loadContactsFromFile(AddressBook *addressBook);

#endif
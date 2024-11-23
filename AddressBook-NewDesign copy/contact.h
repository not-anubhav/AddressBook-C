#ifndef CONTACT_H
#define CONTACT_H

#define MAX_CONTACTS 100

typedef struct {
    char name[50];
    char phone[20];
    char email[50];
} Contact;

typedef struct {
    Contact contacts[MAX_CONTACTS];
    int contactCount;
} AddressBook;

void createContact(AddressBook *addressBook);
int searchContact(AddressBook *addressBook, int*);
void editContact(AddressBook *addressBook);
void deleteContact(AddressBook *addressBook);
void listContacts(AddressBook *addressBook);
void initialize(AddressBook *addressBook);
void saveContactsToFile(AddressBook *AddressBook);
int read_name(AddressBook *addressBook, char []);
int read_mob(AddressBook *addressBook, char []);
int read_email(AddressBook *addressBook, char []);
int search_name(AddressBook *addressBook, char [], int*, int*);
int search_phone(AddressBook *addressBook, char [], int*, int*);
int search_email(AddressBook *addressBook, char [], int*, int*);
int validate_phone(AddressBook *addressBook, char []);
int validate_email(AddressBook *addressBook, char []);

#endif
#ifndef CONTACT_H
#define CONTACT_H // We have defined a header file named contact.h

#define MAX_CONTACTS 100 // We have defined a maximum size of 100 for contacts

// Define a typedef structure with Contact as the name of the Datatype

typedef struct
{
    char name[50];
    char phone[20];
    char email[50];
} Contact;

// Define another structure with AddressBook as the name of the Datatype

typedef struct
{
    Contact contacts[MAX_CONTACTS]; // Declare a character array with size of MAX_CONTACT i.e previously defined as 100
    int contactCount; // Declare an integer variable for keeping the count of the number of contacts in the AddressBook
} AddressBook;

// Fuction Declaration for all the functions used in the program

void createContact(AddressBook *addressBook);
int searchContact(AddressBook *addressBook, int *);
void editContact(AddressBook *addressBook);
void deleteContact(AddressBook *addressBook);
int listContacts(AddressBook *addressBook);
void initialize(AddressBook *addressBook);
void saveAndExit(AddressBook *addressBook);
int read_name(AddressBook *addressBook, char[]);
int read_mob(AddressBook *addressBook, char[]);
int read_email(AddressBook *addressBook, char[]);
int search_name(AddressBook *addressBook, char[], int *, int *);
int search_phone(AddressBook *addressBook, char[], int *, int *);
int search_email(AddressBook *addressBook, char[], int *, int *);
int validate_phone(AddressBook *addressBook, char[]);
int validate_email(AddressBook *addressBook, char[]);
void edit_contact(AddressBook *addressBook, int);
#endif
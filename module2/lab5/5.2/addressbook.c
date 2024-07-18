#include <stdlib.h>
#include <stdio.h>


#define SOCIAL_SIZE 5

#define LENGTH_NAME 20
#define LENGTH_COMPANY 40
#define LENGTH_PHONE 13
#define LENGTH_MAX 256

typedef struct Emails {
    char home[LENGTH_MAX];
    char work[LENGTH_MAX];
} Emails;

typedef struct Phones {
    char phone[LENGTH_PHONE];
    char home[LENGTH_PHONE];
    char work[LENGTH_PHONE];
} Phones;

typedef struct Social {
    char social_name[20];
    char url[LENGTH_MAX];
    char nickname[LENGTH_NAME];
} Social;

typedef struct FullName {
    char firstname[LENGTH_NAME];
    char lastname[LENGTH_NAME];
    char patronomic[LENGTH_NAME];
} FullName;

typedef struct Company {
    char company[LENGTH_COMPANY];
    char position[LENGTH_COMPANY];
} Company;

typedef struct ContactNote {
    FullName name;
    Company company;
    Phones phones;
    Emails emails;
    Social socials[SOCIAL_SIZE];
} ContactNote;

typedef struct Item
{
    ContactNote note;
    struct Item *next;
    struct Item *prev;
} AddressBook;

AddressBook *head = NULL;

//CRUD methods
int add_note(ContactNote contact);
int update_note(int id, ContactNote contact);
int delete_note(int id);
int get_note(int id, ContactNote* note);

//clear all elements
int free_all();

//find methods
int find_first(char* firstname, char* lastname, char* patronomic, char* phone, char *email);
int find_all(int* get_ids, char* firstname, char* lastname, char* patronomic, char* phone, char *email);

//Show methods
void show_notes();
void show_note(int id);

//Methods for creating stuctures
FullName create_full_name(char* first_name, char* last_name, char* patronomic);
Company create_company(char* company, char* postion);
Phones create_phones(char* phone, char* home, char* work);
Emails create_emails(char* home, char* work);
Social create_social(char* social_name, char* url, char* nickname);
ContactNote create_contact(FullName full_name, Company company, Phones phones, Emails emails, Social* socials);


FullName create_full_name(char* first_name, char* last_name, char* patronomic) {
    FullName name;
    strcpy(name.firstname, first_name);
    strcpy(name.lastname, last_name);
    strcpy(name.patronomic, patronomic);
    return name;
}

Company create_company(char* company, char* postion) {
    Company comp;
    strcpy(comp.company, company);
    strcpy(comp.position, postion);
    return comp;
}

Phones create_phones(char* phone, char *home, char *work) {
    Phones phones;
    strcpy(phones.phone, phone);
    strcpy(phones.home, home);
    strcpy(phones.work, work);
    return phones;
}

Emails create_emails(char *home, char *work) {
    Emails emails;
    strcpy(emails.home, home);
    strcpy(emails.work, work);
    return emails;
    
}

Social create_social(char* social_name, char* url, char* nickname) {
    Social social;
    strcpy(social.social_name, social_name);
    strcpy(social.url, url);
    strcpy(social.nickname, nickname);
    return social;

}

ContactNote create_contact(FullName full_name, Company company, Phones phones, Emails emails, Social* socials) {
    ContactNote note;
    note.name = full_name;
    note.company = company;
    note.phones = phones;
    note.emails = emails;
    int i = 0;
    for (i; i < 5; i++) {
        note.socials[i] = socials[i];
    }
    return note;
}

int add_note(const ContactNote contact) {
    if (contact.name.firstname == NULL || contact.name.lastname == NULL || strlen(contact.name.firstname) == 0 || strlen(contact.name.lastname) == 0) return -1;
    AddressBook *node = (AddressBook*) malloc(sizeof(AddressBook));
    node->note = contact;
    node->next = NULL;

    if (head == NULL) {
        head = node;
        head->prev = NULL;
    } else {
        AddressBook *current = head;
        while (current->next != NULL)
        {
            current = current->next;
        }
        current->next = node;
        node->prev = current;
    }
    return 0;
}

int update_note(int id, const ContactNote contact) {
    if (contact.name.firstname == NULL || contact.name.lastname == NULL || strlen(contact.name.firstname) == 0 || strlen(contact.name.lastname) == 0) return -1;
    AddressBook* current = head;
    int counter = 0;
    while (current != NULL) {
        if (id == counter) {
            current->note = contact;
            return 0;
        }
        counter++;
        current = current->next;
    }
    return -1;
}

int delete_note(int id) {
    AddressBook* current = head;
    int counter = 0;
    while (current != NULL) {
        if (id == counter) {
            if (current->prev != NULL) {
                current->prev->next = current->next;
            } else {
                head = current->next;
            }
            if (current->next != NULL) {
                current->next->prev = current->prev;
            }
            free(current);
            return 0;
        }
        counter++;
        current = current->next;
    }
    return -1;
}

int get_note(int id, ContactNote *note) {
    printf("*\n");
    AddressBook* current = head;
    int counter = 0;
    while (current != NULL) {
        if (id == counter) {
            *note = current->note;
            return 0;
        }
        counter++;
        current = current->next;
    }
    return -1;
}

int free_all() {
    AddressBook* current = head;
    AddressBook* next;
    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }
    head = NULL;
    return 0;
}

int count_note() {
    int counter = 0;
    AddressBook* current = head;
    while (current != NULL)
    {
        counter++;
        current = current->next;
    }
    return counter;
}

int find_first(char* firstname, char* lastname, char* patronomic, char* phone, char *email) {
    if (firstname == NULL && lastname == NULL && patronomic == NULL && phone == NULL && email == NULL) 
        return -1;
    
    int i = 0, count = count_note();
    ContactNote contact;

    for (i; i < count; i++) {
        //printf("*\n");
        get_note(i, &contact);
        //printf("*\n");
        if (
            (firstname == NULL || strcmp(contact.name.firstname, firstname) == 0) &&
            (lastname == NULL || strcmp(contact.name.lastname, lastname) == 0) &&
            (patronomic == NULL || strcmp(contact.name.patronomic, patronomic) == 0) && ( 
                phone == NULL  ||
                strcmp(contact.phones.phone, phone) == 0 ||
                strcmp(contact.phones.home, phone) == 0 ||
                strcmp(contact.phones.work, phone) == 0
            ) && (
                email == NULL ||
                strcmp(contact.emails.home, email) == 0 ||
                strcmp(contact.emails.work, email) == 0
            )
        ) {
            return i;
        }
    }

    return -1;
}

int find_all(int* get_ids, char* firstname, char* lastname, char* patronomic, char* phone, char *email) {
        if (firstname == NULL && lastname == NULL && patronomic == NULL && phone == NULL && email == NULL) 
        return -1;

    int i = 0;
    int counter = 0;
    int contact_count = count_note();
    ContactNote contact;

    for (i; i < contact_count; i++) {
        get_note(i, &contact);
        if (
            (firstname == NULL || strcmp( contact.name.firstname, firstname) == 0) &&
            (lastname == NULL || strcmp(  contact.name.lastname, lastname) == 0) &&
            (patronomic == NULL || strcmp(contact.name.patronomic, patronomic) == 0) && ( 
                phone == NULL  ||
                strcmp(contact.phones.phone, phone) == 0 ||
                strcmp(contact.phones.home, phone) == 0 ||
                strcmp(contact.phones.work, phone) == 0
            ) && (
                email == NULL ||
                strcmp(contact.emails.home, email) == 0 ||
                strcmp(contact.emails.work, email) == 0
            )
        ) {
            counter++;
        }
    }

    if(counter == 0) 
        return -1;

    int ids[counter];

    i = 0;
    int j = 0;

    for (i; i < contact_count; i++) {
        get_note(i, &contact);
        if (
            (firstname == NULL || strcmp( contact.name.firstname, firstname) == 0) &&
            (lastname == NULL || strcmp(  contact.name.lastname, lastname) == 0) &&
            (patronomic == NULL || strcmp(contact.name.patronomic, patronomic) == 0) && ( 
                phone == NULL  ||
                strcmp(contact.phones.phone, phone) == 0 ||
                strcmp(contact.phones.home, phone) == 0 ||
                strcmp(contact.phones.work, phone) == 0
            ) && (
                email == NULL ||
                strcmp(contact.emails.home, email) == 0 ||
                strcmp(contact.emails.work, email) == 0
            )
        ) {
            ids[j++] = i;
        }
    }

    get_ids = ids;
    return counter;
}

void show_note(int id) 
{
    ContactNote note;
    get_note(id, &note);
    printf("contact #%d\n", id);
    printf("Full name:\t%s\t%s\t%s\n", note.name.firstname, note.name.patronomic, note.name.lastname);
    printf("Company: %s, %s\n", note.company.company, note.company.position);
    printf("Phones:\n\tphone: %s\n\thome: %s\n\twork: %s\n", note.phones.phone, note.phones.home, note.phones.work);
    printf("Emails:\n\thome: %s\n\twork: %s\n", note.emails.home, note.emails.work);
    int j = 0;
    printf("Socials:\n");
    for (j; j < SOCIAL_SIZE; j++)
    {
        printf("\t%s(%s): %s\n", note.socials[j].nickname, note.socials[j].social_name, note.socials[j].url);
    }
}

void show_notes()
{
    int count = count_note();
    printf("Show all contacts (%d)\n", count);
    int id = 0;
    for (id; id < count; id++) {
        show_note(id);
    }
    printf("-----------------------------------------------------------------------------------------\n\n");
}

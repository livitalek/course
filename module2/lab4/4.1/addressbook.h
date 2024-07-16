#include <stdarg.h>
#include <stdio.h>
#include <string.h>

#ifndef H_ADDRESSBOOK
#define H_ADDRESSBOOK

#define NOTE_SIZE 100
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


//CRUD methods
int add_note(ContactNote contact);
int update_note(int id, ContactNote contact);
int delete_note(int id);
int get_note(int id, ContactNote* get_note);
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

#endif
#include "addressbook.h"
#include <unistd.h>
#include <fcntl.h>

int contact_count = 0;

int load_file(char *filename) {
    int fd = open(filename, O_RDONLY, 0666);
    if (fd == -1) {
        return -1;
    }

    contact_count = 0;

    ssize_t bytes_read; 
    while ((bytes_read = read(fd, &address_book[contact_count++], sizeof(ContactNote))) > 0 && contact_count < NOTE_SIZE);

    if (bytes_read == -1) {
        close(fd);
        return -1;
    }

    close(fd);

    return 0;
}

int save_file(char *filename) {
    int fd = open(filename, O_CREAT | O_WRONLY | O_TRUNC, 0666);
    if (fd == -1) {
        return -1;
    }

    ssize_t bytes_read; 
    int i;
    for (i = 0; i < contact_count; i++) {
        if (write(fd, &address_book[i], sizeof(ContactNote)) == -1 ) {
            close(fd);
            return -1;
        }
    }

    close(fd);
    return 0;
}

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
    if (contact_count >= NOTE_SIZE) return -1;
    if (contact.name.firstname == NULL || contact.name.lastname == NULL || strlen(contact.name.firstname) == 0 || strlen(contact.name.lastname) == 0) return -1;
    address_book[contact_count++] = contact;
    return 0;
}

int update_note(int id, const ContactNote contact) {
    if (id < 0 || id >= contact_count || id >= NOTE_SIZE) return -1;
    if (contact.name.firstname == NULL || contact.name.lastname == NULL || strlen(contact.name.firstname) == 0 || strlen(contact.name.lastname) == 0) return -1;
    address_book[id] = contact;
    return 0;
}

int delete_note(int id) {
    if (id < 0 || id >= contact_count || id >= NOTE_SIZE) return -1;
    int i = id;
    for (i; i < contact_count - 1; i++) {
        address_book[i] = address_book[i + 1];
    }
    contact_count --;
    return 0;
}

int get_note(int id, ContactNote *note) {
    if (id < 0 || id >= contact_count || id >= NOTE_SIZE) return -1;
    *note = address_book[id];
    return 0;
}

int first_find(char* firstname, char* lastname, char* patronomic, char* phone, char *email) {
    if (firstname == NULL && lastname == NULL && patronomic == NULL && phone == NULL && email == NULL) 
        return -1;
    
    int i = 0;
    for (i; i < contact_count; i++) {
        if (
            (firstname == NULL || strcmp(address_book[i].name.firstname, firstname) == 0) &&
            (lastname == NULL || strcmp(address_book[i].name.lastname, lastname) == 0) &&
            (patronomic == NULL || strcmp(address_book[i].name.patronomic, patronomic) == 0) && ( 
                phone == NULL  ||
                strcmp(address_book[i].phones.phone, phone) == 0 ||
                strcmp(address_book[i].phones.home, phone) == 0 ||
                strcmp(address_book[i].phones.work, phone) == 0
            ) && (
                email == NULL ||
                strcmp(address_book[i].emails.home, email) == 0 ||
                strcmp(address_book[i].emails.work, email) == 0
            )
        ) {
            return i;
        }
    }

    return -1;
}

int all_find(int* get_ids, char* firstname, char* lastname, char* patronomic, char* phone, char *email)
{
    if (firstname == NULL && lastname == NULL && patronomic == NULL && phone == NULL && email == NULL) 
        return -1;

    int i = 0;

    int counter = 0;

    for (i; i < contact_count; i++) {
        if (
            (firstname == NULL || strcmp(address_book[i].name.firstname, firstname) == 0) &&
            (lastname == NULL || strcmp(address_book[i].name.lastname, lastname) == 0) &&
            (patronomic == NULL || strcmp(address_book[i].name.patronomic, patronomic) == 0) && ( 
                phone == NULL  ||
                strcmp(address_book[i].phones.phone, phone) == 0 ||
                strcmp(address_book[i].phones.home, phone) == 0 ||
                strcmp(address_book[i].phones.work, phone) == 0
            ) && (
                email == NULL ||
                strcmp(address_book[i].emails.home, email) == 0 ||
                strcmp(address_book[i].emails.work, email) == 0
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
        if (
            (firstname == NULL || strcmp(address_book[i].name.firstname, firstname) == 0) &&
            (lastname == NULL || strcmp(address_book[i].name.lastname, lastname) == 0) &&
            (patronomic == NULL || strcmp(address_book[i].name.patronomic, patronomic) == 0) && ( 
                phone == NULL  ||
                strcmp(address_book[i].phones.phone, phone) == 0 ||
                strcmp(address_book[i].phones.home, phone) == 0 ||
                strcmp(address_book[i].phones.work, phone) == 0
            ) && (
                email == NULL ||
                strcmp(address_book[i].emails.home, email) == 0 ||
                strcmp(address_book[i].emails.work, email) == 0
            )
        ) {
            ids[j++] = i;
        }
    }

    get_ids = ids;
    return counter;
}

void show_notes()
{
    printf("Show all contacts (%d)\n", contact_count);
    ContactNote note;
    int id = 0;
    for (id; id < contact_count; id++) 
    {
        get_note(id, &note);
        show_note(id);
    }
    printf("-----------------------------------------------------------------------------------------\n\n");
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

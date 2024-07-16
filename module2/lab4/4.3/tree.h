#ifndef H_TREE
#define H_TREE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
} ContactNote;

typedef struct Node {
    ContactNote note;
    struct Node *left;
    struct Node *right;
    int height;
} Node;

Node* create_node(ContactNote note);
int get_height(Node* node);
void update_height(Node* node);
Node* rotate_right(Node* y);
Node* rotate_left(Node* x);
int get_balance(Node* node);
int name_cmp(FullName name1, FullName name2);
Node* insert_node(Node* root, ContactNote note);

Node* find_min_node(Node* node);
Node* delete_node(Node* root, ContactNote note);
void free_all(Node* node);

void print_in_order(Node* root);
void print_pre_order(Node* root);
void print_post_order(Node* root);

FullName create_full_name(char* first_name, char* last_name, char* patronomic);
Company create_company(char* company, char* postion);
Phones create_phones(char* phone, char* home, char* work);
Emails create_emails(char* home, char* work);
ContactNote create_contact(FullName full_name, Company company, Phones phones, Emails emails);


#endif
#include "tree.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

ContactNote create_contact(FullName full_name, Company company, Phones phones, Emails emails) {
    ContactNote note;
    note.name = full_name;
    note.company = company;
    note.phones = phones;
    note.emails = emails;
    int i = 0;
    return note;
}


Node* create_node(ContactNote note) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->note = note;
    newNode->left = NULL;
    newNode->right = NULL;
    newNode->height = 1;
    return newNode;
}

int get_height(Node* node) {
    if (node == NULL) {
        return 0;
    }
    return node->height;
}

void update_height(Node* node) {
    int leftHeight = get_height(node->left);
    int rightHeight = get_height(node->right);
    node->height = 1 + (leftHeight > rightHeight ? leftHeight : rightHeight);
}

Node* rotate_right(Node* y) {
    Node* x = y->left;
    Node* T2 = x->right;
    x->right = y;
    y->left = T2;
    
    update_height(y);
    update_height(x);
    
    return x;
}

Node* rotate_left(Node* x) {
    Node* y = x->right;
    Node* T2 = y->left;
    y->left = x;
    x->right = T2;
    
    update_height(x);
    update_height(y);
    
    return y;
}

int get_balance(Node* node) {
    if (node == NULL) {
        return 0;
    }

    return get_height(node->left) - get_height(node->right);
}

int name_cmp(FullName name1, FullName name2) {
    int cmp = strcmp(name1.firstname, name2.firstname);    
    if (cmp != 0) {
        return cmp;
    } 
    cmp = strcmp(name1.lastname, name2.lastname);    
    if (cmp != 0) {
        return cmp;
    } 
    cmp = strcmp(name1.patronomic, name2.patronomic);
    return cmp;
}

Node* insert_node(Node* root, ContactNote note) {
    if (root == NULL) {
        return create_node(note);
    }
    
    if (name_cmp(note.name, root->note.name) <= 0) {
        root->left = insert_node(root->left, note);
    } else {
        root->right = insert_node(root->right, note);
    } 
    
    update_height(root);
    
    int balance = get_balance(root);
    
    // Вращения для балансировки
    if (balance > 1 && name_cmp(note.name, root->left->note.name) <= 0) {
        return rotate_right(root);
    }
    
    if (balance < -1 && name_cmp(note.name, root->right->note.name) > 0) {
        return rotate_left(root);
    }
    
    if (balance > 1 && name_cmp(note.name, root->left->note.name) > 0) {
        root->left = rotate_left(root->left);
        return rotate_right(root);
    }
    
    if (balance < -1 && name_cmp(note.name, root->right->note.name) <= 0) {
        root->right = rotate_right(root->right);
        return rotate_left(root);
    }
    
    return root;
}

Node* find_min_node(Node* node) {
    Node* current = node;
    
    while (current->left != NULL) {
        current = current->left;
    }
    
    return current;
}


Node* delete_node(Node* root, ContactNote note) {
    if (root == NULL) {
        return root;
    }

    if (name_cmp(note.name, root->note.name) < 0) {
        root->left = delete_node(root->left, note);
    } else if (name_cmp(note.name, root->note.name) > 0) {
        root->right = delete_node(root->right, note);
    } else {
        if (root->left == NULL || root->right == NULL) {
            Node* temp = root->left ? root->left : root->right;
            
            if (temp == NULL) {
                temp = root;
                root = NULL;
            } else {
                *root = *temp;
            }
            
            free(temp);
        } else {
            Node* temp = find_min_node(root->right);
            root->note = temp->note;
            root->right = delete_node(root->right, temp->note);
        }
    }
    
    if (root == NULL) {
        return root;
    }
    
    update_height(root);
    
    int balance = get_balance(root);
    
    // Вращения для балансировки
    if (balance > 1 && get_balance(root->left) >= 0) {
        return rotate_right(root);
    }
    
    if (balance > 1 && get_balance(root->left) < 0) {
        root->left = rotate_left(root->left);
        return rotate_right(root);
    }
    
    if (balance < -1 && get_balance(root->right) <= 0) {
        return rotate_left(root);
    }
    
    if (balance < -1 && get_balance(root->right) > 0) {
        root->right = rotate_right(root->right);
        return rotate_left(root);
    }
    
    return root;
}

void print_in_order(Node* root) {
    if (root == NULL) {
        return;
    }
    
    print_in_order(root->left);
    ContactNote note = root->note;
    printf("Full name:\t%s\t%s\t%s\n", note.name.firstname, note.name.patronomic, note.name.lastname);
    printf("Company: %s, %s\n", note.company.company, note.company.position);
    printf("Phones:\n\tphone: %s\n\thome: %s\n\twork: %s\n", note.phones.phone, note.phones.home, note.phones.work);
    printf("Emails:\n\thome: %s\n\twork: %s\n", note.emails.home, note.emails.work);
    printf("---------------------------------------------------------------------\n");
    print_in_order(root->right);
}

void print_pre_order(Node* root) {
    if (root == NULL) {
        return;
    }
    
    ContactNote note = root->note;
    printf("Full name:\t%s\t%s\t%s\n", note.name.firstname, note.name.patronomic, note.name.lastname);
    printf("Company: %s, %s\n", note.company.company, note.company.position);
    printf("Phones:\n\tphone: %s\n\thome: %s\n\twork: %s\n", note.phones.phone, note.phones.home, note.phones.work);
    printf("Emails:\n\thome: %s\n\twork: %s\n", note.emails.home, note.emails.work);
    printf("---------------------------------------------------------------------\n");
    print_pre_order(root->left);
    print_pre_order(root->right);
}

void print_post_order(Node* root) {
    if (root == NULL) {
        return;
    }
    
    print_post_order(root->left);
    print_post_order(root->right);
    ContactNote note = root->note;
    printf("Full name:\t%s\t%s\t%s\n", note.name.firstname, note.name.patronomic, note.name.lastname);
    printf("Company: %s, %s\n", note.company.company, note.company.position);
    printf("Phones:\n\tphone: %s\n\thome: %s\n\twork: %s\n", note.phones.phone, note.phones.home, note.phones.work);
    printf("Emails:\n\thome: %s\n\twork: %s\n", note.emails.home, note.emails.work);
    printf("---------------------------------------------------------------------\n");
}

void free_all(Node* node) {
    if (node == NULL) {
        return;
    }

    free_all(node->left);
    free_all(node->right);

    free(node);
}

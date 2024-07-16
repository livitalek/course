#include <stdio.h>
#include <string.h>
#include "tree.h"

int main(int argc, char* argv[]) {
    ContactNote contact = {{"Ivan", "Ivanov", "Ivanovich"}, {"NSTU", "Student"}, {"+88005553535", NULL, NULL}, {"ivan_ivanov@example.com", NULL} };
    ContactNote contact2 = {{"Peter", "Ivanov", "Ivanovich"}, {"NSTU", "Student"}, {"+88005553535", NULL, NULL}, {"ivan_ivanov@example.com", NULL} };
    ContactNote contact3 = {{"Jacob", "Ivanov", "Ivanovich"}, {"NSTU", "Student"}, {"+88005553535", NULL, NULL}, {"ivan_ivanov@example.com", NULL} };
    ContactNote contact4 = {{"Ivan", "Ivanov", "Alexandrovich"}, {"NSTU", "Student"}, {"+123456789012", NULL, NULL}, {"aleksandr_ivanov@example.com", NULL} };
    ContactNote contact5 = create_contact(
        create_full_name("Alexander", "Liwicki", "Yrievich"), 
        create_company("NSTU", "Master student"), 
        create_phones("+79139546512", "+73833367435", "+78005553535"),
        create_emails("livitalek@yandex.ru", "liviczkii2023@stud.nstu.ru")
    );

    Node* root = NULL;
    root = insert_node(root, contact);
    root = insert_node(root, contact2);
    root = insert_node(root, contact3);
    root = insert_node(root, contact4);
    root = insert_node(root, contact5);

    printf("\n\n^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\n");
    print_in_order(root);

    root = delete_node(root, contact3);

    printf("\n\n^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\n");
    print_in_order(root);


    free_all(root);

    return 0;
}
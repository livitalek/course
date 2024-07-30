#include "addressbook.h"

void test(int val, int expect) {
    printf("value = %d, expect = %d ", val, expect);
    printf((val == expect) ? "(SUCCESS)\n" : "(FAIL)");
}

void tests() {
    ContactNote contact = {{"Ivan", "Ivanov", "Ivanovich"}, {"NSTU", "Student"}, {"+88005553535", NULL, NULL}, {"ivan_ivanov@example.com", NULL}, {{"VK", "https: vk.com/ivan78", "Ivan"}}};
    ContactNote contact2 = {{NULL, "Ivanov", "Ivanovich"}, {"NSTU", "Student"}, {"+88005553535", NULL, NULL}, {"ivan_ivanov@example.com", NULL}, {{"VK", "https: vk.com/ivan78", "Ivan"}}};
    ContactNote contact3 = {{"", "Ivanov", "Ivanovich"}, {"NSTU", "Student"}, {"+88005553535", NULL, NULL}, {"ivan_ivanov@example.com", NULL}, {{"VK", "https: vk.com/ivan78", "Ivan"}}};
    ContactNote contact4 = {{"Alexandr", "Ivanov", "Ivanovich"}, {"NSTU", "Student"}, {"+123456789012", NULL, NULL}, {"aleksandr_ivanov@example.com", NULL}, {{"VK", "https: vk.com/alex08", "Alex"}}};
    ContactNote contact5 = create_contact(
        create_full_name("Alexander", "Liwicki", "Yrievich"), 
        create_company("NSTU", "Master student"), 
        create_phones("+79139546512", "+73833367435", "+78005553535"),
        create_emails("livitalek@yandex.ru", "liviczkii2023@stud.nstu.ru"),
        (Social[]) {
            create_social("VK", "vk.com/livitalek", "Alex"),
            create_social("VK", "vk.com/livitalek", "Alex"),
            create_social("VK", "vk.com/livitalek", "Alex"),
            create_social("VK", "vk.com/livitalek", "Alex"),
            create_social("VK", "vk.com/livitalek", "Alex")
        });
    
    int val, exp;

    printf("\n\n^^^^^^^^^^^^^^^^^^^^^^^^^^^^\nTest: add contact\n");
    printf("1) add contact: contact = {{'Ivan','Ivanovich','Ivanov'}, ...}\n\n");
    val = add_note(contact);
    exp = 0;
    test(val, exp);

    printf("\n\n^^^^^^^^^^^^^^^^^^^^^^^^^^^^\nTest: add contact\n");
    printf("2) add contact: contact2 = {{NULL,'Ivanovich','Ivanov'}, ...}\n\n");
    val = add_note(contact2);
    exp = -1;
    test(val, exp);

    printf("\n\n^^^^^^^^^^^^^^^^^^^^^^^^^^^^\nTest: add contact\n");
    printf("3) add contact: contact3 = {{'','Ivanovich','Ivanov'}, ...}\n\n");
    val = add_note(contact2);
    exp = -1;
    test(val, exp);

    printf("\n\n^^^^^^^^^^^^^^^^^^^^^^^^^^^^\nTest: update contact\n");
    printf("4) add contact: contact = {{'Ivan','Ivanovich','Ivanov'}, ...}\n\n");
    val = add_note(contact);
    exp = 0;
    test(val, exp);


    printf("udate contact: contact4 = {{'Alexandr','Ivanovich','Ivanov'}, ...}, id = 1\n\n");
    val = update_note(1, contact4);
    exp = 0;
    test(val, exp);

    printf("\n\n^^^^^^^^^^^^^^^^^^^^^^^^^^^^\nTest: add contact\n");
    printf("5) add contact: contact = create_contact(create_full_name('Alexander', 'Liwicki', 'Yrievich'), ...)\n\n");

    val = add_note(contact5);
    exp = 0;
    test(val, exp);

    printf("\n\n^^^^^^^^^^^^^^^^^^^^^^^^^^^^\nTest: show all notes\n");
    printf("5) show all notes\n\n");
    show_notes();

    printf("\n\n^^^^^^^^^^^^^^^^^^^^^^^^^^^^\nTest: show note\n");
    printf("6) show all note id = 1\n\n");
    show_note(1);

    printf("\n\n^^^^^^^^^^^^^^^^^^^^^^^^^^^^\nTest: find first\n\n");
    printf("7) first_find(\"Alexandr\", \"Ivanov\", NULL, NULL, NULL)\n\n");
    int id = first_find("Alexandr", "Ivanov", NULL, NULL, NULL);
    exp = 1;
    test(id, exp);

    printf("\n\n^^^^^^^^^^^^^^^^^^^^^^^^^^^^\nTest: find first\n\n");
    printf("8) first_find(NULL, NULL, NULL, \"+88005553535\", NULL)\n\n");
    id = first_find(NULL, NULL, NULL, "+88005553535", NULL);
    exp = 0;
    test(id, exp);

    printf("\n\n^^^^^^^^^^^^^^^^^^^^^^^^^^^^\nTest: find first\n\n");
    printf("9) first_find(NULL, \"Ivanov\", NULL, NULL, NULL)\n\n");
    id = first_find(NULL, "Ivanov", NULL, NULL, NULL);
    exp = 0;
    test(id, exp);

    printf("\n\n^^^^^^^^^^^^^^^^^^^^^^^^^^^^\nTest: find all\n\n");
    printf("9) all_find(NULL, \"Ivanov\", NULL, NULL, NULL)\n\n");
    
    int* ids;
    int count = all_find(ids, NULL, "Ivanov", NULL, NULL, NULL);
    exp = 2;
    test(count, exp);
    
    printf("\n\n^^^^^^^^^^^^^^^^^^^^^^^^^^^^\nTest: delete note\n\n");
    printf("10) delete note id: 0\n\n");
    val = delete_note(0);
    exp = 0;
    test(val, exp);

    printf("\nShow all notes\n\n");
    show_notes();

    printf("\nSave & open file");

    save_file("my_file.txt");
    load_file("my_file.txt");
    show_notes();
}

int main(int argc, char* argv) {
    tests();
    return 0;
}
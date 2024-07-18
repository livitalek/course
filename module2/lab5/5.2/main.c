#include <stdio.h>
#include <dlfcn.h>
#include "addressbook.h"

void test(int val, int expect) {
    printf("value = %d, expect = %d ", val, expect);
    printf((val == expect) ? "(SUCCESS)\n" : "(FAIL)");
}

void tests() {
    void* handle;
    char* error;
    handle = dlopen("./libaddressbook.so", RTLD_LAZY);
    if (!handle) {
        fputs(dlerror(), stderr);
        printf("\n");
        exit(1);
    }
    
    _create_full_name = dlsym(handle, "create_full_name");
    _create_company = dlsym(handle, "create_company");
    _create_phones = dlsym(handle, "create_phones");
    _create_emails = dlsym(handle, "create_emails");
    _create_social = dlsym(handle, "create_social");
    _create_contact = dlsym(handle, "create_contact");

    _find_first = dlsym(handle, "find_first");
    _find_all = dlsym(handle, "find_all");

    _show_notes = dlsym(handle, "show_notes");
    _show_note = dlsym(handle, "show_note");


    _add_note = dlsym(handle, "add_note");
    _update_note = dlsym(handle, "update_note");
    _delete_note = dlsym(handle, "delete_note");
    _get_note = dlsym(handle, "get_note");
    _free_all = dlsym(handle, "free_all");
 
    ContactNote contact = {{"Ivan", "Ivanov", "Ivanovich"}, {"NSTU", "Student"}, {"+88005553535", NULL, NULL}, {"ivan_ivanov@example.com", NULL}, {{"VK", "https: vk.com/ivan78", "Ivan"}}};
    ContactNote contact2 = {{NULL, "Ivanov", "Ivanovich"}, {"NSTU", "Student"}, {"+88005553535", NULL, NULL}, {"ivan_ivanov@example.com", NULL}, {{"VK", "https: vk.com/ivan78", "Ivan"}}};
    ContactNote contact3 = {{"", "Ivanov", "Ivanovich"}, {"NSTU", "Student"}, {"+88005553535", NULL, NULL}, {"ivan_ivanov@example.com", NULL}, {{"VK", "https: vk.com/ivan78", "Ivan"}}};
    ContactNote contact4 = {{"Alexandr", "Ivanov", "Ivanovich"}, {"NSTU", "Student"}, {"+123456789012", NULL, NULL}, {"aleksandr_ivanov@example.com", NULL}, {{"VK", "https: vk.com/alex08", "Alex"}}};
    
    ContactNote contact5 = _create_contact(
        _create_full_name("Alexander", "Liwicki", "Yrievich"), 
        _create_company("NSTU", "Master student"), 
        _create_phones("+79139546512", "+73833367435", "+78005553535"),
        _create_emails("livitalek@yandex.ru", "liviczkii2023@stud.nstu.ru"),
        (Social[]) {
            _create_social("VK", "vk.com/livitalek", "Alex"),
            _create_social("VK", "vk.com/livitalek", "Alex"),
            _create_social("VK", "vk.com/livitalek", "Alex"),
            _create_social("VK", "vk.com/livitalek", "Alex"),
            _create_social("VK", "vk.com/livitalek", "Alex")
        });
    
    int val, exp;

    printf("\n\n^^^^^^^^^^^^^^^^^^^^^^^^^^^^\nTest: add contact\n");
    printf("1) add contact: contact = {{'Ivan','Ivanovich','Ivanov'}, ...}\n\n");
    val = _add_note(contact);
    exp = 0;
    test(val, exp);

    printf("\n\n^^^^^^^^^^^^^^^^^^^^^^^^^^^^\nTest: add contact\n");
    printf("2) add contact: contact2 = {{NULL,'Ivanovich','Ivanov'}, ...}\n\n");
    val = _add_note(contact2);
    exp = -1;
    test(val, exp);

    printf("\n\n^^^^^^^^^^^^^^^^^^^^^^^^^^^^\nTest: add contact\n");
    printf("3) add contact: contact3 = {{'','Ivanovich','Ivanov'}, ...}\n\n");
    val = _add_note(contact2);
    exp = -1;
    test(val, exp);

    printf("\n\n^^^^^^^^^^^^^^^^^^^^^^^^^^^^\nTest: update contact\n");
    printf("4) add contact: contact = {{'Ivan','Ivanovich','Ivanov'}, ...}\n\n");
    val = _add_note(contact);
    exp = 0;
    test(val, exp);


    printf("udate contact: contact4 = {{'Alexandr','Ivanovich','Ivanov'}, ...}, id = 1\n\n");
    val = _update_note(1, contact4);
    exp = 0;
    test(val, exp);

    printf("\n\n^^^^^^^^^^^^^^^^^^^^^^^^^^^^\nTest: add contact\n");
    printf("5) add contact: contact = create_contact(create_full_name('Alexander', 'Liwicki', 'Yrievich'), ...)\n\n");

    val = _add_note(contact5);
    exp = 0;
    test(val, exp);

    printf("\n\n^^^^^^^^^^^^^^^^^^^^^^^^^^^^\nTest: show all notes\n");
    printf("5) show all notes\n\n");
    _show_notes();

    printf("\n\n^^^^^^^^^^^^^^^^^^^^^^^^^^^^\nTest: show note\n");
    printf("6) show all note id = 1\n\n");
    _show_note(1);

    printf("\n\n^^^^^^^^^^^^^^^^^^^^^^^^^^^^\nTest: find first\n\n");
    printf("7) first_find(\"Alexandr\", \"Ivanov\", NULL, NULL, NULL)\n\n");
    int id;
    id = _find_first("Alexandr", "Ivanov", NULL, NULL, NULL);
    exp = 1;
    test(id, exp);

    printf("\n\n^^^^^^^^^^^^^^^^^^^^^^^^^^^^\nTest: find first\n\n");
    printf("8) first_find(NULL, NULL, NULL, \"+88005553535\", NULL)\n\n");
    id = _find_first(NULL, NULL, NULL, "+88005553535", NULL);
    exp = 0;
    test(id, exp);

    printf("\n\n^^^^^^^^^^^^^^^^^^^^^^^^^^^^\nTest: find first\n\n");
    printf("9) first_find(NULL, \"Ivanov\", NULL, NULL, NULL)\n\n");
    ContactNote out;
    id = _find_first(NULL, "Ivanov", NULL, NULL, NULL);
    exp = 0;
    test(id, exp);

    printf("\n\n^^^^^^^^^^^^^^^^^^^^^^^^^^^^\nTest: find all\n\n");
    printf("9) all_find(NULL, \"Ivanov\", NULL, NULL, NULL)\n\n");
    
    int* ids;
    int count = _find_all(ids, NULL, "Ivanov", NULL, NULL, NULL);
    exp = 2;
    test(count, exp);
    
    printf("\n\n^^^^^^^^^^^^^^^^^^^^^^^^^^^^\nTest: delete note\n\n");
    printf("10) delete note id: 0\n\n");
    val = _delete_note(0);
    exp = 0;
    test(val, exp);

    printf("\nShow all notes\n\n");
    _show_notes();
    
    _free_all();
    dlclose(handle);
}

int main(int argc, char* argv) {
    tests();
    return 0;
}
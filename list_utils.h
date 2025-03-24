#pragma once

#include <stdbool.h>

#define FILENAME "contacts.txt"
#define BUFFER_SIZE 512
#define MAX_STRING_LENGTH 128

typedef struct Contact {
	char* name;
	char* phone;
	char* email;
	struct Contact* next;
	struct Contact* prev;
} Contact;

bool load_file(Contact** head, Contact** tail);
int extract_string(char* output, char* input, int index);
bool add_node_sort(Contact** head, Contact** tail, char* name, char* phone, char* email);
bool add_contact(Contact** head, Contact** tail);
void clear_input_buffer(void);
bool get_input(char* str, char* prompt);
bool delete_contact(Contact* contacts);
bool search_contacts(Contact* contacts);
bool search_list(Contact* contacts, char* query);
void list_contacts(Contact* contacts);
bool edit_contact(Contact* contacts);
bool save_file(Contact* contacts);
bool free_memory(Contact* contacts);

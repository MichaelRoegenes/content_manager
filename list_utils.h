#pragma once

#include <stdbool.h>

#define FILENAME "contacts.txt"          // File name for storing contacts
#define BUFFER_SIZE 512                  // Size of buffer for reading file lines
#define MAX_STRING_LENGTH 128            // Maximum length for contact fields

// Structure representing a contact with doubly linked list pointers
typedef struct Contact {
	char* name;                          // Dynamically allocated name string
	char* phone;                         // Dynamically allocated phone string
	char* email;                         // Dynamically allocated email string
	struct Contact* next;                // Pointer to the next contact
	struct Contact* prev;                // Pointer to the previous contact
} Contact;

bool load_file(Contact** head, Contact** tail);              // Load contacts from file
int extract_string(char* output, char* input, int index);   // Extract tab-separated field
bool add_node_sort(Contact** head, Contact** tail, char* name, char* phone, char* email); // Add contact in sorted order
bool add_contact(Contact** head, Contact** tail);           // Add a new contact interactively
void clear_input_buffer(void);                              // Clear leftover input
bool get_input(char* str, char* prompt);                    // Get user input with prompt
bool delete_contact(Contact** head, Contact** tail);        // Delete a contact by name
bool search_contacts(Contact* contacts);                    // Search and display a contact
Contact* search_list(Contact* contacts, char* query);       // Search list for a contact
void list_contacts(Contact* contacts);                      // List all contacts
bool edit_contact(Contact* contacts);                       // Edit an existing contact
bool save_file(Contact* contacts);                          // Save contacts to file
bool free_memory(Contact* contacts);                        // Free allocated memory
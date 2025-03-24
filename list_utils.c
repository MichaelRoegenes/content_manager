#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "list_utils.h"
#include "output_utils.h"

// Loads contact data from a file into a sorted linked list
bool load_file(Contact** head, Contact** tail)
{
	// Open the file for reading
	FILE* input_file = fopen(FILENAME, "r");
	// Return false if file cannot be opened
	if (input_file == NULL)
	{
		return false;
	}
	// Allocate temporary buffer for reading lines
	char* buffer = malloc(sizeof(char) * BUFFER_SIZE);
	if (buffer == NULL)
	{
		fclose(input_file);
		return false;
	}
	// Allocate buffers for individual fields (name, phone, email)
	char* buffer_name = malloc(sizeof(char) * MAX_STRING_LENGTH);
	if (buffer_name == NULL)
	{
		fclose(input_file);
		free(buffer);
		return false;
	}
	char* buffer_phone = malloc(sizeof(char) * MAX_STRING_LENGTH);
	if (buffer_phone == NULL)
	{
		fclose(input_file);
		free(buffer);
		free(buffer_name);
		return false;
	}
	char* buffer_email = malloc(sizeof(char) * MAX_STRING_LENGTH);
	if (buffer_email == NULL)
	{
		fclose(input_file);
		free(buffer);
		free(buffer_name);
		free(buffer_phone);
		return false;
	}
	// Read the file line by line
	while (fgets(buffer, BUFFER_SIZE, input_file) != NULL)
	{
		int index = 0;
		// Extract name, phone, and email from the current line
		index = extract_string(buffer_name, buffer, index);
		index = extract_string(buffer_phone, buffer, index);
		index = extract_string(buffer_email, buffer, index);
		// Add extracted data as a new sorted node in the list
		add_node_sort(head, tail, buffer_name, buffer_phone, buffer_email);
	}
	// Clean up allocated memory and close the file
	free(buffer);
	free(buffer_name);
	free(buffer_phone);
	free(buffer_email);
	fclose(input_file);
	return true;
}

// Extracts a tab-separated string from input starting at index, stores it in output
int extract_string(char* output, char* input, int index)
{
	int i = 0;
	// Copy characters until tab, newline or null terminator is encountered
	while (input[index] != '\t' && input[index] != '\n' && input[index] != '\0')
	{
		output[i] = input[index];
		index++;
		i++;
	}
	// Null terminate the output string
	output[i] = '\0';
	// Move index past the delimiter
	index++;
	return index;
}

// Adds a new contact node to the list in alphabetical order by name
bool add_node_sort(Contact** head, Contact** tail, char* name, char* phone, char* email)
{
	// Allocate memory for the new contact node
	Contact* new_node = malloc(sizeof(Contact));
	if (new_node == NULL)
	{
		return false;
	}
	// Allocate and copy the strings (name, phone, email)
	char* new_name = malloc(sizeof(char) * strlen(name) + 1);
	if (new_name == NULL)
	{
		free(new_node);
		return false;
	}
	char* new_phone = malloc(sizeof(char) * strlen(phone) + 1);
	if (new_phone == NULL)
	{
		free(new_node);
		free(new_name);
		return false;
	}
	char* new_email = malloc(sizeof(char) * strlen(email) + 1);
	if (new_email == NULL)
	{

		free(new_node);
		free(new_name);
		free(new_phone);
		return false;
	}
	strcpy(new_name, name);
	strcpy(new_phone, phone);
	strcpy(new_email, email);
	// Assign fields to the new node
	new_node->name = new_name;
	new_node->phone = new_phone;
	new_node->email = new_email;
	new_node->next = NULL;
	new_node->prev = NULL;

	// If list is empty, set new node as head and tail 
	if (*head == NULL)
	{
		*head = new_node;
		*tail = *head;
		return true;
	}
	// If new node belongs at the start (alphabetically before head)
	else if (strcasecmp(new_node->name, (*head)->name) < 0)
	{
		new_node->next = *head;
		(*head)->prev = new_node;
		*head = new_node;
		return true;
	}
	// If new node belongs at the end (alphabetically after tail)
	else if (strcasecmp(new_node->name, (*tail)->name) > 0)
	{
		new_node->prev = *tail;
		(*tail)->next = new_node;
		*tail = new_node;
		return true;
	}
	// Otherwise, insert node in the correct position within the list
	else
	{
		Contact* ptr = *tail;
		while (ptr != NULL)
		{
			if (strcasecmp(new_node->name, ptr->name) > 0)
			{
				new_node->prev = ptr;
				new_node->next = ptr->next;
				ptr->next->prev = new_node;
				ptr->next = new_node;
				return true;
			}
			ptr = ptr->prev;
		}
	}
	// (should not reach this)
	return false;
}

// Adds a new contact to a sorted linked list
bool add_contact(Contact** head, Contact** tail)
{
	// Initialize temporary storage
	char buffer_name[MAX_STRING_LENGTH];
	char buffer_phone[MAX_STRING_LENGTH];
	char buffer_email[MAX_STRING_LENGTH];

	// Clear any remaining input
	clear_input_buffer();

	// Prompt and store input
	get_input(buffer_name, "Name: ");
	get_input(buffer_phone, "Phone: ");
	get_input(buffer_email, "Email: ");

	// Add new contact in sorted position
	add_node_sort(head, tail, buffer_name, buffer_phone, buffer_email);
	search_list(*head, buffer_name);
	return true;
}

// Clears the input buffer of any remaining characters
void clear_input_buffer(void)
{
	int c;
	while ((c = getchar()) != '\n' && c != EOF);
}

// Gets user input and stores it in the provided string
bool get_input(char* str, char* prompt)
{
	printf("%s", prompt);
	if (fgets(str, sizeof(char) * MAX_STRING_LENGTH, stdin) != NULL)
	{
		// Check for length and remove trailing newline if present
		int len = strlen(str);
		if (len > 0 && str[len - 1] == '\n')
		{
			str[len - 1] = '\0';
		}
	}
	return true;
}

bool delete_contact(Contact* contacts)
{
	return true;
}

bool search_contacts(Contact* contacts)
{
	char query[MAX_STRING_LENGTH];
	clear_input_buffer();

	get_input(query, "Name: ");

	return search_list(contacts, query);
}

bool search_list(Contact* contacts, char* query)
{
	for (Contact* ptr = contacts; ptr != NULL; ptr = ptr->next)
	{
		if (strcasecmp(ptr->name, query) == 0)
		{
			print_single_contact(ptr);
			return true;
		}
	}
}

// Displays a formatted table of contacts from a linked list
void list_contacts(Contact* contacts)
{
	int name_max, phone_max, email_max;
	// Initialize minimum column widths for formatting
	name_max = phone_max = email_max = 0;

	// Determine maximum length of each field for column alignment
	for (Contact* ptr = contacts; ptr != NULL; ptr = ptr->next)
	{
		int name_len = strlen(ptr->name);
		int phone_len = strlen(ptr->phone);
		int email_len = strlen(ptr->email);
		// Update maximum lengths if current entry exceeds them
		if (name_len > name_max)
			name_max = name_len;
		if (phone_len > phone_max)
			phone_max = phone_len;
		if (email_len > email_max)
			email_max = email_len;
	}

	// Print table header and get total line length
	int line_len = print_table_header(name_max, phone_max, email_max);

	// Print each contact's details in aligned columns
	for (Contact* ptr = contacts; ptr != NULL; ptr = ptr->next)
	{
		print_contact(ptr, name_max, phone_max, email_max);
	}
	// Print closing line of the table
	print_line(line_len);
}


bool edit_contact(Contact* contacts)
{
	return true;
}

bool save_file(Contact* contacts)
{
	FILE* output_file = fopen(FILENAME, "w");
	if (output_file == NULL)
	{
		return false;
	}
	for (Contact* ptr = contacts; ptr != NULL; ptr = ptr->next)
	{
		fprintf(output_file, "%s\t%s\t%s\n", ptr->name, ptr->phone, ptr->email);
	}
	fclose(output_file);
	return true;
}

bool free_memory(Contact* contacts)
{
	Contact* ptr = contacts;
	Contact* tmp = contacts;
	while (ptr != NULL)
	{
		tmp = ptr;
		ptr = ptr->next;
		free(tmp->name);
		free(tmp->phone);
		free(tmp->email);
		free(tmp);
	}
}
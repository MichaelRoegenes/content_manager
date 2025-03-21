#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#define FILENAME "contacts.txt"
#define BUFFER_SIZE 512
#define MAX_STRING_LENGTH 128
#define FORMAT_MIN_LENTH 20
#define SPACES_IN_TABLE 3
#define VERTICAL_BARS_IN_TABLE 4
#define LIST_PADDING 4

typedef struct Contact{
	char* name;
	char* phone;
	char* email;
	struct Contact *next;
	struct Contact *prev;
} Contact;

bool load_file(Contact** contacts);
int extract_string(char* output, char* input, int index);
bool add_node_sort(Contact** head, Contact** tail, char* name, char* phone, char* email);
bool add_contact(Contact* contacts);
bool delete_contact(Contact* contacts);
bool search_contacts(Contact* contacts);
void list_contacts(Contact* contacts);
void print_line(int len);
void print_contact(Contact* ptr, int name_len, int phone_len, int email_len);
int print_table_header(int name_len, int phone_len, int email_len);
bool edit_contact(Contact* contacts);
bool save_file(Contact* contacts);
bool free_memory(Contact* contacts);

const Contact header = { "Name", "Phone", "Email", NULL, NULL};

// Entry point of the Content Manager program
int main(void)
{
	// Display program title with decorative borders
	printf("---------------\n"
		   "Content Manager\n"
		   "---------------\n");
	// Initialize an empty linked list of contacts
	Contact* contacts = NULL;
	// Load existing contacts from a file into the list
	load_file(&contacts);
	
	// Main program loop for user interaction 
	while (true)
	{
		// Display menu options for user selection
		printf("1. Add contact\n"
			   "2. Delete contact\n"
			   "3. Search contact\n"
			   "4. List all contacts\n"
			   "5. Edit contact\n"
			   "6. Exit\n"
			   "Enter your choice: ");

		// Variable to store user's menu choice
		int menu_selection = 0;
		// Wait for valid input (characters '1' to '6')
		while ((menu_selection = getchar()) < '1' || menu_selection > '6')
			; // Empty loop body; continues until valid input is received
		
		// Execute corresponding action based on user selection
		if (menu_selection == '1')
			// Add a new contact to the list
			add_contact(contacts);
		else if (menu_selection == '2')
			// Remove a contact from the list
			delete_contact(contacts);
		else if (menu_selection == '3')
			// Search for a contact in the list
			search_contacts(contacts);
		else if (menu_selection == '4')
			// Display all contacts in a formatted table
			list_contacts(contacts);
		else if (menu_selection == '5')
			// Modify an existing contacts's details
			edit_contact(contacts);
		else
		{
			// Save contacts to file before exiting
			save_file(contacts);
			// Free allocated memory to prevent leaks
			free_memory(contacts);
			// Exit the program successfully
			return 0;
		}
	}
}

// Loads contact data from a file into a sorted linked list
bool load_file(Contact** contacts)
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
	// Track the tail of the list for efficient insertion
	Contact* tail = NULL;
	// Read the file line by line
	while (fgets(buffer, BUFFER_SIZE, input_file) != NULL)
	{
		int index = 0;
		// Extract name, phone, and email from the current line
		index = extract_string(buffer_name, buffer, index);
		index = extract_string(buffer_phone, buffer, index);
		index = extract_string(buffer_email, buffer, index);
		// Add extracted data as a new sorted node in the list
		add_node_sort(contacts, &tail, buffer_name, buffer_phone, buffer_email);
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

bool add_contact(Contact* contacts)
{
	return true;
}

bool delete_contact(Contact* contacts)
{
	return true;
}

bool search_contacts(Contact* contacts)
{

	return true;
}

// Displays a formatted table of contacts from a linked list
void list_contacts(Contact* contacts)
{
	int name_max, phone_max, email_max;
	// Initialize minimum column widths for formatting
	name_max = phone_max = email_max = FORMAT_MIN_LENTH;

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

	// Add padding to maximum lengths for better readability
	name_max += LIST_PADDING;
	phone_max += LIST_PADDING;
	email_max += LIST_PADDING;
	
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

// Prints table header with specified column widths and returns total line length
int print_table_header(int name_len, int phone_len, int email_len)
{
	// Calculate total line length including vertical bars and spaces
	int line_len = name_len + phone_len + email_len + VERTICAL_BARS_IN_TABLE + SPACES_IN_TABLE;
	// Print top border of the table
	print_line(line_len);
	// Print header row with field names, left aligned within their columns
	printf("| %-*s| %-*s| %-*s|\n", name_len, header.name, phone_len, header.phone, email_len, header.email);
	// Print separator line below header
	print_line(line_len);
	return line_len;
}

// Prints a single contact's details in a formatted table row
void print_contact(Contact* ptr, int name_len, int phone_len, int email_len)
{
	// Print contact info with specified field widths, left aligned
	printf("| %-*s| %-*s| %-*s|\n", name_len, ptr->name, phone_len, ptr->phone, email_len, ptr->email);
}

// Prints a horizontal line of dashes with the specified length
void print_line(int len)
{
	// Output a series of dashes with the specified length
	for (int i = 0; i < len; i++)
		printf("-");
	// End the line with a newline character
	printf("\n");
}

bool edit_contact(Contact* contacts)
{
	return true;
}

bool save_file(Contact* contacts)
{
	return true;
}

bool free_memory(Contact* contacts)
{
	return true;
}
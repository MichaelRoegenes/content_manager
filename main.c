#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#define FILENAME "contacts.txt"
#define BUFFER_SIZE 512
#define MAX_STRING_LENGTH 128
#define FORMAT_MIN_LENTH 20
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
bool edit_contact(Contact* contacts);
bool save_file(Contact* contacts);
bool free_memory(Contact* contacts);

int main(void)
{
	printf("---------------\n"
		   "Content Manager\n"
		   "---------------\n");
	Contact* contacts = NULL;
	load_file(&contacts);
	while (true)
	{
		printf("1. Add contact\n"
			   "2. Delete contact\n"
			   "3. Search contact\n"
			   "4. List all contacts\n"
			   "5. Edit contact\n"
			   "6. Exit\n"
			   "Enter your choice: ");
		int menu_selection = 0;
		while ((menu_selection = getchar()) < '1' || menu_selection > '6')
			;
		if (menu_selection == '1')
			add_contact(contacts);
		else if (menu_selection == '2')
			delete_contact(contacts);
		else if (menu_selection == '3')
			search_contacts(contacts);
		else if (menu_selection == '4')
			list_contacts(contacts);
		else if (menu_selection == '5')
			edit_contact(contacts);
		else
		{
			save_file(contacts);
			free_memory(contacts);
			return 0;
		}
	}
	return 0;
}

bool load_file(Contact** contacts)
{
	FILE* input_file = fopen(FILENAME, "r");
	if (input_file == NULL)
	{
		return false;
	}
	char* buffer = malloc(sizeof(char) * BUFFER_SIZE);
	if (buffer == NULL)
	{
		fclose(input_file);
		return false;
	}
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
	Contact* tail = NULL;
	while (fgets(buffer, BUFFER_SIZE, input_file) != NULL)
	{
		int index = 0;
		index = extract_string(buffer_name, buffer, index);
		index = extract_string(buffer_phone, buffer, index);
		index = extract_string(buffer_email, buffer, index);
		add_node_sort(contacts, &tail, buffer_name, buffer_phone, buffer_email);
	}
	free(buffer);
	free(buffer_name);
	free(buffer_phone);
	free(buffer_email);
	fclose(input_file);
	return true;
}

int extract_string(char* output, char* input, int index)
{
	int i = 0;
	while (input[index] != '\t' && input[index] != '\n' && input[index] != '\0')
	{
		output[i] = input[index];
		index++;
		i++;
	}
	output[i] = '\0';
	index++;
	return index;
}

bool add_node_sort(Contact** head, Contact** tail, char* name, char* phone, char* email)
{
	Contact* new_node = malloc(sizeof(Contact));
	if (new_node == NULL)
	{
		return false;
	}
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
	new_node->name = new_name;
	new_node->phone = new_phone;
	new_node->email = new_email;
	new_node->next = NULL;
	new_node->prev = NULL;
	if (*head == NULL)
	{
		*head = new_node;
		*tail = *head;
		return true;
	}
	else if (strcasecmp(new_node->name, (*head)->name) < 0)
	{
		new_node->next = *head;
		(*head)->prev = new_node;
		*head = new_node;
		return true;
	}
	else if (strcasecmp(new_node->name, (*tail)->name) > 0)
	{
		new_node->prev = *tail;
		(*tail)->next = new_node;
		*tail = new_node;
		return true;
	}
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

void list_contacts(Contact* contacts)
{
	int name_max, phone_max, email_max;
	name_max = phone_max = email_max = FORMAT_MIN_LENTH;

	for (Contact* ptr = contacts; ptr != NULL; ptr = ptr->next)
	{
		int name_len = strlen(ptr->name);
		int phone_len = strlen(ptr->phone);
		int email_len = strlen(ptr->email);
		if (name_len > name_max)
			name_max = name_len;
		if (phone_len > phone_max)
			phone_max = phone_len;
		if (email_len > email_max)
			email_max = email_len;
	}
	name_max += LIST_PADDING;
	phone_max += LIST_PADDING;
	email_max += LIST_PADDING;
	int line_lenth = name_max + phone_max + email_max + VERTICAL_BARS_IN_TABLE;
	print_line(line_lenth + VERTICAL_BARS_IN_TABLE);
	printf("| %-*s| %-*s| %-*s|\n", name_max, "Name", phone_max, "Phone", email_max, "Email");
	print_line(line_lenth + VERTICAL_BARS_IN_TABLE);
	for (Contact* ptr = contacts; ptr != NULL; ptr = ptr->next)
	{
		printf("| %-*s| %-*s| %-*s|\n", name_max, ptr->name, phone_max, ptr->phone, email_max, ptr->email);
	}
	print_line(line_lenth + VERTICAL_BARS_IN_TABLE);
}

void print_line(int len)
{
	for (int i = 0; i < len; i++)
		printf("-");
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
#include <stdio.h>
#include <stdbool.h>

#define FILENAME "contacts.txt"

typedef struct Contact{
	char* name;
	char* phone;
	char* email;
	struct Contact *next;
	struct Contact *prev;
} Contact;

bool load_file(Contact* list);
bool add_contact(Contact* contacts);
bool delete_contact(Contact* contacts);
bool search_contacts(Contact* contacts);
bool list_contacts(Contact* contacts);
bool edit_contact(Contact* contacts);

int main(void)
{
	printf("---------------\n"
		   "Content Manager\n"
		   "---------------\n");
	Contact* contacts = NULL;
	load_file(contacts);
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
			return 0;
		}
	}
	return 0;
}

bool load_file(Contact* contacts)
{
	FILE* input_file = fopen(FILENAME, "r");
	if (input_file == NULL)
	{
		return false;
	}
	fclose(input_file);
	return true;
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

bool list_contacts(Contact* contacts)
{
	return true;
}

bool edit_contact(Contact* contacts)
{
	return true;
}
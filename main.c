#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "list_utils.h"
#include "output_utils.h"

// Entry point of the Content Manager program
int main(void)
{
	// Display program title with decorative borders
	printf("------------------------\n"
		   "|   Content Manager    |\n");
	// Initialize an empty linked list of contacts
	Contact* contacts_head = NULL;
	Contact* contacts_tail = contacts_head;
	// Load existing contacts from a file into the list
	load_file(&contacts_head, &contacts_tail);
	
	// Main program loop for user interaction 
	while (true)
	{
		// Display menu options for user selection
		printf("------------------------\n"
			   "|      Main Menu       |\n"
			   "------------------------\n"
			   "| 1. Add contact       |\n"
			   "| 2. Delete contact    |\n"
			   "| 3. Search contact    |\n"
			   "| 4. List all contacts |\n"
			   "| 5. Edit contact      |\n"
			   "| 6. Exit              |\n"
			   "------------------------\n"
			   "Enter your choice: ");

		// Variable to store user's menu choice
		int menu_selection = 0;
		// Wait for valid input (characters '1' to '6')
		while ((menu_selection = getchar()) < '1' || menu_selection > '6'); 
		// Empty loop body; continues until valid input is received
		
		// Execute corresponding action based on user selection
		if (menu_selection == '1')
			// Add a new contact to the list
			add_contact(&contacts_head, &contacts_tail);
		else if (menu_selection == '2')
			// Remove a contact from the list
			delete_contact(contacts_head);
		else if (menu_selection == '3')
			// Search for a contact in the list
			search_contacts(contacts_head);
		else if (menu_selection == '4')
			// Display all contacts in a formatted table
			list_contacts(contacts_head);
		else if (menu_selection == '5')
			// Modify an existing contacts' details
			edit_contact(contacts_head);
		else
		{
			// Save contacts to file before exiting
			save_file(contacts_head);
			// Free allocated memory to prevent leaks
			free_memory(contacts_head);
			// Exit the program successfully
			return 0;
		}
	}
}

#include "output_utils.h"
#include "list_utils.h"

#include <stdio.h>
#include <stdbool.h>
#include <string.h>

void print_single_contact(Contact* contact)
{
	int name_len = strlen(contact->name);
	int phone_len = strlen(contact->phone);
	int email_len = strlen(contact->email);
	int line_len = print_table_header(name_len, phone_len, email_len);
	print_contact(contact, name_len, phone_len, email_len);
	print_line(line_len);
}

// Prints table header with specified column widths and returns total line length
int print_table_header(int name_len, int phone_len, int email_len)
{
	Contact header = { "Name", "Phone", "Email", NULL, NULL };
	// Calculate total line length including vertical bars and spaces
	int line_len = name_len + phone_len + email_len + VERTICAL_BARS_IN_TABLE + SPACES_IN_TABLE;
	// Print top border of the table
	print_line(line_len);
	// Print header row with field names, left aligned within their columns
	print_contact(&header, name_len, phone_len, email_len);
	// Print separator line below header
	print_line(line_len);
	return line_len;
}

// Prints a single contact's details in a formatted table row
void print_contact(Contact* ptr, int name_len, int phone_len, int email_len)
{
	// Print contact info with specified field widths, left aligned
	printf("| %-*s   | %-*s   | %-*s   |\n", name_len, ptr->name, phone_len, ptr->phone, email_len, ptr->email);
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
#pragma once

#include "list_utils.h"

void print_single_contact(Contact* contact);                // Print details of a single contact
void print_line(int len);                                   // Print a horizontal line of given length
void print_contact(Contact* ptr, int name_len, int phone_len, int email_len); // Print a contact in table format
int print_table_header(int name_len, int phone_len, int email_len); // Print table header and return length

#define SPACES_IN_TABLE 12                                  // Number of spaces in table formatting
#define VERTICAL_BARS_IN_TABLE 4                            // Number of vertical bars in table
#pragma once

#include "list_utils.h"

void print_single_contact(Contact* contact);
void print_line(int len);
void print_contact(Contact* ptr, int name_len, int phone_len, int email_len);
int print_table_header(int name_len, int phone_len, int email_len);

#define SPACES_IN_TABLE 12
#define VERTICAL_BARS_IN_TABLE 4
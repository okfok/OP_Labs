#ifndef LAB1_FILEPOINTER_H
#define LAB1_FILEPOINTER_H

#include <iostream>
//#include "string.h"

void file_pointer_main(const char *in_file_name, const char *out_file_name);

void print_from_file(const char *file_name);

void create_or_append_file(const char *file_name);

int to_number(const char *file_name, int begin, int end);

void write_task_line(const char *in_file_name, FILE * out_file_ptr, int begin, int end, int min);

void task(const char *in_file_name, const char *out_file_name);

#endif //LAB1_FILEPOINTER_H

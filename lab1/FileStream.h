#ifndef LAB1_FILESTREAM_H
#define LAB1_FILESTREAM_H

#include <fstream>
#include <iostream>
#include <algorithm>

void file_stream_main(const std::string& in_file_name, const std::string& out_file_name);

void print_from_file(const std::string& file_name);

void create_or_append_file(const std::string& file_name);

bool is_number(const std::string &s);

void task(const std::string& in_file_name, const std::string& out_file_name);

#endif //LAB1_FILESTREAM_H

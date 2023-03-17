#include <iostream>
#include "ClinicAttendance.h"


std::string INPUT_FILE_NAME = "in.bin";


int main() {
    std::cout << "Ctrl+B char: " << (char) 2 << '\n';
    create_or_append_file(INPUT_FILE_NAME);
    std::cout << "Input file:\n";
    print_from_file(INPUT_FILE_NAME);


}




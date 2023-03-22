#include <iostream>
#include "ClinicAttendance.h"


const char INPUT_FILE_NAME[] = "in.bin";
const char SECONDARY_PATIENTS_FILE_NAME[] = "secondary_patients.bin";
const char OTHER_PATIENTS_FILE_NAME[] = "other_patients.bin";


int main() {
    std::cout << "Ctrl+B char: " << (char) 2 << '\n';

    create_or_append_file(INPUT_FILE_NAME);

    std::cout << "Input file:\n";
    print_from_file(INPUT_FILE_NAME);

    delete_by_filter(INPUT_FILE_NAME);

    std::cout << "Input file after deleting:\n";
    print_from_file(INPUT_FILE_NAME);


}




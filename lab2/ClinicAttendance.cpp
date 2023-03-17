#include "ClinicAttendance.h"

void create_or_append_file(const std::string &file_name) {
    std::ifstream in_file(file_name, std::ios::binary);
    int mode = 0;
    if (in_file.is_open()) { // if file found print content and ask what to do
        std::cout << "Found file, content:\n";
        in_file.close();

        print_from_file(file_name);

        std::cout << "To rewrite file enter 0, to append 1, to not change 2: ";
        std::cin >> mode;
    }

    switch (mode) {
        case 0:
        case 1:
            write_to_file(file_name, mode);
            break;
        case 2:
            return; // not edit
        default:
            throw;
    }

}

void write_ca_record(std::ostream &out, ClinicAttendance const &data) {
    size_t size = data.surname.size();
    out.write(reinterpret_cast<const char *>(&size), sizeof(size));
    out.write(&data.surname[0], size);
    out.write(reinterpret_cast<char const *>(&data.prev_attendance_date), sizeof(data.prev_attendance_date));
    out.write(reinterpret_cast<char const *>(&data.cur_attendance_time), sizeof(data.cur_attendance_time));

}

ClinicAttendance *read_ca_record(std::istream &in) {
    auto ca = new ClinicAttendance;
    size_t size;
    in.read(reinterpret_cast<char *>(&size), sizeof(size));

    if (in.eof())
        return nullptr;

    ca->surname.resize(size);
    in.read(&ca->surname[0], size);

    in.read(reinterpret_cast<char *>(&ca->prev_attendance_date), sizeof(ca->prev_attendance_date));
    in.read(reinterpret_cast<char *>(&ca->cur_attendance_time), sizeof(ca->cur_attendance_time));


    return ca;
}

void write_to_file(const std::string &file_name, bool append) {
    ClinicAttendance ca;

    std::ofstream file;
    if (append)
        file.open(file_name, std::ios::binary | std::ios::app);
    else
        file.open(file_name, std::ios::binary);

    std::cout << "Writing to file.\nIf you want to end input, press Ctrl+B and then Enter in surname entry.\n";

    while (true) {
        std::cout << "Surname: ";
        std::cin >> ca.surname;
        if (ca.surname[0] == 2) // 2 is code of Ctrl+B
            break;
        std::cout << "Previous attendance prev_attendance_date (dd.mm.yyyy): ";
        scanf("%i.%i.%i",
              &ca.prev_attendance_date.day,
              &ca.prev_attendance_date.month,
              &ca.prev_attendance_date.year
        );
        std::cout << "Attendance cur_attendance_time (hh:mm): ";
        scanf("%i:%i",
              &ca.cur_attendance_time.hours,
              &ca.cur_attendance_time.minutes
        );

        write_ca_record(file, ca);

    }

    file.close();
}

void print_from_file(const std::string &file_name) {
    ClinicAttendance *ca;
    std::ifstream file(file_name, std::ios::binary);

    if (!file) {
        std::cout << "Error opening file. Program aborting.\n";
        return;
    }


    while ((ca = read_ca_record(file))) {
        std::cout << "Surname: " << ca->surname << '\n'
                  << "Previous attendance: "
                  << ca->prev_attendance_date.day << "."
                  << ca->prev_attendance_date.month << "."
                  << ca->prev_attendance_date.year << '\n'
                  << "Attendance cur_attendance_time: "
                  << ca->cur_attendance_time.hours << ':'
                  << ca->cur_attendance_time.minutes << "\n\n";

    }
    std::cout << "That's all the data in the file!\n";
    file.close();
}

bool attendance_passed(Time time){
    tm* now = cur_time();
    return (now->tm_hour* 60 + now->tm_min) > (time.hours * 60 + time.minutes);
}

tm* cur_time(){
    std::time_t t = std::time(nullptr);
    return std::localtime(&t);
}
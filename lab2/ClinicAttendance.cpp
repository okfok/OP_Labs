#include "ClinicAttendance.h"

void create_or_append_file(const char file_name[]) {
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
            write_console_to_file(file_name, mode);
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

void write_console_to_file(const char file_name[], bool append) {
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

void print_from_file(const char file_name[]) {
    ClinicAttendance *ca;
    std::ifstream file(file_name, std::ios::binary);

    if (!file) {
        std::cout << "Error opening file. Program aborting.\n";
        throw;
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

bool attendance_passed_filter(const ClinicAttendance &ca) {
    tm now = cur_time();
    return (now.tm_hour * 60 + now.tm_min) >
           (ca.cur_attendance_time.hours * 60 + ca.cur_attendance_time.minutes);
}

bool secondary_patient_filter(const ClinicAttendance &ca) {
    tm now = cur_time(), time = prev_attendance_time(ca);
    return difftime(mktime(&now), mktime(&time)) <= 10 * 24 * 3600;

}

tm cur_time() {
    time_t t = std::time(nullptr);
    return *std::localtime(&t);
}

tm prev_attendance_time(ClinicAttendance const &ca) {
    tm time = cur_time();

    time.tm_year = ca.prev_attendance_date.year - 1900;
    time.tm_mon = ca.prev_attendance_date.month - 1;
    time.tm_mday = ca.prev_attendance_date.day;
    return time;
}


void delete_by_filter(const char file_name[], bool (*filter)(const ClinicAttendance &)) {
    std::ifstream file(file_name, std::ios::binary);
    std::ofstream temp_file(TEMP_FILE_NAME, std::ios::binary);

    ClinicAttendance *ca;

    while ((ca = read_ca_record(file))) {
        if (!filter(*ca)) {
            write_ca_record(temp_file, *ca);
        }
    }

    file.close();
    temp_file.close();
    remove(file_name);
    rename(TEMP_FILE_NAME, file_name);


}


void sort_patients(
        const char in_file_name[],
        const char passed_file_name[],
        const char not_passed_file_name[],
        bool (*filter)(const ClinicAttendance &)
) {
    std::ifstream in_file(in_file_name, std::ios::binary);
    std::ofstream pass_file(passed_file_name, std::ios::binary);
    std::ofstream not_pass_file(not_passed_file_name, std::ios::binary);

    ClinicAttendance *ca;

    while ((ca = read_ca_record(in_file))) {
        write_ca_record(
                filter(*ca) ? pass_file : not_pass_file,
                *ca
        );
    }

    in_file.close();
    pass_file.close();
    not_pass_file.close();

}
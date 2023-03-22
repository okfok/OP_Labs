#ifndef LAB2_CLINICATTENDANCE_H
#define LAB2_CLINICATTENDANCE_H

#include <string>
#include <fstream>
#include <iostream>
#include <ctime>

const char TEMP_FILE_NAME[] = "temp.bin";

struct Date {
    int day;
    int month;
    int year;
};

struct Time {
    int minutes;
    int hours;
};

struct ClinicAttendance {
    std::string surname;
    Date prev_attendance_date;
    Time cur_attendance_time;
};

tm cur_time();

tm prev_attendance_time(ClinicAttendance const &ca);

void create_or_append_file(const char file_name[]);

void write_ca_record(std::ostream &out, ClinicAttendance const &data);

ClinicAttendance *read_ca_record(std::istream &in);

void write_console_to_file(const char file_name[], bool append = false);

void print_from_file(const char file_name[]);

bool attendance_passed_filter(const ClinicAttendance &);

bool secondary_patient_filter(const ClinicAttendance &);

void delete_by_filter(
        const char file_name[],
        bool (*filter)(const ClinicAttendance &) = attendance_passed_filter
);

void sort_patients(
        const char in_file_name[],
        const char passed_file_name[],
        const char not_passed_file_name[],
        bool (*filter)(const ClinicAttendance &) = secondary_patient_filter
);


#endif //LAB2_CLINICATTENDANCE_H

#ifndef LAB2_CLINICATTENDANCE_H
#define LAB2_CLINICATTENDANCE_H

#include <string>
#include <fstream>
#include <iostream>
#include <ctime>

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

tm* cur_time();

void create_or_append_file(const std::string &file_name);

void write_ca_record(std::ostream &out, ClinicAttendance const &data);

ClinicAttendance *read_ca_record(std::istream &in);

void write_to_file(const std::string &file_name, bool append = false);

void print_from_file(const std::string &file_name);

bool attendance_passed(Time time);

void delete_if_attendance_passed(const std::string &file_name);


#endif //LAB2_CLINICATTENDANCE_H

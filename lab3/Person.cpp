#include "Person.h"

DateOfBirth::DateOfBirth(int day, int month, int year) {
    if (0 < day && day <= 31)
        this->day = day;
    else
        throw "Day must be from 1 to 31";

    if (0 < month && month <= 12)
        this->month = month;
    else
        throw "Month must be from 1 to 12";

    if (1800 <= year && year <= 2023)
        this->year = year;
    else
        throw "Year must be from 1800 to 2023";

}

std::string to_str(int num) {
    std::string s;
    return (((s = std::to_string(num)).size() == 1) ? "0" + s : s);
}

std::string DateOfBirth::str() const {
    return to_str(day)
           + '-' + to_str(month)
           + '-' + to_str(year);
}

int sum_of_digits(int num) {
    int sum = 0;
    while (num > 0) {
        sum += num % 10;
        num /= 10;
    }
    return sum;
}

bool DateOfBirth::happy_day() const {
    int num = sum_of_digits(day) % 7;
    return num == sum_of_digits(month) % 7
           && num == sum_of_digits(year) % 7;
}

std::string input_valid_str(const std::string &input_name) {
    std::string str;

    bool valid = false;
    while (!valid) {

        std::cout << input_name << ": ";
        getline(std::cin, str);
        valid = true;

        for (char chr: str) {
            if (isdigit(chr))
                valid = false;
        }

        if (!valid)
            std::cout << "Validation error: " << input_name << " is not valid, try one more time.\n";
    }

    return str;
}

DateOfBirth input_valid_date() {

    while (true) {
        std::cout << "Date of birth (dd-mm-yyyy): ";

        std::string line;
        getline(std::cin, line);
        try {

            if (line.size() != 10)
                throw std::invalid_argument("Not valid format");

            int day = std::stoi(line.substr(0, 2));
            int month = std::stoi(line.substr(3, 2));
            int year = std::stoi(line.substr(6, 4));


            try {
                return DateOfBirth(day, month, year);
            }
            catch (const char *exception) {
                std::cout << "Validation error: " << exception << "\n";
            }
        }
        catch (std::invalid_argument) {
            std::cout << "Validation error: date should be in \"dd-mm-yyyy\" format.\n";
        }


    }
}

Person *Person::input_from_console() {

    std::string surname, name, patronymic;
    surname = input_valid_str("Surname");
    name = input_valid_str("Name");
    patronymic = input_valid_str("Patronymic");

    DateOfBirth date_of_birth = input_valid_date();


    return new Person(surname, name, patronymic, date_of_birth);
}

std::string Person::str() {
    return surname + ' ' + name + ' ' + patronymic + ' ' + date_of_birth.str();
}

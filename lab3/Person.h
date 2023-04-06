#ifndef LAB3_PERSON_H
#define LAB3_PERSON_H

#include <iostream>
#include <utility>


class DateOfBirth {
    int day;
    int month;
    int year;
public:
    DateOfBirth(int day, int month, int year);

    std::string str() const;

    bool happy_day() const;
};

class Person {
    std::string surname;
    std::string name;
    std::string patronymic;
    DateOfBirth date_of_birth;

public:

    Person(
            std::string surname,
            std::string name,
            std::string patronymic,
            DateOfBirth date_of_birth
    ) :
            surname(std::move(surname)),
            name(std::move(name)),
            patronymic(std::move(patronymic)),
            date_of_birth(date_of_birth) {};

    static Person *input_from_console();

    std::string str();

    bool happy_day() { return date_of_birth.happy_day(); };

};


#endif //LAB3_PERSON_H

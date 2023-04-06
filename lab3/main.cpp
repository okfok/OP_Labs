#include <iostream>
#include "Person.h"

int main() {

    int count;
    std::cout << "Enter count of peoples: ";
    std::cin >> count;


    Person *person_array[count];

    for (int i = 0; i < count; ++i) {
        person_array[i] = Person::input_from_console();
    }

    std::cout << "List of peoples:\n";

    for (int i = 0; i < count; ++i) {
        std::cout << person_array[i]->str()
                  << ((person_array[i]->happy_day()) ? " Happy day!" : "")
                  << '\n';

    }

}

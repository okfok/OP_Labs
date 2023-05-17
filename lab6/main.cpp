#include <iostream>
#include "Map.h"
#include "Map.cpp"

template<typename Data>
void task(int size);

int main() {
    int size, type;

    std::cout << "Input hash-matrix size:";
    std::cin >> size;

    std::cout << "Input one of supported data types\n0 - int\n1 - double\n2 - char\n3 - string\n";
    std::cin >> type;

    switch (type) {
        case 0: {
            task<int>(size);
            break;
        }
        case 1: {
            task<double>(size);
            break;
        }
        case 2: {
            task<char>(size);
            break;
        }
        case 3: {
            task<std::string>(size);
            break;
        }
        default: {
            throw std::logic_error("Wrong type");
        }
    }

}

template<typename Data>
void task(int size) {
    Map<Data> map(size);

    int count = 0;
    std::string key;

    std::cout << "[add]Enter count of records you want to store:";
    std::cin >> count;

    for (int i = 0; i < count; ++i) {
        std::cout << "Enter key:";
        std::cin.ignore();
        std::getline(std::cin, key);

        Data data;
        std::cout << "Enter data:";
        std::cin >> data;

        map.add(key, data);
    }


    std::cout << "[iterator] short for loop\n";
    for (auto i: map) {
        std::cout << '(';
        if (i)
            std::cout << i->key << ':' << i->data;
        std::cout << ") ";

    }
    std::cout << '\n';


    std::cout << "[find]Enter key of node you want to find:";
    std::cin.ignore();
    std::getline(std::cin, key);
    std::cout << "Key: " << key << " Value: " << map.find(key) << '\n';


    std::cout << "[del]Enter key of node you want to delete:";
    std::getline(std::cin, key);
    std::cout << "Deleted node:\nKey: " << key << " Value: " << map.del(key) << '\n';


    std::cout << "[iterator] for loop\n";
    for (auto i = map.begin(); i < map.end(); ++i) {
        std::cout << '(';
        if (i.get())
            std::cout << i.get()->key << ':' << i.get()->data;
        std::cout << ") ";
    }
    std::cout << '\n';


    std::cout << "[iterator] while loop\n";
    auto ptr = map.begin();
    while (ptr < map.end()) {
        Node<Data> *cur_node = ptr.get();

        std::cout << '(';
        if (cur_node)
            std::cout << cur_node->key << ':' << cur_node->data;
        std::cout << ") ";

        ptr.next();
    }


    std::cout << '\n';


}


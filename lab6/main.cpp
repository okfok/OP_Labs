#include <iostream>
#include "Map.h"
#include "Map.cpp"

int main() {
    Map<int> map(5);

    map.add("ifrst", 11);
    map.add("first", 15);


    std::cout << map.find("first") << '\n';

//    Test a(6);

    for (Node<int>* i : map) {
        if (i == nullptr)
            std::cout << "nullptr ";
        else
            std::cout << i->key() << ':' << i->value() << ' ';
    }
    std::cout << '\n';



    map.del("ifrst");
    map.add(new Node<int>("second", 20));

    for (auto i = map.begin(); i != map.end(); ++i){
        if (i.get() == nullptr)
            std::cout << "nullptr ";
        else
            std::cout << i.get()->key() << ':' << i.get()->value() << ' ';
    }

    std::cout << '\n';

    map.resize(20);

    auto ptr = map.begin();
    while (ptr != map.end()){
        auto cur_node = ptr.get();

        if (cur_node == nullptr)
            std::cout << "null ";
        else
            std::cout << cur_node->key() << ':' << cur_node->value() << ' ';

        ptr.next();
    }



    std::cout << '\n';



}

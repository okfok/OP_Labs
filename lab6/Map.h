#ifndef LAB6_MAP_H
#define LAB6_MAP_H

#include <iostream>


template<typename Data>
class Node {
public:
    std::string key;
    Data data;

    Node(std::string key, Data data) : key(std::move(key)), data(data) {};
};

template<typename Data>
class Map {
    int _size;
    int _count = 0;
    Node<Data> **_nodes;

    int find_pos(std::string key); // finding pos for find and delete funcs

public:
    // Constructors / Destructors
    explicit Map(int size = 50);

    Map(Map &);

    ~Map();
    // hash func

    int hash(const std::string &key);
    // data editing

    int size() { return _size; }

    void resize(int size);

    void clear();

    void add(std::string key, Data data);

    void add(Node<Data> *node);

    Data find(std::string key);

    Data del(std::string key);

    // Iterator
    class Iterator {
        Node<Data> **m_ptr;

    public:
        explicit Iterator(Node<Data> **ptr) : m_ptr(ptr) {} // constructor

        // cur element
        Node<Data> *get() { return *m_ptr; }

        // next element
        Iterator &operator++();

        Iterator &operator++(int);

        void next() { operator++(); }

        // operators overload
        Node<Data> *operator*() { return *m_ptr; }

        Node<Data> **operator->() { return m_ptr; }

        friend bool operator==(const Iterator &a, const Iterator &b) { return a.m_ptr == b.m_ptr; };

        friend bool operator!=(const Iterator &a, const Iterator &b) { return a.m_ptr != b.m_ptr; };

        friend bool operator<(const Iterator &a, const Iterator &b) { return a.m_ptr < b.m_ptr; }

        friend bool operator>(const Iterator &a, const Iterator &b) { return a.m_ptr > b.m_ptr; }

    };

    // funcs to get iterator
    Iterator begin() { return Iterator(&_nodes[0]); }

    Iterator end() { return Iterator(&_nodes[_size]); }


};


#endif //LAB6_MAP_H

#include "Map.h"

template<typename Data>
int Map<Data>::hash(const std::string &key) {
    int hash_code = 0;

    for (char chr: key) {
        hash_code += (int) chr;
    }

    return hash_code % _size;
}

template<typename Data>
Map<Data>::Map(int size): _size(size) {
    _nodes = new Node<Data> *[size];
    for (int i = 0; i < size; ++i) {
        _nodes[i] = nullptr;
    }
}

template<typename Data>
Map<Data>::~Map() {
    for (int i = 0; i < _size; ++i)
        if (_nodes[i])
            delete _nodes[i];

    delete[] _nodes;
}

template<typename Data>
Map<Data>::Map(Map &other): _size(other._size) {
    _nodes = new Node<Data> *[_size];
    for (int i = 0; i < _size; ++i) {
        _nodes[i] = other._nodes[i];
    }
}

template<typename Data>
void Map<Data>::clear() {
    for (int i = 0; i < _size; ++i) {
        if (_nodes[i]) {
            delete _nodes[i];
            _nodes[i] = nullptr;
        }
    }
    _count = 0;
}

template<typename Data>
void Map<Data>::add(std::string key, Data data) {
    if (_count + 1 >= _size) {
        throw; // TODO: exception
    }

    add(new Node(key, data));

}

template<typename Data>
void Map<Data>::add(Node<Data> *node) {
    if (_count + 1 >= _size) {
        throw; // TODO: exception
    }
    _count++;


    int hash_code = hash(node->key());

    if (!_nodes[hash_code])
        _nodes[hash_code] = node;
    else {
        for (int i = 0; i < _size; ++i) {
            hash_code++;
            if (hash_code == _size)
                hash_code -= _size;

            if (!_nodes[hash_code]) {
                _nodes[hash_code] = node;
                break;
            }

        }

    }

}

template<typename Data>
Data Map<Data>::find(std::string key) {
    int hash_code = hash(key);

    if (!_nodes[hash_code] || _nodes[hash_code]->key() == key)
        return _nodes[hash_code]->value();
    else {
        for (int i = 0; i < _size; ++i) {
            hash_code++;
            if (hash_code == _size)
                hash_code -= _size;

            if (_nodes[hash_code] && _nodes[hash_code]->key() == key) {
                return _nodes[hash_code]->value();
            }

        }
    }

    throw; // TODO: exception
}

template<typename Data>
Data Map<Data>::del(std::string key) {
    int hash_code = hash(key);

    if (!_nodes[hash_code] || _nodes[hash_code]->key() == key) {
        Data data = _nodes[hash_code]->value();
        delete _nodes[hash_code];
        _nodes[hash_code] = nullptr;
        _count--;
        return data;
    } else {
        for (int i = 0; i < _size; ++i) {
            hash_code++;
            if (hash_code == _size)
                hash_code -= _size;

            if (_nodes[hash_code] && _nodes[hash_code]->key() == key) {
                Data data = _nodes[hash_code]->value();
                delete _nodes[hash_code];
                _nodes[hash_code] = nullptr;
                return data;
            }

        }
    }

    throw; // TODO: exception
}

template<typename Data>
void Map<Data>::resize(int size) {
    int count = _count;
    auto **temp_array = new Node<Data> *[count];

    int cur = 0;
    for (int i = 0; i < _size; ++i) {
        if (_nodes[i]) {
            temp_array[cur] = _nodes[i];
            _nodes[i] = nullptr;
            cur++;
        }
    }


    delete[] _nodes;
    _size = size;
    _nodes = new Node<Data> *[_size];
    _count = 0;

    for (int i = 0; i < _size; ++i)
        _nodes[i] = nullptr;


    for (int i = 0; i < count; ++i) {
        add(temp_array[i]);
    }

    delete[] temp_array;

}


template<typename Data>
typename Map<Data>::Iterator Map<Data>::begin() {
//    for (int i = 0; i < _size; ++i) {
//        if (_nodes[i])
//            return Iterator(&_nodes[i]);
//    }

    return Iterator(&_nodes[0]);

}

template<typename Data>
typename Map<Data>::Iterator Map<Data>::end() {
//    for (int i = _size - 1; i >= 0; --i) {
//        if (_nodes[i]) {
//            return Iterator(&_nodes[i+1]);
//        }
//    }

    return Iterator(&_nodes[_size]);

}

template<typename Data>
typename Map<Data>::Iterator &Map<Data>::Iterator::operator++() {
    m_ptr++;
    return *this;
}

template<typename Data>
typename Map<Data>::Iterator &Map<Data>::Iterator::operator++(int) {
    Iterator tmp = (*this);
    m_ptr++;
    return tmp;
}


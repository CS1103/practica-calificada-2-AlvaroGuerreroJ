#ifndef GUARD_UTIL_HPP
#define GUARD_UTIL_HPP

#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>

#include "heap.hpp"

template<class T, class... Args>
void insert(heap<T>& hp, T first, Args... items)
{
    hp.insert(first);
}

template<class T>
void load_from(std::string const& file_name, heap<T>& hp)
{
    std::ifstream in(file_name);

    if (!in)
    {
        throw std::runtime_error("The file " + file_name + " doesn't exist");
    }

    T temp;
    while (in >> temp)
    {
        hp.insert(temp);
    }
}

#endif
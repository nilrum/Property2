//
// Created by user on 07.11.2021.
//

#ifndef PROPERTY_TYPES_H
#define PROPERTY_TYPES_H

#include <type_traits>
#include <string>
#include <vector>
#include <map>
#include <memory>

using TString = std::string;
using TVecString = std::vector<TString>;
using TVecDouble = std::vector<double>;


template<class T>
T &Single()
{
    static T o;
    return o;
}

template<class T>
T &Single(T&& value)
{
    static T o;
    o = std::move(value);
    return o;
}

#define STATIC_ARG(TYPE, NAME, ...) static TYPE& NAME(){ static TYPE value(__VA_ARGS__); return value; };
#define STATIC(TYPE, NAME) static TYPE& NAME(){ static TYPE value; return value; };
#define STR(VALUE) (VALUE).c_str()
#endif //PROPERTY_TYPES_H

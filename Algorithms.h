//
// Created by user on 07.11.2021.
//

#ifndef PROPERTYEXAMPLE_ALGORITHMS_H
#define PROPERTYEXAMPLE_ALGORITHMS_H

#include <algorithm>

template<typename T>
std::vector<T> Split(const T& value, typename T::value_type delim)
{
    size_t begin = 0;
    size_t count = 0;
    std::vector<T> rez;
    for(auto i : value)
    {
        if(i == delim)
        {
            rez.emplace_back(value, begin, count);
            begin = begin + count + 1;//+1 пропускаем сам символ разделитель
            count = 0;
        }
        else
            count++;
    }
    if(count) rez.emplace_back(value, begin, count);
    return rez;
}

template<typename T>
T Trim(const T& value)
{
    auto isspace = [](char ch) { return std::isspace(static_cast<unsigned char>(ch)); };
    auto begin = std::find_if_not(value.begin(), value.end(), isspace);
    auto end = value.end();
    if(begin != end)
        end = std::find_if_not(value.rbegin(), value.rend(), isspace).base();
    return TString(begin, end);
}

template<typename T>
std::vector<T> SplitTrim(const T& value, typename T::value_type delim)
{
    std::vector<T> rez = Split(value, delim);
    for(size_t i = 0; i < rez.size(); i++)
        rez[i] = Trim(rez[i]);
    return rez;
}

template<typename T>
T ToUpperCase(const T& value)
{
    T res = value;
    std::transform(value.begin(), value.end(), res.begin(), ::toupper);
    return res;
}

template<typename T>
T ToLowerCase(const T& value)
{
    T res = value;
    std::transform(value.begin(), value.end(), res.begin(), ::tolower);
    return res;
}

template<typename T>
T TrimBefore(const T& value, typename T::value_type delim, size_t maxCount = 0)
{
    if(value.empty()) return value;
    auto v = std::find(value.rbegin(), value.rend(), delim);
    if(v != value.rend())
        return T{".."} + T{value.begin() + (value.rend() - v - 1), value.end()};//-1 чтобы знак тоже входил
    if(maxCount == 0)
        return value;
    return T{value.begin() + value.size() - maxCount, value.end()};
}

#endif //PROPERTYEXAMPLE_ALGORITHMS_H

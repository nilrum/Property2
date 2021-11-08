//
// Created by user on 07.11.2021.
//

#ifndef PROPERTYEXAMPLE_ALGORITHMS_H
#define PROPERTYEXAMPLE_ALGORITHMS_H

#include <algorithm>
#include <cmath>

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

inline bool TryStrToInt(const TString& str, int& value)
{
    try{
        value = std::stoi(str);
        return true;
    }
    catch (...)
    {
        return false;
    }
}



struct TDoubleCheck{

    static bool Equal(const double& one, const double& two)
    {
        if(one > 0. && two > 0. || one < 0. && two < 0.)
            return std::fabs(one - two) < 0.00001;
        else
            return std::fabs(one + two) < 0.00001;
    }

    static bool Less(const double& one, const double& two)
    {
        if(one > 0. && two > 0. || one < 0. && two < 0.)
            return std::fabs(two) - std::fabs(one) > 0.00001;
        else
            return std::fabs(two + one) > 0.00001;
    }

    static bool Great(const double& one, const double& two)
    {
        return Less(two, one);
    }

    static bool LessEq(const double& one, const double& two)
    {
        return Less(one, two) || Equal(one, two);
    }

    static bool GreatEq(const double& one, const double& two)
    {
        return Great(one, two) || Equal(one, two);
    }

    struct TDoubleLess// : public std::binary_function<double, double, bool>
    {
        bool operator()(const double& x, const double& y) const
        { return Less(x, y); }
    };

    struct TDoubleLessEq// : public std::binary_function<double, double, bool>
    {
        bool operator()(const double& x, const double& y) const
        { return LessEq(x, y); }
    };

    struct TDoubleGreater// : public std::binary_function<double, double, bool>
    {
        bool operator()(const double& x, const double& y) const
        { return Great(x, y); }
    };
    struct TDoubleGreaterEq// : public std::binary_function<double, double, bool>
    {
        bool operator()(const double& x, const double& y) const
        { return GreatEq(x, y); }
    };
};


template<typename TVec>
bool RemoveVal(TVec& vec, const typename TVec::value_type& val)
{
    typename TVec::iterator it = std::find(vec.begin(), vec.end(), val);
    if(it == vec.end()) return false;
    vec.erase(it);
    return true;
}

template<typename TVec>
bool RemoveValFor(TVec& vec, const typename TVec::value_type& val)
{
    for(auto it = vec.begin(); it != vec.end(); it++)
        if(*it == val)
        {
            vec.erase(it);
            return true;
        }
    return false;
}



#endif //PROPERTYEXAMPLE_ALGORITHMS_H

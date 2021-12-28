//
// Created by user on 07.11.2021.
//

#ifndef PROPERTY2_RESULT_H
#define PROPERTY2_RESULT_H

#include "Types.h"
#include "EnumInfo.h"

class TResult{
public:
    TResult():info(&typeid(int)){};
    TResult(int value):code(value), info(&typeid(int)){}
    template <typename T> TResult(const T& value):code(static_cast<int>(value)), info(&typeid(T)){}
    TResult(const TResult& oth):code(oth.code), info(oth.info){};
    void operator =(const TResult& oth){ code = oth.code; info = oth.info; }

    enum TDefault{Cancel = -1, Ok = 0};

    inline bool IsNoError() const { return code == Ok; }
    inline bool IsError() const { return code != Ok; }
    inline bool IsCancel() const { return code == Cancel; }
    inline bool IsHardError() const { return IsError() && IsCancel() == false; }
    template<typename T>
    inline bool Is(const T& value) { return static_cast<T>(code) == value && *info == typeid(T); }

    inline int Code() const { return code; }
    inline const std::type_info& Info() const { return *info; };

    static bool Register(const std::type_info& info, int code, const TString& text)
    {
        Enums()[info.name()][code] = text;
        return true;
    }

    static TString TextError(const TResult& value)
    {
        //Сначало пробуем найти в зарегистрированных кодах ошибок
        TMapEnums::iterator it = Enums().find(value.Info().name());
        if(it != Enums().end())
        {
            TMapCodes &codes = it->second;
            TMapCodes::iterator code = codes.find(value.Code());
            if (code != codes.end()) return code->second;
        }
        //Если код не регистрировали, то найдем в перечислениях
        auto enInf = TEnumInfo::EnumInfo(value.Info());
        if(enInf.IsValid())
            return enInf.Name(value.Code());
        //Если это не перечисление, то просто вернем код
        return std::to_string(value.Code());
    }

    using TMapCodes = std::map<int, TString>;
    using TMapEnums = std::map<TString, TMapCodes>;

    static TMapEnums& Enums() { static TMapEnums enums; return enums; }
private:
    int code = Ok;
    const std::type_info* info;

};

#define REGISTER_CODE(TYPE, CODE, TEXT)\
    namespace{\
        const bool r##CODE = TResult::Register(typeid(TYPE), static_cast<int>(TYPE::CODE), TEXT);\
    }
#define REGISTER_CODES(TYPE, ...)       \
    namespace Namespace##TYPE{          \
        using TResType = TYPE;          \
        bool Fun##TYPE()                \
        {                               \
            __VA_ARGS__                 \
            return true;                \
        }                               \
        const bool r##TYPE = Fun##TYPE();\
    }
#define TEXT_CODE(CODE, TEXT)\
    TResult::Register(typeid(TResType), static_cast<int>(TResType::CODE), TEXT);

#endif //PROPERTY2_RESULT_H

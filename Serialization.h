//
// Created by user on 26.08.2019.
//

#ifndef TESTAPP_SERIALIZATION_H
#define TESTAPP_SERIALIZATION_H

#include "Result.h"
#include "PropertyClass.h"

class TSerializationInterf{
public:
    virtual TString SaveTo(TPropertyClass *value) const = 0;
    virtual TResult LoadFrom(const TString& text, TPropertyClass *value) const = 0;
    virtual TPtrPropertyClass CreateFrom(const TString& text) const = 0;

    virtual TResult SaveToFile(const TString& path, TPropertyClass *value) const = 0;
    virtual TResult LoadFromFile(const TString& path, TPropertyClass *value) const = 0;

    virtual TResult SavePropToFile(const TString& path, TPropertyClass *value, const TPropInfo &prop) const = 0;
    virtual TResult LoadPropFromFile(const TString& path, TPropertyClass *value, const TPropInfo& prop) const = 0;
};

enum class TSerializationKind{Xml = 0, Bin, Count};
enum class TSerializationResult{ Ok, FileNotOpen, FileNotSave, ErrorData};

class TSerialization : public TSerializationInterf{
public:
    TSerialization(TSerializationKind kind = TSerializationKind::Xml);

    TString SaveTo(TPropertyClass *value) const override;
    TResult LoadFrom(const TString& text, TPropertyClass *value) const override;

    TPtrPropertyClass CreateFrom(const TString& text) const override;

    TResult SaveToFile(const TString& path, TPropertyClass *value) const override;
    TResult LoadFromFile(const TString& path, TPropertyClass *value) const override;

    TResult SavePropToFile(const TString& path, TPropertyClass *value, const TPropInfo &prop) const override;
    TResult LoadPropFromFile(const TString& path, TPropertyClass *value, const TPropInfo& prop) const override;

    inline TResult SavePropToFileName(const TString& path, TPropertyClass *value, const TString& name) const;
    inline TResult LoadPropFromFileName(const TString& path, TPropertyClass *value, const TString& name) const;
protected:
    std::unique_ptr<TSerializationInterf> impl;
    static std::unique_ptr<TSerializationInterf> SerFromKind(TSerializationKind kind);
};

TResult TSerialization::SavePropToFileName(const TString &path, TPropertyClass *value, const TString &name) const
{
    const TPropInfo & prop = value->Manager().FindProperty(name);
    if(prop.IsValid() == false) return false;
    return SavePropToFile(path, value, prop);
}

TResult TSerialization::LoadPropFromFileName(const TString &path, TPropertyClass *value, const TString &name) const
{
    const TPropInfo & prop = value->Manager().FindProperty(name);
    if(prop.IsValid() == false) return false;
    return LoadPropFromFile(path, value, prop);
}


#endif //TESTAPP_SERIALIZATION_H

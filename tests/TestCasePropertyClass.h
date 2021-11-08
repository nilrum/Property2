//
// Created by user on 30.09.2019.
//

#ifndef TESTAPP_TESTCASEPROPERTYCLASS_H
#define TESTAPP_TESTCASEPROPERTYCLASS_H

#include "../Serialization.h"

class TPropertyInher2 : public TPropertyClass{
public:
    PROPERTIES(TPropertyInher2, TPropertyClass,
               PROPERTY(int, intVar2, IntVar2, SetIntVar2);
    )
    PROPERTY_FUN(int, intVar2, IntVar2, SetIntVar2);
private:
    int intVar2 = 0;
};

using TPtrPropertyInher2 = std::shared_ptr<TPropertyInher2>;

ENUM(TTestEnumInher, teOne, teTwo, teThree)

class TPropertyInher : public TPropertyClass{
public:
    int IntVar() const{ return intVar; };
    void SetIntVar(int value){ intVar = value; };
    TString StringVar() const{ return stringVar; }
    TPropertyClass& SetStringVar(const std::string& value){ stringVar = value; return *this; }

    TPtrPropertyClass ClassVar() const { return classVar; };
    void SetClassVar(const TPtrPropertyClass& value) { classVar = value; };


    PROPERTY_FUN(bool, boolVar, BoolVar, SetBoolVar);
    PROPERTY_FUN(double, doubleVar, DoubleVar, SetDoubleVar);
    PROPERTY_FUN(TTestEnumInher, enumVar, EnumVar, SetEnumVar);
    PROPERTY_FUN(TPtrPropertyInher2, classVar2, ClassVar2, SetClassVar2);
    PROPERTY_ARRAY_FUN_CHG(TPtrPropertyClass, children, CountChildren, Child, AddChild, DelChild);

    PROPERTIES(TPropertyInher, TPropertyClass,
           PROPERTY(int, intVar, IntVar, SetIntVar);
           PROPERTY(TString, stringVar, StringVar, SetStringVar);
           PROPERTY(bool, boolVar, BoolVar, SetBoolVar);
           PROPERTY(double, doubleVar, DoubleVar, SetDoubleVar);
           PROPERTY(TTestEnumInher, enumVar, EnumVar, SetEnumVar);
           PROPERTY(TPropertyClass, classVar, ClassVar, SetClassVar);
           PROPERTY(TPropertyInher2, classVar2, ClassVar2, SetClassVar2);
           PROPERTY_ARRAY(TPropertyClass, children, CountChildren, Child, AddChild, DelChild);
    )

private:
    int intVar = 0;
    TString stringVar;
    bool boolVar = false;
    double doubleVar = 0.;
    TTestEnumInher enumVar = teOne;
    TPtrPropertyClass classVar = std::make_shared<TPropertyClass>();
    std::shared_ptr<TPropertyInher2> classVar2 = std::make_shared<TPropertyInher2>();
    std::vector<TPtrPropertyClass> children;
};



using TPtrPropertyInher = std::shared_ptr<TPropertyInher>;


#endif //TESTAPP_TESTCASEPROPERTYCLASS_H

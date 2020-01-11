#pragma once

#include "Value.h"
#include "Integer.h"
#include "../Iterable.h"

class Array : public Value, public Iterable {
    ValueList values;
public:
    Array() = default;
    Array(ValueList& values) : values(values) { }
    void add(ptr<Value>& value);
    void addAll(ValueList& values);
    void remove(ptr<Value>& value);
    void clean();
    ptr<Integer> length();

    Type getType() override;
    std::string asString() override;
    long long int asInteger() override;
    double asDouble() override;
    bool asBoolean() override;

    ptr<Value> getValue() override;
    ptr<ValueList> getValues() override;
};
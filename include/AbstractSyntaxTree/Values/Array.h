#pragma once

#include "Value.h"
#include "Integer.h"
#include "../Iterable.h"

class Array : public Value, public Iterable {
    ValueList values;
    ptr<Array> thisArray = ptr<Array>(this);
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
    ptr<Array> asArray() override;

    ptr<Value> getValue() override;
    ptr<ValueList> getValues() override;
};
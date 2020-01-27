#pragma once

#include <utility>

#include "TypeDefinitions.h"

class Iterator {
    ptr<ValueList> values;
    long long int position = 0;
public:
    explicit Iterator(ptr<ValueList> values) : values(values) { }
    bool hasNext() {
        return position < values->size();
    }
    ptr<Value> next() {
        return (*values)[position++];
    }
};
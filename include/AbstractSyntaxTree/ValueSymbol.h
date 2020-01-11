#pragma once

#include "Values/Value.h"
#include "Symbol.h"

class ValueSymbol : public Symbol {
    ptr<Value> value;
public:
    ValueSymbol(const std::string &ident, bool constant, ptr<Value>& value)
        : Symbol(ident, constant, value -> getType()), value(value) { }

    ptr<Value> getValue() override {
        return value;
    }
};

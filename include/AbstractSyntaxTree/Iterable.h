#pragma once

#include "TypeDefinitions.h"

struct Iterable {
    virtual ptr<ValueList> getValues() = 0;
};
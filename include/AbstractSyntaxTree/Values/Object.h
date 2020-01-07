#pragma once

#include "Value.h"
#include "../Environment.h"

class Object : public Value {
    Environment members;
public:
    Environment& getEnvironment();
    Type getType() override;
};
#pragma once

#include "../Expression.h"
#include "../Member.h"
#include "../Type.h"

class Object;
class Array;

class Value : public Member {
public:
    virtual std::string asString();
    virtual long long int asInteger();
    virtual double asDouble();
    virtual bool asBoolean();
    virtual ptr<Object> asObject();
    virtual ptr<Array> asArray();

    virtual Type getType() = 0;
    virtual ~Value() { }
};
